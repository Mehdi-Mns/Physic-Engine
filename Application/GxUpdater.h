#ifndef MYGXUPDATER_H
#define MYGXUPDATER_H

#include "Quantum.h"

class GxParticle;

/**
 * @class GxUpdater
 * @brief Connects a Quantum particle to a graphics particle.
 *
 * This class inherits from Quantum::QmUpdater and allows
 * QmParticles to notify GxParticles of position updates.
 * Whenever a particle moves in the physics simulation, its
 * corresponding GxParticle can be updated for rendering.
 */
class GxUpdater : public Quantum::QmUpdater {
public:

	/**
	* @brief Default constructor.
	*/
	GxUpdater();

	/**
	 * @brief Constructs an updater linked to a GxParticle.
	 * @param p Pointer to the GxParticle to update.
	 */
	GxUpdater(GxParticle*);

	/**
	 * @brief Called by a QmParticle when its position changes.
	 * @param pos The new position of the particle.
	 */
	void update(glm::vec3);

private:

};

#endif


