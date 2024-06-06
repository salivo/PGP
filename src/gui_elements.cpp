#include "gui_elements.hpp"
#include "process_bodies.hpp"

#include "raygui.h"
#include <cstddef>
#include <cstring>
#include <raylib.h>
#include <string>
#include <vector>

std::string ShowBodyFinder(Bodies* bodies){
    static char text[21];
    static char last_text[21];
    static int focus = 0;
    std::string to_return = "";
    
    std::vector<std::string> sortedBodies = bodies->SortedNamesByKeyword(text);
    int sortedbodyCount = sortedBodies.size();

    if (IsKeyPressed(KEY_DOWN)){
        focus++;
    }
    if (IsKeyPressed(KEY_UP)){
        focus--;
    }
    if (IsKeyPressed(KEY_ESCAPE)){
        to_return = "IWANTJUSTEXITPLEASELEAVEME";
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
    
    if (GuiTextBox((Rectangle){ 24, 24, 120, 30 }, text, 20, true)){
        text[0] = 0;
        to_return = sortedBodies[focus];
        focus = 0;
        
    }
    
    float i = 0;
    for (std::string name : sortedBodies){
        if (focus == i){
            DrawRectangle(24, 54+30*i,120,30, ColorAlpha(ORANGE, 0.5));    
        }
        int clicked = GuiLabelButton({ 24, 54+30*i, 120, 30 }, (char*)name.c_str());
        if (clicked){
            printf("%s clicked!\n", name.c_str());
            to_return = name;
        }
        i += 1.0f; // float because above in the code it multiplying by posY
    }
    return to_return;
}