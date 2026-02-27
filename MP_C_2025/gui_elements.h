#ifndef GUI_ELEMENTS_H_INCLUDED
#define GUI_ELEMENTS_H_INCLUDED

#include "raylib.h"
#include <stdbool.h>

#define MAX_TEXT 64
#define MAX_ITEMS 200

/* ================= TEXTBOX ================= */

typedef struct {
    Rectangle bounds;
    char text[MAX_TEXT];
    int maxLength;
    bool active;
} TextBox;

void UpdateTextBox(TextBox *box);
void DrawTextBox(TextBox *box);


/* ================= SCROLLABLE LIST ================= */

typedef struct {
    Rectangle view;
    const char* items[MAX_ITEMS];
    int itemCount;
    int scrollOffset;
    int selected;
} ScrollableList;

void UpdateScrollableList(ScrollableList *list, int itemHeight);
void DrawScrollableList(ScrollableList *list, int itemHeight);
void UI_ListAddItem(ScrollableList *list, const char *text);
void UI_ListClear(ScrollableList *list);
void UI_UpdateAndDraw(void);

#endif // GUI_ELEMENTS_H_INCLUDED
