#pragma once
#include <glm/glm.hpp>
#include <particlesystem/particle.h>

using vec2 = glm::vec2;

class effect {
public:
    void virtual applyEffect(Particle){};

	vec2 getPos() { 
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

private:
	vec2 position;
	float radius;
};
