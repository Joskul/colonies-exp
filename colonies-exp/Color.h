#pragma once
#include <SDL.h>

struct Color {
	Color() = default;
	Color(const Color& src) 
		:
		r(src.r),
		g(src.g),
		b(src.b),
		a(src.a)
	{
	}
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) 
		:
		r(r),
		g(g),
		b(b),
		a(a)
	{
	}
	Color operator* (const float& fac) const {
		return Color(Uint8(r * fac), Uint8(g * fac), Uint8(b * fac));
	}
	Color& operator*= (const float& fac) {
		return *this = *this * fac;
	}
	Uint8 r = 0, g = 0, b = 0;
	Uint8 a = 255;
};

namespace Colors {
	static const Color Red{ 255,0,0 };
	static const Color Green{ 0,255,0 };
	static const Color Blue{ 0,0,255 };
	static const Color Black{ 0,0,0 };
	static const Color White{ 255,255,255 };
};