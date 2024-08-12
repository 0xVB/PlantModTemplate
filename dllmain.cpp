#include <Windows.h>

#include "Functions.h"
#include "Original.h"

void __stdcall Hook(DWORD Address, void* Function)
{
	DWORD OldProt;
	VirtualProtect((LPVOID)Address, 5, PAGE_EXECUTE_READWRITE, &OldProt);

	DWORD Offset = (DWORD)Function - Address - 5;// Relative offset
	*(BYTE*)Address = 0xE9;// Set to jmp
	*(DWORD*)(Address + 1) = Offset;

	DWORD Temp;
	VirtualProtect((LPVOID)Address, 5, OldProt, &Temp);
}

void __declspec(naked) PLANTADDED()
{
	__asm
	{
		pop ebx
		pop ecx
		push eax
		push eax
		call PlantAdded
		pop eax
		ret 0x10
	}
}

void __declspec(naked) PLANTUPDATING()
{
	__asm
	{
		push eax
		call PlantUpdating
		ret
	}
}

void __declspec(naked) ZOMBIEEATING()
{
	__asm
	{
		pop eax// Return addr
		pop edx// Zombie*
		push ecx// Plant*
		push edx// Zombie*
		push eax// Return addr
		jmp ZombieEating
	}
}

CONST DWORD _F0 = 0x463E49;
__declspec(naked) void __stdcall Original::PlantUpdate(Plant*)
{
	__asm
	{
		pop ecx// Return addr
		pop eax// Plant*
		push ecx// Return addr

		push ebx
		mov ebx, eax
		mov dl, byte ptr [ebx + 0x144]
		jmp _F0
	}
}

CONST DWORD _F1 = 0x465A96;
__declspec(naked) void __stdcall Original::PlantDraw(Plant*, Sexy::Graphics*)
{
	__asm
	{
		push ebp
		mov ebp, esp
		and esp, 0xFFFFFFF8
		jmp _F1
	}
}

CONST DWORD _F2 = 0x466E08;
__declspec(naked) void __stdcall Original::PlantShoot(Plant*, Zombie*, int, bool)
{
	__asm
	{
		sub esp, 0x1C
		push ebx
		mov ebx, [esp + 0x30]
		jmp _F2
	}
}

CONST DWORD _F3 = 0x52FB47;
__declspec(naked) void __stdcall Original::BitePlant(Zombie*, Plant*)
{
	__asm
	{
		pop edx // Return addr
		pop eax // Zombie*
		pop ecx // Plant*
		push eax // Zombie*
		push edx // Return addr

		push -1
		push 0x64F598
		jmp _F3
	}
}

CONST DWORD _F4 = 0x452CB7;
__declspec(naked) void ONLOAD()
{
	__asm
	{
		push ecx
		push ecx
		call GameLoaded
		pop ecx
		
		push -1
		push 0x64F348
		jmp _F4
	}
}

__declspec(naked) void ONNEWZOMB()
{
	__asm
	{
		push eax
		push eax
		call ZombieAdded
		pop eax
		ret 0x8
	}
}

__declspec(naked) void ZOMBUPDATE()
{
	__asm
	{
		push eax
		call ZombieUpdating
		ret
	}
}

__declspec(naked) void ZOMBDRAW()
{
	__asm
	{
		push [esp + 0x4]
		push ebx
		call ZombieDrawing
		ret 0x4
	}
}

__declspec(naked) void NEWPROJ()
{
	__asm
	{
		push eax
		push eax
		call ProjectileAdded
		pop eax
		ret 0x14
	}
}

__declspec(naked) void PROJUPD()
{
	__asm
	{
		push eax
		call ProjectileUpdating
		ret
	}
}

__declspec(naked) void PROJCOLL()
{
	__asm
	{
		push eax
		push ecx
		call ProjectileColliding
		ret
	}
}

CONST DWORD _F5 = 0x46E006;
__declspec(naked) void __stdcall Original::ProjectileCollide(Projectile*, Zombie*)
{
	__asm
	{
		pop edx// Ret
		pop ecx
		pop eax
		push edx
		sub esp, 0x14
		push ebx
		push ebp
		push esi
		jmp _F5
	}
}

CONST DWORD _F6 = 0x46E546;
__declspec(naked) void __stdcall Original::ProjectileDraw(Projectile*, Sexy::Graphics*)
{
	__asm
	{
		push ebp
		mov ebp, esp
		and esp, -0x8
		jmp _F6
	}
}

CONST DWORD _F7 = 0x46E468;
__declspec(naked) void __stdcall Original::ProjectileUpdate(Projectile*)
{
	__asm
	{
		pop edx// Ret
		pop eax// this*
		push edx
		push ecx
		push esi
		mov esi, eax
		add [esi + 0x60], 01
		jmp _F7
	}
}

CONST DWORD _F8 = 0x52E2E6;
__declspec(naked) void __stdcall Original::ZombieDraw(Zombie*, Sexy::Graphics*)
{
	__asm
	{
		push ebx
		push [esp + 0xC]
		mov ebx, [esp + 0xC]
		mov eax, fs: [00000000]
		call _F8
		pop ebx
		ret 0x8
	}
}

CONST DWORD _F9 = 0x52AE66;
__declspec(naked) void __stdcall Original::ZombieUpdate(Zombie*)
{
	__asm
	{
		pop edx// Ret
		pop eax// this*
		push edx

		push ebp
		mov ebp, esp
		and esp, -0x8
		jmp _F9
	}
}

BOOL APIENTRY DllMain
(
    HMODULE ModHandle,
    DWORD CallReason,
    LPVOID Reserved
)
{
    if (CallReason != DLL_PROCESS_ATTACH) return TRUE;
	
	// Hooks
	Hook(0x452CB0, ONLOAD);

	// Plant
	Hook(0x40D19B, PLANTADDED);
	Hook(0x463E40, PLANTUPDATING);
	Hook(0x466E00, PlantShooting);
	Hook(0x465A90, PlantDrawing);

	// Zombie
	Hook(0x52FB40, ZOMBIEEATING);
	Hook(0x52AE60, ZOMBUPDATE);
	Hook(0x40DE90, ONNEWZOMB);
	Hook(0x52E2E0, ZOMBDRAW);

	// Projectile
	Hook(0x40D653, NEWPROJ);
	Hook(0x46E460, PROJUPD);
	Hook(0x46E000, PROJCOLL);
	Hook(0x46E540, ProjectileDrawing);

	
	AllocConsole();
	FILE* O = nullptr;
	freopen_s(&O, "CONOUT$", "w", stdout);
	SetConsoleTitleA("LunaIO");

    return TRUE;
}