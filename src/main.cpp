#include "body.hpp"
#include "gui_elements.hpp"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "space.hpp"
#include "space_tasker.hpp"
#include "thread.hpp"
#include <cstdio>
#include <string>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
using std::string;

void WorldResizing(Camera2D *camera, Space& space,
                   std::string body_to_follow, Scales scales) {
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
    Body* b = space.getBodyByName(body_to_follow);
    if (b){
        camera->target = Vector2Scale(b->getCenter(), 1.0/scales.distance_scale);
        camera->offset = (Vector2){GetRenderWidth() / 2.0f,
                                GetRenderHeight() / 2.0f};
    }
  }
}



int main ()
{
  string body_to_follow = "";
  bool drawBodyFinder = false;
  Scales scales;
  const int WindowWidth = GetMonitorWidth(GetCurrentMonitor());
  const int WindowHeight = GetMonitorHeight(GetCurrentMonitor());
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WindowWidth, WindowHeight, "PGP");
  SetExitKey(KEY_NULL);
  ToggleFullscreen();
  Camera2D camera = {0};
  camera.zoom = 1.0f;
  SetTargetFPS(120);
  Space space;
  TaskThread taskthread;
  SpaceTasker spacetasker(taskthread,space);
  this_thread::sleep_for(chrono::milliseconds(10));
  BodyParams bp = {
      .name = "body 1",
      .velocity = {0,0},
  };
  GuiElements gui(&space, &body_to_follow, &spacetasker, &scales);
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_F11)) {
      ToggleFullscreen();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
      bool can_choose = true;
      for (const auto& pair : gui.gui_rects) {
        if (CheckCollisionPointRec(GetMousePosition(), pair.second))
        can_choose = false;
      }
      if (can_choose){
        body_to_follow = space.getBodyNameByPoint(mouseWorldPos, scales);
      }
    }
    WorldResizing(&camera, space, body_to_follow, scales);
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    space.displayAll(scales);
    EndMode2D();
    gui.DrawAll();
    EndDrawing();
    }
    CloseWindow();

    return 0;
}
