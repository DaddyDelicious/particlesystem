#pragma once
#include <iostream>
#include <vector>
#include <particlesystem/emitter.h>
#include <particlesystem/effect.h>
#include <particlesystem/particle.h>
#include "../../../build/ExplosionE.h"
#include "../../../build/UniformE.h"
#include "../../../build/ConeE.h"
#include "../../../build/EffectB.h"
#include "../../../build/EffectW.h"
#include <rendering/window.h>
#include <memory>

class Particlesystem {
public:
    
  void addEmitter(Emitter& emitter) {
        if (auto explosionEmitter = dynamic_cast<ExplosionE*>(&emitter)) {
            // 'emitter' is an instance of ExplosionE
            std::shared_ptr<ExplosionE> explosionPtr(new ExplosionE(*explosionEmitter));
            explosionPtr->setParticles(createParticles());
            emitters.push_back(explosionPtr);
        } else if (auto uniformEmitter = dynamic_cast<UniformE*>(&emitter)) {
            // 'emitter' is an instance of UniformE
            std::shared_ptr<UniformE> uniformPtr(new UniformE(*uniformEmitter));
            uniformPtr->setParticles(createParticles());
            emitters.push_back(uniformPtr);
        } else if (auto coneEmitter = dynamic_cast<ConeE*>(&emitter)) {
            // 'emitter' is an instance of ConeE
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
            // 'effect' is an instance of EffectB
            std::shared_ptr<EffectB> blackHolePointer(new EffectB(*effectB));
            effects.push_back(blackHolePointer);
        } else if (auto effectW = dynamic_cast<EffectW*>(&effect)) {
            // 'effect' is an instance of EffectW
            std::shared_ptr<EffectW> windPointer(new EffectW(*effectW));
            effects.push_back(windPointer);
        } else {
            // 'effect' is not an instance of any known effect class
            // do something else...
        }
    }
    
    void render(rendering::Window& window, float dt) {

        for (auto& e : emitters) {

            for (auto& p : e->getParticles()) 
            {
                if (p.isAlive()) {

                    window.drawPoint(p.getPos(), p.getRad(), p.getColor());
                }
            }

            e->update(dt);
            updatePos(dt);

        }
    }

    void updatePos(float dt) {
        for (auto& e : emitters) {
            for (auto& p : e->getParticles()) {

                p.killPart(dt);

                if (p.isAlive()) {

                    glm::vec2 externalForces = calcExternalForces(p);                
                    
                    // Update particle's force
                    p.setForce(p.getForce() + externalForces);

                    p.setAcc(glm::vec2(p.getForce().x / p.getMass(), p.getForce().y / p.getMass()));
                    p.setVel(glm::vec2(p.getVel().x + p.getAcc().x * dt,
                                       p.getVel().y + p.getAcc().y * dt));
                    p.setPos(glm::vec2(p.getPos().x + p.getVel().x * dt,
                                       p.getPos().y + p.getVel().y * dt));
                }
            }
        }
    }


    glm::vec2 calcExternalForces(Particle& p) 
    {  
        glm::vec2 applyForce = glm::vec2{0.0f, 0.0f};

        for (auto& eff : effects) 
        {
            applyForce = eff->getForce();
            applyForce = eff->calculateForce(p);

        }
        return applyForce;
    }
   

    private:

    std::vector<Particle> createParticles() 
    {
        
        const size_t num_particles = 100;        
        std::vector<float> size(num_particles);
        std::vector<glm::vec4> color(num_particles);
        std::vector<float> lifetime(num_particles);

        for (size_t i = 0; i < num_particles; ++i) {
                   
            size[i] = {1.0f + rnd() * 9.0f};         // Radius between (1.0-10.0)
            color[i] = {rnd(), rnd(), rnd(), 0.5f};  // Color between (0-1) per channel, alpha = 0.5
            lifetime[i] = {0.5f + 2.0f * rnd()};     // Lifetime between (0.5-2.5) seconds
        }

        std::vector<Particle> particles(num_particles);

        for (size_t i = 0; i < particles.size(); i++) {

            particles[i].setRad(size[i]);
            particles[i].setColor(color[i]);
            
        }
    
        return particles;
    }
    
    std::vector<std::shared_ptr<Emitter>> emitters;
    
    std::vector<std::shared_ptr<Effect>> effects;
    



};
