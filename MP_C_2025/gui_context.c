#include "headers.h"
UIContext ui = {0};
void UI_Clear()
{
    ui.textboxCount = 0;
    ui.listCount = 0;
    ui.focusedTextbox = -1;
}
TextBox* UI_CreateTextBox(Rectangle bounds, int maxLen)
{
    if(ui.textboxCount >= MAX_TEXTBOXES)
        return NULL;

    TextBox* box = &ui.textboxes[ui.textboxCount++];

    box->bounds = bounds;
    box->text[0] = '\0';
    box->maxLength = maxLen;
    box->active = false;

    return box;
}
ScrollableList* UI_CreateList(Rectangle bounds)
{
    if(ui.listCount >= MAX_LISTS)
        return NULL;

    ScrollableList* list = &ui.lists[ui.listCount++];

    list->view = bounds;
    list->itemCount = 0;
    list->scrollOffset = 0;
    list->selected = -1;

    return list;
}
void UI_BeginFrame()
{
    for(int i=0;i<ui.textboxCount;i++)
        UpdateTextBox(&ui.textboxes[i]);

    for(int i=0;i<ui.listCount;i++)
        UpdateScrollableList(&ui.lists[i],30);
    if(IsKeyPressed(KEY_TAB))
{
    ui.focusedTextbox++;

    if(ui.focusedTextbox >= ui.textboxCount)
        ui.focusedTextbox = 0;

    for(int i=0;i<ui.textboxCount;i++)
        ui.textboxes[i].active = (i == ui.focusedTextbox);
}
}
void UI_Draw()
{
    for(int i=0;i<ui.textboxCount;i++)
        DrawTextBox(&ui.textboxes[i]);

    for(int i=0;i<ui.listCount;i++)
        DrawScrollableList(&ui.lists[i],30);
}
void UI_ListAddItem(ScrollableList *list, const char *text)
{
    if (!list) return;

    if (list->itemCount >= MAX_ITEMS)
        return;

    list->items[list->itemCount] = text;
    list->itemCount++;
}
void UI_ListClear(ScrollableList *list)
{
    if (!list) return;

    list->itemCount = 0;
    list->selected = -1;
    list->scrollOffset = 0;
}
void UI_UpdateAndDraw(void)
{
    UI_BeginFrame();
    UI_Draw();
}
