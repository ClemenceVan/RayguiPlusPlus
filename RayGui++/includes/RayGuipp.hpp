#pragma once
#include "RayGui++.hpp"
class Scene;
/**
 * @brief Class used to create an RayGuipp in the server
 * 
 */
class RayGuipp {
  private:
    Rectangle _size;
    Scene *_parent;
    bool _active = true;
    bool _focused = false;
    bool _hovered = false;

    std::function<void()> _onFocus;
    std::function<void()> _onUnfocus;

    std::string _id;
    std::vector<std::string> _class;
  public:
    RayGuipp(Rectangle size);

    virtual void draw() = 0;
    virtual void update() = 0;

    void setParent(Scene *parent);
    Scene *getParent();
    Font getFont();
    Rectangle getSize();
    bool isActive();
    void setActive(bool active);
    bool is_focused();
    void setFocused(bool focused);
    bool hover();
    void setHover(bool hovered);
    void onFocus(std::function<void()> function);
    void onUnfocus(std::function<void()> function);
    std::string *getId();
    void setId(std::string id);
    std::vector<std::string> *getClass();
    void addClass(std::string class_);
    void setPos(Vector2 pos);
    Vector2 getPos();
};