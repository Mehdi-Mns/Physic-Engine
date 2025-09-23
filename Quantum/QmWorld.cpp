#include "stdafx.h"
#include <iostream>

#include "QmWorld.h"

using namespace Quantum;

QmWorld::QmWorld() :
	gravity(glm::vec3(0, -9.81, 0))
{
	std::cout << "Starting Quantum Physics engine." << std::endl;
	time = 0.f;
	ticktime = 0.f;
}

QmWorld::~QmWorld()
{
}

float QmWorld::tick(float t, bool g, float damping, bool euler, bool c) 
{
	// former world::simulate
	ClearParticles();
	if (g)
		ApplyGravity();
	updateForces();
	integrate(t, damping, euler);
	if(c)
		resolve(broadphase());
	ticktime += t;
	return time - ticktime; // the remaining time interval
}


void QmWorld::simulate(float t, bool g, bool useDelta, float damping, bool euler, bool c)
{
	time += t;
	float dt = time - ticktime;
	if (useDelta) { // deterministic framerate-independent simulation
		while (dt >= 5)
			dt = tick(5, g, damping, euler, c);
		interpolate(dt, damping, euler);
	}
	else { // old fashioned all-frame non-deterministic simulation
		tick(t, g, damping, euler, c);
		interpolate(0, damping, euler);
	}
}


void QmWorld::integrate(float t, float damping, bool euler)
{
	time += t;
	for (QmBody* b : bodies)
		b->integrate(t, damping, euler);
	
}

void QmWorld::interpolate(float dt, float damping, bool euler)
{
	for (QmBody* b : bodies)
		b->update(dt, damping, euler);
}

bool QmWorld::intersect(AABB a, AABB b) {
	return (a.getMin().x <= b.getMax().x && a.getMax().x >= b.getMin().x) &&
		(a.getMin().y <= b.getMax().y && a.getMax().y >= b.getMin().y) &&
		(a.getMin().z <= b.getMax().z && a.getMax().z >= b.getMin().z);
}

std::list<QmContact> QmWorld::broadphase()
{
	std::list<QmContact>* ContactList = new std::list<QmContact>();
	for (QmBody* b1 : bodies)
	{
		for (QmBody* b2 : bodies)
		{
			if (intersect(((QmParticle*)b1)->getAABB(), ((QmParticle*)b2)->getAABB()))
			{
				QmContact contact = QmContact((QmParticle*)b1, (QmParticle*)b2);
				ContactList->push_back(contact);
			}
		}
		/*for (HalfSpace* h : halfSpaces)
		{
			if (intersect(((QmParticle*)b1)->getAABB(), h->getAABB()))
			{
				QmContact contact = QmContact((QmParticle*)b1, (QmParticle*)h);
				ContactHalf->push_back(contact);
			}
		}*/
	}
	return *ContactList;
}

//std::list<QmContact> QmWorld::narrowphase(QmParticle* b1, QmParticle* b2)
//{
//	std::list<QmContact>* ContactList = new std::list<QmContact>();
//	for (QmContact c : cList)
//	{
//		if (intersect(c.getB1()->getAABB(), c.getB2()->getAABB()))
//		{
//			ContactList->push_back(c);
//		}
//	}
//	return *ContactList;
//}

