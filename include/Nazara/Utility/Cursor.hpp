// Copyright (C) 2012 J�r�me Leclercq
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_CURSOR_HPP
#define NAZARA_CURSOR_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Math/Vector2.hpp>

class NzCursorImpl;
class NzImage;
class NzWindowImpl;

class NAZARA_API NzCursor
{
	friend class NzWindowImpl;

	public:
		NzCursor();
		~NzCursor();

		bool Create(const NzImage& cursor, int hotSpotX = 0, int hotSpotY = 0);
		bool Create(const NzImage& cursor, const NzVector2i& hotSpot);
		void Destroy();

		bool IsValid() const;

	private:
		NzCursorImpl* m_impl;
};

#endif // NAZARA_CURSOR_HPP