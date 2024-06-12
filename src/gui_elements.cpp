#include "gui_elements.hpp"
#include "process_bodies.hpp"

#include "raygui.h"
#include <cstdio>
#include <cstring>
#include <raylib.h>
#include <string>
#include <vector>

std::string GuiElements::ShowBodyFinder(Bodies* bodies){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    static char text[21];
    static char last_text[21];
    static int focus = 0;
    std::string to_return = "";
    std::vector<std::string> sortedBodies = bodies->SortedNamesByKeyword(text);
    int sortedbodyCount = sortedBodies.size();
    
    DrawRectangleRec(finder_rect, WHITE);

    if (IsKeyPressed(KEY_DOWN)){
        focus++;
    }
    if (IsKeyPressed(KEY_UP)){
        focus--;
    }
    if (IsKeyPressed(KEY_ESCAPE)){
        to_return = EXIT_WITHOUT_CHOOSING;
        focus = 0;
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
    if (GuiTextBox((Rectangle){ FINDER_MARGIN, FINDER_MARGIN, FINDER_WIDTH, FINDER_TEXT_SIZE+FINDER_TEXT_PADDING }, text, 20, true)){
        if(IsKeyPressed(KEY_ENTER)){
            if(sortedbodyCount == 0){
                to_return = "";
            }
            else {
                text[0] = 0;
                to_return = sortedBodies[focus];
                focus = 0;
            }
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (!CheckCollisionPointRec(GetMousePosition(), finder_rect)){
            to_return = EXIT_WITHOUT_CHOOSING;
            focus = 0;
        }
    }
    float i = 0;
    for (std::string name : sortedBodies){
        if (focus == i){
            DrawRectangle(
                FINDER_MARGIN, 
                FINDER_MARGIN + FINDER_TEXT_SIZE+FINDER_TEXT_PADDING + (FINDER_TEXT_SIZE+FINDER_TEXT_PADDING)*i,
                FINDER_WIDTH,
                FINDER_TEXT_SIZE+FINDER_TEXT_PADDING, 
                ColorAlpha(ORANGE, 0.5));    
        }
        int clicked = GuiLabelButton(
            { 
                FINDER_MARGIN,
                FINDER_MARGIN + FINDER_TEXT_SIZE+FINDER_TEXT_PADDING + (FINDER_TEXT_SIZE+FINDER_TEXT_PADDING)*i,
                FINDER_WIDTH,
                FINDER_TEXT_SIZE+FINDER_TEXT_PADDING},
            (char*)name.c_str());
        if (clicked){
            printf("%s clicked!\n", name.c_str());
            to_return = name;
        }
        i += 1.0f; // float because above in the code it multiplying by posY
    }
    return to_return;
}


void GuiElements::ShowBodyParams(Body* Body){
    DrawRectangleRec(params_rect, (Color){15,15,15,230});
    const char buffer_text[21] = "";
    bool editMode = true;
    DrawText("position", params_rect.x+BODY_PARAMS_PADDING,BODY_PARAMS_PADDING,24,WHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, BODY_PARAMS_TEXT_SIZE);
    GuiLabelButton({params_rect.x+BODY_PARAMS_PADDING, params_rect.y+BODY_PARAMS_PADDING*2+24, 20,20}, "X:10");
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