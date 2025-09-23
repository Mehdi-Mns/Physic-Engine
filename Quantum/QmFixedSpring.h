#pragma once
#include "QmForceGenerator.h"


namespace Quantum {

	class QmParticle;

    /**
     * @class QmFixedSpring
     * @brief Applies a spring force between a particle and a fixed point.
     *
     * This force generator implements Hooke's law:
     *      F = -k * (|x - x0| - l0) * direction
     * where:
     *  - k is the spring stiffness coefficient,
     *  - l0 is the rest length,
     *  - x0 is the fixed point (`fix`),
     *  - x is the particle's current position.
     */
	class QmFixedSpring : QmForceGenerator {
	public:

        /**
         * @brief Constructs a fixed spring.
         *
         * @param K Spring stiffness coefficient.
         * @param lo Rest length of the spring.
         * @param pos Fixed position in space where the spring is anchored.
         */
		QmFixedSpring(float K, int lo, glm::vec3 pos);

        /**
         * @brief Destructor.
         */
		~QmFixedSpring();

        /**
         * @brief Applies spring force to the given particle.
         *
         * @param p Pointer to the particle influenced by the spring.
         */
		virtual void update(QmParticle* p);

        /**
         * @brief Fixed point in space where the spring is anchored.
         */
		glm::vec3 fix;
	private:

        /**
         * @brief Spring stiffness coefficient.
         */
		float k_;

        /**
         * @brief Rest length of the spring.
         */
		int l_;
	};
}
