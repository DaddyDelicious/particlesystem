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
   

    void addEmitter(Emitter& emitter) {

          //We use shared_ptr because of problem with object slicing. 
          //Not efficient because we use copyconstructor. Dunno how to fix it.
        if (auto explosionEmitter = dynamic_cast<ExplosionE*>(&emitter)) {
            // 'emitter' is an instance of ExplosionE
            // create a new shared pointer to an ExplosionE object
            std::shared_ptr<ExplosionE> explosionPtr(new ExplosionE(*explosionEmitter));
            // set the particles for the new object
            explosionPtr->setParticles(createParticles());
            // add the new object to the emitters vector
            emitters.push_back(explosionPtr);

        } else if (auto uniformEmitter = dynamic_cast<UniformE*>(&emitter)) {
            //Same but for UniformE
            std::shared_ptr<UniformE> uniformPtr(new UniformE(*uniformEmitter));           
            uniformPtr->setParticles(createParticles());            
            emitters.push_back(uniformPtr);

        } else if (auto coneEmitter = dynamic_cast<ConeE*>(&emitter)) {
            //Same but for coneE
            std::shared_ptr<ConeE> conePtr(new ConeE(*coneEmitter));          
            conePtr->setParticles(createParticles());           
            emitters.push_back(conePtr);

        } else {
            // 'emitter' is not an instance of any of the three classes
            // do something else...
        }
    }



  void addEffect(Effect& effect) {
        if (auto effectB = dynamic_cast<EffectB*>(&effect)) {
            //Works the same as addEmitter()
            std::shared_ptr<EffectB> blackHolePointer(new EffectB(*effectB));
            effects.push_back(blackHolePointer);

        } else if (auto effectW = dynamic_cast<EffectW*>(&effect)) {
            
            std::shared_ptr<EffectW> windPointer(new EffectW(*effectW));
            effects.push_back(windPointer);
        } else {
            // 'effect' is not an instance of any known effect class
            // do something else...
        }
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

    
    std::vector<std::shared_ptr<Emitter>> emitters;
    
    std::vector<std::shared_ptr<Effect>> effects;
    



};
