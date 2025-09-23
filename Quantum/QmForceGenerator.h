#pragma once
#include "QmParticle.h"

namespace Quantum {

	class QmParticle;

    /**
	 * @class QmForceGenerator
	 * @brief Abstract base class for force generators.
	 *
	 * A QmForceGenerator applies a force to a particle.
	 * Derived classes implement specific physical forces such as:
	 *  - Drag (air resistance, friction-like effects)
	 *  - Magnetism (attraction/repulsion between particles)
	 *  - Spring forces (Hooke’s law between two bodies)
	 *  - Gravity (constant acceleration force)
	 */
	class QmForceGenerator {
	public:
		/**
		 * @brief Applies a force update to the given particle.
		 *
		 * @param p Pointer to the particle that the force acts upon.
		 *
		 * This method should be overridden by derived classes to
		 * implement the specific force logic.
		 */
		virtual void update(QmParticle* p) {};
	};

}