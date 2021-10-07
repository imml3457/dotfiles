#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd ${DIR}

for plug in *.c; do
    echo "compiling $(dirname ${plug})/$(basename ${plug} ".c").so"
    gcc -o $(dirname ${plug})/$(basename ${plug} ".c").so ${plug} -shared -fPIC -lyed || exit 1
done
