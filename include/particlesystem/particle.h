#pragma once
#include <glm/glm.hpp>
#include <vector>


class Particle {
public: 

    Particle() 
    { 
        position = glm::vec2{0.0f, 0.0f};
        velocity = glm::vec2{0.0f, 0.0f};
        acceleration = glm::vec2{0.0f, 0.0f};
        color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
        radius = 10.0f;
        time = 1.0f;
       
        
    }


glm::vec2 getPos() { return position; }

void setPos(glm::vec2 newPos) { position = newPos; }

void setAcc(glm::vec2 newAcc) { acceleration = newAcc; }

void setRad(float setRad) { radius = setRad; }

float getRad() { return radius; }

glm::vec4 getColor() { return color; }

void setColor(glm::vec4 colorArg) { color = colorArg; }




private:

	glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    glm::vec4 color;
    
    float radius;
    float time;
 
};

  


