#ifndef GUI_ELEMENTS_HPP
#define GUI_ELEMENTS_HPP

#include "process_bodies.hpp"
#include <raylib.h>
#include <string>
#include <map>

#define ELEMENTS_BACKGROUND_COLOR (Color){15, 15, 15, 230}
#define ELEMENTS_BACKGROUND_COLOR2 (Color){20, 20, 20, 245}
#define ELEMENTS_ACCENT_COLOR (Color){5, 100, 30, 255}
#define ELEMENTS_FOCUS_COLOR (Color){40, 122, 62, 255}

#define H2_TEXT_SIZE 30
#define H3_TEXT_SIZE 24
#define H4_TEXT_SIZE 20
#define H6_TEXT_SIZE 16

#define CONTROL_PANEL_RADIUS 30
#define CONTROL_PANEL_MARGIN 24

#define CHANGER_WIDTH_PERCENT 0.25
#define CHANGER_HEIGHT 150
#define CHANGER_BUTTON_HEIGHT 35
#define CHANGER_PADDING 12
#define CHANGER_GAP 14
#define CHANGER_BUFFER 32
#define CHANGER_UNIT_PREFIX_WIDTH 50
#define CHANGER_ARROW_PADDING 14

#define BODY_PARAMS_WIDTH_PERCENT 0.3
#define BODY_PARAMS_PADDING 16
#define BODY_PARAMS_SECTION_GAP 16
#define BODY_PARAMS_GAP 26

#define FINDER_MARGIN 20
#define FINDER_PADDING 10
#define FINDER_GAP 20
#define FINDER_TEXT_PADDING 14
#define FINDER_WIDTH 150
#define FINDER_ROUNDING 0.05

#define EXIT_WITHOUT_CHOOSING "IWANTJUSTEXITPLEASELEAVEME" // I know that it isn't good solution

enum{RECT_FINDER,RECT_PARAMS,RECT_CHANGER,RECT_ALL,RECT_CTRL_PANEL};

struct TwoStrings {
    std::string s1 = "";
    std::string s2 = "";
};
struct ChangerValues{
    float* value = nullptr;
    std::string unit = "";
    std::string name = "";
};

class GuiElements{
private:
    Rectangle finder_rect{FINDER_MARGIN, FINDER_MARGIN, FINDER_WIDTH+2*FINDER_PADDING, 0};
    Rectangle params_rect = {
      (float)(GetRenderWidth()-GetRenderWidth()*BODY_PARAMS_WIDTH_PERCENT),
      0,
      (float)(GetRenderWidth() * BODY_PARAMS_WIDTH_PERCENT),
      (float)GetRenderHeight()};
    Rectangle changer_rect = {
        static_cast<float>((GetRenderWidth()-GetRenderWidth()*CHANGER_WIDTH_PERCENT)*0.5),
        static_cast<float>((GetRenderHeight()-CHANGER_HEIGHT)*0.5),
        static_cast<float>(GetRenderWidth()*CHANGER_WIDTH_PERCENT),
        CHANGER_HEIGHT,
    };
    Rectangle control_panel_rect = {
        CONTROL_PANEL_MARGIN,
        (float)GetRenderHeight()-CONTROL_PANEL_MARGIN-2*CONTROL_PANEL_RADIUS,
        2*CONTROL_PANEL_RADIUS,
        2*CONTROL_PANEL_RADIUS
    };
    Rectangle render_rect = {0, 0, (float)GetRenderWidth(), (float)GetRenderHeight()};
    ChangerValues changervalues;
    void draw_section(Vector2 &data, TwoStrings names, TwoStrings units);
    void ShowBodyParams(Body* Body);
    void ShowParamsChanger();
    void ShowControlPanel(Bodies* bodies);
    std::string ShowBodyFinder(Bodies* bodies);

public:
    std::map<int, Rectangle> gui_rects;
    void DrawAll(Bodies* bodies, std::string* body_to_folow);
    void disableBodyChoosing();
    void enableBodyChoosing();
    bool isBodyChoosingEnabled();
    GuiElements();
};





#endif
