#include "ui.h"
#include <ncurses.h>
#include <string.h>

void ui_init(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void ui_cleanup(void) {
    endwin();
}

void ui_show_inventory(Item items[]) {
    clear();
    mvprintw(0, 0, "--- Store Inventory ---");
    for (int i = 0; i < ITEM_COUNT; i++) {
        mvprintw(i + 2, 2, "%d. %-8s : %2d in stock - $%.2f each",
                 i + 1, items[i].name, items[i].stock, items[i].price);
    }
    mvprintw(ITEM_COUNT + 4, 0, "Enter quantities or 'exit' to cancel.\n");
    refresh();
}

int ui_get_order(Item items[], int quantities[]) {
    ui_show_inventory(items);

    char input[16];
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (items[i].stock == 0) {
            quantities[i] = 0;
            continue;
        }

        mvprintw(ITEM_COUNT + 6 + i, 0, "How many %s? (max %d): ", items[i].name, items[i].stock);
        clrtoeol();
        echo();
        move(ITEM_COUNT + 6 + i, 20 + strlen(items[i].name));
        getnstr(input, 15);
        noecho();

        if (strcasecmp(input, "exit") == 0) {
            return 1;  
        }

        int qty = 0;
        if (sscanf(input, "%d", &qty) != 1 || qty < 0) {
            mvprintw(ITEM_COUNT + 6 + i + 1, 0, "Invalid input, try again.");
            i--;  
            continue;
        }
        if (qty > items[i].stock) qty = items[i].stock;
        quantities[i] = qty;
    }
    return 0;
}

void ui_show_receipt(Item items[], int quantities[], float total, float change) {
    clear();
    mvprintw(0, 0, "--- Receipt ---");
    int line = 2;
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (quantities[i] > 0) {
            mvprintw(line++, 2, "%-8s x %2d = $%.2f", items[i].name, quantities[i], items[i].price * quantities[i]);
        }
    }
    mvprintw(line + 1, 0, "Total: $%.2f", total);
    mvprintw(line + 2, 0, "Change: $%.2f", change);
    mvprintw(line + 4, 0, "Press any key to continue...");
    refresh();
    getch();
}

int ui_ask_continue(void) {
    clear();
    mvprintw(0, 0, "Next customer? (y/n): ");
    int ch;
    while ((ch = getch())) {
        if (ch == 'y' || ch == 'Y') return 1;
        if (ch == 'n' || ch == 'N') return 0;
    }
    return 0;
}
