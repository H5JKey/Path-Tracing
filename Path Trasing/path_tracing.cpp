#include "path_tracing.h"
#include <iostream>
#include "lib/imgui/imgui-SFML.h"
#include "lib/imgui/imgui.h"


PathTracingProgramm::PathTracingProgramm():window(sf::VideoMode(), "Path Tracing", sf::Style::Fullscreen),
                                           render(),
                                           player(sf::Vector3f(7,7,7))
{
    render.init(window);
    ImGui::SFML::Init(window);

    
}

void PathTracingProgramm::update() {
    clock.restart();
    rotating = true;

    Sphere* selectedSphere=nullptr;
    Box* selectedBox = nullptr;

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
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                float distSphere = 0;
                float distBox = 0;
                selectedSphere = player.getSphereLookingAt(world,distSphere);
                selectedBox = player.getBoxLookingAt(world, distBox);
                if (selectedSphere && selectedBox)
                    if (distSphere > distBox)
                        selectedSphere = nullptr;
                    else
                        selectedBox = nullptr;
            }

        }
        ImGui::SFML::Update(window, ellapsed);
        ImGui::Begin("Menu", nullptr);
        {
            ImGui::SliderInt("Samples", &render.settings.samples,1,64);
            ImGui::SliderInt("Reflections", &render.settings.reflections,1,32);
        }
        if (selectedBox || selectedSphere) {
            ImGui::Begin("Object");
            {
                if (selectedSphere) {
                    if (ImGui::Checkbox("Light emission", &selectedSphere->getMaterial().lightEmitter))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Diffuseness", &selectedSphere->getMaterial().diffuseness, 0, 1))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Opacity", &selectedSphere->getMaterial().opacity, 0, 5))
                        render.resetFrames();
                    sf::Vector3f color = selectedSphere->getMaterial().color;
                    float color_array[3] = { color.x, color.y,color.z };
                    ImGui::ColorPicker3("Color", color_array);
                    if (color.x!=color_array[0] || color.y != color_array[1] || color.z != color_array[2])
                        render.resetFrames();
                    selectedSphere->getMaterial().color = { color_array[0],color_array[1],color_array[2] };
                }
                else {
                    if (ImGui::Checkbox("Light emission", &selectedBox->getMaterial().lightEmitter))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Diffuseness", &selectedBox->getMaterial().diffuseness, 0, 1))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Opacity", &selectedBox->getMaterial().opacity, 0, 5))
                        render.resetFrames();
                    sf::Vector3f color = selectedBox->getMaterial().color;
                    float color_array[3] = { color.x, color.y,color.z };
                    ImGui::ColorPicker3("Color", color_array);
                    if (color.x != color_array[0] || color.y != color_array[1] || color.z != color_array[2])
                        render.resetFrames();
                    selectedBox->getMaterial().color = { color_array[0],color_array[1],color_array[2] };

                }
            }
        }
      
        ImGui::End();
        bool moved1= player.update(ellapsed);
        bool moved2 = false;
        if (rotating) 
            moved2 = player.rotate(window);

        if (moved1 || moved2) {
            render.resetFrames();
        }
        render.setShaderUniforms(player, world, sf::Vector2f(window.getSize()), programmTime);


        window.clear();
        render(window);
        ImGui::SFML::Render(window);
        window.display();

    }

}

PathTracingProgramm::~PathTracingProgramm() {
    ImGui::SFML::Shutdown();
}

