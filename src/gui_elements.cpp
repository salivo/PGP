
#include "raygui.h"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <raylib.h>
#include <string>
#include <vector>

#include "gui_elements.hpp"
#include "process_bodies.hpp"
#include "calc_helper.hpp"

using namespace std;


GuiElements::GuiElements(){
      GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, ColorToInt(ELEMENTS_ACCENT_COLOR));
      GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, ColorToInt(BLACK));
      GuiSetStyle(DEFAULT, BORDER_WIDTH, 2);
      GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt(ELEMENTS_ACCENT_COLOR));
      GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(ELEMENTS_FOCUS_COLOR));
}

std::string GuiElements::ShowBodyFinder(Bodies* bodies){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    static char text[21];
    static char last_text[21];
    static int focus = 0;
    std::string to_return = "";
    std::vector<std::string> sortedBodies = bodies->SortedNamesByKeyword(text);
    int sortedbodyCount = sortedBodies.size();

    finder_rect.height = 2*FINDER_PADDING + H6_TEXT_SIZE+FINDER_TEXT_PADDING + (H6_TEXT_SIZE+FINDER_TEXT_PADDING)*sortedbodyCount;
    DrawRectangleRounded(finder_rect, FINDER_ROUNDING, 4,  ELEMENTS_BACKGROUND_COLOR);

    if (IsKeyPressed(KEY_DOWN)){
        focus++;
    }
    if (IsKeyPressed(KEY_UP)){
        focus--;
    }
    if (IsKeyPressed(KEY_ESCAPE)){
        to_return = EXIT_WITHOUT_CHOOSING;
        focus = 0;
        text[0] = 0;
    }
    if (!(focus < sortedbodyCount)){
        focus = 0;
    }
    if (focus < 0){
        focus = sortedbodyCount-1;
    }
    if (strcmp(text, last_text) != 0){
        focus = 0;
        strcpy(last_text, text);
    }
    if (GuiTextBox((Rectangle){
            FINDER_MARGIN+FINDER_PADDING,
            FINDER_MARGIN+FINDER_PADDING,
            FINDER_WIDTH,
            H6_TEXT_SIZE+FINDER_TEXT_PADDING
        }, text, 20, true))
    {
        if(IsKeyPressed(KEY_ENTER)){
            if(sortedbodyCount == 0){
                to_return = "";
            }
            else {
                to_return = sortedBodies[focus];
                focus = 0;
            }
            text[0] = 0;
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (!CheckCollisionPointRec(GetMousePosition(), finder_rect)){
            to_return = EXIT_WITHOUT_CHOOSING;
            text[0] = 0;
            focus = 0;
        }
    }
    float i = 0;
    for (std::string name : sortedBodies){
        Rectangle rect = {
            FINDER_MARGIN+FINDER_PADDING,
            FINDER_MARGIN+FINDER_PADDING + H6_TEXT_SIZE+FINDER_TEXT_PADDING + (H6_TEXT_SIZE+FINDER_TEXT_PADDING)*i,
            FINDER_WIDTH,
            H6_TEXT_SIZE+FINDER_TEXT_PADDING,
        };
        if (focus == i){
            DrawRectangleLinesEx(rect, 2,ELEMENTS_ACCENT_COLOR);
        }
        rect.x += (float)FINDER_TEXT_PADDING/2;
        rect.width -= (float)FINDER_TEXT_PADDING/2; // pading for text

        int clicked = GuiLabelButton(rect,(char*)name.c_str());
        if (clicked){
            printf("%s clicked!\n", name.c_str());
            to_return = name;
            text[0] = 0;
        }
        i += 1.0f; // float because above in the code it multiplying by posY
    }
    return to_return;
}
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

void GuiElements::ShowParamsChanger(){
    static char stringvalue[CHANGER_BUFFER] = "@#$%";
    if (strcmp(stringvalue, "@#$%") == 0){
        float value = *changervalues.value;
        char format[CHANGER_BUFFER] = "%.3f";
        if (value < 0){
            value = value * (-1);
            strcpy(format, "-%.3f");
        }
        sprintf(stringvalue, format, value);
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, H4_TEXT_SIZE);
    DrawRectangleRec(changer_rect, ELEMENTS_BACKGROUND_COLOR2);
    DrawText(changervalues.name.c_str(),
        changer_rect.x+CHANGER_PADDING,
        changer_rect.y+CHANGER_PADDING,
        H2_TEXT_SIZE,
        WHITE);
    bool enter = GuiTextBox({
        changer_rect.x+CHANGER_PADDING,
        changer_rect.y+CHANGER_PADDING+H3_TEXT_SIZE+CHANGER_GAP,
        changer_rect.width-2*CHANGER_PADDING,
        H2_TEXT_SIZE

    }, stringvalue, CHANGER_BUFFER-2, true);
    bool chanceled = GuiButton({
        changer_rect.x+CHANGER_PADDING,
        changer_rect.y+changer_rect.height-CHANGER_BUTTON_HEIGHT-CHANGER_PADDING,
        (float)(changer_rect.width*0.5-CHANGER_PADDING-CHANGER_GAP*0.5),
        CHANGER_BUTTON_HEIGHT
    }, "cancel");

    bool done = GuiButton({
        (float)(changer_rect.x+changer_rect.width*0.5+CHANGER_GAP*0.5),
        changer_rect.y+changer_rect.height-CHANGER_BUTTON_HEIGHT-CHANGER_PADDING,
        (float)(changer_rect.width*0.5-CHANGER_PADDING-CHANGER_GAP*0.5),
        CHANGER_BUTTON_HEIGHT
    }, "done");
    if (done || enter){
        char *endptr;
        float newValue = strtof(stringvalue, &endptr);
        if (*endptr == '\0' && endptr != stringvalue) {
            *changervalues.value = newValue;
        }
        strcpy(stringvalue, "@#$%");
        changervalues.value = nullptr;
    }
    if (chanceled){
        changervalues.value = nullptr;
        strcpy(stringvalue, "@#$%");
    }
    if (IsKeyPressed(KEY_ESCAPE)){
        changervalues.value = nullptr;
        strcpy(stringvalue, "@#$%");
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (!CheckCollisionPointRec(GetMousePosition(), changer_rect)){
            changervalues.value = nullptr;
            strcpy(stringvalue, "@#$%");
        }
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
}

void GuiElements::DrawAll(Bodies* bodies, std::string* body_to_folow){
    if (changervalues.value != nullptr){
        ShowParamsChanger();
        gui_rects[CHANGER] = changer_rect;
    }
    else{
        if (gui_rects.find(CHANGER) != gui_rects.end()){
            gui_rects.erase(CHANGER);
        }
    }
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F)) {
        gui_rects[FINDER] = finder_rect;
    }
    if (gui_rects.find(FINDER) != gui_rects.end()){
        std::string choosed_body = ShowBodyFinder(bodies);
        if (choosed_body != ""){
            if (choosed_body != EXIT_WITHOUT_CHOOSING) {
                (*body_to_folow) = choosed_body;
            }
            gui_rects.erase(FINDER);
        }
    }
    if ((*body_to_folow) != ""){
        ShowBodyParams(bodies->getBodyByName(*body_to_folow));
        gui_rects[PARAMS] = params_rect;
    }
    else {
        gui_rects.erase(PARAMS);
    }
}
