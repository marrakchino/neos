#!/usr/bin/env bash
# 
# Execute this bash script to prepend the license header to 
# kernel source files (.c, .h, .s) not already embedding it.
#

set -u
HERE=$(cd "$(dirname "$0")" && pwd)
KERNEL_PATH="${HERE}/../"

for f in $(find ${KERNEL_PATH} -name "*.[h|c|s]"); do
    if ! grep -Fxq "${license}" "${f}"; then
        cp license_header "${f}_cpy"
        cat "${f}" >> "${f}_cpy"
        mv "${f}_cpy" "${f}"
    fi
done
