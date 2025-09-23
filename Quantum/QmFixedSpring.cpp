#include "QmFixedSpring.h"
#include <glm/glm.hpp>

using namespace Quantum;

QmFixedSpring::QmFixedSpring(float K, int lo, glm::vec3 pos) : k_(K)
{
	fix = pos;
	l_ = lo;
}

QmFixedSpring::~QmFixedSpring() {}


void QmFixedSpring::update(QmParticle* p) {
	glm::vec3 d = p->getPos() - fix;
	float N = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
	float coeff = -(N - l_) * k_;
	p->AddForce(normalize(d)*coeff);
}