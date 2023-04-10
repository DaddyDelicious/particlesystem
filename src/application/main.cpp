#include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>

#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

#include <particlesystem/particle.h>
#include <particlesystem/emitter.h>


int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);


    double prevTime = 0.0;
    float speed = 1.0f;
    bool running = true;
    float spawnRate = 0.5f;

    Particlesystem particleSystem;

    UniformE emitter1{glm::vec2{-0.9f,0.0f}};
    ExplosionE emitter2{glm::vec2{0.0f, 0.0f}};
    ConeE emitter3{glm::vec2{0.0f, -0.5f}};

    EffectB effect1{glm::vec2{0.0f, 0.0f}};
    EffectW effect2{glm::vec2{0.0f, 1.0f}, glm::vec2{0.0f, -0.10f}};
    

    particleSystem.addEmitter(emitter1);
    particleSystem.addEmitter(emitter2);
    particleSystem.addEmitter(emitter3);
   
    particleSystem.addEffect(effect1);
    particleSystem.addEffect(effect2);
   
 
    while (running) {
        window.beginFrame();

        const double t = window.time();
        const double dt = t - prevTime;
        prevTime = t;

     

        {
            ZoneScopedN("Update particles");

            // Simulation dt may differ from actual dt based on the simulation speed
            const float sim_dt = static_cast<float>(dt) * speed;

        }
        
        // Clear screen with color
        window.clear({0, 0, 0, 1});

            
       
        particleSystem.render(window, dt);
         
        
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
