#pragma once
#include "QmForceGenerator.h"


namespace Quantum {

	class QmParticle;

    /**
     * @class QmSpring
     * @brief Applies a spring force between two particles.
     *
     * This force generator simulates a spring connecting the given particle
     * and a reference particle. The spring follows Hooke's law:
     *     F = -k * (|d| - L0) * (d / |d|)
     *
     * where:
     *  - k is the spring stiffness (raideur),
     *  - |d| is the current distance between the two particles,
     *  - L0 is the rest length of the spring,
     *  - d/|d| is the unit vector along the displacement.
     *
     * This allows particles to oscillate or be constrained together realistically.
     */
	class QmSpring: QmForceGenerator {
	public:

        /**
         * @brief Constructs a spring force generator.
         *
         * @param K  Spring stiffness (Hooke’s constant).
         * @param lo Rest length of the spring.
         * @param p  Pointer to the reference particle attached to the spring.
         */
		QmSpring(float K, int lo, QmParticle* p);

        /**
         * @brief Destructor.
         */
		~QmSpring();

        /**
         * @brief Applies the spring force to the given particle.
         *
         * @param p Particle that experiences the spring force.
         */
		virtual void update(QmParticle* p);

        /**
        * @brief Sets the spring stiffness (raideur).
        *
        * @param k New spring stiffness.
        */
		void setRaideur(int k);

        /// @brief Reference particle attached to the spring.
		QmParticle* part;
	private:

        /// @brief Spring stiffness coefficient.
		float k_;

        /// @brief Rest length of the spring.
		int l_;
	};
}