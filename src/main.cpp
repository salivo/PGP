
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <cstddef>
#include <string>
#include "process_bodies.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui_elements.hpp"

using std::string;

void WorldResizing(Camera2D *camera, Bodies *bodies,
                   std::string body_to_folow) {
  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / camera->zoom);
    camera->target = Vector2Add(camera->target, delta);
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);
    if (body_to_folow == "") {
      camera->offset = GetMousePosition();
    }
    camera->target = mouseWorldPos;
    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
    if (wheel < 0)
      scaleFactor = 1.0f / scaleFactor;
    camera->zoom = Clamp(camera->zoom * scaleFactor, 0.01f, 100.0f);
  }
  if (body_to_folow != "") {
    camera->target = bodies->getBodyByName(body_to_folow)->center;
    camera->offset = (Vector2){GetMonitorWidth(GetCurrentMonitor()) / 2.0f,
                               GetMonitorHeight(GetCurrentMonitor()) / 2.0f};
  }
}
int main ()
{
  string body_to_folow = "";
  const int WindowWidth = GetMonitorWidth(GetCurrentMonitor());
  const int WindowHeight = GetMonitorHeight(GetCurrentMonitor());
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WindowWidth, WindowHeight, "PGP");
  ToggleFullscreen();
  Camera2D camera = {0};
  camera.zoom = 1.0f;
  SetTargetFPS(60);

  Bodies bodies;
  bodies.addBody(Body("body1", {1, 0}, {1, 0}, {0, 0}, 10.0f));
  bodies.addBody(Body("body2", {0, 100}, {0, 0}, {0, 0}, 10.0f));
  bodies.addImpulseToBody(bodies.getBodyByName("body1"), {0, 1});
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_F11)) {
      ToggleFullscreen();
    }

    WorldResizing(&camera, &bodies, body_to_folow);
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    bodies.drawAll();
    EndMode2D();
    string choosed_body = ShowBodyFinder(&bodies);
    if (choosed_body != ""){
        body_to_folow = choosed_body;
    }
    
    EndDrawing();
    }
    CloseWindow();

    return 0;
}