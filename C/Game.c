#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITEM_COUNT 5

typedef struct {
    char name[20];
    float price;
    int stock;
} Item;

void randomize() {
    srand(time(NULL));
}

int get_random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

void show_inventory(Item items[]) {
    printf("\n--- Store Inventory ---\n");
    for (int i = 0; i < ITEM_COUNT; i++) {
        printf("%d. %-8s : %2d in stock - $%.2f each\n", i + 1, items[i].name, items[i].stock, items[i].price);
    }
    printf("------------------------\n");
}

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
        printf("\n=== Customer #%d ===\n", customer++);
        show_inventory(items);

        int quantities[ITEM_COUNT] = {0};
        float total = 0.0f;

       
        for (int i = 0; i < ITEM_COUNT; i++) {
            if (items[i].stock == 0) continue;

            printf("How many %s? (0 to skip): ", items[i].name);
            int qty = 0;
            scanf("%d", &qty);

            if (qty > items[i].stock) qty = items[i].stock;
            quantities[i] = qty;
            total += qty * items[i].price;
        }

        
        float paid = 0.0f;
        if (total > 0) {
            printf("\nTotal: $%.2f\n", total);
            printf("Enter payment: $");
            scanf("%f", &paid);

            if (paid < total) {
                printf("Not enough money! Transaction cancelled.\n");
                continue;
            }

            printf("Change: $%.2f\n", paid - total);
        } else {
            printf("You didn't buy anything.\n");
            continue;
        }

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

        char choice;
        printf("\nNext customer? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y') {
            printf("Store closed.\n");
            break;
        }
    }

    return 0;
}
