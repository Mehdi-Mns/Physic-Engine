#ifndef GXWORLD_H
#define GXWORLD_H

#include <list>

class GxParticle;

/**
 * @class GxWorld
 * @brief Manages particles on the graphics/rendering side.
 *
 * Unlike Quantum::QmWorld, which handles physics simulation,
 * GxWorld only keeps track of GxParticle objects for rendering
 * or application-level logic.
 */
class GxWorld {
public:

	/**
	 * @brief Constructs an empty graphics world.
	 */
	GxWorld();

	/**
	 * @brief Destructor.
	 */
	~GxWorld();

	/**
	 * @brief Adds a particle to the graphics world.
	 * @param p Pointer to the particle to add.
	 */
	void addParticle(GxParticle*);

	/**
	* @brief Returns the list of particles in the world.
	*/
	std::list<GxParticle*> getParticles();

	/**
	 * @brief Replaces the entire particle list.
	 * @param newParticles The new list of particles.
	 */
	void setParticles(std::list<GxParticle*>);

	/**
	 * @brief Clears all particles from the graphics world.
	 */
	void clear();

private:
	/// @brief All particles managed by the graphics world.
	std::list<GxParticle*> particles;
};

#endif