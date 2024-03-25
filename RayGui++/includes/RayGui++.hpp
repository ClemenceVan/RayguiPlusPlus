#pragma once
#include "raylib.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

extern Font font; // THIS IS TO BE CHANGED TO A DIFFERENT SYSTEM
/**
 * @brief Class used to create an RayGuipp in the server
 * 
 */
class RayGuipp {
  public:
    RayGuipp(Rectangle size) { _size = size; };
    virtual void draw() = 0;
    virtual void update() = 0;
    Rectangle getSize() { return _size; };
    bool isActive() { return _active; };
    void setActive(bool active) { _active = active; };
    bool is_focused() { return _focused; };
    void setFocused(bool focused) {
        if (focused && _onFocus)
            _onFocus();
        if (!focused && _onUnfocus)
            _onUnfocus();
        _focused = focused;
    };
    bool hoover() { return _hoovered; };
    void setHoover(bool hoovered) {
        if (hoovered && !_hoovered)
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (!hoovered && _hoovered)
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (hoovered != _hoovered)
            _hoovered = hoovered;
    };
    void onFocus(std::function<void()> function) { _onFocus = function; };
    void onUnfocus(std::function<void()> function) { _onUnfocus = function; };
    std::string *getId() { return &_id; };
    void setId(std::string id) { _id = id; };
    std::vector<std::string> *getClass() { return &_class; };
    void addClass(std::string class_) { _class.push_back(class_); };
    void setPos(Vector2 pos) {
        _size.x = pos.x;
        _size.y = pos.y;
    };
    Vector2 getPos() { return {_size.x, _size.y}; };

  private:
    // interface *parent;
    Rectangle _size;
    bool _active = true;
    bool _focused = false;
    bool _hoovered = false;

    std::function<void()> _onFocus;
    std::function<void()> _onUnfocus;

    std::string _id;
    std::vector<std::string> _class;
};

class interface {
  public:
    interface(){};
    ~interface(){};
    RayGuipp *add(RayGuipp *element) {
        _elements.push_back(element);
        return element;
    };
    void remove(RayGuipp *element) {
        for (auto it = _elements.begin(); it != _elements.end(); it++) {
            if (*it == element) {
                _elements.erase(it);
                break;
            }
        }
    };
    void draw() {
        for (auto &element : _elements)
            element->draw();
    };
    void update() {
        check_focused();
        for (auto &element : _elements)
            element->update();
    };
    void unfocus() {
        for (auto &element : _elements)
            if (element->is_focused())
                element->setFocused(false);
    };
    void focus(RayGuipp *element) {
        unfocus();
        element->setFocused(true);
    };
    RayGuipp *getFocused() {
        for (auto &element : _elements)
            if (element->is_focused())
                return element;
        return nullptr;
    };
    void check_focused() {
        for (auto &elem : _elements)
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(GetMousePosition(), elem->getSize()))
                    elem->setFocused(true);
                else
                    elem->setFocused(false);
            } else {
                if (CheckCollisionPointRec(GetMousePosition(), elem->getSize()))
                    elem->setHoover(true);
                else
                    elem->setHoover(false);
            }
    };
    RayGuipp *getId(std::string id) {
        for (auto &element : _elements)
            if (element->getId() && *element->getId() == id)
                return element;
        return nullptr;
    };
    std::vector<RayGuipp *> getClass(std::string class_) {
        std::vector<RayGuipp *> elements;
        for (auto &element : _elements)
            for (auto &elem_class : *element->getClass())
                if (elem_class == class_)
                    elements.push_back(element);
        return elements;
    };

  private:
    std::vector<RayGuipp *> _elements;
};

class text : public RayGuipp {
  public: // size = {x, y, size, space}
    text(std::string text, Rectangle size, Color color = WHITE) : RayGuipp(size) {
        _color = color;
        _text = text;
    };
    ~text(){};
    void draw() { DrawTextEx(font, _text.c_str(), Vector2{getSize().x, getSize().y}, getSize().width, getSize().height, _color); };
    void update(){};
    void setText(std::string text) { _text = text; };

  private:
    Color _color;
    std::string _text;
};

class textbox : public RayGuipp {
  public:
    textbox(Rectangle size, Color box_color, Color text_color, std::function<void(std::string)> callback, std::string prompt = "prompt")
        : RayGuipp(size) {
        _text_color = text_color;
        _box_color = box_color;
        _callback = callback;
        _prompt = prompt;
    };
    ~textbox(){};
    void draw() {
        DrawRectangleRec(getSize(), _box_color);
        DrawTextEx(font, (_prompt + _text + (is_focused() ? "_" : "")).c_str(), Vector2{getSize().x + 4, getSize().y}, 25, 1, WHITE);
    };
    void update() {
        if (is_focused()) {
            std::string tmp = handle_input();
            if (tmp != "")
                _callback(tmp);
        }
    }
    bool maj() { return IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT); }
    std::string handle_input() {
        int key = GetKeyPressed();
        std::string tmp;
        if (key == KEY_SPACE)
            _text += " ";
        else if (key >= 32 && key <= 90) // alphabetical keys
            _text += maj() ? (char)key : (char)key + 32;
        else if (key >= 320 && key <= 329) // numerical keys
            _text += (char)key - 272;
        else if (key > 90 && key < 125)
            _text += (char)key;
        else if (key == KEY_ENTER || key == KEY_KP_ENTER) {
            tmp = _text;
            _text = "";
            return tmp;
        }
        if (key == KEY_BACKSPACE)
            if (_text.length() > 0)
                _text = _text.substr(0, _text.length() - 1);
        return "";
    };
    std::string get_text() { return _text; };

  private:
    std::string _prompt;
    std::string _text = "";
    Color _text_color;
    Color _box_color;
    std::function<void(std::string)> _callback;
};

class textButton : public RayGuipp {
  public:
    textButton(Rectangle size, Color box_color, std::string text, Color text_color, std::function<void()> callback) : RayGuipp(size) {
        // getSize() = size;
        _text = text;
        _text_color = text_color;
        _box_color = box_color;
        _callback = callback;
    };
    ~textButton(){};
    std::string getText() { return _text; };
    void draw() {
        DrawRectangleRec(getSize(), _box_color);
        DrawTextEx(font, _text.c_str(), Vector2{getSize().x + 4, getSize().y + getSize().height - 25}, 25, 1, _text_color);
    };
    void update() {
        if (isActive() && CheckCollisionPointRec(GetMousePosition(), getSize()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            _callback();
    };

  private:
    std::string _text;
    Color _text_color;
    Color _box_color;
    std::function<void()> _callback;
};
