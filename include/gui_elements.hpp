#ifndef GUI_ELEMENTS_HPP
#define GUI_ELEMENTS_HPP

#include "process_bodies.hpp"
#include <raylib.h>
#include <string>
#include <map>

#define ELEMENTS_BACKGROUND_COLOR (Color){15, 15, 15, 230}
#define ELEMENTS_ACCENT_COLOR (Color){5, 100, 30, 255}
#define ELEMENTS_FOCUS_COLOR (Color){40, 122, 62, 255}

#define H2_TEXT_SIZE 30
#define H3_TEXT_SIZE 24
#define H6_TEXT_SIZE 16

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

enum{FINDER,PARAMS};

struct TwoStrings {
    std::string s1 = "";
    std::string s2 = "";
};

class GuiElements{
private:
    Rectangle finder_rect{FINDER_MARGIN, FINDER_MARGIN, FINDER_WIDTH+2*FINDER_PADDING, 0};
    Rectangle params_rect = {
      (float)(GetRenderWidth()-GetRenderWidth()*BODY_PARAMS_WIDTH_PERCENT),
      0,
      (float)(GetRenderWidth() * BODY_PARAMS_WIDTH_PERCENT),
      (float)GetRenderHeight()};
    void ShowBodyParams(Body* Body);
    std::string ShowBodyFinder(Bodies* bodies);
public:
    std::map<int, Rectangle> gui_rects;
    void DrawAll(Bodies* bodies, std::string* body_to_folow);
    GuiElements();
};





#endif
