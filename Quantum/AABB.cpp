#include "AABB.h"
using namespace Quantum;


AABB::AABB() : min_(0), max_(0) {}

AABB::AABB(glm::vec3 min, glm::vec3 max) : min_(min), max_(max) {}

AABB::~AABB() {}

glm::vec3 AABB::getMin() {
	return min_;
}

glm::vec3 AABB::getMax() {
	return max_;
}