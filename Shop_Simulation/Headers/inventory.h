#ifndef INVENTORY_H
#define INVENTORY_H

#define ITEM_COUNT 5

typedef struct {
    char name[20];
    float price;
    int stock;
} Item;

void randomize();
int get_random_number(int min, int max);
void show_inventory(Item items[]);

#endif
