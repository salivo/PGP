#include "gui_elements.hpp"
#include <cstring>
#include <iostream>

void GuiElements::ShowNameChanger(){
    static bool active = false;
    static char buffer[21] = "";
    if (strlen(buffer) == 0 && !active){
        strcpy(buffer, name_to_change.c_str());
        active = true;
    }
    auto doStuffToExit = [&] () { // Yes function in function, but why not? It's my project.
        *body_to_follow = buffer;
        strcpy(buffer, "");
        active = false;
        name_to_change = "";

    };
    GuiSetStyle(DEFAULT, TEXT_SIZE, H4_TEXT_SIZE);
    GuiSetStyle(DROPDOWNBOX, ARROW_PADDING, 14);

    DrawRectangleRec(changer_rect, ELEMENTS_BACKGROUND_COLOR2);
    DrawText("Set new name",
        changer_rect.x+CHANGER_PADDING,
        changer_rect.y+CHANGER_PADDING,
        H2_TEXT_SIZE,
        WHITE);
    GuiTextBox({
        changer_rect.x+CHANGER_PADDING,
        changer_rect.y+CHANGER_PADDING+H3_TEXT_SIZE+CHANGER_GAP,
        changer_rect.width-2*CHANGER_PADDING,
        H2_TEXT_SIZE
    }, buffer, CHANGER_BUFFER-2, true);
    bool canceled = GuiButton({
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
    if (done || IsKeyPressed(KEY_ENTER)){
        spacetasker->setParams(space->getBodyByName(name_to_change), {.name=buffer});
        doStuffToExit();
    }
    if (canceled){
        doStuffToExit();
    }
    if (IsKeyPressed(KEY_ESCAPE)){
        doStuffToExit();
    }
    if (
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        !CheckCollisionPointRec(GetMousePosition(), changer_rect)
    ) {
        doStuffToExit();
    }
}
