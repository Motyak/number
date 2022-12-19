set -o errexit
set -o errtrace
set -o nounset
set -o pipefail

trap handle_errexit ERR
trap handle_sigint SIGINT
trap handle_sigterm SIGTERM

function require {
    declare -r E_REQUIREMENT_NOT_MET=98

    read -a caller_output <<< "$(caller 0)"
    local lineno=${caller_output[0]}
    local func_name=${caller_output[1]}
    local filename=${caller_output[2]}

    # if unmet requirement passed rather than a condition to check
    [ $# -eq 1 ] && {
        local requirement=$1
        >&2 echo "Assertion \`$requirement\` failed in $func_name"
        >&2 echo "  -> $filename:$lineno"
        exit $E_REQUIREMENT_NOT_MET
    }

    local condition=$*
    $condition || {
        >&2 echo "Assertion \`$condition\` failed in $func_name"
        >&2 echo "  -> $filename:$lineno"
        exit $E_REQUIREMENT_NOT_MET
    }
}

function handle_errexit {
    local status=$?

    trap - ERR

    declare -r E_COMMAND_FAILING=99

    local cmd=$BASH_COMMAND
    local func_name=${FUNCNAME[1]}
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
