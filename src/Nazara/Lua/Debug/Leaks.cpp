// Copyright (C) 2014 J�r�me Leclercq
// This file is part of the "Nazara Engine - Lua scripting module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Lua/Config.hpp>
#if NAZARA_LUA_MEMORYLEAKTRACKER || defined(NAZARA_DEBUG)
#include <Nazara/Core/Debug/MemoryLeakTracker.hpp>
#include <new>

void* operator new(std::size_t size)
{
	return NzMemoryManager::Allocate(size, false);
}

void* operator new[](std::size_t size)
{
	return NzMemoryManager::Allocate(size, true);
}

void operator delete(void* pointer) noexcept
{
	NzMemoryManager::Free(pointer, false);
}

void operator delete[](void* pointer) noexcept
{
	NzMemoryManager::Free(pointer, true);
}
#endif
