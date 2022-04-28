#pragma once

#include <cmath>

template<typename T>
class Vec2
{
public:
	Vec2() = default;
	Vec2(T x_in, T y_in)
		:
		x(x_in),
		y(y_in)
	{}
	template<typename S>
	explicit Vec2(const Vec2<S>& src)
		:
		x((T)src.x),
		y((T)src.y)
	{}
	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}
	Vec2 operator*(T rhs) const
	{
		return Vec2(x * rhs, y * rhs);
	}
	Vec2& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}
	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}
	Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}
	T GetLength() const
	{
		return (T)std::sqrt(GetLengthSq());
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	Vec2& Normalize()
	{
		return *this = GetNormalized();
	}
	Vec2 GetNormalized() const
	{
		const T len = GetLength();
		if (len != (T)0)
		{
			return *this * ((T)1 / len);
		}
		else {
			return *this;
		}
	}
	Vec2& Rotate(const T deg) {
		return *this = GetRotated(deg);
	}
	Vec2 GetRotated(const T deg) const {
		const T rad = float(M_PI) * deg / 180.0f;
		const T sinRad = std::sin(rad);
		const T cosRad = std::cos(rad);
		return { (x * cosRad) - (y * sinRad), (x * sinRad) + (y * cosRad) };
	}
	float GetTheta() const
	{
		return atan2(y, x);
	}
public:
	T x;
	T y;
};