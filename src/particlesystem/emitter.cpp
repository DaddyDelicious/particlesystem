#include <particlesystem/emitter.h>

float rnd() { return rand() / static_cast<float>(RAND_MAX); }

float srnd() { return rnd() * 2.0f - 1.0f; }