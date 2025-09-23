#pragma once
#include "QmForceGenerator.h"


namespace Quantum {

	class QmParticle;

	/**
	* @class QmMagnetism
	* @brief Applies a magnetic-like force between two particles.
	*
	* This force generator simulates attraction or repulsion between
	* a given particle and another reference particle. The magnitude
	* of the force is scaled by the coefficient K.
	*
	* It can be used to simulate interactions similar to charges,
	* magnets, or gravitational-like attraction/repulsion.
	*/
	class QmMagnetism : QmForceGenerator {
	public:

		/**
		 * @brief Constructs a magnetism force generator.
		 *
		 * @param K Force scaling coefficient.
		 * @param p Pointer to the reference particle that generates the force.
		 */
		QmMagnetism(float K, QmParticle* p);

		/**
		 * @brief Destructor.
		 */
		~QmMagnetism();

		/**
		 * @brief Applies the magnetic force to the given particle.
		 *
		 * @param p Pointer to the particle that experiences the force.
		 */
		virtual void update(QmParticle* p);

		/**
		 * @brief Reference particle exerting the force.
		 */
		QmParticle* part;
	private:

		/**
		 * @brief Force scaling coefficient.
		 */
		float k_;
	};
}