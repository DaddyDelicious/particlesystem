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
   

    void render(rendering::Window& window, float dt) {
        
        for (auto& e : emitters) {
            
            for (auto& p : e.getParticles()) 
            {
                
                window.drawPoint(p.getPos(), p.getRad(), p.getColor());
                
            }

            e.update(dt);
            updatePos(dt);

        }
    }

    void updatePos(float dt) {

        for (auto& e: emitters) {

            for (auto& p : e.getParticles())
            {
                
                p.setAcc(glm::vec2(e.getForce().x / p.getMass(), e.getForce().y / p.getMass()));
                p.setVel(glm::vec2(p.getVel().x + p.getAcc().x * dt, p.getVel().y + p.getAcc().y * dt));
                p.setPos(glm::vec2(p.getPos().x + p.getVel().x * dt, p.getPos().y + p.getVel().y * dt));
            
            }

        }
    }
};
