#include "QmForceRegistry.h"

using namespace Quantum;

QmForceRegistry::QmForceRegistry(QmParticle* particle, QmForceGenerator* forceGen)
{
	p = particle;
	fg = forceGen;
}

QmForceRegistry::~QmForceRegistry() 
{
}

QmParticle* QmForceRegistry::getPart()
{
	return p;
}

QmForceGenerator* QmForceRegistry::getForceGen()
{
	return fg;
}