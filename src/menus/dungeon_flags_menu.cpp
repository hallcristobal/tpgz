#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "libtp_c/include/flag.h"
#include "libtp_c/include/tp.h"
#include <stdio.h>
#include <stdint.h>

#define LINES 8
#define MAX_DUNGEON_OPTIONS 9

static Cursor cursor = {0, 0};
bool init_once = false;
bool dungeon_flags_visible;

bool map_flag;
bool compass_flag;
bool boss_key_flag;
bool small_keys_flag;
bool miniboss_flag;
bool boss_flag;

int select_dungeon_index = 0;
Flags::GlobalFlags* dungeon_node;

Line lines[LINES] = {
    {"dungeon:", SELECT_DUNGEON_INDEX, "Selected dungeon flags", false, nullptr, MAX_DUNGEON_OPTIONS},
    {"have map", MAP_FLAG_INDEX, "Give selected dungeon map", true, &map_flag},
    {"have compass", COMPASS_FLAG_INDEX, "Give selected dungeon compass", true, &compass_flag},
    {"have boss key", BOSS_KEY_FLAG_INDEX, "Give selected dungeon boss key", true, &boss_key_flag},
    {"have small keys", SMALL_KEY_FLAG_INDEX, "Give selected dungeon small keys", true, &small_keys_flag},
    {"miniboss dead", DEFEAT_MINIBOSS_FLAG_INDEX, "Selected dungeon miniboss is defeated", true, &miniboss_flag},
    {"boss dead", DEFEAT_BOSS_FLAG_INDEX, "Selected dungeon boss is defeated", true, &boss_flag},
    {"clear flags", CLEAR_DUNGEON_FLAGS_INDEX, "Clear all selected dungeon flags"}};

void DungeonFlagsMenu::render(Font& font) {
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

    ListMember dungeon_options[MAX_DUNGEON_OPTIONS] = {
        "Forest Temple",
        "Goron Mines",
        "Lakebed Temple",
        "Arbiter's Grounds",
        "Snowpeak Ruins",
        "Temple of Time",
        "City in the Sky",
        "Palace of Twilight",
        "Hyrule Castle"};

    if (cursor.y == SELECT_DUNGEON_INDEX) {
        cursor.x = select_dungeon_index;
        Utilities::move_cursor(cursor, LINES, MAX_DUNGEON_OPTIONS);
        if (cursor.y == SELECT_DUNGEON_INDEX) {
            select_dungeon_index = cursor.x;
        }
    } else {
        Utilities::move_cursor(cursor, LINES);
    }

    switch (select_dungeon_index) {
        case 0: {
            dungeon_node = &tp_gameInfo.dungeon_flags.forest_temple_flags;
            break;
        }
        case 1: {
            dungeon_node = &tp_gameInfo.dungeon_flags.goron_mines_flags;
            break;
        }
        case 2: {
            dungeon_node = &tp_gameInfo.dungeon_flags.lakebed_flags;
            break;
        }
        case 3: {
            dungeon_node = &tp_gameInfo.dungeon_flags.arbiters_flags;
            break;
        }
        case 4: {
            dungeon_node = &tp_gameInfo.dungeon_flags.snowpeak_ruins_flags;
            break;
        }
        case 5: {
            dungeon_node = &tp_gameInfo.dungeon_flags.temple_of_time_flags;
            break;
        }
        case 6: {
            dungeon_node = &tp_gameInfo.dungeon_flags.cits_flags;
            break;
        }
        case 7: {
            dungeon_node = &tp_gameInfo.dungeon_flags.palace_flags;
            break;
        }
        case 8: {
            dungeon_node = &tp_gameInfo.dungeon_flags.hyrule_castle_flags;
            break;
        }
    }

    // update flags
    map_flag = (dungeon_node->flags_29 & (1 << 0));
    compass_flag = (dungeon_node->flags_29 & (1 << 1));
    boss_key_flag = (dungeon_node->flags_29 & (1 << 2));
    small_keys_flag = dungeon_node->flags_28;
    miniboss_flag = (dungeon_node->flags_29 & (1 << 7));
    boss_flag = (dungeon_node->flags_29 & (1 << 3));

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case MAP_FLAG_INDEX: {
                dungeon_node->flags_29 ^= 1UL << 0;
                break;
            }
            case COMPASS_FLAG_INDEX: {
                dungeon_node->flags_29 ^= 1UL << 1;
                break;
            }
            case BOSS_KEY_FLAG_INDEX: {
                dungeon_node->flags_29 ^= 1UL << 2;
                break;
            }
            case SMALL_KEY_FLAG_INDEX: {
                if (small_keys_flag) {
                    dungeon_node->flags_28 = 0x00;
                } else {
                    dungeon_node->flags_28 = 0x05;
                }
                break;
            }
            case DEFEAT_MINIBOSS_FLAG_INDEX: {
                dungeon_node->flags_29 ^= 1UL << 7;
                break;
            }
            case DEFEAT_BOSS_FLAG_INDEX: {
                dungeon_node->flags_29 ^= 1UL << 3;
                break;
            }
            case CLEAR_DUNGEON_FLAGS_INDEX: {
                dungeon_node->flags_0 = 0;  // is there a better way to do this
                dungeon_node->flags_1 = 0;
                dungeon_node->flags_2 = 0;
                dungeon_node->flags_3 = 0;
                dungeon_node->flags_4 = 0;
                dungeon_node->flags_5 = 0;
                dungeon_node->flags_6 = 0;
                dungeon_node->flags_7 = 0;
                dungeon_node->flags_8 = 0;
                dungeon_node->flags_9 = 0;
                dungeon_node->flags_10 = 0;
                dungeon_node->flags_11 = 0;
                dungeon_node->flags_12 = 0;
                dungeon_node->flags_13 = 0;
                dungeon_node->flags_14 = 0;
                dungeon_node->flags_15 = 0;
                dungeon_node->flags_16 = 0;
                dungeon_node->flags_17 = 0;
                dungeon_node->flags_18 = 0;
                dungeon_node->flags_19 = 0;
                dungeon_node->flags_20 = 0;
                dungeon_node->flags_21 = 0;
                dungeon_node->flags_22 = 0;
                dungeon_node->flags_23 = 0;
                dungeon_node->flags_24 = 0;
                dungeon_node->flags_25 = 0;
                dungeon_node->flags_26 = 0;
                dungeon_node->flags_27 = 0;
                dungeon_node->flags_28 = 0;
                dungeon_node->flags_29 = 0;
                dungeon_node->flags_30 = 0;
                dungeon_node->flags_31 = 0;
                break;
            }
        }
    }
    tp_gameInfo.temp_flags.temp_flag_bit_field_34 = dungeon_node->flags_29;  // need to add condition here to only update temp flags if in a dungeon
    tp_gameInfo.temp_flags.temp_flag_bit_field_33 = dungeon_node->flags_28;

    sprintf(lines[SELECT_DUNGEON_INDEX].line, "dungeon: <%s>", dungeon_options[select_dungeon_index].member);

    Utilities::render_lines(font, lines, cursor.y, LINES, 150.0f);
};
