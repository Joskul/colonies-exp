#pragma once
#include "Vec2.h"
#include "Entity.h"
#include "Graphics.h"
#include "Color.h"
#include <vector>
#include <random>

class Agent {
public:
	Agent() = default;
	Agent(Vec2<float> setPos, float speedIn, float wanderRateIn);
	Agent(Agent& src);
	Agent(Agent&& src) noexcept;

	void Update(const std::vector<Pheromone>& ph, const std::vector<Food>& fd);
	void Draw(Graphics& gfx);
	Vec2<float> getPos() const;
private:
	Vec2<float> pos{ 0.0f, 0.0f };
	Vec2<float> desiredDirection{ 0.0f,0.0f };
	float speed;
	float wanderRate = 0.0f;
	float detectionRange = 5.0f;
	bool holdingFood = false;

	Color c = Colors::White;
	std::minstd_rand rng;
	std::uniform_real_distribution<float> randDist;
};