#!/usr/bin/env bash

set -o errexit
set -o errtrace
set -o nounset
set -o pipefail

trap handle_errexit ERR
trap handle_sigint SIGINT
trap handle_sigterm SIGTERM
trap clean_and_exit EXIT

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)

function require {
    declare -r E_REQUIREMENT_NOT_MET=98

    read -a caller_output <<< "$(caller 0)"
    local lineno=${caller_output[0]}
    local func_name=${caller_output[1]}
    local filename=${caller_output[2]}

    local condition=$*

    $condition || {
        >&2 echo "Assertion \`$condition\` failed in $func_name"
        >&2 echo "  -> $filename:$lineno"
        exit $E_REQUIREMENT_NOT_MET
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
    declare -r E_NO_SRC_FILE=10

    [ -f "$SRC_FILE" ] || {
        >&2 echo "$SRC_FILE cannot be found"
        exit $E_NO_SRC_FILE
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
    # mkdir bin # for testing purpose
    # echo $$; read # for testing purpose

    exec "$BINARY_FILE"
}

function handle_errexit {
    local status=$?

    trap - ERR

    declare -r E_COMMAND_FAILING=99

    local cmd=$BASH_COMMAND
    local func_name=${FUNCNAME[1]:-main context}
    local filename=${BASH_SOURCE[1]}
    local lineno=${BASH_LINENO[0]}

    >&2 echo "Command \`$cmd\` failed in $func_name with status $status"
    >&2 echo "  -> $filename:$lineno"

    exit $E_COMMAND_FAILING
}

function handle_sigint  {
    declare -r E_SIGINT_SENT=130 # 128 + 2 (SIGINT)

    trap - SIGINT

    >&2 echo # newline after ^C
    >&2 echo "SIGINT was sent"

    exit $E_SIGINT_SENT
}

function handle_sigterm {
    declare -r E_SIGTERM_SENT=143 # 128 + 15 (SIGTERM)

    trap - SIGTERM

    >&2 echo "SIGTERM was sent"

    exit $E_SIGTERM_SENT
}

function clean_and_exit {
    local exit_code=${?:-0}

    >&2 echo "Cleaning..."
    # clean tmp resources

    >&2 echo "Exiting with status $exit_code"
    exit $exit_code
}

assert_src_exists

{ binary_exists_and_is_up_to_date || build_binary; } && run_binary
