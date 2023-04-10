#pragma once
#include "emitter.h"
#include <glm/glm.hpp>
#pragma once
//
#include <particlesystem/emitter.h>




class ExplosionE : public Emitter
{

    public:
  
        ExplosionE(glm::vec2 position = { 0.0f, 0.0f }, bool oneTime = true, float spawnRate = 2.0f) : Emitter(position, force, spawnRate), oneTime{oneTime}
        {}
    
  

         void addParticle(size_t arg) override {
             (void)arg;
            for (size_t i = 0; i < particlesloaded.size(); i++) {

                float spreadX = srnd();
                float spreadY = srnd();

                glm::vec2 forceTest(spreadX, spreadY);

                particlesloaded[i].setForce(forceTest);
                particles.push_back(particlesloaded[i]);

            }
        }

         void update(const double dt) override {
            time_since_last_spawn += dt;
          
            
            if (active) {

                if (time_since_last_spawn > spawnRate) {

                    counter++;
                    
                    if (counter < particlesloaded.size() - 1) {

                        addParticle(counter);

                    }
                    else { active = false; }

                    time_since_last_spawn = 0.0;
                    if (oneTime) { active = false; };
                }
            }
           
        }

    
    

private:
    bool oneTime;

};

