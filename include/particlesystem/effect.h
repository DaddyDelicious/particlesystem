#pragma once
#include <glm/glm.hpp>
#include <particlesystem/particle.h>
//


class Effect {
public:

	   Effect(glm::vec2 pos = {0.0f, 0.0f}, float rad = 0.0f, glm::vec2 frc = {0.0f, 0.0f})
        : position{pos}
        , force{frc}
        , radius{rad}
         {}
    
	virtual glm::vec2 calculateForce(Particle& particle) {
               
		return particle.getForce();
    
	}

	glm::vec2& getForce() { return force; }

    void setForce(glm::vec2 newForce) { force = newForce; }

	glm::vec2& getPos() { 
		return position;
	}

	void setPos(glm::vec2 newPos) { 
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
  
};
