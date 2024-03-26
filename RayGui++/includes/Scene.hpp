#pragma once
#include "./RayGui++.hpp"

class Scene {
    private:
        std::vector<RayGuipp *> _elements;
        Font _font;

    public:
        Scene();
        ~Scene();
        RayGuipp *add(RayGuipp *element);
        Font getFont();
        void remove(RayGuipp *element);
        void draw();
        void update();
        void unfocus();
        void focus(RayGuipp *element);
        RayGuipp *getFocused();
        void check_focused();
        RayGuipp *getId(std::string id);
        std::vector<RayGuipp *> getClass(std::string class_);
};