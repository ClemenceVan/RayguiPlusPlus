#pragma once
#include "./RayGui++.hpp"

class text : public RayGuipp {
  private:
    Color _color;
    std::string _text;
  public: // size = {x, y, size, space}
    text(std::string text, Rectangle size, Color color = WHITE);
    ~text();
    void draw();
    void update();
    void setText(std::string text);
};

class textBox : public RayGuipp {
  private:
    std::string _prompt;
    std::string _text = "";
    Color _text_color;
    Color _box_color;
    std::function<void(std::string)> _callback;
  public:
    textBox(Rectangle size, Color box_color, Color text_color, std::function<void(std::string)> callback, std::string prompt = "prompt");
    ~textBox();
    void draw();
    void update();
    bool maj();
    std::string handle_input();
    std::string get_text();
};

class textButton : public RayGuipp {
  private:
    std::string _text;
    Color _text_color;
    Color _box_color;
    std::function<void()> _callback;
  public:
    textButton(Rectangle size, Color box_color, std::string text, Color text_color, std::function<void()> callback);
    ~textButton();
    std::string getText();
    void draw();
    void update();
};
