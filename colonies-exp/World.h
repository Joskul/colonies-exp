#pragma once
#include <vector>
#include "Vec2.h"
#include "Entity.h"
#include "Agent.h"
#include "Graphics.h"

class World {
public:
	World(int antCount)
		:
		antCount(antCount)
	{
		for (int i = 0; i < antCount; i++) {
			ants.emplace_back(colonyPos, antSpeed, wanderRate);
		}
		// foods.emplace_back(Vec2<float>(800, 800));
	}

	void Update(float deltaTime) {
		int i = 0;
		for (auto& ant : ants) {
			ant.Update(deltaTime, pheromones, foods);
			if ((frame + i) % phSpawnRate == 0) {
				spawnPheromone(Pheromone::Type::toHome, ant.getPos());
			}
			i++;
		}
		for (std::vector<Pheromone>::iterator ph = pheromones.begin(); ph != pheromones.end();) {
			if (ph->isDepleted()) {
				ph = pheromones.erase(ph);
			}
			else {
				ph->Update(deltaTime);
				ph++;
			}
		}
		frame++;
	}

	void Draw(Graphics& gfx) {
		for (auto ph : pheromones) {
			ph.Draw(gfx);
		}
		for (auto ant : ants) {
			ant.Draw(gfx);
		}
		for (auto food : foods) {
			food.Draw(gfx);
		}
	}

	std::vector<Agent> getAnts() const {
		return ants;
	}

	std::vector<Pheromone> getPheromones() const {
		return pheromones;
	}
private:
	void spawnPheromone(Pheromone::Type setType, Vec2<float> setPos) {
		pheromones.emplace_back(setType, dissipationRate, depletionThreshold, setPos);
	}

	const int antCount;
	const float antSpeed = 15.0f;
	const float wanderRate = 0.15f;
	const int phSpawnRate = 12;
	const float dissipationRate = 0.7f;
	const float depletionThreshold = 0.2f;
	int frame = 0;
	std::vector<Pheromone> pheromones;
	std::vector<Agent> ants;
	std::vector<Food> foods;

	Vec2<float> colonyPos{ 640,360 };
};