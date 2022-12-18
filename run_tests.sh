#!/usr/bin/env bash

# set -o errexit
# set -o errtrace
# set -o nounset
# set -o pipefail

# trap handle_err ERR
# trap cleanup SIGINT SIGTERM EXIT


SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)



function require {
    declare -r E_MISSING_ARGS=11
    declare -r E_ASSERT_FAILED=12

    [ $# -ge 2 ] || exit $E_MISSING_ARGS

    read -a caller_output <<< "$(caller 0)"
    lineno=${caller_output[0]}
    func_name=${caller_output[1]}
    filename=${caller_output[2]}

    local condition=$*

    $condition || {
        >&2 echo "Assertion \`$condition\` failed in $func_name"
        >&2 echo "  -> $filename:$lineno"
        exit $E_ASSERT_FAILED
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
    [ -f "$SRC_FILE" ] || {
        >&2 echo "$SRC_FILE cannot be found"
        exit 1
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

    "$BINARY_FILE"
}

# function cleanup {
#     trap - SIGINT SIGTERM EXIT
#     echo "cleanup"
# }

# function handle_err {
#     trap - ERR
#     echo "handle_err"
# }

# trap 'echo "ERR trap called in ${FUNCNAME-main context}."' ERR

assert_src_exists

{ binary_exists_and_is_up_to_date || build_binary; } \
&& run_binary
