#include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>

#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

#include <particlesystem/particle.h>
#include <particlesystem/emitter.h>
//
// Simple random functions to get started
// Random float (0,1)
//float rnd() { return rand() / static_cast<float>(RAND_MAX); }
//
//// Random float (-1,1)
//float srnd() { return rnd() * 2.0f - 1.0f; }

int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);


    double prevTime = 0.0;
    float speed = 1.0f;
    bool running = true;
    float spawnRate = 0.5f;

    Particlesystem test;
    test.addEmitter(1, glm::vec2(0.0f, -0.5f));
    test.addEmitter(2, glm::vec2(-1.0f, 0.0f));
    test.addEmitter(3, glm::vec2(0.0f, 0.0f));

    //test.addEffect(1, glm::vec2(0.0f, 0.5f));
    test.addEffect(2, glm::vec2(0.0f, 0.5f));
    
    //test.emitters.push_back(test2Emitter);
    //
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

            
       
        test.render(window, dt);
         
        
        // UI
        {
            window.beginGuiWindow("UI");
            window.text("I'm text!");
            window.sliderFloat("Speed", speed, 0.001f, 10.0f);
            window.sliderFloat("SpawnRate", spawnRate, 0.001f, 1.0f);

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
