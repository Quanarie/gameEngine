#ifndef ANIMATOR_COMPONENT_H
#define ANIMATOR_COMPONENT_H

#include <string>
#include <thread>
#include <vector>

#include "component/component.h"

class SpriteRenderComponent;

class AnimatorComponent : public Component
{
public:
  void initialize() override;
  AnimatorComponent(const std::vector<std::string>& imgs/*, std::vector<int> tmsBetweenMs*/);
  ~AnimatorComponent() override;

private:
  const std::vector<std::string> imagePaths;
  int currentImage = -1;
  std::vector<int> timesBetweenMc;
  std::atomic<bool> keepRunning;
  std::thread worker;

  SpriteRenderComponent* spriteRenderComponent;

  void run();
};

#endif //ANIMATOR_COMPONENT_H
