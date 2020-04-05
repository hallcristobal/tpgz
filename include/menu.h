#pragma once
#include "font.h"
#include "timer.h"
#include "input_viewer.h"
#include "cheats.h"
#include <string.h>

// main menu
#define INVENTORY_INDEX 2
#define CHEAT_INDEX 3
#define WARPING_INDEX 4
#define MEMORY_INDEX 5
#define PRACTICE_INDEX 6
#define TOOLS_INDEX 7
#define SETTINGS_INDEX 8
extern bool mm_visible;

// inventory
#define ITEM_WHEEL_INDEX 2
#define PAUSE_MENU_INDEX 3
extern bool inventory_visible;

// item wheel
extern bool item_wheel_visible;
enum ItemID {
    OOCCOO_SR = 37,
    OOCCOO_JR = 39,
    OOCCOOS_NOTE = 45,
    HAWKEYE = 62,
    GALE_BOOMERANG = 64,
    SPINNER,
    BALL_AND_CHAIN,
    HEROS_BOW,
    CLAWSHOT,
    IRON_BOOTS,
    DOMINION_ROD,
    DOUBLE_CLAWSHOT,
    LANTERN,
    MASTER_SWORD,
    FISHING_ROD,
    SLINGSHOT,
    EMPTY_BOMBBAG = 80,
    ROD_BEE_LARVA = 91,
    ROD_CORAL_EARRING,
    ROD_WORM,
    ROD_CORAL_EARRING_BEE_LARVA,
    ROD_CORAL_EARRING_WORM,
    EMPTY_BOTTLE,
    RED_POTION,
    MAGIC_POTION,
    BLUE_POTION,
    MILK,
    HALF_MILK,
    LANTERN_OIL,
    WATER,
    NASTY_SOUP = 106,
    HOT_SPRING_WATER,
    FAIRY,
    REGULAR_BOMBS = 112,
    WATER_BOMBS,
    BOMBLINGS,
    FAIRY_TEARS,
    WORM,
    BEE_LARVA = 118,
    RARE_CHU,
    RED_CHU,
    BLUE_CHU,
    GREEN_CHU,
    YELLOW_CHU,
    PURPLE_CHU,
    SIMPLE_SOUP,
    GOOD_SOUP,
    SUPERB_SOUP,
    RENADOS_LETTER,
    INVOICE,
    WOODEN_STATUE,
    ILIAS_CHARM,
    HORSE_CALL,
    AURUS_MEMO = 144,
    ASHEIS_SKETCH,
    ANCIENT_SKY_BOOK_EMPTY = 233,
    ANCIENT_SKY_BOOK_PARTIAL,
    ANCIENT_SKY_BOOK_FILLED,
    NO_ITEM = 255
};

enum Slot {
    SLOT_0,
    SLOT_1,
    SLOT_2,
    SLOT_3,
    SLOT_4,
    SLOT_5,
    SLOT_6,
    SLOT_7,
    SLOT_8,
    SLOT_9,
    SLOT_10,
    SLOT_11,
    SLOT_12,
    SLOT_13,
    SLOT_14,
    SLOT_15,
    SLOT_16,
    SLOT_17,
    SLOT_18,
    SLOT_19,
    SLOT_20,
    SLOT_21,
    SLOT_22,
    SLOT_23
};

struct SlotItem {
    enum Slot slot_id;
    int item_id;
};

struct ItemLookup {
    enum ItemID item_id;
    char item_description[40];
};

// pause menu
#define stuff 2
extern bool pause_visible;

// cheats
extern bool cheats_visible;

// warping
#define stuff 2
extern bool warping_visible;

// memory
#define stuff 2
extern bool memory_visible;

// practice
enum PracticeIndex {
    ORDON_GATE_CLIP_INDEX = 2,
    BACK_IN_TIME_INDEX,
    GOATS_INDEX,
    HUGO_INDEX,
    EMS_INDEX,
    MIST_INDEX,
    FRST_BIT_INDEX,
    FRST_ESCAPE_INDEX,
    GORGE_VOID_INDEX,
    RUPEE_ROLL_INDEX,
    LANAYRU_GATE_CLIP_INDEX,
    PILLAR_CLIP_INDEX,
    LAKEBED_1_INDEX,
    TOAD_INDEX,
    KARG_INDEX,
    ELDIN_TWILIGHT_INDEX,
    LANAYRU_TWILIGHT_INDEX,
    BOSS_BUG_INDEX,
    IZA_INDEX,
    NORGOR_INDEX,
    SPR_WARP_SKIP_INDEX,
    SPR_INDEX,
    DARK_HAMMER_INDEX,
    LAKEBED_2_INDEX,
    LAKEBED_BK_SKIP_INDEX,
    ONEBOMB_INDEX,
    MDH_TOWER_INDEX,
    MDH_BRIDGE_INDEX,
    BULBLIN_CAMP_INDEX,
    AG_INDEX,
    POE_1_SKIP_INDEX,
    DSS_INDEX,
    STALLORD_INDEX,
    CITS_EARLY_INDEX,
    CITS_1_INDEX,
    AERALFOS_SKIP_INDEX,
    CITS_2_INDEX,
    FAN_TOWER_INDEX,
    ARGOROK_INDEX,
    PALACE_1_INDEX,
    PALACE_2_INDEX,
    EARLY_PLATFORM_INDEX,
    ZANT_INDEX,
    HC_INDEX,
    DARKNUT_INDEX,
    HC_TOWER_INDEX,
    BEAST_GANON_INDEX,
    HORSEBACK_GANON_INDEX
};

