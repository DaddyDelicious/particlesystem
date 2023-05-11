#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <particlesystem/particle.h>
#include <algorithm>
#include <random>

float rnd();

float srnd();


class Emitter {

public:
    
    Emitter(glm::vec2 position = {0.0f, 0.0f}, glm::vec2 force = {0.0f, 0.0f} ,
            float spawnRate = 0.04f        
        ): position{position}
        , spawnRate{spawnRate}
        , time_since_last_spawn{0.0f}
        , active{true}
        , force{force}
        , particles{}
        , particlesloaded{}
        , counter{0} {}

    
    glm::vec2 getPos() { return position; }

    void setPos(glm::vec2 newPos) { position = newPos; }

    void setSpawnRate(float spawnRateArg) { spawnRate = spawnRateArg; }


    std::vector<Particle>& getParticles() { return particles; }
  
    std::vector<Particle>& getParticlesLoaded() { return particlesloaded; }


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


  
   virtual void addParticle(size_t arg)  {

        particlesloaded[arg].setForce(force);
        particles.push_back(particlesloaded[arg]);
    }

    virtual void update(const double dt) {
        time_since_last_spawn += dt;
        if (active) {

            if (time_since_last_spawn > spawnRate) {
                
                counter++;
               
                if (counter < particlesloaded.size()-1) {
                    
                    addParticle(counter);
                    
                } else {
                    this->active = false;
                }  
               
                time_since_last_spawn = 0.0f;
                
            }
        }
    }

    protected:
    glm::vec2 position;
    glm::vec2 force;
    float spawnRate;
    double time_since_last_spawn;
    bool active;
    std::vector<Particle> particles;
    std::vector<Particle> particlesloaded;   
    size_t counter;


};




