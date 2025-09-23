#pragma once
#ifndef QMBODY_H
#define QMBODY_H

#include <glm/glm.hpp>
#include "QmUpdater.h"
#include "AABB.h"

namespace Quantum {

	/**
	 * @brief Constant defining the default type of physical body.
	 */
	const int TYPE_PARTICLE = 0;
	
	/**
	 * @class QmBody
	 * @brief Abstract base class representing a physical body in the engine.
	 *
	 * A QmBody encapsulates generic properties and behaviors of a simulated object,
	 * such as its type, time integration, and state updates.
	 * Derived classes (e.g., QmParticle, QmHalfSpace, etc.) must implement
	 * certain methods to handle physical interactions.
	 */
	class QmBody {
	public:
		/**
		 * @brief Integrates the motion equations over a given timestep.
		 *
		 * @param t        Time step (delta time).
		 * @param damping  Damping factor applied to motion.
		 * @param euler    Boolean flag to choose Euler integration (true) or another method.
		 *
		 * Derived classes should override it to define their own behavior.
		 */
		virtual void integrate(float t, float damping, bool euler) {};

		/**
		 * @brief Returns the axis-aligned bounding box (AABB) of this body.
		 *
		 * @return AABB representing the spatial boundaries of the object.
		 *
		 * This is a pure virtual method and MUST be implemented in derived classes.
		 */
		virtual AABB getAABB() = 0;

		/**
		 * @brief Updates the body’s state (positions, velocities, forces, etc.).
		 *
		 * @param dt       Time step.
		 * @param damping  Damping factor.
		 * @param euler    Boolean flag to select integration method.
		 */
		virtual void update(float dt, float damping, bool euler) {};

		/**
		 * @brief Returns the type of the body (e.g., particle, half space, etc.).
		 */
		int getType() const { return type; }


	protected:
		/**
		 * @brief Type of the body.
		 */
		int type;
	private:
	};
}

#endif