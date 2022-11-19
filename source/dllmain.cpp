#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <thread>
#include <cstdint>

#include "headers/hooks.h"

// setup func
void Setup(const HMODULE instance)
{
	try
	{
		gui::Setup();
		hooks::Setup();
	}
	catch (const std::exception& error)
	{
		MessageBeep(MB_ICONERROR);
		MessageBox(
			0,
			error.what(),
			"?",
			MB_OK | MB_ICONEXCLAMATION
		);

	}

	//FreeLibraryAndExitThread(instance, 0);
}

// entry point
bool WINAPI DllMain(
	const HMODULE instance,
	const std::uintptr_t reason,
	const void* reserved
)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		const auto thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup),
			instance,
			0,
			nullptr
		);
		if (thread)
			CloseHandle(thread);
	}

	return TRUE;
}