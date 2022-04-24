#pragma once
#include "Vec2.h"
#include "Color.h"
#include "Graphics.h"
#include <vector>

class Entity {
public:
	Vec2<float> getPos() {
		return pos;
	}
	Vec2<float> getPos() const {
		return pos;
	}
	void Draw(Graphics& gfx) {
		gfx.putPixel(pos.x - 1, pos.y - 1, c);
		gfx.putPixel(pos.x, pos.y - 1, c);
		gfx.putPixel(pos.x - 1, pos.y, c);
		gfx.putPixel(pos.x, pos.y, c);
	}
protected:
	Entity(Vec2<float> setPos)
		:
		pos(setPos)
	{
	}
	Color c;
	Vec2<float> pos;
};

class Pheromone : public Entity {
public:
	enum class Type {
		toHome,
		toFood,
		noFood
	};
public:
	Pheromone(Type setType, float setDissipationRate, Vec2<float> setPos)
		:
		type(setType),
		dissipationRate(setDissipationRate),
		Entity(setPos)
	{
		switch (type) {
		case Type::toHome:
			c = {255,255,192};
			break;
		case Type::toFood:
			c = { 255,128,64 };
			break;
		case Type::noFood:
			c = Colors::Red;
			break;
		}
		baseColor = c;
	}
	Type getType() {
		return type;
	}
	void Update() {
		intensity *= dissipationRate;
		c = baseColor * (1 / (1 - depletionThreshold)) * (intensity - depletionThreshold);
		//c = baseColor * intensity;
	}
	float getIntensity() const {
		return intensity;
	}
	bool isDepleted() const {
		return intensity <= depletionThreshold;
	}
private:
	float intensity = 1.0f;
	float depletionThreshold = 0.1f;
	float dissipationRate;
	Type type;

	Color baseColor;
};

class Colony : public Entity {
public:
	Colony(Vec2<float> setPos)
		:
		Entity(setPos)
	{
		c = Colors::Blue;
	}
private:
};

class Food : public Entity {
	Food(Vec2<float> setPos) 
		:
		Entity(setPos)
	{
		c = Colors::Green;
	}
};