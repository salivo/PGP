
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <cstdio>
#include <string>
#include "bodies.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui_elements.hpp"

using std::string;
void WorldResizing(Camera2D *camera, Bodies *bodies,
                   std::string body_to_follow) {
  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / camera->zoom);
    camera->target = Vector2Add(camera->target, delta);
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);
    if (body_to_follow == "") {
      camera->offset = GetMousePosition();
    }
    camera->target = mouseWorldPos;
    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
    if (wheel < 0)
      scaleFactor = 1.0f / scaleFactor;
    camera->zoom = Clamp(camera->zoom * scaleFactor, 0.01f, 100.0f);
  }
  if (body_to_follow != "") {
    camera->target = bodies->getBodyByName(body_to_follow)->center;
    camera->offset = (Vector2){GetRenderWidth() / 2.0f,
                               GetRenderHeight() / 2.0f};
  }
}

int main ()
{
  string body_to_follow = "";
  bool drawBodyFinder = false;
  const int WindowWidth = GetMonitorWidth(GetCurrentMonitor());
  const int WindowHeight = GetMonitorHeight(GetCurrentMonitor());
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WindowWidth, WindowHeight, "PGP");
  SetExitKey(KEY_NULL);
  ToggleFullscreen();
  Camera2D camera = {0};
  camera.zoom = 1.0f;
  SetTargetFPS(120);


  Bodies bodies;
  GuiElements gui_elem;
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_F11)) {
      ToggleFullscreen();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
      bool can_choose = true;
      for (const auto& pair : gui_elem.gui_rects) {
        if (CheckCollisionPointRec(GetMousePosition(), pair.second))
        can_choose = false;
      }
      if (can_choose){
        printf("%s\n",bodies.getBodyNameByPoint(mouseWorldPos).c_str());
        body_to_follow = bodies.getBodyNameByPoint(mouseWorldPos);
      }
    }
    WorldResizing(&camera, &bodies, body_to_follow);
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    bodies.drawAll();
    EndMode2D();
    gui_elem.DrawAll(&bodies, &body_to_follow);
    EndDrawing();
    }
    CloseWindow();

    return 0;
}
