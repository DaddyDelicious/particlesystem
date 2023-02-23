#pragma once
#include <glm/glm.hpp>
#include <vector>
using vec2 = glm::vec2;

class Particle {
public: 

    Particle() 
    { 
        position = vec2{0.0f, 0.0f};
        velocity = vec2{0.0f, 0.0f};
        acceleration = vec2{0.0f, 0.0f};
        color = glm::vec4(1.0f, 1.0f, 1.0f, 1.5f);
        radius = 10.0f;
        time = 1.0f;
       
        
    }


vec2 getPos() { return position; }

void setPos(vec2 newPos) { position = newPos; }

void setAcc(vec2 newAcc) { acceleration = newAcc; }

void setRad(float setRad) { radius = setRad; }

float getRad() { return radius; }

glm::vec4 getColor() { return color; }

void setColor(glm::vec4 colorArg) { color = colorArg; }




private:

	vec2 position;
    vec2 velocity;
    vec2 acceleration;

    glm::vec4 color;
    
    float radius;
    float time;
 
};

  


