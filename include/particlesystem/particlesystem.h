#pragma once
#include <iostream>
#include <vector>
#include <vector>
#include <particlesystem/emitter.h>
#include <particlesystem/effect.h>

class particlesystem {
protected:
    std::vector<emitter> emitters;
    std::vector<effect> effects;
};
