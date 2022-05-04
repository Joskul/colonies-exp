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

	void Update(const float deltaTime, const std::vector<Pheromone>& pheromones, const std::vector<Food>& foods, const Colony& colony);
	void Draw(Graphics& gfx) const;
	Vec2<float> getPos() const;

	bool isHoldingFood() const;
	void giveFood();
	void takeFood();
private:
	Vec2<float> pos{ 0.0f, 0.0f };
	Vec2<float> desiredDirection{ 0.0f,0.0f };
	const float speed;
	const float wanderRate = 0.0f;
	const float detectionRange = 25.0f;
	const float foodInfluence = 10.0f;
	const float phInfluence = 0.0005f;
	const float fov = 60.0f;
	bool holdingFood = false;

	Color c = Colors::Red;
	std::minstd_rand rng; // ~1.5x the performance of mt19937
	//std::mt19937 rng;
	std::uniform_real_distribution<float> randDist;
};