void QmWorld::resolve(std::list<QmContact> cList)
{
	for (QmContact c : cList) 
	{
		
		glm::vec3  d = c.getB1()->getPos() - c.getB2()->getPos();

		// Only process if the bodies are not at the same position
		if (glm::length(d) > 0)
		{
			glm::vec3 dN = glm::normalize(d);

			// Decompose velocities into perpendicular and parallel components
			glm::vec3 vperp1 = glm::dot(c.getB1()->getVel(), glm::normalize(d)) * glm::normalize(d);
			glm::vec3 vpara1 = glm::dot(c.getB1()->getVel(), glm::normalize(c.getN())) * glm::normalize(c.getN());
			glm::vec3 vperp2 = glm::dot(c.getB2()->getVel(), glm::normalize(d)) * glm::normalize(d);
			glm::vec3 vpara2 = glm::dot(c.getB2()->getVel(), glm::normalize(c.getN())) * glm::normalize(c.getN());

			// Extract masses from inverse mass (invMass = 1/m)
			float m1 = 1 / c.getB1()->getInvMass();
			float m2 = 1 / c.getB2()->getInvMass();

			// Compute new perpendicular velocities using 1D elastic collision equations
			glm::vec3 v1 = vperp1 * ((m1 - m2) / (m1 + m2)) + vperp2 * ((2 * m2) / (m1 + m2));
			glm::vec3 v2 = vperp1 * ((2 * m1) / (m1 + m2)) + vperp2 * ((m2 - m1) / (m1 + m2));

			// Recombine with the unchanged parallel components
			c.getB1()->setVel(v1 + vpara1);
			c.getB2()->setVel(v2 + vpara2);
		}
		
	}

	// Example of handling collisions with half-spaces (unfinished code).
	/*for (QmContact ch : *ContactHalf)
	{
		glm::vec3 vperp1 = glm::dot(ch.getB1()->getVel(), ((HalfSpace*)ch.getB2)->GetNormal()) * glm::normalize(d);
		glm::vec3 vperp = glm::dot(ch.getB1()->getVel(), (HalfSpace*)ch.getB2)->GetNormal()) * (HalfSpace*)ch.getB2)->GetNormal();
		glm::vec3 vpara = glm::dot(ch.getB1()->getVel(), glm::normalize(c.getN())) * glm::normalize(c.getN());
		c.getB1()->setVel(v1 + vpara1);
	}*/
	
}


void QmWorld::CreateBox()
{
	halfSpaces.push_back(new HalfSpace(glm::vec3(1, 0, 0), glm::vec3(-6, -6, -6))); 
	halfSpaces.push_back(new HalfSpace(glm::vec3(0, 1, 0), glm::vec3(-6, -6, -6)));
	halfSpaces.push_back(new HalfSpace(glm::vec3(0, 0, 6), glm::vec3(-6, -6, -6)));
	halfSpaces.push_back(new HalfSpace(glm::vec3(-1, 0, 0), glm::vec3(6, 6, 6)));
	halfSpaces.push_back(new HalfSpace(glm::vec3(0, -1, 0), glm::vec3(6, 6, 6)));
	halfSpaces.push_back(new HalfSpace(glm::vec3(0, 0, -1), glm::vec3(6, 6, 6)));
}

void QmWorld::addBody(QmBody* b)
{
	bodies.push_back(b);
}

std::vector<QmBody*> QmWorld::getBodies()
{
	return bodies;
}

std::list<QmForceRegistry*> QmWorld::getForces()
{
	return forceRegistry;
}

void QmWorld::ApplyGravity() {
	for (QmBody* b : bodies)
		if(((QmParticle*)b)->IsAcc())
			((QmParticle*)b)->setAcc(gravity);
}

void QmWorld::ChangeRaideur(int K) {
	for (QmForceRegistry* fr : forceRegistry)
		((QmSpring*)fr->fg)->setRaideur(K);
}

void QmWorld::updateForces() {
	for (QmForceRegistry* fr : forceRegistry)
		fr->fg->update(fr->p);
}

void QmWorld::AddParticle(QmParticle* p) {
	bodies.push_back(p);
}

void QmWorld::AddForceRegistry(QmForceRegistry* fg) {
	forceRegistry.push_back(fg);
}

void QmWorld::DelParticle(QmParticle* b) {
	/*b->clear();
	bodies.*/
}

void QmWorld::ClearParticles() {
	for (QmBody* b : bodies)
	{
		((QmParticle*)b)->clear();
	}
}


void QmWorld::clear()
{
	ClearParticles();
	for (QmBody* b : bodies)
	{
		delete b;
	}
	forceRegistry.clear();
	bodies.clear();
}

