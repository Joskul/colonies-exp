#pragma once
#include <vector>
#include <algorithm>
#include "Vec2.h"
#include "Entity.h"
#include "Agent.h"
#include "Graphics.h"

class World {
public:
	World();

	void Update(float deltaTime);

	void Draw(Graphics& gfx);
private:
	void spawnPheromone(Pheromone::Type setType, Vec2<float> setPos);

	const int antCount = 200;
	const float antSpeed = 15.0f;
	const float wanderRate = 0.15f;
	const int phSpawnRate = 80;
	const float dissipationRate = 0.95f;
	const float depletionThreshold = 0.01f;
	int frame = 0;
	std::vector<Pheromone> pheromones;
	std::vector<Agent> ants;
	std::vector<Food> foods;

	Vec2<float> colonyPos{ 640,360 };
	Colony home{colonyPos, 12.0f};
};