#include "raygui.h"

#include "gui_elements.hpp"
#include "calc_helper.hpp"

using namespace std;

void GuiElements::draw_section(Vector2 &data, TwoStrings names, TwoStrings units){
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
        changervalues.value = &(data.x);
        changervalues.name = names.s1;
        changervalues.unit = units.s1;
    }
    if (pressed_y){
        changervalues.value = &(data.y);
        changervalues.name = names.s2;
        changervalues.unit = units.s2;
    }
}

void GuiElements::ShowBodyParams(Body* Body){
    DrawRectangleRec(params_rect, ELEMENTS_BACKGROUND_COLOR);
    const char buffer_text[21] = "";
    bool editMode = true;
    DrawText(Body->name.c_str(),
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
    draw_section(Body->center, {"Position"}, {"m"});
    draw_section(Body->velocity, {"Velocity"}, {"m/s"});
    draw_section(Body->acceleration, {"Acceleration"}, {"m/s^2"});
    draw_section(Body->massradius, {"Mass", "Radius"}, {"g", "m"});
    bool delete_body = GuiButton({
        params_rect.x + params_rect.width - BODY_PARAMS_DEL_BTN_SIZE - BODY_PARAMS_DEL_BTN_MARGIN,
        params_rect.y + params_rect.height - BODY_PARAMS_DEL_BTN_SIZE - BODY_PARAMS_DEL_BTN_MARGIN,
        BODY_PARAMS_DEL_BTN_SIZE,
        BODY_PARAMS_DEL_BTN_SIZE
    }, "#143#");
    if (delete_body){
        bodies->deleteBody(Body);
    }
}
