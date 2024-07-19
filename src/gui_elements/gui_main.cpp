#include "raygui.h"

#include "gui_elements.hpp"

using namespace std;

GuiElements::GuiElements(){
      GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, ColorToInt(ELEMENTS_ACCENT_COLOR));
      GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, ColorToInt(BLACK));
      GuiSetStyle(DEFAULT, BORDER_WIDTH, 2);
      GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt(ELEMENTS_ACCENT_COLOR));
      GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(ELEMENTS_FOCUS_COLOR));
}

void GuiElements::DrawAll(Bodies* bodies, std::string* body_to_folow){
    if (changervalues.value != nullptr){
        ShowParamsChanger();
        gui_rects[RECT_CHANGER] = changer_rect;
    }
    else{
        if (gui_rects.find(RECT_CHANGER) != gui_rects.end()){
            gui_rects.erase(RECT_CHANGER);
        }
    }
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F)) {
        gui_rects[RECT_FINDER] = finder_rect;
    }
    if (gui_rects.find(RECT_FINDER) != gui_rects.end()){
        std::string choosed_body = ShowBodyFinder(bodies);
        if (choosed_body != ""){
            if (choosed_body != EXIT_WITHOUT_CHOOSING) {
                (*body_to_folow) = choosed_body;
            }
            gui_rects.erase(RECT_FINDER);
        }
    }
    if ((*body_to_folow) != ""){
        ShowBodyParams(bodies->getBodyByName(*body_to_folow));
        gui_rects[RECT_PARAMS] = params_rect;
    }
    else {
        gui_rects.erase(RECT_PARAMS);
    }
}
void GuiElements::disableBodyChoosing(){
    gui_rects[RECT_ALL] = render_rect;
}

void GuiElements::enableBodyChoosing(){
    if (gui_rects.find(RECT_ALL) != gui_rects.end()){
        gui_rects.erase(RECT_ALL);
    }
}
bool GuiElements::isBodyChoosingEnabled(){
    if (gui_rects.find(RECT_ALL) != gui_rects.end()){
        return false;
    }
    return true;
}