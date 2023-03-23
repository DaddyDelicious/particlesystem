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
        position = glm::vec2{0.0f, 0.0f};
        spawnRate = 1.0f;
        time_since_last_spawn = 0.0f;
        spawnThis = Particle{};
        active = false;
        tempForce = 0.5f;
        force = glm::vec2(0.2f, 0.4f);
        
    }
    glm::vec2 getPos() { return position; }
    void setPos(glm::vec2 newPos) { position = newPos; }

    void setSpawnRate(float spawnRateArg) { spawnRate = spawnRateArg; }
    void setParticle(Particle& particleRef) {
        spawnThis = particleRef;
        spawnThis.setPos(position);
    }

    void setParticles(std::vector<Particle>& particlesArg) 
    { 

        for (size_t i = 0; i < particlesArg.size(); i++) {

            particlesArg[i].setPos(glm::vec2(0.0f, i/100.0f));
            
        }

        particles = particlesArg;
        
    
    }

    void emitterActive(bool arg) { active = arg; }

    void spawnParticles(rendering::Window& window, float dt) {

        if (active) {

            for (size_t i = 0; i < particles.size(); i++) {

                 window.drawPoint(particles[i].getPos(), particles[i].getRad(),
                                 particles[i].getColor());

                 this->updatePos(particles[i],dt);

            }
             
           
              time_since_last_spawn = 0.0f;
        }
    }

    void updatePos(Particle& arg, float dt){
    
        arg.setAcc(glm::vec2(force.x / arg.getMass(),force.y/ arg.getMass()));
        arg.setVel(glm::vec2(arg.getVel().x + arg.getAcc().x * dt, arg.getVel().y + arg.getAcc().y * dt));
        glm::vec2 test = arg.getPos();
        test.x +=  arg.getVel().x * dt;
        test.y += arg.getVel().y * dt;
        arg.setPos(test);
    }


private:

    glm::vec2 position;
    glm::vec2 force;
    float spawnRate;
    float time_since_last_spawn;
    Particle spawnThis;
    bool active;

    float tempForce;
    std::vector<Particle> particles;


};


