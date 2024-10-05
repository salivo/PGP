#include "raygui.h"
#include "gui_elements.hpp"
#include "space.hpp"
#include <raylib.h>

using namespace std;




void GuiElements::DrawAll(){
    gui_rects[RECT_CTRL_PANEL] = control_panel_rect;
    ShowControlPanel();
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
        std::string chosen_body = ShowBodyFinder();
        if (chosen_body != ""){
            if (chosen_body != EXIT_WITHOUT_CHOOSING) {
                (*body_to_follow) = chosen_body;
            }
            gui_rects.erase(RECT_FINDER);
        }
    }
    if ((*body_to_follow) != ""){
        ShowBodyParams(space->getBodyByName(*body_to_follow));
        gui_rects[RECT_PARAMS] = params_rect;
        control_panel_rect.width = GetRenderWidth() - params_rect.width - 2*CONTROL_PANEL_MARGIN;
    }
    else {
        gui_rects.erase(RECT_PARAMS);
        control_panel_rect.width = GetRenderWidth() - 2*CONTROL_PANEL_MARGIN;
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
