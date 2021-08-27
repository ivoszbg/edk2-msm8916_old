#!/bin/bash
# based on the instructions from edk2-platform
set -e
. build_common.sh
# not actually GCC5; it's GCC7 on Ubuntu 18.04.
GCC5_AARCH64_PREFIX=aarch64-linux-gnu- build -s -n 0 -a AARCH64 -t GCC5 -p MSM8916Pkg/Devices/SM-J500F.dsc
gzip -c < workspace/Build/MSM8916/DEBUG_GCC5/FV/MSM8916_UEFI.fd >uefi.img
cat DT/j5.dtb >>uefi.img
