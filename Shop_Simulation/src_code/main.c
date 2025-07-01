#include <stdio.h>
#include "inventory.h"
#include "ui.h"

int main(void) {
    randomize();

    Item items[ITEM_COUNT] = {
        {"Pizza", 7.50f, get_random_number(0, 10)},
        {"Orange", 1.20f, get_random_number(0, 10)},
        {"Soda", 0.99f, get_random_number(0, 10)},
        {"Bread", 2.10f, get_random_number(0, 10)},
        {"Cheese", 4.25f, get_random_number(0, 10)}
    };

    ui_init();

    int customer = 1;
    while (1) {
        clear();
        mvprintw(0, 0, "Welcome to Shop Simulation - Customer #%d", customer++);
        mvprintw(2, 0, "Press any key to start or 'q' to quit.");
        refresh();
        int ch = getch();
        if (ch == 'q' || ch == 'Q') break;

        int quantities[ITEM_COUNT] = {0};
        if (ui_get_order(items, quantities)) {
            mvprintw(20, 0, "Order cancelled.");
            getch();
            continue;
        }

        float total = 0.0f;
        for (int i = 0; i < ITEM_COUNT; i++) {
            total += quantities[i] * items[i].price;
        }
        if (total == 0.0f) {
            mvprintw(20, 0, "No items bought.");
            getch();
            continue;
        }

        float paid = 0.0f;
        while (1) {
            char paystr[20];
            echo();
            mvprintw(20, 0, "Total: $%.2f, Enter payment: ", total);
            getnstr(paystr, sizeof(paystr) - 1);
            noecho();
            if (sscanf(paystr, "%f", &paid) != 1 || paid < total) {
                mvprintw(21, 0, "Insufficient payment, try again.");
                clrtoeol();
                continue;
            }
            break;
        }

        float change = paid - total;

        for (int i = 0; i < ITEM_COUNT; i++) {
            items[i].stock -= quantities[i];
        }

        ui_show_receipt(items, quantities, total, change);

        int items_left = 0;
        for (int i = 0; i < ITEM_COUNT; i++) {
            items_left += items[i].stock;
        }
        if (items_left == 0) {
            mvprintw(22, 0, "Store is out of stock! Closing.");
            getch();
            break;
        }

        if (!ui_ask_continue()) break;
    }

    ui_cleanup();
    return 0;
}
