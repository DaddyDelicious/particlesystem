#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <particlesystem/particle.h>
#include <rendering/window.h>
#include <iostream>
#include <tracy/Tracy.hpp>

class Emitter {

public:

    Emitter() 
    {   
        position = glm::vec2
        {0.0f, 0.0f};
        spawnRate = 1.0f;
        time_since_last_spawn = 0.0f;
        spawnThis = Particle{};
        active = false;
        
    }
    glm::vec2 getPos() { return position; }
    void setPos(glm::vec2 newPos) { position = newPos; }

    void setSpawnRate(float spawnRateArg) { spawnRate = spawnRateArg; }
    void setParticle(Particle& particleRef) {
        spawnThis = particleRef;
        spawnThis.setPos(position);
    }
    void emitterActive(bool arg) { active = arg; }

    void spawnParticle(rendering::Window& window, float dt) 
    { 
   
       
        if (active) {

           
               
               
              window.drawPoint(spawnThis.getPos(), spawnThis.getRad(), spawnThis.getColor());                    
              glm::vec2 test = spawnThis.getPos();                   
              test.x += 0.0001f;
              spawnThis.setPos(test);
              time_since_last_spawn = 0.0f;
                   
               
            

            
        }

        
    
    }

private:

    glm::vec2 position;
    float spawnRate;
    float time_since_last_spawn;
    Particle spawnThis;
    bool active;
   


};


