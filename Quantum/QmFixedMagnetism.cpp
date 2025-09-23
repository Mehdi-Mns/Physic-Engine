#include "QmFixedMagnetism.h"

using namespace Quantum;

QmFixedMagnetism::QmFixedMagnetism(float K, QmParticle* pfix) : k_(K)
{
	partfix= pfix;
}

QmFixedMagnetism::~QmFixedMagnetism() {}


void QmFixedMagnetism::update(QmParticle* p) {
	glm::vec3 d = p->getPos() - partfix->getPos();
	float N = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
	float coeff = k_ * (p->getCharge() * partfix->getCharge());
	p->AddForce(normalize(d) * (coeff / (float)(pow(N, 2) + 1))); //0.001 explosion

}