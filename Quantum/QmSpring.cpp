#include "QmSpring.h"
#include <glm/glm.hpp>

using namespace Quantum;

QmSpring::QmSpring(float K, int lo, QmParticle* p) : k_(K)
{
	part = p;
	l_ = lo;
}

QmSpring::~QmSpring() {}

void QmSpring::setRaideur(int k)
{
	k_ = k;
}

void QmSpring::update(QmParticle* p) {
	glm::vec3 d = p->getPos() - part->getPos();
	float N = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
	float coeff = -(N - l_) * k_;
	p->AddForce(normalize(d)*coeff);
}