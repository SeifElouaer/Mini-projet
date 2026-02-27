#include "gui_elements.h"
#include <string.h>

/* -------- TEXTBOX UPDATE -------- */

void UpdateTextBox(TextBox *box)
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        box->active = CheckCollisionPointRec(mouse, box->bounds);

    if (!box->active) return;

    int key = GetCharPressed();

    while (key > 0)
    {
        int len = strlen(box->text);

        if (len < box->maxLength && key >= 32 && key <= 125)
        {
            box->text[len] = (char)key;
            box->text[len+1] = '\0';
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        int len = strlen(box->text);
        if (len > 0)
            box->text[len-1] = '\0';
    }
}
void DrawTextBox(TextBox *box)
{
    DrawRectangleRec(box->bounds,
        box->active ? LIGHTGRAY : RAYWHITE);

    DrawRectangleLinesEx(box->bounds, 2, BLACK);

    DrawText(box->text,
        box->bounds.x + 5,
        box->bounds.y + 8,
        20,
        BLACK);
    Color border = box->active ? BLUE : BLACK;
    DrawRectangleLinesEx(box->bounds,2,border);
}
void UpdateScrollableList(ScrollableList *list, int itemHeight)
{
    Vector2 mouse = GetMousePosition();

    if(!CheckCollisionPointRec(mouse, list->view))
        return;

    int wheel = GetMouseWheelMove();

    if (wheel != 0)
        list->scrollOffset -= wheel * itemHeight;

    if (list->scrollOffset < 0)
        list->scrollOffset = 0;
}
void DrawScrollableList(ScrollableList *list, int itemHeight)
{
    BeginScissorMode(
        list->view.x,
        list->view.y,
        list->view.width,
        list->view.height);

    for(int i=0;i<list->itemCount;i++)
    {
        int y = list->view.y + i*itemHeight - list->scrollOffset;

        Rectangle itemRect = {
            list->view.x,
            y,
            list->view.width,
            itemHeight
        };

        if(CheckCollisionPointRec(GetMousePosition(), itemRect)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            list->selected = i;

        DrawRectangleRec(itemRect,(i==list->selected)? SKYBLUE : LIGHTGRAY);

        DrawText(list->items[i],
                 itemRect.x+5,
                 itemRect.y+5,
                 20,
                 BLACK);

        if(!CheckCollisionPointRec(GetMousePosition(), list->view))
            continue;
    }

    EndScissorMode();
}
