#pragma once
#include <iostream>
#include <vector>
#include <particlesystem/emitter.h>
#include <particlesystem/effect.h>
#include <particlesystem/particle.h>
#include <particlesystem/ExplosionE.h>
#include <particlesystem/UniformE.h>
#include <particlesystem/ConeE.h>
#include <particlesystem/EffectB.h>
#include <particlesystem/EffectW.h>
#include <rendering/window.h>
#include <memory>


class Particlesystem {
public:
   

    void addEmitter(Emitter* emitter) {

        emitter->setParticles(createParticles());
        emitters.push_back(emitter);

    }



  void addEffect(Effect* effect) {

        effects.push_back(effect);
    }
    
    void render(rendering::Window& window, const double dt) {
        // iterate over all emitters
        for (auto& e : emitters) {
            // iterate over all particles in the current emitter
            for (auto& p : e->getParticles()) {
                // if the particle is alive, draw it on the window
                if (p.isAlive()) {
                    window.drawPoint(p.getPos(), p.getRad(), p.getColor());
                }
            }
            // update the current emitter's state
            e->update(dt);            
            updatePos(dt);
        }
    }



    private:

       void updatePos(const double dt) {
        // iterate over all emitters
        for (auto& e : emitters) {
            // iterate over all particles in the current emitter
            for (auto& p : e->getParticles()) {
                // kill particle if it is no longer alive
                p.killPart(dt);
               
                // if particle is still alive, update its position
                if (p.isAlive()) {
                    // calculate external forces acting on the particle
                    glm::vec2 externalForces = calcExternalForces(p);
                   
                    // update particle's force
                    p.setForce(p.getForce() + externalForces);
                    // update particle's acceleration
                    p.setAcc(glm::vec2(p.getForce().x / p.getMass(), p.getForce().y / p.getMass()));
                    // update particle's velocity
                    p.setVel(glm::vec2(p.getVel().x + p.getAcc().x * dt,
                                       p.getVel().y + p.getAcc().y * dt));
                    // update particle's position
                    p.setPos(glm::vec2(p.getPos().x + p.getVel().x * dt,
                                       p.getPos().y + p.getVel().y * dt));
                }
            }
        }
        }

    //
    glm::vec2 calcExternalForces(Particle& p) {
        // initialize a zero vector to represent the net force acting on the particle
        glm::vec2 applyForce{0.0f, 0.0f};
        // iterate over all effects
        for (auto& eff : effects) {
           
            // calculate the force to apply to the current particle based on the current effect
            applyForce += eff->calculateForce(p);
        }
        // return the net force vector acting on the particle
        return applyForce;
        }



    std::vector<Particle> createParticles() {
        // set the number of particles to create
        const size_t num_particles = 100;

        // initialize vectors to store particle properties
        std::vector<float> size(num_particles);       // size of each particle
        std::vector<glm::vec4> color(num_particles);  // color of each particle
       

        // generate random properties for each particle
        for (size_t i = 0; i < num_particles; ++i) {
            size[i] = {1.0f + rnd() * 9.0f};  // set radius between (1.0-10.0)
            color[i] = {rnd(), rnd(), rnd(), 0.5f};  // set color between (0-1) per channel, alpha = 0.5
            
        }

        // create a vector to store the particles
        std::vector<Particle> particles(num_particles);

        // set the properties for each particle
        for (size_t i = 0; i < particles.size(); i++) {
            particles[i].setRad(size[i]);           // set particle radius
            particles[i].setColor(color[i]);        // set particle color
           
        }

        // return the vector of particles
        return particles;
        }

    
    std::vector<Emitter*> emitters;
    
    std::vector<Effect*> effects;
    



};
