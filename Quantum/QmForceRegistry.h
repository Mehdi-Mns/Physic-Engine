#pragma once


namespace Quantum 
{
	class QmParticle;

	class QmForceGenerator;

	/**
	 * @class QmForceRegistry
	 * @brief Associates a particle with a force generator.
	 *
	 * A force registry entry stores a mapping between:
	 *  - A particle (`QmParticle*`)
	 *  - A force generator (`QmForceGenerator*`)
	 *
	 * During the simulation update step, the registry is iterated
	 * so that each force generator can apply its force to the associated particle.
	 */
	class QmForceRegistry 
	{
	public:

		/**
		 * @brief Constructs a registry entry linking a particle with a force generator.
		 *
		 * @param p Pointer to the particle.
		 * @param fg Pointer to the force generator that acts on the particle.
		 */
		QmForceRegistry(QmParticle* p, QmForceGenerator* fg);

		/**
		 * @brief Destructor.
		 */
		~QmForceRegistry();

		/**
		 * @brief Returns the particle associated with this registry entry.
		 */
		QmParticle* getPart();

		/**
		 * @brief Returns the force generator associated with this registry entry.
		 */
		QmForceGenerator* getForceGen();

		/**
		 * @brief Pointer to the particle.
		 */
		QmParticle* p;

		/**
		 * @brief Pointer to the force generator.
		 */
		QmForceGenerator* fg;
	
	private:
		
	};
}

