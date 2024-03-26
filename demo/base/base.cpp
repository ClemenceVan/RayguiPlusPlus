#include "raylib.h"
#include "RayGui++.hpp"
#include <iostream>

Font font;

void main() {
    InitWindow(800, 450, "RayGui++ Basic example");
    SetTargetFPS(60);

    Scene *_scene = new Scene();
    _scene->add(new textButton({25, 200, 175, 50}, WHITE, "Hello world", BLACK, [](){
        std::cout << "Hello World !!!" << std::endl;
    }));

    while (!WindowShouldClose()) {
        _scene->update();
        BeginDrawing();

            ClearBackground(RAYWHITE);
            _scene->draw();

        EndDrawing();
    }
    CloseWindow();
}