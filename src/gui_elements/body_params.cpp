#include "raygui.h"

#include "gui_elements.hpp"
#include "calc_helper.hpp"
#include <functional>

using namespace std;

void GuiElements::draw_section(Vector2 data, TwoStrings names, TwoStrings units, ValuesSetterVector changevalue){
    static string first_draw_name;
    static int section_draw_count = 0;
    if (section_draw_count == 0){
        first_draw_name = names.s1;
    }
    if (first_draw_name == names.s1){
        section_draw_count = 0;
    }
    section_draw_count++;
    int draw_offset_from_draw_count = section_draw_count*(H3_TEXT_SIZE+BODY_PARAMS_GAP+BODY_PARAMS_SECTION_GAP);
    if (units.s2==""){
        units.s2=units.s1;
    }
    float half_width = (params_rect.width-2*BODY_PARAMS_PADDING)/2.0;
    DrawText(names.s1.c_str(),
        params_rect.x+BODY_PARAMS_PADDING,
        BODY_PARAMS_PADDING+draw_offset_from_draw_count,
        H3_TEXT_SIZE,
        WHITE);
    DrawText(names.s2.c_str(),
        params_rect.x+BODY_PARAMS_PADDING+half_width,
        BODY_PARAMS_PADDING+draw_offset_from_draw_count,
        H3_TEXT_SIZE,
        WHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, H3_TEXT_SIZE);

    bool pressed_x = GuiLabelButton({
        params_rect.x+BODY_PARAMS_PADDING,
        params_rect.y+H3_TEXT_SIZE+BODY_PARAMS_GAP+draw_offset_from_draw_count,
        half_width,
        H6_TEXT_SIZE
    }, formatWithPrefix(data.x, units.s1).c_str());
    bool pressed_y = GuiLabelButton({
        params_rect.x+half_width+BODY_PARAMS_PADDING,
        params_rect.y+H3_TEXT_SIZE+BODY_PARAMS_GAP+draw_offset_from_draw_count,
        half_width,
        H6_TEXT_SIZE
    }, formatWithPrefix(data.y, units.s2).c_str());
    if (names.s2 == ""){
        names.s2 = names.s1+" Y";
        names.s1 = names.s1+" X";
    }
    if (pressed_x){
        changervalues.value = new float(data.x);
        changervalues.name = names.s1;
        changervalues.unit = units.s1;
        changervalues.setValue = changevalue.setValueX;
    }
    if (pressed_y){
        changervalues.value = new float(data.y);
        changervalues.name = names.s2;
        changervalues.unit = units.s2;
        changervalues.setValue = changevalue.setValueY;
    }
}

void GuiElements::ShowBodyParams(Body* body){
    DrawRectangleRec(params_rect, ELEMENTS_BACKGROUND_COLOR);
    const char buffer_text[21] = "";
    bool editMode = true;
    DrawText(body->getName().c_str(),
        params_rect.x+BODY_PARAMS_PADDING,
        BODY_PARAMS_PADDING,
        H3_TEXT_SIZE,
        WHITE);
    DrawLineEx({
        .x = params_rect.x+BODY_PARAMS_PADDING,
        .y = BODY_PARAMS_PADDING*2+H2_TEXT_SIZE
    },
    {
        .x = params_rect.x+params_rect.width-BODY_PARAMS_PADDING,
        .y = BODY_PARAMS_PADDING*2+H2_TEXT_SIZE
    }, 1, WHITE);
    draw_section(body->getCenter(), {"Position"}, {"m"},
        {
            .setValueX = [this](float value){
                spacetasker->setParams(space->getBodyByName(*body_to_follow), {.center = {value, NAN}});
            },
            .setValueY = [this](float value){
                spacetasker->setParams(space->getBodyByName(*body_to_follow), {.center = {NAN, value}});
            }
        });
    draw_section(body->getVelocity(), {"Velocity"}, {"m/s"},
        {
            .setValueX = [this](float value){
                spacetasker->setParams(space->getBodyByName(*body_to_follow), {.velocity = {value, NAN}});
            },
            .setValueY = [this](float value){
                spacetasker->setParams(space->getBodyByName(*body_to_follow), {.velocity = {NAN, value}});
            }
        });
    draw_section(body->getAcceleration(), {"Acceleration"}, {"m/s^2"},
        {
        .setValueX = [this](float value){
            spacetasker->setParams(space->getBodyByName(*body_to_follow), {.acceleration = {value, NAN}});
        },
        .setValueY = [this](float value){
            spacetasker->setParams(space->getBodyByName(*body_to_follow), {.acceleration = {NAN, value}});
        }
    });
    draw_section({body->getMass(), body->getRadius()}, {"Mass", "Radius"}, {"g", "m"},
        {
        .setValueX = [this](float value){
            spacetasker->setParams(space->getBodyByName(*body_to_follow), {.mass = value});
        },
        .setValueY = [this](float value){
            spacetasker->setParams(space->getBodyByName(*body_to_follow), {.radius = value});
        }
    });
    bool delete_body = GuiButton({
        params_rect.x + BODY_PARAMS_DEL_BTN_MARGIN,
        params_rect.y + params_rect.height - BODY_PARAMS_DEL_BTN_SIZE - BODY_PARAMS_DEL_BTN_MARGIN,
        BODY_PARAMS_DEL_BTN_SIZE,
        BODY_PARAMS_DEL_BTN_SIZE
    }, "#143#");
    if (delete_body ){
        spacetasker->DelBody(*body_to_follow);
        *body_to_follow = "";
    }
}
