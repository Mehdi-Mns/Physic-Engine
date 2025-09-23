#pragma once
#include <glm/glm.hpp>

namespace Quantum {

	/**
	 * @class AABB
	 * @brief Represents an Axis-Aligned Bounding Box (AABB).
	 *
	 * An AABB is defined by two 3D points: the minimum and maximum corners.
	 * It is commonly used in physics engines for broad-phase collision detection
	 * and spatial queries, since axis-aligned boxes are efficient to compute and test.
	 */
	class AABB {
	public:
		/**
		 * @brief Default constructor.
		 */
		AABB();

		/**
		 * @brief Constructs an AABB from a minimum and maximum point.
		 *
		 * @param min The minimum corner of the box (x_min, y_min, z_min).
		 * @param max The maximum corner of the box (x_max, y_max, z_max).
		 */
		AABB(glm::vec3 min, glm::vec3 max);

		/**
         * @brief Destructor.
         */
		~AABB();

		/**
		 * @brief Returns the minimum corner of the bounding box.
		 */
		glm::vec3 getMin();

		/**
		 * @brief Returns the maximum corner of the bounding box.
		 */
		glm::vec3 getMax();

	private:
		/**
		* @brief Minimum corner.
		*/
		glm::vec3 min_;

		/**
		* @brief Maximum corner.
		*/
		glm::vec3 max_;
	};
}