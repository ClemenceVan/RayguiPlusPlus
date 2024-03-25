#pragma once
#include "./RayGui++.hpp"

class Scene {
  public:
    Scene();
    ~Scene();
    RayGuipp *add(RayGuipp *element);
    void remove(RayGuipp *element);
    void draw();
    void update();
    void unfocus();
    void focus(RayGuipp *element);
    RayGuipp *getFocused();
    void check_focused();
    RayGuipp *getId(std::string id);
    std::vector<RayGuipp *> getClass(std::string class_);

  private:
    std::vector<RayGuipp *> _elements;
};