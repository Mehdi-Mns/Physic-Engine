#include "QmContact.h"
#include "QmParticle.h"
using namespace Quantum;


QmContact::QmContact(QmParticle* body1, QmParticle* body2)
{
	body1_ = body1;
	body2_ = body2;

	glm::vec3 vect = body1_->getPos() - body2_->getPos();

	normal_ = glm::normalize(glm::vec3(vect.y, -vect.x, 0));

	depth_ = glm::length(vect) - (glm::length(vect) - body1->getRadius()) - (glm::length(vect) - body2->getRadius());
}

QmContact::~QmContact() {}

QmParticle* QmContact::getB1() {
	return body1_;
}

QmParticle* QmContact::getB2() {
	return body2_;
}

glm::vec3 QmContact::getN() {
	return normal_;
}

float QmContact::getD() {
	return depth_;
}