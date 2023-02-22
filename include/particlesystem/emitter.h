#pragma once
#include <glm/glm.hpp>
#include <vector>
using vec2 = glm::vec2;
class emitter {

public:
    
    vec2 getPos() { return position; }

    void setPos(vec2 newPos) { position = newPos; }

private:

    vec2 position{0.0f, 0.0f};

};


