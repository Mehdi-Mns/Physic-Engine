#include "QmDrag.h"

using namespace Quantum;

QmDrag::QmDrag(float K1, float K2) : k1_(K1), k2_(K2) {}

QmDrag::~QmDrag() {}

void QmDrag::update(QmParticle* p) {
	float N = sqrt(pow(p->getVel().x, 2) + pow(p->getVel().y, 2) + pow(p->getVel().z, 2));
	float coeff = -(k1_ * N + k2_ * pow(N, 2));
	p->AddForce(normalize(p->getVel())*coeff);
}