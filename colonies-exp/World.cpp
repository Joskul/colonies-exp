#include "World.h"

World::World()
{
	// place entities here
	for (int i = 0; i < antCount; i++) {
		ants.emplace_back(colonyPos, antSpeed, wanderRate);
	}
	for (int x = 0; x < 1280; x++) {
		foods.emplace_back(Vec2<float>((float)x, 300.0f));
	}
}

void World::Update(float deltaTime) {

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

void World::Draw(Graphics& gfx) {
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

void World::spawnPheromone(Pheromone::Type setType, Vec2<float> setPos) {
	pheromones.emplace_back(setType, dissipationRate, depletionThreshold, setPos);
}
