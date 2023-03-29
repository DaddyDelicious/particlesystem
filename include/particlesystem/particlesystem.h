#pragma once
#include <iostream>
#include <vector>
#include <particlesystem/emitter.h>
#include <particlesystem/effect.h>
#include <particlesystem/particle.h>

class Particlesystem {
public:

    std::vector<Emitter> emitters;
    std::vector<effect> temp1;
    glm::vec2 testPost = glm::vec2(0.0f, 0.5f);

    float dampingFactor = 0.1f;

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
        for (auto& e : emitters) {
            for (auto& p : e.getParticles()) {
                glm::vec2 blackHoleForce = calculateGravitationalForce(p, testPost, 0.001f);

                // Calculate the damping force
                glm::vec2 distanceVec = p.getPos() - testPost;
                float distance = glm::length(distanceVec);
                glm::vec2 dampingForce = -dampingFactor * distance * p.getVel();

                // Update particle's force
                p.setForce(p.getForce() + blackHoleForce + dampingForce);

                p.setAcc(glm::vec2(p.getForce().x / p.getMass(), p.getForce().y / p.getMass()));
                p.setVel(glm::vec2(p.getVel().x + p.getAcc().x * dt, p.getVel().y + p.getAcc().y * dt));
                p.setPos(glm::vec2(p.getPos().x + p.getVel().x * dt, p.getPos().y + p.getVel().y * dt));
            }
        }
    }



    glm::vec2 calculateGravitationalForce(Particle& particle, glm::vec2& blackHolePos,
                                          float blackHoleMass) {
        glm::vec2 dir = blackHolePos - particle.getPos();
        float distance = glm::length(dir);

        float distanceThreshold = 0.01f;

        if (distance < distanceThreshold) {
            return glm::vec2(0.0f, 0.0f);
        }

       /* float maxRadius = 1.0f;
        if (distance > maxRadius) {
            return glm::vec2(0.0f, 0.0f);
        }*/

        dir = glm::normalize(dir);
        float forceMagnitude = (particle.getMass() * blackHoleMass) / (distance * distance);
        glm::vec2 force = dir * forceMagnitude;
        return force;
    }



};
