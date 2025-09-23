#pragma once
#include <glm/glm.hpp>
#include "AABB.h"
#include "QmBody.h"

namespace Quantum {

	class AABB;

	/**
	* @class HalfSpace
	* @brief Represents an infinite half-space (plane) in the physics engine.
	*
	* A half-space is defined by a normal vector and an offset from the origin.
	* It is often used as a static boundary in simulations (e.g., ground plane,
	* walls, or constraints).
	*
	* This class inherits from QmBody, so it can interact with other physics
	* bodies in the simulation (e.g., particles colliding with the plane).
	*/
	class HalfSpace : QmBody {
	public:
		/**
		 * @brief Constructs a half-space from a normal and offset.
		 *
		 * @param normal A unit vector representing the orientation of the plane.
		 * @param offset A vector indicating the displacement of the plane from the origin.
		 */
		HalfSpace(glm::vec3 normal, glm::vec3 offset);

		/**
		 * @brief Destructor.
		 */
		~HalfSpace();

		/**
		 * @brief Returns the normal vector of the half-space.
		 */
		glm::vec3 GetNormal();

		/**
		 * @brief Returns the axis-aligned bounding box (AABB) for the half-space.
		 *
		 * Since a half-space is infinite, the AABB may be defined with large bounds
		 * or special handling in collision detection.
		 */
		AABB getAABB();

		/**
		 * @brief Updates the internal AABB of the half-space.
		 *
		 * Should be called whenever the plane’s position/orientation changes.
		 */
		void setAABB();
	private:

		/**
		 * @brief Bounding box approximation of the half-space.
		 */
		AABB aabb_;

		/**
		 * @brief Normal vector of the plane (orientation).
		 */
		glm::vec3 normal_;

		/**
		 * @brief Offset from the origin defining the plane position.
		 */
		glm::vec3 offset_;
	};
}
