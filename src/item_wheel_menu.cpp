#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define LINES 3

static int cursor = 2;

Line lines[LINES] = {
    {"item wheel", 0, "", false},
    {"", 1, "", false},
    {"TBD", 2, "TBD", false}};

void ItemWheelMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        item_wheel_visible = false;
        inventory_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);
};