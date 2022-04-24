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
		return Color(r * fac, g * fac, b * fac);
	}
	Color& operator*= (const float& fac) {
		return *this = *this * fac;
	}
	Uint8 r, g, b;
	Uint8 a = 255;
};

namespace Colors {
	static const Color Red{ 255,0,0 };
	static const Color Green{ 0,255,0 };
	static const Color Blue{ 0,0,255 };
	static const Color Black{ 0,0,0 };
	static const Color White{ 255,255,255 };
};