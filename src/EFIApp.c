#include "EFIApp.h"
#include "application.h"

// This is the actual entrypoint.
// Application entrypoint (must be set to 'efi_main' for gnu-efi crt0 compatibility)
EFI_STATUS efi_main(
	EFI_HANDLE ImageHandle, 
	EFI_SYSTEM_TABLE *SystemTable
)
{
	return EFI_SUCCESS;
}
