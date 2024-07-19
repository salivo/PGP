#include "raygui.h"

#include "gui_elements.hpp"
#include "calc_helper.hpp"

#include <cmath>
#include <cstring>

using namespace std;

void GuiElements::ShowParamsChanger(){
    static int active;
    static bool editMode = false;
    static char stringvalue[CHANGER_BUFFER] = "@#$%";
    bool canchoosebodies = isBodyChoosingEnabled();
    char *endptr;
    float value;
    float newValue;
    int unit_width = MeasureText(changervalues.unit.c_str(), H3_TEXT_SIZE);

    auto doStuffToExit = [&] () { // Yes function in function, but why not? It's my project.
        strcpy(stringvalue, "@#$%");
        changervalues.value = nullptr;
        GuiUnlock();
        enableBodyChoosing();
    };
    if (strcmp(stringvalue, "@#$%") == 0){
        active = getUnitPrefixByNumber(*changervalues.value).count;
        value = *changervalues.value / pow(10.0, getUnitPrefixByNumber(*changervalues.value).exponent);
        char format[CHANGER_BUFFER] = "%.3f";
        if (value < 0){
            value = value * (-1);
            strcpy(format, "-%.3f");
        }
        sprintf(stringvalue, format, value);
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, H4_TEXT_SIZE);
    GuiSetStyle(DROPDOWNBOX, ARROW_PADDING, 14);

    DrawRectangleRec(changer_rect, ELEMENTS_BACKGROUND_COLOR2);
    DrawText(changervalues.name.c_str(),
        changer_rect.x+CHANGER_PADDING,
        changer_rect.y+CHANGER_PADDING,
        H2_TEXT_SIZE,
        WHITE);
    GuiTextBox({
        changer_rect.x+CHANGER_PADDING,
        changer_rect.y+CHANGER_PADDING+H3_TEXT_SIZE+CHANGER_GAP,
        changer_rect.width-3*CHANGER_PADDING-CHANGER_UNIT_PREFIX_WIDTH-unit_width-2*CHANGER_GAP,
        H2_TEXT_SIZE
    }, stringvalue, CHANGER_BUFFER-2, true);

    DrawText(
        changervalues.unit.c_str(),
        changer_rect.x+changer_rect.width-2*CHANGER_PADDING-unit_width,
        changer_rect.y+CHANGER_PADDING+H3_TEXT_SIZE+CHANGER_GAP,
        H3_TEXT_SIZE,
        WHITE
    );
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
    bool dropdown = GuiDropdownBox({
        changer_rect.x+changer_rect.width-2*CHANGER_PADDING-CHANGER_UNIT_PREFIX_WIDTH-unit_width-CHANGER_GAP,
        changer_rect.y+CHANGER_PADDING+H3_TEXT_SIZE+CHANGER_GAP,
        CHANGER_UNIT_PREFIX_WIDTH,
        H2_TEXT_SIZE
    }, "-;k;M;G;T;P;E", &active, editMode);

    newValue = strtof(stringvalue, &endptr);
    if (dropdown) editMode = !editMode;
    if (editMode) {
        GuiLock();
        disableBodyChoosing();
    }
    else {
        GuiUnlock();
        enableBodyChoosing();
    }
    if (done || IsKeyPressed(KEY_ENTER)){
        if (*endptr == '\0' && endptr != stringvalue) {
            *changervalues.value = newValue * pow(10.0, getUnitPrefixbByCount(active).exponent);
        }
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
        !CheckCollisionPointRec(GetMousePosition(), changer_rect) &&
        canchoosebodies
    ) {
        doStuffToExit();
    }
}
