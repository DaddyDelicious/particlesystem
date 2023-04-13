#pragma once
//
#include <particlesystem/emitter.h>

//
class ConeE : public Emitter{
	
	public:
        ConeE(glm::vec2 position = { 0.0f, 0.0f }, glm::vec2 force = { 1.0f, 1.0f }, float spawnRate = 0.1f, float angle = 40.0f)
            : Emitter(position, force, spawnRate), coneAngleDeg{ angle }
        {
        }


        void addParticle(size_t arg) override {

            for (size_t i = 0; i < particlesloaded.size(); i++) {

                float coneAngleRad = glm::radians(coneAngleDeg);

                // Generate a random angle between -coneAngleRad/2 and coneAngleRad/2
                float randomAngle = (static_cast<float>(rand()) / RAND_MAX) * coneAngleRad - coneAngleRad * 0.5f;

                // Create the force vector using polar coordinates
                glm::vec2 newForce(std::cos(randomAngle) * force.x, std::sin(randomAngle) * force.y);

                particlesloaded[arg].setForce(newForce);

             }
            particles.push_back(particlesloaded[arg]);
                   
        }

private: 
    float coneAngleDeg;
	

};

