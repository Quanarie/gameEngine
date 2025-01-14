#ifndef ANIMATOR_COMPONENT_H
#define ANIMATOR_COMPONENT_H

#include <string>
#include <thread>
#include <vector>

#include "component/component.h"

struct Animation
{
  std::string name;
  std::vector<std::string> imagePaths;
  std::vector<int> timesBetweenMs;
  int currentImage = -1;
};

class SpriteRenderComponent;

class AnimatorComponent : public Component
{
public:
  void initialize() override;

  AnimatorComponent(const std::vector<Animation>& anmts) : animations(anmts) {}

  ~AnimatorComponent() override;

  void startPlaying(std::string animationName);
  void stopPlaying();
  bool isPlaying() { return keepRunning; }

private:
  std::vector<Animation> animations;
  std::atomic<bool> keepRunning = false;
  std::thread worker;

  SpriteRenderComponent* spriteRenderComponent;

  void run(Animation anim);
  void deleteWorker();
};

#endif //ANIMATOR_COMPONENT_H
