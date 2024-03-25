#pragma once
#include "Elements.hpp"

// text class implementation

text::text(std::string text, Rectangle size, Color color) : RayGuipp(size) {
    _color = color;
    _text = text;
}

text::~text() {
    // Text elements don't require destruction
}

void text::draw(){
    DrawTextEx(font, _text.c_str(), Vector2{getSize().x, getSize().y}, getSize().width, getSize().height, _color);
}

void text::update() {
    // Text elements don't require updating
}

void text::setText(std::string text) {
    _text = text;
}



// textbox class implementation

textbox::textbox(Rectangle size, Color box_color, Color text_color, std::function<void(std::string)> callback, std::string prompt) : RayGuipp(size) {
    _text_color = text_color;
    _box_color = box_color;
    _callback = callback;
    _prompt = prompt;
}

textbox::~textbox() {
    // Textbox elements don't require destruction
}

void textbox::draw() {
    DrawRectangleRec(getSize(), _box_color);
    DrawTextEx(font, (_prompt + _text + (is_focused() ? "_" : "")).c_str(), Vector2{getSize().x + 4, getSize().y}, 25, 1, WHITE);
}

void textbox::update() {
    if (is_focused()) {
        std::string tmp = handle_input();
        if (tmp != "")
            _callback(tmp);
    }
}

bool textbox::maj() {
    return IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
}

std::string textbox::handle_input() {
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
}

std::string textbox::get_text() {
    return _text;
}




// textButton class implementation

textButton::textButton(Rectangle size, Color box_color, std::string text, Color text_color, std::function<void()> callback) : RayGuipp(size) {
    _text = text;
    _text_color = text_color;
    _box_color = box_color;
    _callback = callback;
}

textButton::~textButton() {
    // TextButton elements don't require destruction
}

std::string textButton::getText() {
    return _text;
}

void textButton::draw() {
    DrawRectangleRec(getSize(), _box_color);
    DrawTextEx(font, _text.c_str(), Vector2{getSize().x + 4, getSize().y + getSize().height - 25}, 25, 1, _text_color);
}

void textButton::update() {
    if (isActive() && CheckCollisionPointRec(GetMousePosition(), getSize()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        _callback();
}