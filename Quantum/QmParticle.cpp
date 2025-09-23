#include "stdafx.h"

#include "QmParticle.h"
#include "QmUpdater.h"

using namespace Quantum;

QmParticle::QmParticle() : position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0)
{
}

QmParticle::QmParticle(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc, float masse, float charge, float rad, bool isacc) : QmParticle()
{
	position = pos;
	velocity = vel;
	acceleration = acc;
	if (masse == 0)
		invMass = 0;
	else
		invMass = 1 / masse;
	e = charge;
	radius = rad;
	isAcc = isacc;
	setAABB();
	damping = 0.995f;
	type = TYPE_PARTICLE;
}

QmParticle::~QmParticle()
{
	delete updater;
}

void QmParticle::integrate(float t, float damping, bool euler)
{
	this->damping = damping;
	if (euler) 
	{
		acceleration += forceAccumulateur * invMass;
		position = getPos() + t * getVel();
		setAABB();
		velocity = getVel() * damping + t * getAcc();
	}
	else
	{
		acceleration += forceAccumulateur * invMass;
		velocity = getVel() * damping + t * getAcc();
		position = getPos() + t * getVel();
		setAABB();
	}
	if (updater != NULL)
		updater->update(getPos());
}

void QmParticle::update(float dt, float damping, bool euler)
{
	this->damping = damping;

	acceleration += forceAccumulateur * invMass;

	if (euler)
	{
		// Explicit Euler integration
		position = getPos() + dt * getVel();          // Update position from velocity
		setAABB();                                   // Update bounding box
		velocity = getVel() * damping + dt * getAcc(); // Update velocity from acceleration
	}
	else
	{
		// Semi-implicit Euler (slightly more stable)
		velocity = getVel() * damping + dt * getAcc(); // Update velocity first
		position = getPos() + dt * getVel();           // Then update position
		setAABB();                                    // Update bounding box
	}
	if (updater != NULL)
		updater->update(getPos() + dt * getVel());
}

float QmParticle::getInvMass()
{
	return invMass;
}

float QmParticle::getRadius()
{
	return radius;
}

float QmParticle::getCharge()
{
	return e;
}

bool QmParticle::IsAcc()
{
	return isAcc;
}

glm::vec3 QmParticle::getAcc()
{
	return acceleration;
}

glm::vec3 QmParticle::getVel()
{
	return velocity;
}

glm::vec3 QmParticle::getPos()
{
	return position;
}

AABB QmParticle::getAABB()
{
	return aabb;
}

void QmParticle::setAcc(glm::vec3 acc)
{
	acceleration = acc;
	
}

void QmParticle::setVel(glm::vec3 vel)
{
	velocity = vel;

}

void QmParticle::setPos(glm::vec3 pos)
{
	position = pos;

}

void QmParticle::setCharge(int charge)
{
	e = charge;

}

void QmParticle::setAABB()
{
	glm::vec3 min = glm::vec3(getPos().x - radius*sqrt(3), getPos().y - radius * sqrt(3), getPos().z - radius * sqrt(3));
	glm::vec3 max = glm::vec3(getPos().x + radius * sqrt(3), getPos().y + radius * sqrt(3), getPos().z + radius * sqrt(3));
	aabb = AABB(min, max);
}

void QmParticle::setUpdater(QmUpdater* updater)
{
	this->updater = updater;
}

void QmParticle::AddForce(glm::vec3 f) 
{
	this->forceAccumulateur += f;
}

void QmParticle::clear()
{
	this->acceleration = glm::vec3(0, 0, 0);
	this->forceAccumulateur = glm::vec3(0, 0, 0);
}


