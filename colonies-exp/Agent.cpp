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

void Agent::Update(float deltaTime, const std::vector<Pheromone>& ph, const std::vector<Food>& fd) {

	if (fd.size() > 0) {
		Vec2<float> nearestFood = fd[0].getPos();
		for (auto food : fd) {
			if ((food.getPos() - pos).GetLengthSq() > (nearestFood - pos).GetLengthSq()) {
				continue;
			};
			nearestFood = food.getPos();
		}
		if (!((nearestFood - pos).GetLengthSq() > std::pow(detectionRange, 2))) {
			desiredDirection += (nearestFood - pos).GetNormalized() * 10;
		}
		// TODO: Eat da food
	}

	Vec2<float> randomDir = Vec2<float>{ randDist(rng),randDist(rng) };
	desiredDirection += randomDir;

	desiredDirection.Normalize();

	pos += desiredDirection * speed * deltaTime;
	c = holdingFood ? Color(192, 255, 192): Colors::White;
}

void Agent::Draw(Graphics& gfx)
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
