#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomize() {
    srand(time(NULL));
}

int get_random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

void show_inventory(Item items[]) {
    printf("\n--- Store Inventory ---\n");
    for (int i = 0; i < ITEM_COUNT; i++) {
        printf("%d. %-8s : %2d in stock - $%.2f each\n",
               i + 1, items[i].name, items[i].stock, items[i].price);
    }
    printf("------------------------\n");
}
