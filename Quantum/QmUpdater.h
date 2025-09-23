#ifndef QMUPDATER_H
#define QMUPDATER_H

#include <glm/glm.hpp>

namespace Quantum {

	/**
	 * @class QmUpdater
	 * @brief Abstract interface for objects that react to particle updates.
	 *
	 * This class provides a callback mechanism between the physics engine
	 * and external systems.
	 */
	class QmUpdater {
	public:

		/**
		 * @brief Default constructor.
		 */
		QmUpdater() {};

		/**
		 * @brief Virtual destructor.
		 */
		~QmUpdater() {};

		/**
		 * @brief Callback invoked when a particle updates its position.
		 *
		 * @param pos The updated position of the particle.
		 */
		virtual void update(glm::vec3) = 0;

	protected:

		/// @brief Pointer to an external graphics or game object.
		void* gxObject;
	};

}

#endif