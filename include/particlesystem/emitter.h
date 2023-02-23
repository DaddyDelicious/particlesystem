#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <particlesystem/particle.h>
#include <rendering/window.h>
#include <iostream>

using vec2 = glm::vec2;
class Emitter {

public:

    Emitter() 
    {   
        position = vec2{0.0f, 0.0f};
        spawnRate = 1.0f;
        time_since_last_spawn = 0.0f;
        spawnThis = Particle{};
        active = false;
    
    }
    vec2 getPos() { return position; }
    void setPos(vec2 newPos) { position = newPos; }

    void setSpawnRate(float spawnRateArg) { spawnRate = spawnRateArg; }
    void setParticle(Particle& particleRef) {
        spawnThis = particleRef;
        spawnThis.setPos(position);
    }
    void emitterActive(bool arg) { active = arg; }

    void spawnParticles(rendering::Window& window, float dt) 
    { 
        time_since_last_spawn += dt;

        if (active) {

            if (time_since_last_spawn > spawnRate) 
            {
                time_since_last_spawn = 0.0f;
                
                window.drawPoint(spawnThis.getPos(), spawnThis.getRad(), spawnThis.getColor());
                glm::vec2 test = spawnThis.getPos();
                std::cout << test.x << " " << test.y;
                test.x += 0.05f;
                spawnThis.setPos(test);
             
            }


        }

       
    
    }

private:

    vec2 position;
    float spawnRate;
    float time_since_last_spawn;
    Particle spawnThis;
    bool active;


};


