#ifndef GXPARTICLE_H
#define GXPARTICLE_H

#include <glm/glm.hpp>

/**
 * @class GxParticle
 * @brief Represents a particle for the graphics/rendering layer.
 *
 * GxParticle is the visual counterpart to Quantum::QmParticle.
 * It stores information needed for rendering:
 *  - Position in 3D space
 *  - Color
 *  - Radius (size)
 *
 * This class does not handle physics; it simply holds data
 * to display the particle in the graphics layer.
 */
class GxParticle {
public:

	/**
	 * @brief Default constructor. Initializes a particle at origin with default values.
	 */
	GxParticle();

	/**
	 * @brief Constructs a graphics particle with specified properties.
	 * @param c Initial color (RGB vector).
	 * @param rad Radius of the particle.
	 * @param pos Initial position.
	 */
	GxParticle(glm::vec3 c, float rad, glm::vec3);

	/**
	 * @brief Destructor.
	 */
	~GxParticle();

	/**
	 * @brief Sets the position of the particle.
	 * @param pos New position.
	 */
	void setPos(glm::vec3);

	/**
	 * @brief Sets the color of the particle.
	 * @param col New color.
	 */
	void setCol(glm::vec3);

	/**
	 * @brief Sets the radius (size) of the particle.
	 * @param r New radius.
	 */
	void setRad(float);

	/**
	 * @brief Returns the current position.
	 * @return Position as a glm::vec3.
	 */
	glm::vec3 getPos();

	/**
	 * @brief Returns the current color.
	 * @return Color as a glm::vec3 (RGB).
	 */
	glm::vec3 getColor();

	/**
	 * @brief Returns the current radius.
	 * @return Radius as a float.
	 */
	float getRadius();

private:
	/// @brief Current position of the particle.
	glm::vec3 position;

	/// @brief Particle color (RGB).
	glm::vec3 color;

	/// @brief rticle radius for rendering.
	float radius;
};



#endif