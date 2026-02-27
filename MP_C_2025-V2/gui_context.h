#ifndef GUI_CONTEXT_H_INCLUDED
#define GUI_CONTEXT_H_INCLUDED

#include "gui_elements.h"

#define MAX_TEXTBOXES 20
#define MAX_LISTS 10

typedef struct {

    TextBox textboxes[MAX_TEXTBOXES];
    int textboxCount;

    ScrollableList lists[MAX_LISTS];
    int listCount;

    int focusedTextbox;

} UIContext;

extern UIContext ui;

void UI_Clear();
void UI_BeginFrame();
void UI_Draw();

TextBox* UI_CreateTextBox(Rectangle bounds, int maxLen);
ScrollableList* UI_CreateList(Rectangle bounds);



#endif // GUI_CONTEXT_H_INCLUDED
