#pragma once
#include <glm/glm.hpp>
#include <vector>


class Particle {
public: 

    Particle() 
    { 
        acceleration = glm::vec2(0.0f, 0.0f);
        position = glm::vec2{0.0f, 0.0f};
        velocity = glm::vec2{0.0f, 0.0f};
        force = glm::vec2{0.0f, 0.0f};
        mass = 1.0f;
        color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
        radius = 10.0f;
        lifeTime = 1.0f;
       
        
    }
    
void setAcc(glm::vec2 ac) { acceleration = ac; }

glm::vec2 getAcc() { return acceleration; }

glm::vec2 getPos() { return position; }

void setPos(glm::vec2 newPos) { position = newPos; }

glm::vec2 getVel() { return velocity; }

void setVel(glm::vec2 newVel) { velocity = newVel; }

glm::vec2 getForce() { return force; }

void setForce(glm::vec2 newForce) { force = newForce; }

void setMass(float newMass) {mass = newMass;}

float getMass() { return mass; }

void setLifeTime(float newLife) { lifeTime = newLife; }

float getLifeTime() { return lifeTime; }

void setRad(float setRad) { radius = setRad; }

float getRad() { return radius; }

glm::vec4 getColor() { return color; }

void setColor(glm::vec4 colorArg) { color = colorArg; }




private:

    glm::vec2 acceleration;
	glm::vec2 position;
    glm::vec2 velocity;    
    glm::vec2 force;
    float mass;
    glm::vec4 color;
    
    float radius;
    float lifeTime;

 
};

  


