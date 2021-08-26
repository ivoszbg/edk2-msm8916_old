#!/bin/bash
# based on the instructions from edk2-platform
set -e
. build_common.sh
# not actually GCC5; it's GCC7 on Ubuntu 18.04.
GCC5_AARCH64_PREFIX=aarch64-linux-gnu- build -s -n 0 -a AARCH64 -t GCC5 -p MSM8916Pkg/HiKey960.dsc
gzip -c < workspace/Build/HiKey960/DEBUG_GCC5/FV/BL33_AP_UEFI.fd >uefi.img
cat DT/j5.dtb >>uefi.img
