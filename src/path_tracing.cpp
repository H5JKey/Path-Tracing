#include "path_tracing.h"
#include <iostream>


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

    Sphere newSphere;
    Box newBox;

    bool addBox = false;
    bool addSphere = false;


    while (window.isOpen()) {
        ellapsed = clock.restart();
        programmTime += ellapsed;
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape) {
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
            if (ImGui::Button("Add new box"))
                addBox = true;
            if (ImGui::Button("Add new sphere"))
                addSphere = true;


        }
        if (addBox || addSphere) {
            ImGui::Begin("New object"); {
                if (addSphere) {
                    //Material

                    Material material = newSphere.getMaterial();
                    ImGui::Checkbox("Light emission", &material.lightEmitter);
                    ImGui::SliderFloat("Diffuseness", &material.diffuseness, 0, 1);
                    ImGui::SliderFloat("Opacity", &material.opacity, 0, 5);
                    sf::Vector3f color = material.color;
                    float color_array[3] = { color.x, color.y,color.z };
                    ImGui::ColorPicker3("Color", color_array);

                    material.color = { color_array[0],color_array[1],color_array[2] };

                   newSphere.setMaterial(material);

                    //Position and size
                    sf::Vector3f position =newSphere.getPosition();
                    if (ImGui::Button("Copy player's position"))
                        position = player.getPosition();
                    float position_array[3] = { position.x,position.y,position.z };
                    ImGui::InputFloat3("Position", position_array);
                   newSphere.setPosition(sf::Vector3f(position_array[0], position_array[1], position_array[2]));

                    float size =newSphere.getSize();
                    ImGui::InputFloat("Size", &size);
                   newSphere.setSize(size);

                   ImGui::Separator();
                   if (ImGui::Button("Add")) {
                       world.addNewSphere(newSphere);
                       render.resetFrames();
                       addSphere = false;
                   }
                   if (ImGui::Button("Exit"))
                       addSphere = false;
                }
                else {
                    //Material

                    Material material = newBox.getMaterial();
                    ImGui::Checkbox("Light emission", &material.lightEmitter);
                    ImGui::SliderFloat("Diffuseness", &material.diffuseness, 0, 1);
                    ImGui::SliderFloat("Opacity", &material.opacity, 0, 5);
                    sf::Vector3f color = material.color;
                    float color_array[3] = { color.x, color.y,color.z };
                    ImGui::ColorPicker3("Color", color_array);

                    material.color = { color_array[0],color_array[1],color_array[2] };

                    newBox.setMaterial(material);

                    //Position and size

                    sf::Vector3f position = newBox.getPosition();
                    if (ImGui::Button("Copy player's position"))
                        position = player.getPosition();
                    float position_array[3] = { position.x,position.y,position.z };

                    ImGui::InputFloat3("Position", position_array);
                    newBox.setPosition(sf::Vector3f(position_array[0], position_array[1], position_array[2]));

                    sf::Vector3f size = newBox.getSize();
                    float size_array[3] = { size.x,size.y,size.z };
                    ImGui::InputFloat3("Size", size_array);
                    newBox.setSize(sf::Vector3f(size_array[0], size_array[1], size_array[2]));


                    ImGui::Separator();
                    if (ImGui::Button("Add")) {
                        world.addNewBox(newBox);
                        render.resetFrames();
                        addBox = false;
                    }
                    if (ImGui::Button("Exit"))
                        addBox = false;
                }
            }

        }

        if (selectedBox || selectedSphere) {
            ImGui::Begin("Object");
            {
                if (selectedSphere) {
                    //Material

                    Material material = selectedSphere->getMaterial();
                    if (ImGui::Checkbox("Light emission", &material.lightEmitter))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Diffuseness", &material.diffuseness, 0, 1))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Opacity", &material.opacity, 0, 5))
                        render.resetFrames();
                    sf::Vector3f color = material.color;
                    float color_array[3] = { color.x, color.y,color.z };
                    ImGui::ColorPicker3("Color", color_array);
                    if (color.x!=color_array[0] || color.y != color_array[1] || color.z != color_array[2])
                        render.resetFrames();
                    material.color = { color_array[0],color_array[1],color_array[2] };

                    selectedSphere->setMaterial(material);

                    //Position and size
                    sf::Vector3f position = selectedSphere->getPosition();
                    float position_array[3] = { position.x,position.y,position.z };
                    if (ImGui::InputFloat3("Position", position_array))
                        render.resetFrames();
                    selectedSphere->setPosition(sf::Vector3f(position_array[0], position_array[1], position_array[2]));
                    
                    float size = selectedSphere->getSize();
                    if (ImGui::InputFloat("Size", &size))
                        render.resetFrames();
                    selectedSphere->setSize(size);

                    ImGui::Separator();

                    if (ImGui::Button("Delete")) {
                        render.resetFrames();
                        for (int i = 0; i < world.getSpheres().size(); i++) {
                            if (&world.getSpheres()[i] == selectedSphere) {
                                world.getSpheres().erase(world.getSpheres().begin() + i);
                                break;
                            }
                        }
                    }
                    if (ImGui::Button("Exit")) {
                        selectedSphere = nullptr;
                    }
                }
                else {
                    //Material

                    Material material = selectedBox->getMaterial();
                    if (ImGui::Checkbox("Light emission", &material.lightEmitter))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Diffuseness", &material.diffuseness, 0, 1))
                        render.resetFrames();
                    if (ImGui::SliderFloat("Opacity", &material.opacity, 0, 5))
                        render.resetFrames();
                    sf::Vector3f color = material.color;
                    float color_array[3] = { color.x, color.y,color.z };
                    ImGui::ColorPicker3("Color", color_array);
                    if (color.x != color_array[0] || color.y != color_array[1] || color.z != color_array[2])
                        render.resetFrames();
                    material.color = { color_array[0],color_array[1],color_array[2] };

                    selectedBox->setMaterial(material);

                    //Position and size
                    sf::Vector3f position = selectedBox->getPosition();
                    float position_array[3] = { position.x,position.y,position.z };
                    if (ImGui::InputFloat3("Position", position_array))
                        render.resetFrames();
                    selectedBox->setPosition(sf::Vector3f(position_array[0], position_array[1], position_array[2]));

                    sf::Vector3f size = selectedBox->getSize();
                    float size_array[3] = { size.x,size.y,size.z };
                    if (ImGui::InputFloat3("Size", size_array))
                        render.resetFrames();
                    selectedBox->setSize(sf::Vector3f(size_array[0], size_array[1], size_array[2]));

                    ImGui::Separator();

                    if (ImGui::Button("Delete")) {
                        render.resetFrames();
                        for (int i = 0; i < world.getBoxes().size(); i++) {
                            if (&world.getBoxes()[i] == selectedBox) {
                                world.getBoxes().erase(world.getBoxes().begin() + i);
                                break;
                            }
                        }
                    }
                    if (ImGui::Button("Exit")) {
                        selectedBox = nullptr;
                    }
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

