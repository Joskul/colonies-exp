#include "Agent.h"
#include <algorithm>

Agent::Agent(Vec2<float> setPos, float setSpeed, float setWanderRate)
	:
	pos(setPos),
	speed(setSpeed),
	wanderRate(setWanderRate),
	rng(std::random_device{}()),
	randDist(-wanderRate, wanderRate)
{
}

Agent::Agent(Agent& src)
	:
	pos(src.pos),
	speed(src.speed),
	wanderRate(src.wanderRate),
	rng(std::random_device{}()),
	randDist(-src.wanderRate, src.wanderRate)
{
}

Agent::Agent(Agent&& src) noexcept
	:
	pos(src.pos),
	speed(src.speed),
	wanderRate(src.wanderRate),
	rng(std::random_device{}()),
	randDist(-src.wanderRate, src.wanderRate)
{
}

void Agent::Update(const float deltaTime, const std::vector<Pheromone>& pheromones, const std::vector<Food>& foods, const Colony& colony) {

	if (foods.size() && !holdingFood) {
		Vec2<float> nearestFood = foods[0].getPos();

		for (const auto& fd : foods) {
			if ((fd.getPos() - pos).GetLengthSq() > (nearestFood - pos).GetLengthSq()) { continue; };
			nearestFood = fd.getPos();
		}

		if (!((nearestFood - pos).GetLengthSq() > std::pow(detectionRange, 2))) {
			desiredDirection += (nearestFood - pos).GetNormalized() * foodInfluence;
		}
	}

	if (pheromones.size()) {

		Pheromone::Type targetType = holdingFood ? Pheromone::Type::toHome : Pheromone::Type::toFood;

		Pheromone const* bestPh = nullptr;

		const float detectionSq = detectionRange * detectionRange;
		const Vec2<float> detectionVec = desiredDirection.GetRotated(fov);
		const float dotThreshold = desiredDirection * detectionVec;

		for (const auto& ph : pheromones) {
			if (ph.getType() != targetType) { continue; }

			// is within detection range
			const Vec2<float> toEntity = ph.getPos() - pos;
			const float entityDistanceSq = toEntity.GetLengthSq();
			if (entityDistanceSq > detectionSq) { continue; }

			// is within detection angle
			if ((desiredDirection * toEntity) >= dotThreshold) { continue; }

			if (bestPh == nullptr) { bestPh = &ph; }
			if (((bestPh->getPos() - pos).GetLengthSq() / bestPh->getIntensity()) < (entityDistanceSq / ph.getIntensity())) { bestPh = &ph; }
		}
		if (bestPh != nullptr) {
			const float influence = std::min(phInfluence * (float)std::pow((bestPh->getPos() - pos).GetLength(),0.5) / (float)std::pow(bestPh->getIntensity(), 1), phInfluence * 10);
			//const float influence = phInfluence;
			desiredDirection += (bestPh->getPos() - pos).GetNormalized() * influence;
		}
	}

	if ((pos - colony.getPos()).GetLength() <= colony.getRadius() + detectionRange && holdingFood) {
		desiredDirection += (colony.getPos() - pos) * 10.0f;
	}

	Vec2<float> randomDir = Vec2<float>{ randDist(rng),randDist(rng) }; // TODO: make it dependent on time
	desiredDirection += randomDir;

	desiredDirection.Normalize();

	pos += desiredDirection * speed * deltaTime;
	c = holdingFood ? Colors::Blue: Colors::Red;
}

void Agent::Draw(Graphics& gfx) const
{
	int x = (int)pos.x;
	int y = (int)pos.y;
	gfx.putPixel(x - 1, y - 1, c);
	gfx.putPixel(x, y - 1, c);
	gfx.putPixel(x - 1, y, c);
	gfx.putPixel(x, y, c);
}

Vec2<float> Agent::getPos() const
{
	return pos;
}

bool Agent::isHoldingFood() const
{
	return holdingFood;
}

void Agent::giveFood()
{
	if (holdingFood) { return; }
	holdingFood = true;
	desiredDirection -= desiredDirection * 2.0f;
}

void Agent::takeFood()
{
	if (!holdingFood) { return; }
	holdingFood = false;
	desiredDirection -= desiredDirection * 2.0f;
}
