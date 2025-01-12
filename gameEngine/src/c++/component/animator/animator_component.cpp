#include <iostream>
#include <thread>

#include "entity.h"
#include "component/animator/animator_component.h"
#include "component/render/sprite_render_component.h"

void AnimatorComponent::run()
{
  while (keepRunning)
  {
    std::cout << "Animator does its thingy" << std::endl;
    currentImage = (currentImage + 1) % imagePaths.size();
    spriteRenderComponent->changeImage(imagePaths[currentImage]);
    std::this_thread::sleep_for(std::chrono::milliseconds(timesBetweenMs[currentImage]));
  }
}

void AnimatorComponent::initialize()
{
  spriteRenderComponent = entity->getComponent<SpriteRenderComponent>();
  if (!spriteRenderComponent)
    throw std::runtime_error("SpriteRenderComponent not found. It is needed for AnimatorComponent to work");
  keepRunning = true;
  worker = std::thread(&AnimatorComponent::run, this);
}

AnimatorComponent::~AnimatorComponent()
{
  if (worker.joinable())
  {
    keepRunning = false;
    worker.join();
  }
}
