#include "path_tracing.h"
#include <iostream>
#include "lib/imgui/imgui-SFML.h"
#include "lib/imgui/imgui.h"


PathTracingProgramm::PathTracingProgramm():render(1920,1680),
                                           window(sf::VideoMode(1920, 1680), "Path Tracing"), 
                                           boxes(0),
                                           spheres(0),
                                           player(sf::Vector3f(7,7,7)) 
{
    ImGui::SFML::Init(window);

    boxes.push_back(Box(
        sf::Vector3f{ 5.5-20,25.5,94.7 },
        sf::Vector3f{ 40,40,0.2 },
        sf::Vector3f{ 1,1,1},
    0,0,true));

    boxes.push_back(Box(
        sf::Vector3f{ -100,-1,-100 },
        sf::Vector3f{ 200,1,200 },
        sf::Vector3f{ 1,1,1 },
    0.8,0, false));

    boxes.push_back(Box(
        sf::Vector3f{ 7,0,7 },
        sf::Vector3f{ 3,6,3 },
        sf::Vector3f{ 0.5,0.5,0.5 },
        0.99,0, false));

   /* boxes.push_back(Box(
        sf::Vector3f{ 0,0,15 },
        sf::Vector3f{ 15,15,0.4 },
        sf::Vector3f{ 1,0,0 },
        0.8,0, false));*/

    boxes.push_back(Box(
        sf::Vector3f{ 0,0,0 },
        sf::Vector3f{ 15,15,0.4 },
        sf::Vector3f{ 0,0,1 },
        0.8,0, false));

    boxes.push_back(Box(
        sf::Vector3f{ 15,0,0 },
        sf::Vector3f{ 0.4,15,15 },
        sf::Vector3f{ 1,0,0 },
        0.8,0, false));

    boxes.push_back(Box(
        sf::Vector3f{ 0,0,0 },
        sf::Vector3f{ 0.4,15,15 },
        sf::Vector3f{ 0,1,0 },
        1,0, false));


    boxes.push_back(Box(
        sf::Vector3f{ 0,15,0 },
        sf::Vector3f{ 15,0.4,15 },
        sf::Vector3f{ 1,1,1 },
        1,0, false));

    spheres.push_back(Sphere(
        sf::Vector3f{ 9,7,9 },
        1.0,
        sf::Vector3f{ 0.5,0.5,0.5 },
        0.99, 0.5, false));
    
}

void PathTracingProgramm::update() {
    clock.restart();
    rotating = true;
    while (window.isOpen()) {
        ellapsed = clock.restart();
        programmTime += ellapsed;
        sf::Event event;
        ImGui::SFML::ProcessEvent(event);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Tab) {
                rotating = !rotating;
            }

        }
        ImGui::SFML::Update(window, ellapsed);
        ImGui::Begin("Menu", nullptr);
        {
            ImGui::SliderInt("Samples", &render.settings.samples,1,64);
            ImGui::SliderInt("Reflections", &render.settings.reflections,1,32);
        }
        ImGui::End();
        bool moved1= player.update(ellapsed);
        bool moved2 = false;
        if (rotating) 
            moved2 = player.rotate(window);

        if (moved1 || moved2) {
            render.resetFrames();
        }
        render.setShaderUniforms(player,boxes,spheres, sf::Vector2f(window.getSize()), programmTime);


        window.clear();
        render(window);
        ImGui::SFML::Render(window);
        window.display();

    }

}

PathTracingProgramm::~PathTracingProgramm() {
    ImGui::SFML::Shutdown();
}

