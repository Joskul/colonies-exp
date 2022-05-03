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
	virtual void Draw(Graphics& gfx) const
	{
		int x = (int)pos.x;
		int y = (int)pos.y;
		gfx.putPixel(x, y, c);
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
	Pheromone(Type setType, float setDissipationRate, float setDepletionThreshold, Vec2<float> setPos)
		:
		type(setType),
		dissipationRate(setDissipationRate),
		depletionThreshold(setDepletionThreshold),
		Entity(setPos)
	{
		switch (type) {
		case Type::toHome:
			c = {64,255,192};
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
	Type getType() const {
		return type;
	}

	void Draw(Graphics& gfx) const
	{
		int x = (int)pos.x;
		int y = (int)pos.y;
		gfx.putPixel(x - 1, y - 1, c);
		gfx.putPixel(x, y - 1, c);
		gfx.putPixel(x - 1, y, c);
		gfx.putPixel(x, y, c);
	}

	// linear depletion -- sometimes flashes when the trail ends
	//void Update(float deltaTime) {
	//	intensity -= dissipationRate * deltaTime;
	//	//c = baseColor * (1.0f / (1.0f - depletionThreshold)) * (intensity - depletionThreshold); // smoothed calculation
	//	c = baseColor * intensity; // unmapped calculation ++ Recommended since the threshold isn't required
	//}

	// reciprocal depletion -- halves the performance
	void Update(float deltaTime) {
		timeCounter += deltaTime;
		intensity = std::pow(dissipationRate, timeCounter);
		//c = baseColor * (1.0f / (1.0f - depletionThreshold)) * (intensity - depletionThreshold); // smoothed calculation -- output color seems kinda weird
		c = baseColor * intensity; // unmapped calculation
	}

	float getIntensity() const {
		return intensity;
	}
	bool isDepleted() const {
		return intensity <= depletionThreshold;
	}
private:
	float intensity = 1.0f;
	float dissipationRate;
	float depletionThreshold;
	float timeCounter = 0.0f;
	Type type;

	Color baseColor;
};

class Colony : public Entity {
public:
	Colony(Vec2<float> setPos, float radius)
		:
		Entity(setPos),
		radius(radius)
	{
		c = Colors::White;
	}
	void Draw(Graphics& gfx) {
		gfx.drawCircle((int)pos.x, (int)pos.y, radius, c);
	}
	float getRadius() const {
		return radius;
	}
private:
	const float radius;
};

class Food : public Entity {
public:
	Food(Vec2<float> setPos) 
		:
		Entity(setPos)
	{
		c = Colors::Green;
	}
};