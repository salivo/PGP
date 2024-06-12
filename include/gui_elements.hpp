#ifndef GUI_ELEMENTS_HPP
#define GUI_ELEMENTS_HPP

#include "process_bodies.hpp"
#include <raylib.h>
#include <string>
#include <map>
#define BODY_PARAMS_WIDTH_PERCENT 0.3
#define BODY_PARAMS_PADDING 16
#define BODY_PARAMS_TEXT_SIZE 24

#define FINDER_MARGIN 20
#define FINDER_GAP 20
#define FINDER_TEXT_SIZE 16
#define FINDER_TEXT_PADDING 14
#define FINDER_WIDTH 150

#define EXIT_WITHOUT_CHOOSING "IWANTJUSTEXITPLEASELEAVEME" // I now that it isn't good solution

enum{FINDER,PARAMS};

class GuiElements{
private:
    Rectangle finder_rect{FINDER_MARGIN, FINDER_MARGIN, FINDER_WIDTH, 0};
    Rectangle params_rect = {
      (float)(GetRenderWidth()-GetRenderWidth()*BODY_PARAMS_WIDTH_PERCENT),
      0, 
      (float)(GetRenderWidth() / BODY_PARAMS_WIDTH_PERCENT),
      (float)GetRenderHeight()};
    void ShowBodyParams(Body* Body);
    std::string ShowBodyFinder(Bodies* bodies);
public:
    std::map<int, Rectangle> gui_rects;
    void DrawAll(Bodies* bodies, std::string* body_to_folow);
};





#endif