#pragma once
//
#include <particlesystem/effect.h>

class EffectB : public Effect
{
public:
    EffectB(glm::vec2 pos = { 0.0f, 0.0f }, float mass = 0.001f, float rad = 1.5f) : Effect(pos, rad), mass{mass} {
       
    }

private:
	float mass;
    

    glm::vec2 calculateForce(Particle& particle) override {

        glm::vec2 dir = position - particle.getPos();
        float distance = glm::length(dir);
        float distanceThreshold = 0.02f;

        //Don't calculate if the distance is too small (Inside black hole)
        if (distance < distanceThreshold) {
            return glm::vec2(0.0f, 0.0f);
        }
        //
        if (distance > radius) {
            return glm::vec2(0.0f, 0.0f);
        }

        dir = glm::normalize(dir);
        float forceMagnitude = (particle.getMass() * mass) / (distance * distance);
        glm::vec2 forceB = dir * forceMagnitude;
        return forceB;
    }
};

