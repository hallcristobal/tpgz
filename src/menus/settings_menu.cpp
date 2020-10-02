#include "gcn_c/include/card.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "controller.h"
#include "menu.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "utils/card.hpp"
#include <stdio.h>
#include "fifo_queue.h"

#define LINES 6
#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6

static Cursor cursor = {0, 0};
bool g_drop_shadows = true;
bool init_once = false;
bool settings_visible;
int g_area_reload_behavior;
int g_cursor_color;
bool g_cursor_color_flag;

Line lines[LINES] = {
    {"", AREA_RELOAD_BEHAVIOR_INDEX, "load area = Reload last area; load file = Reload last file", false, nullptr, MAX_RELOAD_OPTIONS},
    {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr, MAX_CURSOR_COLOR_OPTIONS},
    {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters", true, &g_drop_shadows},
    {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
    {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
    {"menu positions", POS_SETTINGS_MENU_INDEX, "Change menu object positions (A to toggle selection, DPad to move)", false}};

void SettingsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        settings_visible = false;
        mm_visible = true;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    //Utilities::move_cursor(cursor, LINES, 2);

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case DROP_SHADOWS_INDEX: {
                g_drop_shadows = !g_drop_shadows;
                break;
            };
            case POS_SETTINGS_MENU_INDEX: {
                settings_visible = false;
                pos_settings_visible = true;
                return;
            };
            case SAVE_CARD_INDEX: {
                char buf[8192] __attribute__((aligned(32)));
                SaveLayout& save_layout = *(SaveLayout*)buf;
                static MemCard::Card card;
                card.file_name = "tpgz01";
                card.sector_size = SECTOR_SIZE;
                sprintf(card.file_name_buffer, card.file_name);

                tp_memcpy(save_layout.CheatItems, CheatItems, sizeof(CheatItems));
                tp_memcpy(save_layout.ToolItems, ToolItems, sizeof(ToolItems));
                tp_memcpy(save_layout.SceneItems, SceneItems, sizeof(SceneItems));
                tp_memcpy(save_layout.Watches, Watches, sizeof(Watches));
                tp_memcpy(save_layout.sprite_offsets, sprite_offsets, sizeof(sprite_offsets));
                save_layout.g_drop_shadows = g_drop_shadows;
                save_layout.g_area_reload_behavior = g_area_reload_behavior;
                save_layout.g_cursor_color = g_cursor_color;

                card.card_result = CARDProbeEx(0, nullptr, &card.sector_size);
                if (card.card_result == Ready) {
                    card.card_result = CARDCreate(0, card.file_name_buffer, card.sector_size, &card.card_info);
                    if (card.card_result == Ready || card.card_result == Exist) {
                        card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
                        if (card.card_result == Ready) {
                            card.card_result = CARDWrite(&card.card_info, &save_layout, card.sector_size, 0);
                            if (card.card_result == Ready) {
                                tp_osReport("saved card!");
                                FIFOQueue::push("saved card!", Queue);
                            } else {
                                tp_osReport("failed to save");
                                FIFOQueue::push("failed to save", Queue);
                            }
                            card.card_result = CARDClose(&card.card_info);
                        }
                    }
                }
                break;
            };
            case LOAD_CARD_INDEX: {
                static MemCard::Card card;
                card.file_name = "tpgz01";
                card.sector_size = SECTOR_SIZE;
                sprintf(card.file_name_buffer, card.file_name);
                card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
                Utilities::load_mem_card(card);
                break;
            }
        }
    }

    ListMember reload_options[MAX_RELOAD_OPTIONS] = {
        "load area",
        "load file"};

    ListMember cursor_color_options[MAX_CURSOR_COLOR_OPTIONS] = {
        "green",
        "blue",
        "red",
        "orange",
        "yellow",
        "purple"};

    // handle list rendering
    switch (cursor.y) {
        case AREA_RELOAD_BEHAVIOR_INDEX: {
            cursor.x = g_area_reload_behavior;
            Utilities::move_cursor(cursor, LINES, MAX_RELOAD_OPTIONS);
            if (cursor.y == AREA_RELOAD_BEHAVIOR_INDEX) {
                g_area_reload_behavior = cursor.x;
            }
            break;
        }

        case CURSOR_COLOR_INDEX: {
            cursor.x = g_cursor_color;
            Utilities::move_cursor(cursor, LINES, MAX_CURSOR_COLOR_OPTIONS);
            if (cursor.y == CURSOR_COLOR_INDEX) {
                g_cursor_color = cursor.x;
            }
            break;
        }
        default: {
            Utilities::move_cursor(cursor, LINES, 2);
            break;
        }
    }
    sprintf(lines[AREA_RELOAD_BEHAVIOR_INDEX].line, "area reload behavior: <%s>", reload_options[g_area_reload_behavior].member);
    sprintf(lines[CURSOR_COLOR_INDEX].line, "cursor color:         <%s>", cursor_color_options[g_cursor_color].member);

    Utilities::render_lines(font, lines, cursor.y, LINES, 210.0f);
};