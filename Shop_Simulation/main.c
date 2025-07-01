#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "input.h"

int main() {
    randomize();
    Item items[ITEM_COUNT] = {
        {"Pizza", 7.50f, get_random_number(0, 10)},
        {"Orange", 1.20f, get_random_number(0, 10)},
        {"Soda", 0.99f, get_random_number(0, 10)},
        {"Bread", 2.10f, get_random_number(0, 10)},
        {"Cheese", 4.25f, get_random_number(0, 10)}
    };
    int customer = 1;
    while (1) {
        char shopChoice[16];
        printf("\nWelcome to the shop! Type 'exit' to leave or press Enter to continue: ");
        if (!fgets(shopChoice, sizeof(shopChoice), stdin)) break;
        shopChoice[strcspn(shopChoice, "\n")] = 0;
        if (!strcasecmp_custom(shopChoice, "exit")) break;

        printf("\n=== Customer #%d ===\n", customer++);
        show_inventory(items);

        int quantities[ITEM_COUNT] = {0};
        float total = 0.0f;

        for (int i = 0; i < ITEM_COUNT; i++) {
            if (items[i].stock == 0) continue;
            char prompt[128];
            snprintf(prompt, sizeof(prompt), "How many %s? (0 to skip, or type 'exit' to cancel): ", items[i].name);
            int qty = safe_int_input(prompt, items[i].stock);
            if (qty == -1) {
                printf("Order cancelled by customer.\n");
                total = 0;
                break;
            }
            quantities[i] = qty;
            total += qty * items[i].price;
        }
        if (total <= 0.0f) {
            printf("You didn't buy anything.\n");
            continue;
        }
        float paid = 0.0f;
        while (1) {
            paid = safe_float_input("\nEnter payment: $");
            if (paid < total) {
                printf("Not enough money! You still owe $%.2f\n", total - paid);
                continue;
            }
            break;
        }
        printf("Change: $%.2f\n", paid - total);
        for (int i = 0; i < ITEM_COUNT; i++) {
            items[i].stock -= quantities[i];
        }
        printf("\n--- Receipt ---\n");
        for (int i = 0; i < ITEM_COUNT; i++) {
            if (quantities[i]) {
                printf("%-8s x %2d = $%.2f\n", items[i].name, quantities[i], items[i].price * quantities[i]);
            }
        }
        int items_left = 0;
        for (int i = 0; i < ITEM_COUNT; i++) {
            items_left += items[i].stock;
        }
        if (items_left == 0) {
            printf("Store is out of stock! Closing.\n");
            break;
        }
        char choice[16];
        printf("\nNext customer? (y/n/exit): ");
        if (!fgets(choice, sizeof(choice), stdin)) break;
        choice[strcspn(choice, "\n")] = 0;
        if (choice[0] == 'n' || choice[0] == 'N' || !strcasecmp_custom(choice, "exit")) {
            printf("Store closed.\n");
            break;
        }
    }
    return 0;
}
