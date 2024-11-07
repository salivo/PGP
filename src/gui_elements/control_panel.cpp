#include "body.hpp"
#include "raygui.h"

#include "gui_elements.hpp"
#include <chrono>
#include <cstddef>
#include <raylib.h>
#include <string>

using namespace std;
float value = 0;
bool equals = 1;
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
        CONTROL_PANEL_SLIDER_WIDTH,
        CONTROL_PANEL_SLIDER_HEIGHT,
    };
    Rectangle samples_slider = {
        speed_slider.x + speed_slider.width + CONTROL_PANEL_GAP,
        speed_slider.y,
        CONTROL_PANEL_SLIDER_WIDTH,
        CONTROL_PANEL_SLIDER_HEIGHT,
    };
    Rectangle scale_distance_slider = {
        samples_slider.x + samples_slider.width + CONTROL_PANEL_GAP,
        samples_slider.y,
        CONTROL_PANEL_SLIDER_WIDTH,
        CONTROL_PANEL_SLIDER_HEIGHT,
    };
    Rectangle scale_size_slider = {
        scale_distance_slider.x + scale_distance_slider.width + CONTROL_PANEL_GAP,
        scale_distance_slider.y,
        CONTROL_PANEL_SLIDER_WIDTH,
        CONTROL_PANEL_SLIDER_HEIGHT,
    };
    static Rectangle scale_equals_btn = {
        scale_distance_slider.x + scale_distance_slider.width + CONTROL_PANEL_GAP,
        scale_distance_slider.y,
        CONTROL_PANEL_SLIDER_HEIGHT,
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
    GuiCheckBox(scale_equals_btn,"same?",&equals);
    GuiSlider(scale_distance_slider, NULL, NULL, &scales->distance_scale, 1, 1000000);
    if (equals){
        scales->size_scale = scales->distance_scale;
        scale_equals_btn.x = scale_distance_slider.x + scale_distance_slider.width + CONTROL_PANEL_GAP;
    }
    else{
        GuiSlider(scale_size_slider, NULL, NULL, &scales->size_scale, 1, 1000000);
        scale_equals_btn.x = scale_size_slider.x + scale_size_slider.width + CONTROL_PANEL_GAP;
    }
    bool add_btn = GuiButton(adder_rect, "+");
    bool find_btn = GuiButton(find_rect, "#42#");
    if (add_btn){
        std::shared_ptr<std::string> bodyName = std::make_shared<std::string>();
        spacetasker->AddBody(Body(BodyParams({

        })), bodyName);
        while (*bodyName == "") {
            std::this_thread::sleep_for(std::chrono::microseconds(10000));  // Wait
        }
        *body_to_follow = *bodyName;
    }
    if (find_btn){
        gui_rects[RECT_FINDER] = finder_rect;
    }
}
