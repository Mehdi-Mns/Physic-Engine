#pragma once
#include "QmForceGenerator.h"
#include <glm/glm.hpp>


namespace Quantum {

	class QmParticle;

	/**
	 * @class QmFixedMagnetism
	 * @brief Applies a magnetic-like force between a particle and a fixed particle.
	 *
	 * This force generator simulates attraction or repulsion between a particle
	 * and a fixed reference particle.
	 */
	class QmFixedMagnetism : QmForceGenerator {
	public:

		/**
		 * @brief Constructs a fixed magnetism force generator.
		 *
		 * @param K Scaling coefficient of the force.
		 * @param pfix Pointer to the fixed particle that generates the force.
		 */
		QmFixedMagnetism(float K, QmParticle* pfix);

		/**
		 * @brief Destructor.
		 */
		~QmFixedMagnetism();

		/**
		 * @brief Applies the magnetic force to the given particle.
		 *
		 * @param p Pointer to the particle that experiences the force.
		 */
		virtual void update(QmParticle* p);

		/**
		 * @brief Pointer to the fixed particle generating the force.
		 */
		QmParticle* partfix;
	private:

		/**
		 * @brief Force scaling coefficient.
		 */
		float k_;
	};
}