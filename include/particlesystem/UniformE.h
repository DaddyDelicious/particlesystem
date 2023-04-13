#pragma once
#include <particlesystem/emitter.h>


class UniformE : public Emitter
{
	public:
		UniformE(glm::vec2 position = { 0.0f, 0.0f }, glm::vec2 force = { 0.5f, 0.5f }, float spawnRate = 0.5f) : Emitter(position, force, spawnRate) 
		{}


    
};

