#include "menu.h"

#define ITEM_WHEEL_INDEX 0
#define PAUSE_MENU_INDEX 1
#define AMOUNTS_MENU_INDEX 2

class InventoryMenu : public Menu {
public:
    InventoryMenu() : Menu() {}
    static void render(Font& font);
};