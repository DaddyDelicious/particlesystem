#pragma once
#include <glm/glm.hpp>
#include <vector>
using vec2 = glm::vec2;

class particle {
public: 
vec2 position;
vec2 velocity;
vec2 acceleration;
float radius = 1.0f;
//Color partColor;

vec2 getPos() { return position; }

void setPos(vec2 newPos) { position = newPos; }




private:
};

//
//
//struct Color {
//    constexpr Color() = default;
//    constexpr Color(float r, float g, float b) : r(r), g(g), b(b) {}
//
//    float r = 1.0f;
//    float g = 1.0f;
//    float b = 1.0f;
//};
//
