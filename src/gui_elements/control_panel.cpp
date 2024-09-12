#include "raygui.h"

#include "gui_elements.hpp"
#include <cstddef>
#include <raylib.h>

using namespace std;
float value = 0;
void GuiElements::ShowControlPanel(){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    DrawRectangleRec(control_panel_rect, ELEMENTS_BACKGROUND_COLOR);
    Rectangle playpause_rect = {
        control_panel_rect.x + CONTROL_PANEL_PADDING,
        control_panel_rect.y + CONTROL_PANEL_PADDING,
        control_panel_rect.height - 2*CONTROL_PANEL_PADDING,
        control_panel_rect.height - 2*CONTROL_PANEL_PADDING
    };
    Rectangle speed_slider = {
        playpause_rect.x + control_panel_rect.height - 2*CONTROL_PANEL_PADDING + CONTROL_PANEL_GAP,
        control_panel_rect.y + control_panel_rect.height/2 - (float)CONTROL_PANEL_SLIDER_HEIGHT/2,
        100,
        CONTROL_PANEL_SLIDER_HEIGHT,
    };
    Rectangle samples_slider = {
        speed_slider.x + speed_slider.width + CONTROL_PANEL_GAP,
        speed_slider.y,
        100,
        CONTROL_PANEL_SLIDER_HEIGHT,
    };
    Rectangle adder_rect = {
        control_panel_rect.x + control_panel_rect.width - control_panel_rect.height + CONTROL_PANEL_PADDING,
        control_panel_rect.y + CONTROL_PANEL_PADDING,
        control_panel_rect.height - 2*CONTROL_PANEL_PADDING,
        control_panel_rect.height - 2*CONTROL_PANEL_PADDING
    };
    Rectangle find_rect = {
        adder_rect.x - CONTROL_PANEL_GAP - control_panel_rect.height + 2*CONTROL_PANEL_PADDING,
        control_panel_rect.y + CONTROL_PANEL_PADDING,
        control_panel_rect.height - 2*CONTROL_PANEL_PADDING,
        control_panel_rect.height - 2*CONTROL_PANEL_PADDING
    };
    bool playpause_btn = GuiButton(playpause_rect, "#131#");
    GuiSlider(speed_slider, NULL, NULL, &value, 0, 100);
    GuiSlider(samples_slider, NULL, NULL, &value, 0, 100);
    bool add_btn = GuiButton(adder_rect, "+");
    bool find_btn = GuiButton(find_rect, "#42#");
    if (add_btn){
        // TODO: add body
    }
    if (find_btn){
        gui_rects[RECT_FINDER] = finder_rect;
    }
}
