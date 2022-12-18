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

# import { require, handle_errexit, handle_sigint, handle_sigterm }
source "$SCRIPT_DIR/include/utils.sh"

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

function clean_and_exit {
    local exit_code=${?:-0}

    >&2 echo "Cleaning..."
    # clean tmp resources

    >&2 echo "Exiting with status $exit_code"
    exit $exit_code
}

assert_src_exists

{ binary_exists_and_is_up_to_date || build_binary; } && run_binary
