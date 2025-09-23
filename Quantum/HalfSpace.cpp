#include "HalfSpace.h"

using namespace Quantum;


HalfSpace::HalfSpace(glm::vec3 normal, glm::vec3 offset) : normal_(normal), offset_(offset)
{
	setAABB();
}

HalfSpace::~HalfSpace() {}

AABB HalfSpace::getAABB()
{
	return aabb_;
}

glm::vec3 HalfSpace::GetNormal()
{
	return normal_;
}

void HalfSpace::setAABB()
{
	glm::vec3 min = offset_;
	glm::vec3 max = glm::vec3(0, 0, 0);

	if(offset_.x > 0)
		max = offset_ - 12.0f * (glm::vec3(1,1,1) - normal_) + glm::vec3(1, 1, 1);
	else
		max = offset_ + 12.0f * (glm::vec3(1, 1, 1) - normal_) - glm::vec3(1, 1, 1);

	// Update AABB. 
	aabb_ = AABB(min, max);
}