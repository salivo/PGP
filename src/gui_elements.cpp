#include "gui_elements.hpp"
#include "process_bodies.hpp"

#include "raygui.h"

void ShowBodyFinder(Bodies* bodies){
    static char text[21];
    if (GuiTextBox((Rectangle){ 24, 24, 120, 30 }, text, 20, true)){
    }
    float i = 0;
    for (std::string name : bodies->SortedNamesByKeyword("hello")){
        int clicked = GuiLabelButton({ 24, 54+30*i, 120, 30 }, (char*)name.c_str());
        if (clicked){
            printf("%s clicked!\n", name.c_str());
        }
        i += 1.0f;
    }
    

}