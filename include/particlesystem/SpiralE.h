#pragma once
#include <particlesystem/emitter.h>
#include <iostream>


class SpiralE : public Emitter {

public:
    SpiralE(glm::vec2 position = {0.0f, 0.0f}, glm::vec2 force = {1.0f, 1.0f}, float spawnRate = 0.1f,
          float angle = 0.0f, float angularVel = 15.f)
        : Emitter(position, force, spawnRate), angleDeg{angle}, angularVelocity{angularVel} {}



    void addParticle(size_t arg) override {

        for (size_t i = 0; i < particlesloaded.size(); i++) {
            
            

            angleDeg += angularVelocity / particlesloaded.size();
           float coneAngleRad = glm::radians(angleDeg);

            
            glm::vec2 newForce(std::cos(coneAngleRad), std::sin(coneAngleRad));
            particlesloaded[arg].setForce(newForce);
            
        }
        particles.push_back(particlesloaded[arg]);
    }

private:
   
    float angleDeg = 0.0f;
    float angularVelocity;
    float spreadX = 0.0f;
    float spreadY = 1.0f;
  

};