extern bool prac_visible;
extern bool inject_save_flag;
extern bool g_load_happened;

// tools
#define TOOL_AMNT 13
namespace Tools {
    enum ToolsIndex {
        INPUT_VIEWER_INDEX = 2,
        TIMER_INDEX,
        ROLL_INDEX,
        GORGE_INDEX,
        FREEZE_ACTOR_INDEX,
        HIDE_ACTOR_INDEX,
        DISABLE_BG_INDEX,
        DISABLE_SFX_INDEX,
        FREEZE_CAMERA_INDEX,
        HIDE_HUD_INDEX,
        TUNIC_COLOR_INDEX
    };

    struct Tool {
        enum ToolsIndex id;
        bool active;
    };

    void apply_cheats();
};  // namespace Tools

extern Tools::Tool ToolItems[TOOL_AMNT];

extern bool tools_visible;
extern int g_tunic_color;
extern bool g_tunic_color_flag;

enum tunic_color {
    GREEN,
    BLUE,
    RED,
    ORANGE,
    YELLOW,
    WHITE,
    CYCLE,
    TUNIC_COLOR_COUNT
};

// settings
enum SettingsIndex {
    LOG_LEVEL_INDEX = 2,
    DROP_SHADOWS_INDEX,
    SAVE_CARD,
    LOAD_CARD
};
extern bool settings_visible;
extern bool g_drop_shadows;

struct SaveLayout {
    Cheats::Cheat CheatItems[CHEAT_AMNT];
    Tools::Tool ToolItems[TOOL_AMNT];
} __attribute__((aligned(32)));

#define MAX_LIST_MEMBER_LENGTH 40
#define MAX_LIST_ITEMS 100
#define MAX_LINE_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 100

struct ListMember {
    char member[MAX_LIST_MEMBER_LENGTH];
};

struct Line {
    char line[MAX_LINE_LENGTH];
    const int idx;
    char description[MAX_DESCRIPTION_LENGTH];
    bool toggleable = false;
    bool* activation_flag;
    bool is_list = false;
    ListMember list_member[MAX_LIST_ITEMS];
    int* list_member_idx;
};

class Menu {
   public:
    Menu() {}
    virtual void render() = 0;
};

class MainMenu : public Menu {
   public:
    MainMenu() : Menu(){};
    static void render(Font& font);
};

class InventoryMenu : public Menu {
   public:
    InventoryMenu() : Menu() {}
    static void render(Font& font);
};

class PauseMenu : public Menu {
   public:
    PauseMenu() : Menu() {}
    static void render(Font& font);
};

class ItemWheelMenu : public Menu {
   public:
    ItemWheelMenu() : Menu() {}
    static void render(Font& font);
};

class CheatsMenu : public Menu {
   public:
    CheatsMenu() : Menu() {}
    static void render(Font& font);
};

class WarpingMenu : public Menu {
   public:
    WarpingMenu() : Menu() {}
    static void render(Font& font);
};

class MemoryMenu : public Menu {
   public:
    MemoryMenu() : Menu() {}
    static void render(Font& font);
};
class PracticeMenu : public Menu {
   public:
    PracticeMenu() : Menu() {}
    static void render(Font& font);
};

class SettingsMenu : public Menu {
   public:
    SettingsMenu() : Menu() {}
    static void render(Font& font);
};

class ToolsMenu : public Menu {
   public:
    ToolsMenu() : Menu() {}
    static void render(Font& font);
};

#define MAX_MENU_RENDER_FLAGS 12

struct MenuRenderFlag {
    bool* activation_flag;
    void (*render_function)(Font& font);
};

MenuRenderFlag MenuRenderFlags[MAX_MENU_RENDER_FLAGS] = {
    {&mm_visible, MainMenu::render},
    {&inventory_visible, InventoryMenu::render},
    {&item_wheel_visible, ItemWheelMenu::render},
    {&warping_visible, WarpingMenu::render},
    {&memory_visible, MemoryMenu::render},
    {&prac_visible, PracticeMenu::render},
    {&cheats_visible, CheatsMenu::render},
    {&settings_visible, SettingsMenu::render},
    {&tools_visible, ToolsMenu::render},
    {&ToolItems[Tools::INPUT_VIEWER_INDEX].active, InputViewer::render},
    {&ToolItems[Tools::TIMER_INDEX].active, Timer::render},
    {&pause_visible, PauseMenu::render}};

namespace MenuRendering {
    void render_active_menus(Font& font) {
        for (int i = 0; i < MAX_MENU_RENDER_FLAGS; i++) {
            if (*MenuRenderFlags[i].activation_flag) {
                MenuRenderFlags[i].render_function(font);
            }
        }
    }
};  // namespace MenuRendering