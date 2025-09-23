#pragma once
#include <glm/glm.hpp>

namespace Quantum {
	class QmParticle;

	/**
	 * @class QmContact
	 * @brief Represents a contact (collision) between two particles.
	 *
	 * A QmContact stores the two bodies involved in the collision,
	 * the contact normal, and the penetration depth.
	 */
	class QmContact {
	public:
		/**
		 * @brief Constructs a contact between two particles.
		 *
		 * @param body1 Pointer to the first particle.
		 * @param body2 Pointer to the second particle.
		 */
		QmContact(QmParticle* body1, QmParticle* body2);

		/**
		 * @brief Destructor.
		 */
		~QmContact();

		/**
		 * @brief Returns the first particle involved in the contact.
		 */
		QmParticle* getB1();

		/**
		 * @brief Returns the second particle involved in the contact.
		 */
		QmParticle* getB2();

		/**
		 * @brief Returns the contact normal vector.
		 *
		 * The normal typically points from body1 to body2 and is used
		 * to determine the direction of the collision response.
		 */
		glm::vec3 getN();

		/**
		 * @brief Returns the penetration depth of the contact.
		 *
		 * The depth indicates how much the objects overlap and is used
		 * to correct positions and prevent interpenetration.
		 */
		float getD();

	private:

		/**
		 * @brief Pointer to the first particle.
		 */
		QmParticle* body1_;

		/**
		 * @brief Pointer to the second particle.
		 */
		QmParticle* body2_;

		/**
		 * @brief Contact normal vector.
		 */
		glm::vec3 normal_;

		/**
		 * @brief Penetration depth of the collision.
		 */
		float depth_;
	};
}