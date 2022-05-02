#include "Agent.h"

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

void Agent::Update(const float deltaTime, const std::vector<Pheromone>& pheromones, const std::vector<Food>& foods) {

	if (foods.size() && !holdingFood) {
		Vec2<float> nearestFood = foods[0].getPos();

		for (const auto& fd : foods) {
			if ((fd.getPos() - pos).GetLengthSq() > (nearestFood - pos).GetLengthSq()) { continue; };
			nearestFood = fd.getPos();
		}

		if (!((nearestFood - pos).GetLengthSq() > std::pow(detectionRange, 2))) {
			desiredDirection += (nearestFood - pos).GetNormalized() * foodInfluence;
			if ((pos - nearestFood).GetLengthSq() <= 1.5f) {
				holdingFood = true;
			}
		}
	}

	if (pheromones.size()) {

		Pheromone::Type targetType = holdingFood ? Pheromone::Type::toHome : Pheromone::Type::toFood;

		for (const auto& ph : pheromones) {
			if (ph.getType() != targetType) { continue; }

			// is within detection range
			const Vec2<float> toEntity = ph.getPos() - pos;
			const float entityDistance = toEntity.GetLength();
			if (entityDistance > detectionRange) { continue; }

			//is within detection angle
			const Vec2<float> detectionVec = desiredDirection.GetRotated(fov);
			const float dotThreshold = desiredDirection * detectionVec;
			if ((desiredDirection * toEntity) >= dotThreshold) { continue; }

			const float influence = phInfluence / (ph.getIntensity());
			desiredDirection += toEntity.GetNormalized() * influence;
		}
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
