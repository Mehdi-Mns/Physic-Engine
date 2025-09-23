#ifndef QMWORLD_H
#define QMWORLD_H

#include <list>
#include <vector>
#include <glm/glm.hpp>
#include "QmParticle.h"
#include "QmContact.h"
#include "QmForceRegistry.h"
#include "QmDrag.h"
#include "QmMagnetism.h"
#include "QmFixedMagnetism.h"
#include "QmSpring.h"
#include "QmFixedSpring.h"
#include "HalfSpace.h"

namespace Quantum {

	class QmBody;
	class QmParticle;
	class QmContact;
	class QmForceGenerator;
	class QmForceRegistry;
	class QmDrag;
	class QmMagnetism;
	class QmFixedMagnetism;
	class HalfSpace;

	/**
	* @class QmWorld
	* @brief Manages the entire physics simulation.
	*
	* QmWorld is responsible for:
	*  - Storing and managing all bodies (particles, half-spaces, etc.)
	*  - Applying forces (gravity, drag, springs, magnetism…)
	*  - Detecting and resolving collisions (broadphase collision detection)
	*  - Updating particle positions and velocities through integration
	*  - Running the simulation loop over time
	*/
	class QmWorld {
	public:

		/**
		 * @brief Default constructor. Initializes the world.
		 */
		QmWorld();

		/**
		* @brief Destructor. Cleans up the world.
		*/
		~QmWorld();

		/**
		 * @brief Advances the simulation by one tick.
		 *
		 * @param t       Time step.
		 * @param g       Whether to apply gravity.
		 * @param damping Damping factor applied to particles.
		 * @param euler   If true, use Euler integration; otherwise semi-implicit Euler.
		 * @param c       Whether to handle collisions.
		 * @return The elapsed simulation time after the tick.
		 */
		float tick(float t, bool g, float damping, bool euler, bool c);

		/**
		 * @brief Runs the simulation for a given duration.
		 *
		 * @param t        Total time to simulate.
		 * @param g        Whether to apply gravity.
		 * @param useDelta If true, uses delta time stepping.
		 * @param damping  Damping factor.
		 * @param euler    Integration method selector.
		 * @param c        Whether to resolve collisions.
		 */
		void simulate(float t, bool g, bool useDelta, float damping, bool euler, bool c);

		/**
		* @brief Interpolates particle states for smooth rendering.
		*
		* @param dt      Interpolation delta time.
		* @param damping Damping factor.
		* @param euler   Integration method selector.
		*/
		void interpolate(float dt, float damping, bool euler);

		/**
		 * @brief Performs broadphase collision detection.
		 * @return A list of potential contacts (colliding pairs).
		 */
		std::list<QmContact> broadphase();


		//std::list<QmContact> narrowphase(QmParticle* b1, QmParticle* b2);

		/**
		 * @brief Resolves a list of detected contacts.
		 * @param cList List of contacts to resolve.
		 */
		void resolve(std::list<QmContact> cList);

		/**
		 * @brief Tests whether two AABBs intersect.
		 */
		bool intersect(AABB a, AABB b);

		/**
		 * @brief Creates the simulation box boundaries (HalfSpaces).
		 */
		void CreateBox();

		/**
		 * @brief Adds a body (particle or half-space) to the world.
		 */
		void addBody(QmBody*);

		/**
		 * @return All bodies in the world.
		 */
		std::vector<QmBody*> getBodies();

		/**
		 * @return All registered forces in the world.
		 */
		std::list<QmForceRegistry*> getForces();

		/**
		 * @brief Applies global gravity to all particles.
		 */
		void ApplyGravity();

		/**
		 * @brief Changes the stiffness of spring forces globally.
		 */
		void ChangeRaideur(int K);

		/**
		 * @brief Updates all forces applied to particles.
		 */
		void updateForces();

		/**
		 * @brief Adds a particle to the world.
		 */
		void AddParticle(QmParticle* p);

		/**
		 * @brief Registers a new force generator acting on a particle.
		 */
		void AddForceRegistry(QmForceRegistry* fg);

		/**
		 * @brief Removes a particle from the world.
		 */
		void DelParticle(QmParticle* b);

		/**
		 * @brief Removes all particles from the world.
		 */
		void ClearParticles();

		/**
		 * @brief Clears the world completely (particles, forces, etc.).
		 */
		void clear();
	private:

		/// @brief Total simulation time.
		float time;

		/// @brief Time per tick.
		float ticktime;

		/// @brief All bodies.
		std::vector<QmBody*> bodies;

		/// @brief lation boundaries.
		std::vector<HalfSpace*> halfSpaces;

		/// @brief Registered forces.
		std::list<QmForceRegistry*> forceRegistry;

		/// @brief Contact list (possibly from half-spaces).
		std::list<QmContact>* ContactHalf;

		/// @brief Global gravity vector.
		glm::vec3 gravity;

		/**
		 * @brief Integrates all particles over a time step.
		 */
		void integrate(float t, float damping, bool euler);
	};

}

#endif