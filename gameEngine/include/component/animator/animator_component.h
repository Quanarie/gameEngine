#ifndef ANIMATOR_COMPONENT_H
#define ANIMATOR_COMPONENT_H

#include <string>
#include <thread>
#include <vector>

#include "component/component.h"

class SpriteRenderComponent;

// TODO uses spriterender component directly. Maybe spawn a little spriteRenderCOmponent for itself
// TODO And then no need for user to create spriterendercomponent with empty path, more logical.
// TODO: but also maybe animatorRenderComponent? Or AnimatorController, AnimationController? AnimationControllerComponent
class AnimatorComponent : public Component
{
public:
  void initialize() override;

  AnimatorComponent(const std::vector<std::string>& imgs, std::vector<int> tmsBetweenMs) : imagePaths(imgs),
    timesBetweenMs(tmsBetweenMs) {}

  ~AnimatorComponent() override;

private:
  const std::vector<std::string> imagePaths;
  int currentImage = -1;
  std::vector<int> timesBetweenMs;
  std::atomic<bool> keepRunning;
  std::thread worker;

  SpriteRenderComponent* spriteRenderComponent;

  void run();
};

#endif //ANIMATOR_COMPONENT_H
