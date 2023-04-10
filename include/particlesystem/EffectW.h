#pragma once
#include <particlesystem/effect.h>
class EffectW :
    public Effect
{
//
    public:
        EffectW(glm::vec2 pos = { 0.0f, 0.0f }, glm::vec2 frc = { 0.0f, 0.1f }, float radius = 0.2f) : Effect(pos, radius, frc) {}


private:

    glm::vec2 calculateForce(Particle& particle) override {
        glm::vec2 dir = position - particle.getPos();
        float distance = glm::length(dir);

        if (distance > radius) {
            return glm::vec2(0.0f, 0.0f);
        }

        dir = glm::normalize(dir);
        float forceMagnitude = (particle.getMass()) / (distance * distance);
        glm::vec2 forceReturn = dir * forceMagnitude*force;

  
        return forceReturn;
    }
};

