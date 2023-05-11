#include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>

#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

#include <particlesystem/particle.h>
#include <particlesystem/emitter.h>
#include <particlesystem/SpiralE.h>


int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);


    double prevTime = 0.0;
    float speed = 1.0f;
    bool running = true;
    

    Particlesystem particleSystem;

    UniformE* emitter1 = new UniformE{glm::vec2{-0.9f,0.0f}};
    ExplosionE* emitter2 = new ExplosionE{glm::vec2{0.0f, -0.1f},false};
    ConeE* emitter3 = new ConeE{glm::vec2{0.0f, -0.5f}};
    SpiralE* emitter4 = new SpiralE{glm::vec2{0.0f, 0.0f}};

    //EffectB* effect1 = new EffectB{glm::vec2{0.5f, -0.5f}};
    //EffectW* effect2 = new EffectW{glm::vec2{0.0f, 0.6f}, glm::vec2{-10.1f, 0.0f}};
    

   /* particleSystem.addEmitter(emitter1);
    particleSystem.addEmitter(emitter2);
    particleSystem.addEmitter(emitter3);*/
    particleSystem.addEmitter(emitter4);
  /*
    particleSystem.addEffect(effect1);
    particleSystem.addEffect(effect2);
   */
   
 
    while (running) {

        window.beginFrame();

        const double t = window.time();
        const double dt = t - prevTime;
        prevTime = t;

     

        {
            ZoneScopedN("Update particles");

            // Simulation dt may differ from actual dt based on the simulation speed
            const float sim_dt = static_cast<float>(dt) * speed;
            (void)sim_dt;
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
