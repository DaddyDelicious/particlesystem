#pragma once
#include <glm/glm.hpp>
#include <particlesystem/particle.h>
//////
using vec2 = glm::vec2;
//
class Effect {
public:

	Effect(){
		position = glm::vec2{0.0f, 0.0f};
		force = glm::vec2{0.0f, 0.0f};
		radius = 0.0001f;
        effectRate = 0.04f;
        time_since_last_spawn = 0.0f;  
	}
    
	virtual glm::vec2 calculateForce(Particle& particle) {
               
		return glm::vec2(0.0f, 0.0f);
        }

	glm::vec2& getForce() { return force; }

    void setForce(glm::vec2 newForce) { force = newForce; }

	glm::vec2& getPos() { 
		return position;
	}

	void setPos(vec2 newPos) { 
	position = newPos;
	}

	float getRadius() { 
		return radius;
	}

	void setRadius(float newRadius) {
		radius = newRadius;
	}

	

	protected:
	glm::vec2 position;
    glm::vec2 force;
	float radius;
    float effectRate;
    float time_since_last_effect;
};
