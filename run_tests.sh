#!/usr/bin/env bash

trap clean_and_exit EXIT
function clean_and_exit {
    local exit_code=$?

    >&2 echo "Cleaning..."
    # clean tmp resources

    >&2 echo "Exiting with status $exit_code"
    exit $exit_code
}

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)

# import { require, handle_errexit, handle_sigint, handle_sigterm }
source "$SCRIPT_DIR/include/utils.sh"

function abspath {
    local relpath="$1"
    { [ "${relpath:0:2}" == "./" ] || [ "${relpath:0:3}" == "../" ]; } || {
        require "a valid relative path"
    }

    # intermediate var because "echo" command doesn't fail when subshell fails
    ret="$(realpath "${SCRIPT_DIR}/$relpath")"
    echo -n "$ret"
}

declare -A path=(
    [BINARY_FILE]="../bin/test"
    [SRC_FILE]="./src/test.cpp"
    [INCLUDE_DIR]="./include"
    [LIBS]="./lib/catch.o"
)
for key in "${!path[@]}"; do
    # intermediate var because "declare" command doesn't fail when subshell fails
    ret="$(abspath "${path[$key]}")"
    declare -r "$key"="$ret"
done
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

    [ -f "$BINARY_FILE" ]
    [ "$BINARY_FILE" -nt "$SRC_FILE" ]
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

assert_src_exists

binary_exists_and_is_up_to_date || build_binary

run_binary
