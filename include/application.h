#pragma once

// Sup types
#include "suptypes.h"

// Bootloader
#include "bl.h"
#include "context.h"

// Status enum
#include "ntstatus.h"

// Exports
EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);
