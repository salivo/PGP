#include "gui_elements.hpp"
#include "process_bodies.hpp"

#include "raygui.h"
#include <cstdio>
#include <cstring>
#include <raylib.h>
#include <string>
#include <vector>

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

void draw_section(Rectangle params_rect, Vector2 data, string name){
    DrawText(name.c_str(), params_rect.x+BODY_PARAMS_PADDING,BODY_PARAMS_PADDING,H3_TEXT_SIZE,WHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, H3_TEXT_SIZE);
    float half_width = (params_rect.width-2*BODY_PARAMS_PADDING)/2.0;
    GuiLabelButton({
        params_rect.x+BODY_PARAMS_PADDING,
        params_rect.y+H3_TEXT_SIZE+BODY_PARAMS_GAP,
        half_width,
        H6_TEXT_SIZE
    }, to_string(data.x).c_str());
    GuiLabelButton({
        params_rect.x+half_width+BODY_PARAMS_PADDING,
        params_rect.y+H3_TEXT_SIZE+BODY_PARAMS_GAP,
        half_width,
        H6_TEXT_SIZE
    }, to_string(data.y).c_str());
}

void GuiElements::ShowBodyParams(Body* Body){
    DrawRectangleRec(params_rect, ELEMENTS_BACKGROUND_COLOR);
    const char buffer_text[21] = "";
    bool editMode = true;
    draw_section(params_rect, Body->center, "hello");
}

void GuiElements::DrawAll(Bodies* bodies, std::string* body_to_folow){
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
            printf("erased\n");
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
