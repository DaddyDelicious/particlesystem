#pragma once
#include <iostream>
#include <vector>
#include <vector>
#include <particlesystem/emitter.h>
#include <particlesystem/effect.h>
#include <particlesystem/particle.h>

class Particlesystem {
    public:
    std::vector<Emitter> emitters;
    std::vector<effect> temp1;
    std::vector<Particle> particles;
    float timer = 0.0f;
    int test = 0;
    
    void render(rendering::Window& window, float dt) {

       timer += dt;
       
         for (size_t i = 0; i < emitters.size(); i++) {
				    
                    
                    
                    if (timer > 0.4f) {

                        test++;
                        particles.push_back(emitters[i].getParticles()[test]);
					    timer = 0.0f;

                        if (test == 99) test = 0;

                    }

                    for (size_t j = 0; j < particles.size(); j++) {

                      

                        window.drawPoint(particles[j].getPos(), particles[j].getRad(),
                                         particles[j].getColor());

                        this->updatePos(particles[j], emitters[i].getForce(), dt);
                        
                    }
                   
                 
         }

           
        
    }

    void updatePos(Particle& arg,glm::vec2 force ,float dt) {

        arg.setAcc(glm::vec2(force.x / arg.getMass(), force.y / arg.getMass()));
        arg.setVel(
            glm::vec2(arg.getVel().x + arg.getAcc().x * dt, arg.getVel().y + arg.getAcc().y * dt));
        glm::vec2 test = arg.getPos();
        test.x += arg.getVel().x * dt;
        test.y += arg.getVel().y * dt;
        arg.setPos(test);
    }
	

   
};
//