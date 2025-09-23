#ifndef QMPARTICLE_H
#define QMPARTICLE_H

#include <glm/glm.hpp>
#include "QmBody.h"
#include "QmForceRegistry.h"
#include "AABB.h"

namespace Quantum {
	class QmUpdater;
	class AABB;

	/**
	 * @class QmParticle
	 * @brief Represents a physical particle in the physics engine.
	 *
	 * A QmParticle is the fundamental simulated body. It extends QmBody
	 * and encapsulates the following properties:
	 *  - Position, velocity, and acceleration (motion state)
	 *  - Inverse mass (to avoid division by zero for infinite mass)
	 *  - Radius (for collision handling)
	 *  - Charge (for magnetism/electric-like forces)
	 *  - Restitution (bounciness during collisions)
	 *  - Force accumulator (for applying forces each update)
	 *
	 * QmParticles are updated each simulation step by integrating forces
	 * into velocity and position, and they interact with force generators,
	 * collisions, and other particles.
	 */
	class QmParticle : public QmBody {
	public:

		/**
		 * @brief Default constructor. Creates an uninitialized particle.
		 */
		QmParticle();

		/**
		 * @brief Constructs a particle with initial parameters.
		 *
		 * @param pos Initial position.
		 * @param vel Initial velocity.
		 * @param acc Initial acceleration.
		 * @param masse Particle mass.
		 * @param charge Particle charge (for magnetism/electric-like forces).
		 * @param rad Particle radius (for collision detection).
		 * @param isacc Whether the particle is affected by external accelerations.
		 */
		QmParticle(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc, float masse, float charge, float rad, bool isacc);

		/**
		 * @brief Destructor.
		 */
		~QmParticle();

		/**
		 * @brief Integrates the particle’s motion over time.
		 *
		 * @param t Time step (delta time).
		 * @param damping Damping factor (simulating friction/energy loss).
		 * @param euler If true, uses Euler integration.
		 */
		virtual void integrate(float t, float damping, bool euler);

		/**
		 * @brief Updates the particle state for a simulation step.
		 *
		 * @param dt Time step.
		 * @param damping Damping factor.
		 * @param euler Integration method selector.
		 */
		virtual void update(float dt, float damping, bool euler);

		/// @return The inverse of the particle’s mass.
		float getInvMass();

		/// @return The particle’s charge.
		float getCharge();

		/// @return True if the particle is affected by acceleration forces.
		bool IsAcc();

		/// @return The particle’s radius.
		float getRadius();

		/// @return The particle’s acceleration.
		glm::vec3 getAcc();

		/// @return The particle’s velocity.
		glm::vec3 getVel();

		/// @return The particle’s position.
		glm::vec3 getPos();

		/// @return The particle’s bounding box.
		AABB getAABB();

		/// @brief Sets the particle’s acceleration.
		void setAcc(glm::vec3 acc);

		/// @brief Sets the particle’s velocity
		void setVel(glm::vec3 vel);

		/// @brief Sets the particle’s position.
		void setPos(glm::vec3 pos);

		/// @brief Sets the particle’s charge.
		void setCharge(int charge);

		/// @brief Updates the particle’s bounding box.
		void setAABB();

		/// @brief Assigns an updater (external simulation manager).
		void setUpdater(QmUpdater* updater);

		/// @brief Adds a force to the particle’s accumulator.
		void AddForce(glm::vec3 f);

		/// @brief Clears accumulated forces.
		void clear();

	private:

		/// @brief Pointer to the simulation updater.
		QmUpdater* updater;

		/// @brief Current position of the particle.
		glm::vec3 position;

		/// @brief Current velocity of the particle.
		glm::vec3 velocity;

		/// @brief Current acceleration of the particle.
		glm::vec3 acceleration;

		/// @brief Accumulated forces applied during the frame.
		glm::vec3 forceAccumulateur;
		
		/// @brief Inverse mass (0 for infinite mass objects).
		float invMass;

		/// @brief Possibly energy-related or unused variable.
		float e;

		/// @brief Damping factor (reduces velocity over time).
		float damping;

		/// @brief Whether external acceleration is applied.
		bool isAcc;

		/// @brief Axis-aligned bounding box for collision checks.
		AABB aabb;

		/// @brief Collision radius.
		float radius;

		/// @brief Restitution coefficient (bounciness).
		float restitution;

	};

}

#endif