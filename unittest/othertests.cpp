#include <catch2/catch_all.hpp>
#include <particlesystem/particlesystem.h>
#include <particlesystem/emitter.h>
#include <particlesystem/UniformE.h>
#include <particlesystem/SpiralE.h>
#include <glm/glm.hpp>

// Test 1: Kolla att konstruktorerna för emitters och effekter ger de skapade objekten rätt värden (som i vec2 testerna)
// Kollar också att ärvda funktioner (från emitter) fungerar
TEST_CASE("Constructor", "[UniformE]") {

    // Default constructor
    {
        UniformE* e = new UniformE{};
        REQUIRE(e->getPos() == glm::vec2{0.0f, 0.0f});
    }

    // Initialiserad konstruktor
    {
        UniformE* e = new UniformE{glm::vec2{-0.9f, 0.0f}};
        REQUIRE(e->getPos() == glm::vec2{-0.9f, 0.0f});
    }

}


// Test 2: 
TEST_CASE("Particle interaction", "[Particle]") {
    // Particle set / get position & force
    {
        Particle p;
        REQUIRE(p.getPos() == glm::vec2{0.0f, 0.0f});
        p.setPos(glm::vec2{2.0f, 2.0f});
        REQUIRE(p.getPos() == glm::vec2{2.0f, 2.0f});
        p.setForce(glm::vec2{5.0f, 5.0f});
        REQUIRE(p.getForce() == glm::vec2{5.0f, 5.0f});
    }
}

// Emitter emitting particles in a spiral pattern
TEST_CASE("angle per unit of time", "[SpiralE]") {
    // new emitter tests
    {   //                                                          + grader per ny partikel
        //Emitter(position, force, spawnRate), coneAngleDeg{angle}, angularVelocity{angularVel}

        // Given:
        SpiralE* e = new SpiralE{glm::vec2{0.0f, 0.0f}, glm::vec2{1.0f, 0.0f}, 0.5f, 0.0f, 2.0f};
        
        // When:
        // its initialized as active 

        REQUIRE(e.getAngle() == 0.f);
        
        REQUIRE(e.getAngle() == x.f); // beroende på hur snabbt den roterar per dt.

    }
}

//  Test 3(?): deklarera effekter, se till att effekterna som skapas är effekterna som deklarerades (samma med emitters)
//		       Till exempel, deklarera 2 UniformE emitters med olika argument. kolla att de är separata objekt.
