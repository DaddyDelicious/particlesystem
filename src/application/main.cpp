#include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>

#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

#include <particlesystem/particle.h>
#include <particlesystem/emitter.h>

// Simple random functions to get started
// Random float (0,1)
float rnd() { return rand() / static_cast<float>(RAND_MAX); }

// Random float (-1,1)
float srnd() { return rnd() * 2.0f - 1.0f; }

int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);

    // --- EXAMPLE SNIPPET ---
    const size_t num_particles = 100;
    std::vector<glm::vec2> position(num_particles);
    std::vector<float> size(num_particles);
    std::vector<glm::vec4> color(num_particles);
    std::vector<float> lifetime(num_particles);

    for (size_t i = 0; i < num_particles; ++i) {
        position[i] = {srnd(), srnd()};          // Position between (-1,1) = Screen extent
        size[i] = {1.0f + rnd() * 9.0f};         // Radius between (1.0-10.0)
        color[i] = {rnd(), rnd(), rnd(), 0.5f};  // Color between (0-1) per channel, alpha = 0.5
        lifetime[i] = {0.5f + 2.0f * rnd()};     // Lifetime between (0.5-2.5) seconds
    }
//
    std::vector<Particle> particles(num_particles);
    std::vector<Particle> particles1(num_particles);

    for (int i = 0; i < particles.size(); i++) {

        particles[i].setRad(size[i]);
        particles[i].setColor(color[i]);
        particles[i].setLifeTime(lifetime[i]);
        
    }
 
    particles1 = particles;

    double prevTime = 0.0;
    float speed = 1.0f;
    bool running = true;

    Emitter testEmitter;
    Emitter test2Emitter;
    
    testEmitter.setPos(vec2(0.1f, 0.1f));    
    testEmitter.setParticles(particles);
    testEmitter.emitterActive(true);

    test2Emitter.setPos(vec2(0.5f, 0.5f));
    test2Emitter.setParticles(particles1);
    test2Emitter.emitterActive(true);

    test2Emitter.setForce(glm::vec2(0.1f, -0.1f));
    

    Particlesystem test;
    test.emitters.push_back(testEmitter);
    test.emitters.push_back(test2Emitter);

    while (running) {
        window.beginFrame();

        const double t = window.time();
        const double dt = t - prevTime;
        prevTime = t;

        // Create some global smooth rocking motion
        const glm::vec2 vel =
            glm::vec2{static_cast<float>(std::cos(t)), -static_cast<float>(std::abs(std::sin(t)))} *
            0.2f;

        {
            ZoneScopedN("Update particles");

            // Simulation dt may differ from actual dt based on the simulation speed
            const float sim_dt = static_cast<float>(dt) * speed;

            //for (size_t i = 0; i < num_particles; ++i) {
            //    // Apply per particle jitter
            //    const glm::vec2 jitter = glm::vec2(srnd(), srnd()) * 1.0f;
            //    position[i] += (vel + jitter) * sim_dt;
            //    color[i].a = std::min(color[i].a, lifetime[i]);  // Modify alpha based on lifetime
            //    lifetime[i] -= sim_dt;

            //    // Check lifetime and reset if needed
            //    if (lifetime[i] < 0.0f) {
            //        position[i] = {srnd(), srnd()};
            //        color[i] = {rnd(), rnd(), rnd(), 1.0f};
            //        size[i] = {1.0f + rnd() * 9.0f};
            //        lifetime[i] = {0.5f + 2.0f * rnd()};
            //    }
            //}
        }

        // Clear screen with color
        window.clear({0, 0, 0, 1});

        // Draw particles
         //window.drawPoint(testParticle.getPos(), testParticle.getRad(), testParticle.getColor());
        
         //testEmitter.spawnParticles(window,dt);
        test.render(window, dt);
        
        // UI
        {
            window.beginGuiWindow("UI");
            window.text("I'm text!");
            window.sliderFloat("Speed", speed, 0.001f, 10.0f);
            if (window.button("Close application")) {
                running = false;
            }
            window.endGuiWindow();
        }

        window.endFrame();
        running = running && !window.shouldClose();
    }

    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}
