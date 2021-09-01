#
#  Copyright (c) 2018, Linaro Limited. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################

[Defines]
  PLATFORM_NAME                  = MSM8916
  PLATFORM_GUID                  = bd1a557e-4423-466a-a462-38439588fd37
  PLATFORM_VERSION               = 0.2
  DSC_SPECIFICATION              = 0x00010019
  OUTPUT_DIRECTORY               = Build/$(PLATFORM_NAME)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = MSM8916Pkg/MSM8916.fdf

  DEFINE CONFIG_NO_DEBUGLIB      = TRUE

!include MSM8916Pkg/MSM8916.dsc

[PcdsFixedAtBuild.common]
  # System Memory (1.5GB)
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x60000000
  
  gMSM8916TokenSpaceGuid.PcdMipiFrameBufferAddress|0x8e000000
  gMSM8916TokenSpaceGuid.PcdMipiFrameBufferWidth|720
  gMSM8916TokenSpaceGuid.PcdMipiFrameBufferHeight|1280
