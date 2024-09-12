#include "raygui.h"

#include "gui_elements.hpp"
#include <cstring>

using namespace std;

string GuiElements::ShowBodyFinder(){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    static char text[21];
    static char last_text[21];
    static int focus = 0;
    string to_return = "";
    vector<string> sortedBodies = bodies->SortedNamesByKeyword(text);
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
    for (string name : sortedBodies){
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
        rect.width -= (float)FINDER_TEXT_PADDING/2; // padding for text

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
