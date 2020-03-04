#include "menu.h"
#include "input_viewer.h"
#include "controller.h"
#include "utils.h"
#include "timer.h"
#include "commands.h"
#include "gorge.h"
#include "rollcheck.h"
#define LINES 6

static int cursor = 2;
bool g_roll_check_active;
bool g_gorge_active;

Line lines[LINES] = {
    {"tools", 0, "", false},
    {"", 1, "", false},
    {"input viewer", 2, "show current inputs (buttons only for now)", true, &iv_visible},
    {"timer", 3, "in game timer (frames only for now). Z+A to start/stop, Z+B to reset", true, &timer_visible},
    {"roll check", 4, "see how bad u are at chaining rolls", true, &g_roll_check_active},
    {"gorge void", 5, "gorge void practice -- use L + Z to warp to to kak gorge", true, &g_gorge_active}};

void ToolsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        tools_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);

    if (button_is_pressed(Controller::A)) {
        switch (cursor) {
            case INPUT_VIEWER_INDEX: {
                iv_visible = !iv_visible;
                break;
            }
            case TIMER_INDEX: {
                timer_visible = !timer_visible;
                Commands::enable_command(Commands::TIMER_TOGGLE);
                Commands::enable_command(Commands::TIMER_RESET);
                break;
            }
            case GORGE_INDEX: {
                g_gorge_active = !g_gorge_active;
                break;
            }
            case ROLL_INDEX: {
                g_roll_check_active = !g_roll_check_active;
                break;
            }
        }
    }
}  // namespace Tools