#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <particlesystem/particle.h>
#include <rendering/window.h>
#include <iostream>
#include <tracy/Tracy.hpp>
#include <particlesystem/particle.h>
#include <algorithm>
#include <random>

////
float rnd() { return rand() / static_cast<float>(RAND_MAX); }

// Random float (-1,1)
float srnd() { return rnd() * 2.0f - 1.0f; }

class Emitter {

public:
    

    Emitter() 
    {   
        position = glm::vec2{0.0f, 0.0f};
        spawnRate = 0.04f;
        time_since_last_spawn = 0.0f;        
        active = false;       
        force = glm::vec2(0.0f, 0.0f);
        particles = std::vector<Particle>{};
        particlesloaded = std::vector<Particle>{};
        counter = 0;
    }
    
    glm::vec2 getPos() { return position; }

    void setPos(glm::vec2 newPos) { position = newPos; }

    void setSpawnRate(float spawnRateArg) { spawnRate = spawnRateArg; }

    std::vector<Particle>& getParticles() { return particles; }
  
    void setParticles(std::vector<Particle> particlesArg) 
    { 
        for (Particle e: particlesArg) {

            e.setPos(position);
            particlesloaded.push_back(e);
        }       
    
    }

    void setForce(glm::vec2 forceInput){
        force = forceInput;
    }

    void emitterActive(bool arg) { active = arg; }

    glm::vec2& getForce() { return force; }


  
   virtual void addParticle(int arg)  {

        particlesloaded[arg].setForce(force);
        particles.push_back(particlesloaded[arg]);
    }

    virtual void update(float dt)  {
        time_since_last_spawn += dt;
        if (active) {

            if (time_since_last_spawn > spawnRate) {
                
                counter++;
               
                if (counter < particlesloaded.size()-1) {
                    
                    addParticle(counter);
                    
                } else {
                    counter = 0;
                }  // active = false; }
               
                time_since_last_spawn = 0.0f;
                
            }
        }
    }

    protected:
    glm::vec2 position;
    glm::vec2 force;
    float spawnRate;
    float time_since_last_spawn;
    bool active;
    std::vector<Particle> particles;
    std::vector<Particle> particlesloaded;   
    int counter;
    //

};




