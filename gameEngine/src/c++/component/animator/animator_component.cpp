#include <iostream>
#include <thread>

#include "entity.h"
#include "component/animator/animator_component.h"
#include "component/render/sprite_render_component.h"

std::optional<Animation> findAnimationByName(const std::vector<Animation>& animations, const std::string& animationName)
{
  auto it = std::find_if(animations.begin(), animations.end(), [&animationName](const Animation& anim)
  {
    return anim.name == animationName;
  });

  if (it != animations.end()) { return *it; }
  return std::nullopt;
}

void AnimatorComponent::startPlaying(std::string animationName)
{
  if (keepRunning)
  {
    std::cerr << "You are trying to start animation " << animationName <<
      ", but other animation is already playing. Please stop it first." << std::endl;
    return;
  }
  std::optional<Animation> animation = findAnimationByName(animations, animationName);
  if (!animation.has_value()) { std::cerr << "Animation " << animationName << " not found." << std::endl; }
  keepRunning = true;
  worker = std::thread(&AnimatorComponent::run, this, animation.value());
}

void AnimatorComponent::stopPlaying()
{
  deleteWorker();
  spriteRenderComponent->setInitialImage();
}

void AnimatorComponent::run(Animation anim)
{
  anim.currentImage = 0; // TODO? play from start for now
  while (keepRunning)
  {
    // std::cout << "Animator does its thingy" << std::endl;
    anim.currentImage = (anim.currentImage + 1) % anim.imagePaths.size();
    spriteRenderComponent->changeImage(anim.imagePaths[anim.currentImage]);
    std::this_thread::sleep_for(std::chrono::milliseconds(anim.timesBetweenMs[anim.currentImage]));
  }
}

void AnimatorComponent::initialize()
{
  spriteRenderComponent = entity->getComponent<SpriteRenderComponent>();
  if (!spriteRenderComponent)
    throw std::runtime_error("SpriteRenderComponent not found. It is needed for AnimatorComponent to work");
}

void AnimatorComponent::deleteWorker()
{
  if (worker.joinable())
  {
    keepRunning = false;
    worker.join();
  }
}

AnimatorComponent::~AnimatorComponent() { deleteWorker(); }
