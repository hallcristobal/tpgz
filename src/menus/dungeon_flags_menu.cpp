#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "libtp_c/include/flag.h"
#include "libtp_c/include/tp.h"

#define LINES 4

static Cursor cursor = { 0, 0 };
bool init_once = false;
bool dungeon_flags_visible;

bool map_flag;
bool compass_flag;
bool boss_key_flag;
bool small_keys_flag;

Line lines[LINES] = {
	{"have map", MAP_FLAG_INDEX, "Give current dungeon map", true, &map_flag},
	{"have compass", COMPASS_FLAG_INDEX, "Give current dungeon compass", true, &compass_flag},
	{"have boss key", BOSS_KEY_FLAG_INDEX, "Give current dungeon boss key", true, &boss_key_flag},
	{"have small keys", SMALL_KEY_FLAG_INDEX, "Give current dungeon small keys", true, &small_keys_flag}};

void DungeonFlagsMenu::render(Font& font) {
    // update flags
    map_flag = (tp_gameInfo.temp_flags.temp_flag_bit_field_34 & (1 << 0));
    compass_flag = (tp_gameInfo.temp_flags.temp_flag_bit_field_34 & (1 << 1));
    boss_key_flag = (tp_gameInfo.temp_flags.temp_flag_bit_field_34 & (1 << 2));
    small_keys_flag = tp_gameInfo.temp_flags.temp_flag_bit_field_33;

    if (button_is_pressed(Controller::B)) {
        init_once = false;
        dungeon_flags_visible = false;
        flags_menu_visible = true;
        mm_visible = false;
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
            switch (cursor.y) {
                case MAP_FLAG_INDEX: {
                    tp_gameInfo.temp_flags.temp_flag_bit_field_34 ^= 1UL << 0;
                    break;
                }
                case COMPASS_FLAG_INDEX: {
                    tp_gameInfo.temp_flags.temp_flag_bit_field_34 ^= 1UL << 1;
                    break;
                }
                case BOSS_KEY_FLAG_INDEX: {
                    tp_gameInfo.temp_flags.temp_flag_bit_field_34 ^= 1UL << 2;
                    break;
                }
                case SMALL_KEY_FLAG_INDEX: {
                    if (small_keys_flag) {
                        tp_gameInfo.temp_flags.temp_flag_bit_field_33 = 0x00;
                    } else {
                        tp_gameInfo.temp_flags.temp_flag_bit_field_33 = 0x05;
                    }
                    break;
                }
            }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES, 150.0f);
};
