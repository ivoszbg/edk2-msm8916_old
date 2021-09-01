/** @file
*
*  Copyright (c) 2018, Linaro Ltd. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include <Guid/EventGroup.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootManagerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Protocol/Cpu.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/EmbeddedGpio.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/PlatformBootManager.h>
#include <Protocol/PlatformVirtualKeyboard.h>

#include "../../Include/MSM8916Dxe/MSM8916Dxe.h"

EFI_CPU_ARCH_PROTOCOL     *gCpu;

VOID
InitPeripherals (
  IN VOID
  )
{
  EFI_STATUS            Status;
  // https://lists.01.org/pipermail/edk2-devel/2017-August/013417.html
  Status = gCpu->SetMemoryAttributes (gCpu, 0xa1a10000, 0x200000,
                  EFI_MEMORY_UC | EFI_MEMORY_XP);
  ASSERT_EFI_ERROR (Status);
  Status = gCpu->SetMemoryAttributes (gCpu, 0x9d400000, 0x2400000,
                  EFI_MEMORY_WC | EFI_MEMORY_XP);
  ASSERT_EFI_ERROR (Status);
	// set the screen
	//for (UINT64 addr = 0x8e000000ull; addr < 0x8e000000ull + (720 * 1280 * 3); addr += 3) {
	//	MmioWrite32(addr, 0xFF0320); // green
	//}
	// reboot
	//MmioWrite32(0x004ab000, 0);
	// spin forever
	//while (1) {}
}

/**
  Notification function of the event defined as belonging to the
  EFI_END_OF_DXE_EVENT_GROUP_GUID event group that was created in
  the entry point of the driver.
  This function is called when an event belonging to the
  EFI_END_OF_DXE_EVENT_GROUP_GUID event group is signalled. Such an
  event is signalled once at the end of the dispatching of all
  drivers (end of the so called DXE phase).
  @param[in]  Event    Event declared in the entry point of the driver whose
                       notification function is being invoked.
  @param[in]  Context  NULL
**/
STATIC
VOID
OnEndOfDxe (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
}

EFI_STATUS
EFIAPI
MSM8916EntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS            Status;
  EFI_EVENT             EndOfDxeEvent;

  Status = gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **)&gCpu);
  ASSERT_EFI_ERROR(Status);

  InitPeripherals ();

  //
  // Create an event belonging to the "gEfiEndOfDxeEventGroupGuid" group.
  // The "OnEndOfDxe()" function is declared as the call back function.
  // It will be called at the end of the DXE phase when an event of the
  // same group is signalled to inform about the end of the DXE phase.
  // Install the INSTALL_FDT_PROTOCOL protocol.
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  OnEndOfDxe,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  return Status;
}
