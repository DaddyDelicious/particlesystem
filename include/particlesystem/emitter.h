#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <particlesystem/particle.h>
#include <rendering/window.h>
#include <iostream>
#include <tracy/Tracy.hpp>

class Emitter {
//
public:

    Emitter() 
    {   
        position = glm::vec2{0.0f, 0.0f};
        spawnRate = 1.0f;
        time_since_last_spawn = 0.0f;
        spawnThis = Particle{};
        active = false;       
        force = glm::vec2(0.2f, 0.4f);
        
    }
    
    glm::vec2 getPos() { return position; }

    void setPos(glm::vec2 newPos) { position = newPos; }

    void setSpawnRate(float spawnRateArg) { spawnRate = spawnRateArg; }

    std::vector<Particle>& getParticles() { return particles; }

    void setParticles(std::vector<Particle> particlesArg) 
    { 

        particles = particlesArg;       
    
    }

    void setForce(glm::vec2 forceInput){
        force = forceInput;
    }

    void emitterActive(bool arg) { active = arg; }

    glm::vec2& getForce() { return force; }


private:

    glm::vec2 position;
    glm::vec2 force;
    float spawnRate;
    float time_since_last_spawn;
    Particle spawnThis;
    bool active;
    std::vector<Particle> particles;


};


