#include "EFIApp.h"
#include "application.h"

// This is the actual entrypoint.
// Application entrypoint (must be set to 'efi_main' for gnu-efi crt0 compatibility)
EFI_STATUS efi_main(
	EFI_HANDLE ImageHandle, 
	EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN NumOutputProtocolHandles = 0;
	EFI_HANDLE* pOutputHandles;
	EFI_SIMPLE_TEXT_OUT_PROTOCOL* pScreenEfiOutputProtocol;
	UINTN KeyEvent;

	InitializeLib(ImageHandle, SystemTable);

	Status = gBS->LocateHandleBuffer(
		ByProtocol,
		&gEfiSimpleTextOutProtocolGuid,
		NULL,
		&NumOutputProtocolHandles,
		&pOutputHandles
	);

	// Some sanity check here.
	if (!EFI_ERROR(Status) && NumOutputProtocolHandles >= 3)
	{
		// Take the last handle as ConOut, don't know how I know this.
		// It is painful...and it is 5am now
		Status = gBS->HandleProtocol(
			pOutputHandles[NumOutputProtocolHandles - 1],
			&gEfiSimpleTextOutProtocolGuid,
			(VOID**)&pScreenEfiOutputProtocol
		);

		// Hack: force use the screen output for ConOut
		if (!EFI_ERROR(Status))
		{
			gST->ConOut = pScreenEfiOutputProtocol;
			gST->ConsoleOutHandle = pOutputHandles[NumOutputProtocolHandles - 1];
			// TODO: Maybe set ConOut device later...?
			pScreenEfiOutputProtocol->OutputString(pScreenEfiOutputProtocol, L"At this moment you should have seen something on the screen...\n");
		}
	}

	for (UINTN i = 0; i < 10; i++)
	{
		Print(L"Fuck %H NVIDIA %N\n");
	}

	// Let people inspect the result. Wait a keystoke
	Print(L"%EPress any key to exit.%N\n");
	gST->ConIn->Reset(gST->ConIn, FALSE);
	gST->BootServices->WaitForEvent(1, &gST->ConIn->WaitForKey, &KeyEvent);

	return Status;
}
