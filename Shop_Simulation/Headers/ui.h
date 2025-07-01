#ifndef UI_H
#define UI_H

#include "inventory.h"


void ui_init(void);
void ui_cleanup(void);


int ui_get_order(Item items[], int quantities[]);


void ui_show_receipt(Item items[], int quantities[], float total, float change);


int ui_ask_continue(void);

#endif
