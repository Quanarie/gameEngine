#include "component/animator/animator_component.h"

#include <entity.h>
#include <iostream>
#include <thread>
#include <component/render/sprite_render_component.h>

void AnimatorComponent::run()
{
  while (this->keepRunning)
  {
    std::cout << "Animator does its thingy" << std::endl;
    if (this->spriteRenderComponent)
      this->spriteRenderComponent->changeImage(imagePaths[++currentImage % imagePaths.size()]);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

AnimatorComponent::AnimatorComponent(
  const std::vector<std::string>& imgs/*, std::vector<int> tmsBetweenMs*/) : imagePaths(imgs) /*,
  timesBetweenMc(tmsBetweenMs)*/
{
  worker = std::thread(&AnimatorComponent::run, this);
  keepRunning = true;
}

void AnimatorComponent::initialize()
{
  this->spriteRenderComponent = this->entity->getComponent<SpriteRenderComponent>();
}

AnimatorComponent::~AnimatorComponent()
{
  if (worker.joinable())
  {
    keepRunning = false;
    worker.join();
  }
}
