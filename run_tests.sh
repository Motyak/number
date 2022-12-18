#!/usr/bin/env bash

set -o errexit
set -o errtrace
set -o nounset
set -o pipefail

trap handle_errexit ERR
trap clean_and_exit SIGINT SIGTERM EXIT

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)

function require {
    declare -r E_REQUIREMENT_NOT_MET=10

    read -a caller_output <<< "$(caller 0)"
    local lineno=${caller_output[0]}
    local func_name=${caller_output[1]}
    local filename=${caller_output[2]}

    local condition=$*

    $condition || {
        >&2 echo "Assertion \`$condition\` failed in $func_name"
        >&2 echo "  -> $filename:$lineno"
        clean_and_exit $E_REQUIREMENT_NOT_MET
    }
}

function abspath {
    local relpath="$1"
    require [ "${relpath:0:2}" == "./" ]

    echo -n "${SCRIPT_DIR}/${relpath:2}"
}

declare -A path=(
    [BINARY_FILE]="./bin/test"
    [SRC_FILE]="./src/test.cpp"
    [INCLUDE_DIR]="./include"
    [LIBS]="./lib/catch.o"
)
for key in "${!path[@]}"; do declare -r "$key"="$(abspath "${path[$key]}")"; done
unset path

function assert_src_exists {
    declare -r E_NO_SRC_FILE=20

    [ -f "$SRC_FILE" ] || {
        >&2 echo "$SRC_FILE cannot be found"
        clean_and_exit $E_NO_SRC_FILE
    }
}

function binary_exists_and_is_up_to_date {
    require [ -f "$SRC_FILE" ]

    [ -f "$BINARY_FILE" ] && [ "$BINARY_FILE" -nt "$SRC_FILE" ]
}

function build_binary {
    require [ -f "$SRC_FILE" ]
    require [ -d "$INCLUDE_DIR/" ]
    for lib in $LIBS; do require [ -f "$lib" ]; done
    
    g++ "$LIBS" "$SRC_FILE" -I "$INCLUDE_DIR/" -o "$BINARY_FILE"
}

function run_binary {
    require [ -f "$BINARY_FILE" ]
    mkdir bin # for testing purpose

    exec "$BINARY_FILE"
}

function handle_errexit {
    declare -r E_COMMAND_FAILING=11

    local status=$?
    local cmd=$BASH_COMMAND
    local func_name=${FUNCNAME[1]:-main context}
    local filename=${BASH_SOURCE[1]}
    local lineno=${BASH_LINENO[0]}

    trap - ERR

    >&2 echo "Command \`$cmd\` failed in $func_name with status $status"
    >&2 echo "  -> $filename:$lineno"

    clean_and_exit $E_COMMAND_FAILING
}


function clean_and_exit {
    local exit_code=${1:-0}

    trap - SIGINT SIGTERM EXIT

    # clean tmp resources, ..

    exit $exit_code
}

assert_src_exists

{ binary_exists_and_is_up_to_date || build_binary; } && run_binary
