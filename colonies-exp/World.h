#pragma once
#include <vector>
#include "Vec2.h"
#include "Entity.h"
#include "Agent.h"
#include "Graphics.h"

class World {
public:
	World(int antCount, float antSpeed, float wanderRate, int phSpawnRate, float dissipationRate)
		:
		antCount(antCount),
		antSpeed(antSpeed),
		wanderRate(wanderRate),
		phSpawnRate(phSpawnRate),
		dissipationRate(dissipationRate)
	{
		for (int i = 0; i < antCount; i++) {
			ants.emplace_back(colonyPos, antSpeed, wanderRate);
		}
		// foods.emplace_back(Vec2<float>(800, 800));
	}

	void Update() {
		for (auto& ant : ants) {
			ant.Update(pheromones, foods);
			if (frame == phSpawnRate) {
				spawnPheromone(Pheromone::Type::toHome, ant.getPos());
			}
		}
		for (std::vector<Pheromone>::iterator ph = pheromones.begin(); ph != pheromones.end();) {
			if (ph->isDepleted()) {
				ph = pheromones.erase(ph);
			}
			else {
				ph->Update();
				ph++;
			}
		}
		frame >= phSpawnRate ? frame = 0 : frame++;
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
		pheromones.emplace_back(setType, dissipationRate, setPos);
	}

	const int antCount;
	const float antSpeed;
	const float wanderRate;
	const int phSpawnRate;
	const float dissipationRate;
	int frame = 0;
	std::vector<Pheromone> pheromones;
	std::vector<Agent> ants;
	std::vector<Food> foods;

	Vec2<float> colonyPos{ 640,360 };
};