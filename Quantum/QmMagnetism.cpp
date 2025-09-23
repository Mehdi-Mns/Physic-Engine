#include "QmMagnetism.h"
#include <glm/glm.hpp>

using namespace Quantum;

QmMagnetism::QmMagnetism(float K, QmParticle* p) : k_(K) 
{
	part = p;
}

QmMagnetism::~QmMagnetism() {}


void QmMagnetism::update(QmParticle* p) {
	glm::vec3 d = p->getPos() - part->getPos();
	float N = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
	float coeff = k_ * (p->getCharge() * part->getCharge());
	p->AddForce(normalize(d) * (coeff / (float)(pow(N, 2) + 1))); //0.001 explosion

}