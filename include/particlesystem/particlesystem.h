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
   

    void render(rendering::Window& window, const double dt) {
        for (auto& emitter : emitters) {
            emitter.update(window, dt, *this);
        }
    }

    void updatePos(Particle& arg, glm::vec2 force,  float dt) {
        arg.setAcc(glm::vec2(force.x / arg.getMass(), force.y / arg.getMass()));
        arg.setVel(glm::vec2(arg.getVel().x + arg.getAcc().x * dt, arg.getVel().y + arg.getAcc().y * dt));       
        arg.setPos(glm::vec2(arg.getPos().x + arg.getVel().x * dt, arg.getPos().y + arg.getVel().y * dt));
    }
};
