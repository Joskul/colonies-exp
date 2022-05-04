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

	const float detectionSq = detectionRange * detectionRange;
	const Vec2<float> detectionVec = desiredDirection.GetRotated(fov);
	const float dotThreshold = desiredDirection * detectionVec;

	if (foods.size() && !holdingFood) {
		Food const* bestFd = nullptr;

		for (const auto& fd : foods) {

			// is within detection range
			const Vec2<float> toEntity = fd.getPos() - pos;
			const float entityDistanceSq = toEntity.GetLengthSq();
			if (entityDistanceSq > detectionSq) { continue; }

			// is within detection angle
			if ((desiredDirection * toEntity) >= dotThreshold) { continue; }

			if (bestFd == nullptr || entityDistanceSq < (bestFd->getPos() - pos).GetLengthSq()) { bestFd = &fd; }
		}
		if (bestFd != nullptr) {
			desiredDirection += (bestFd->getPos() - pos).GetNormalized() * foodInfluence;
		}
	}

	if (pheromones.size()) {

		Pheromone::Type targetType = holdingFood ? Pheromone::Type::toHome : Pheromone::Type::toFood;

		Pheromone const* bestPh = nullptr;

		for (const auto& ph : pheromones) {
			if (ph.getType() != targetType) { continue; }

			// is within detection range
			const Vec2<float> toEntity = ph.getPos() - pos;
			const float entityDistanceSq = toEntity.GetLengthSq();
			if (entityDistanceSq > detectionSq) { continue; }

			// is within detection angle
			if ((desiredDirection * toEntity) >= dotThreshold) { continue; }

			if (bestPh == nullptr) { bestPh = &ph; }
			if (((bestPh->getPos() - pos).GetLengthSq()) < (entityDistanceSq)) { bestPh = &ph; }
			//const float influence = phInfluence * entityDistanceSq / std::pow(ph.getIntensity(), 0.5f);
		}
		if (bestPh != nullptr) {
			const float influence = phInfluence /** (float)std::pow((bestPh->getPos() - pos).GetLength(),0.5)*/ / (float)std::pow(bestPh->getIntensity(), 2);
			//const float influence = phInfluence;
			desiredDirection += (bestPh->getPos() - pos).GetNormalized() * influence;
		}
	}

	if ((pos - colony.getPos()).GetLength() <= colony.getRadius() + detectionRange && holdingFood && desiredDirection * (pos - colony.getPos()) < dotThreshold) {
		desiredDirection += (colony.getPos() - pos) * 10.0f;
	}

	Vec2<float> randomDir = Vec2<float>{ randDist(rng),randDist(rng) }; // TODO: make it dependent on time
	desiredDirection += randomDir;

	desiredDirection.Normalize();

	pos += desiredDirection * speed * deltaTime;
	c = holdingFood ? Colors::Blue : Colors::Red;
}

void Agent::Draw(Graphics& gfx) const
{
	gfx.putPixel(int(pos.x + 0.5f), int(pos.y + 0.5f), c);
	gfx.putPixel(int(pos.x + 0.5f), int(pos.y - 0.5f), c);
	gfx.putPixel(int(pos.x - 0.5f), int(pos.y + 0.5f), c);
	gfx.putPixel(int(pos.x - 0.5f), int(pos.y - 0.5f), c);
	gfx.putPixel(int(pos.x - 0.5f), int(pos.y), c);
	gfx.putPixel(int(pos.x + 0.5f), int(pos.y), c);
	gfx.putPixel(int(pos.x), int(pos.y - 0.5f), c);
	gfx.putPixel(int(pos.x), int(pos.y + 0.5f), c);
	gfx.putPixel(int(pos.x), int(pos.y), c);

	gfx.drawLine(pos.x, pos.y, (pos + (desiredDirection * 2.0f)).x, (pos + (desiredDirection * 2.0f)).y, c);
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
