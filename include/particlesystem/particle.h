#pragma once
#include <glm/glm.hpp>
#include <vector>

class Particle {
public: 

  Particle()
        : acceleration(0.0f, 0.0f)
        , position(0.0f, 0.0f)
        , velocity(0.0f, 0.0f)
        , force(0.0f, 0.0f)
        , mass(5.0f)
        , color(1.0f, 1.0f, 1.0f, 0.5f)
        , radius(10.0f)
        , lifeTime(20.0f)
        , alive(true) {}

    
bool isAlive() { return alive;  }

void setAcc(glm::vec2 ac) { acceleration = ac; }

glm::vec2 getAcc() { return acceleration; }

glm::vec2& getPos() { return position; }

void setPos(glm::vec2 newPos) { position = newPos; }

glm::vec2 getVel() { return velocity; }

void setVel(glm::vec2 newVel) { velocity = newVel; }

glm::vec2& getForce() { return force; }

void setForce(glm::vec2 newForce) { force = newForce; }

void setMass(float newMass) {mass = newMass;}

float getMass() { return mass; }

void setLifeTime(double newLife) { lifeTime = newLife; }

double getLifeTime() { return lifeTime; }

void setRad(float setRad) { radius = setRad; }

float getRad() { return radius; }

glm::vec4 getColor() { return color; }

void setColor(glm::vec4 colorArg) { color = colorArg; }

void killPart(double dt) 
{        

    lifeTime -= dt;

    if (lifeTime < 0) {

       alive = false;
    } 
    
}


private:

    glm::vec2 acceleration;
	glm::vec2 position;
    glm::vec2 velocity;    
    glm::vec2 force;
    float mass;
    glm::vec4 color;    
    float radius;
    double lifeTime;
    bool alive;

 
};

  

