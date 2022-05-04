#pragma once
#include <vector>
#include <algorithm>
#include "Vec2.h"
#include "Entity.h"
#include "Agent.h"
#include "Graphics.h"

class World {
public:
	World()
	{
		for (int i = 0; i < antCount; i++) {
			ants.emplace_back(colonyPos, antSpeed, wanderRate);
		}
		for (int x = 0; x < 1280; x++) {
			foods.emplace_back(Vec2<float>((float)x, 300.0f));
		}
	}

	void Update(float deltaTime) {
		int i = 0;
		for (auto& ant : ants) {
			ant.Update(deltaTime, pheromones, foods, home);
			if ((frame + i) % phSpawnRate == 0) { // TODO: make pheromone deployment dependent on time **somehow impossible
				Pheromone::Type targetType = ant.isHoldingFood() ? Pheromone::Type::toFood : Pheromone::Type::toHome;
				spawnPheromone(targetType, ant.getPos());
			}
			if ((ant.getPos() - colonyPos).GetLength() < 12.0f) {
				ant.takeFood();
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

		for (std::vector<Food>::iterator fd = foods.begin(); fd != foods.end();) {
			bool isEaten = false;
			for (auto& ant : ants) {
				if ((ant.getPos() - fd->getPos()).GetLengthSq() < 1.0f && !ant.isHoldingFood()) {
					isEaten = true;
					ant.giveFood();
					break;
				}
			}
			if (isEaten) {
				fd = foods.erase(fd);
			}
			else {
				fd++;
			}
		}
		frame++;
	}

	void Draw(Graphics& gfx) {
		for (const auto& ph : pheromones) {
			ph.Draw(gfx);
		}
		home.Draw(gfx);
		for (const auto& ant : ants) {
			ant.Draw(gfx);
		}
		for (const auto& food : foods) {
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

	const int antCount = 200;
	const float antSpeed = 15.0f;
	const float wanderRate = 0.15f;
	const int phSpawnRate = 60;
	const float dissipationRate = 0.95f;
	const float depletionThreshold = 0.05f;
	int frame = 0;
	std::vector<Pheromone> pheromones;
	std::vector<Agent> ants;
	std::vector<Food> foods;

	Vec2<float> colonyPos{ 640,360 };
	Colony home{colonyPos, 12.0f};
};