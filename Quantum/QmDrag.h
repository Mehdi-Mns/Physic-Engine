#pragma once
#include "QmForceGenerator.h"


namespace Quantum {

	class QmParticle;

    /**
     * @class QmDrag
     * @brief Applies a drag (air resistance) force to a particle.
     *
     * Drag is a resistive force that opposes the velocity of a moving object.
     * It is modeled using two coefficients:
     *  - k1 (linear drag, proportional to velocity)
     *  - k2 (quadratic drag, proportional to velocity squared)
     * 
     * The resulting force is:
     *      F_drag = -(k1 * v + k2 * |v| * v)
     * where v is the velocity of the particle.
     */
	class QmDrag : QmForceGenerator {
	public:
        /**
         * @brief Constructs a drag force generator with given coefficients.
         *
         * @param K1 Linear drag coefficient (proportional to velocity).
         * @param K2 Quadratic drag coefficient (proportional to velocity squared).
         */
		QmDrag(float K1, float K2);

        /**
         * @brief Destructor.
         */
		~QmDrag();

        /**
         * @brief Applies drag force to the given particle.
         *
         * @param p Pointer to the particle.
         * This overrides the base class method and calculates drag based on velocity.
         */
		virtual void update(QmParticle* p);
	private:

        /**
         * @brief Linear drag coefficient.
         */
		float k1_;

        /**
         * @brief Quadratic drag coefficient.
         */
		float k2_;
	};
}