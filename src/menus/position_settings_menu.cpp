#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <cstdio>

#define LINES SPRITES_AMNT
#define NO_SELECTION ((uint8_t)-1)

static Cursor cursor = {0, 0};
bool init_once = false;
bool pos_settings_visible;

uint8_t selected_item = NO_SELECTION;

Vec2 sprite_offsets[SPRITES_AMNT];

Line lines[LINES] = {
    {"main menu", MENU_INDEX, "Change main menu position", false},
    {"input viewer", VIEWER_INDEX, "Change input viewer position", false},
    {"link debug info", DEBUG_INFO_INDEX, "Change link debug info position", false},
    {"timer", TIMER_INDEX, "Change timer position", false},
    {"load timer", LOAD_TIMER_INDEX, "Change load timer position", false},
    {"igt timer", IGT_TIMER_INDEX, "Change IGT timer position", false}};

void PosSettingsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        pos_settings_visible = false;
        settings_visible = true;
        mm_visible = false;

        selected_item = NO_SELECTION;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        if (cursor.y < SPRITES_AMNT) {
            selected_item = selected_item == cursor.y ? NO_SELECTION : cursor.y;
        }
    }

    if (selected_item != NO_SELECTION && selected_item < SPRITES_AMNT) {
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            ++(sprite_offsets[selected_item].x);
        }
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            --(sprite_offsets[selected_item].x);
        }
        if (button_is_pressed(Controller::DPAD_UP)) {
            --(sprite_offsets[selected_item].y);
        }
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            ++(sprite_offsets[selected_item].y);
        }
    }

    Utilities::move_cursor(cursor, LINES, 1, selected_item != NO_SELECTION, selected_item != NO_SELECTION);
    Utilities::render_lines(font, lines, cursor.y, LINES);
};