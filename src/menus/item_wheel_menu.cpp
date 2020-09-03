#include <stdio.h>
#include "libtp_c/include/system.h"
#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"

#define ITEM_WHEEL_SLOTS 24
#define LINES ITEM_WHEEL_SLOTS
#define TOTAL_ITEMS 58

static Cursor cursor = {0,0};
int listIdx = 0;
int new_int_item_id;
bool init_once = false;
bool item_wheel_visible;

// probably a better way to do this
bool IsInItemIDEnum(int val) {
    switch (val) {
        case OOCCOO_SR: {
            return true;
            break;
        }
        case OOCCOO_JR: {
            return true;
            break;
        }
        case OOCCOOS_NOTE: {
            return true;
            break;
        }
        case HAWKEYE: {
            return true;
            break;
        }
        case GALE_BOOMERANG: {
            return true;
            break;
        }
        case SPINNER: {
            return true;
            break;
        }
        case BALL_AND_CHAIN: {
            return true;
            break;
        }
        case HEROS_BOW: {
            return true;
            break;
        }
        case CLAWSHOT: {
            return true;
            break;
        }
        case IRON_BOOTS: {
            return true;
            break;
        }
        case DOMINION_ROD: {
            return true;
            break;
        }
        case DOUBLE_CLAWSHOT: {
            return true;
            break;
        }
        case LANTERN: {
            return true;
            break;
        }
        case SLINGSHOT: {
            return true;
            break;
        }
        case FISHING_ROD: {
            return true;
            break;
        }
        case EMPTY_BOMBBAG: {
            return true;
            break;
        }
        case ROD_BEE_LARVA: {
            return true;
            break;
        }
        case ROD_CORAL_EARRING: {
            return true;
            break;
        }
        case ROD_WORM: {
            return true;
            break;
        }
        case ROD_CORAL_EARRING_BEE_LARVA: {
            return true;
            break;
        }
        case ROD_CORAL_EARRING_WORM: {
            return true;
            break;
        }
        case EMPTY_BOTTLE: {
            return true;
            break;
        }
        case RED_POTION: {
            return true;
            break;
        }
        case MAGIC_POTION: {
            return true;
            break;
        }
        case BLUE_POTION: {
            return true;
            break;
        }
        case MILK: {
            return true;
            break;
        }
        case HALF_MILK: {
            return true;
            break;
        }
        case LANTERN_OIL: {
            return true;
            break;
        }
        case WATER: {
            return true;
            break;
        }
        case NASTY_SOUP: {
            return true;
            break;
        }
        case HOT_SPRING_WATER: {
            return true;
            break;
        }
        case FAIRY: {
            return true;
            break;
        }
        case REGULAR_BOMBS: {
            return true;
            break;
        }
        case WATER_BOMBS: {
            return true;
            break;
        }
        case BOMBLINGS: {
            return true;
            break;
        }
        case FAIRY_TEARS: {
            return true;
            break;
        }
        case WORM: {
            return true;
            break;
        }
        case BEE_LARVA: {
            return true;
            break;
        }
        case RARE_CHU: {
            return true;
            break;
        }
        case RED_CHU: {
            return true;
            break;
        }
        case BLUE_CHU: {
            return true;
            break;
        }
        case GREEN_CHU: {
            return true;
            break;
        }
        case YELLOW_CHU: {
            return true;
            break;
        }
        case PURPLE_CHU: {
            return true;
            break;
        }
        case SIMPLE_SOUP: {
            return true;
            break;
        }
        case GOOD_SOUP: {
            return true;
            break;
        }
        case SUPERB_SOUP: {
            return true;
            break;
        }
        case RENADOS_LETTER: {
            return true;
            break;
        }
        case INVOICE: {
            return true;
            break;
        }
        case WOODEN_STATUE: {
            return true;
            break;
        }
        case ILIAS_CHARM: {
            return true;
            break;
        }
        case HORSE_CALL: {
            return true;
            break;
        }
        case AURUS_MEMO: {
            return true;
            break;
        }
        case ASHEIS_SKETCH: {
            return true;
            break;
        }
        case ANCIENT_SKY_BOOK_EMPTY: {
            return true;
            break;
        }
        case ANCIENT_SKY_BOOK_PARTIAL: {
            return true;
            break;
        }
        case ANCIENT_SKY_BOOK_FILLED: {
            return true;
            break;
        }
        case NO_ITEM: {
            return true;
            break;
        }
        default: {
            return false;
            break;
        }
    }
}

const SlotItem default_items[ITEM_WHEEL_SLOTS] = {
    {SLOT_0, GALE_BOOMERANG},
    {SLOT_1, LANTERN},
    {SLOT_2, SPINNER},
    {SLOT_3, IRON_BOOTS},
    {SLOT_4, HEROS_BOW},
    {SLOT_5, HAWKEYE},
    {SLOT_6, BALL_AND_CHAIN},
    {SLOT_7, NO_ITEM},
    {SLOT_8, DOMINION_ROD},
    {SLOT_9, CLAWSHOT},
    {SLOT_10, DOUBLE_CLAWSHOT},
    {SLOT_11, EMPTY_BOTTLE},
    {SLOT_12, EMPTY_BOTTLE},
    {SLOT_13, EMPTY_BOTTLE},
    {SLOT_14, EMPTY_BOTTLE},
    {SLOT_15, EMPTY_BOMBBAG},
    {SLOT_16, EMPTY_BOMBBAG},
    {SLOT_17, EMPTY_BOMBBAG},
    {SLOT_18, OOCCOO_SR},
    {SLOT_19, AURUS_MEMO},
    {SLOT_20, FISHING_ROD},
    {SLOT_21, HORSE_CALL},
    {SLOT_22, ANCIENT_SKY_BOOK_EMPTY},
    {SLOT_23, SLINGSHOT}};

SlotItem slot_items[ITEM_WHEEL_SLOTS] = {
    {SLOT_0, tp_gameInfo.inventory.item_values.gale_boomerang_id},
    {SLOT_1, tp_gameInfo.inventory.item_values.lantern_id},
    {SLOT_2, tp_gameInfo.inventory.item_values.spinner_id},
    {SLOT_3, tp_gameInfo.inventory.item_values.iron_boots_id},
    {SLOT_4, tp_gameInfo.inventory.item_values.hero_s_bow_id},
    {SLOT_5, tp_gameInfo.inventory.item_values.hawkeye_id},
    {SLOT_6, tp_gameInfo.inventory.item_values.ball_and_chain_id},
    {SLOT_7, tp_gameInfo.inventory.item_values._unk_0},
    {SLOT_8, tp_gameInfo.inventory.item_values.dominion_rod_id},
    {SLOT_9, tp_gameInfo.inventory.item_values.clawshot_id},
    {SLOT_10, tp_gameInfo.inventory.item_values.double_clawshot_id},
    {SLOT_11, tp_gameInfo.inventory.item_values.bottle_1_id},
    {SLOT_12, tp_gameInfo.inventory.item_values.bottle_2_id},
    {SLOT_13, tp_gameInfo.inventory.item_values.bottle_3_id},
    {SLOT_14, tp_gameInfo.inventory.item_values.bottle_4_id},
    {SLOT_15, tp_gameInfo.inventory.item_values.bomb_bag_1_id},
    {SLOT_16, tp_gameInfo.inventory.item_values.bomb_bag_2_id},
    {SLOT_17, tp_gameInfo.inventory.item_values.bomb_bag_3_id},
    {SLOT_18, tp_gameInfo.inventory.item_values.ooccoo_id},
    {SLOT_19, tp_gameInfo.inventory.item_values.auru_s_memo_ashei_s_sketch_id},
    {SLOT_20, tp_gameInfo.inventory.item_values.fishing_rod_earring_id},
    {SLOT_21, tp_gameInfo.inventory.item_values.horse_call_id},
    {SLOT_22, tp_gameInfo.inventory.item_values.ancient_sky_book_id},
    {SLOT_23, tp_gameInfo.inventory.item_values.slingshot_id}};

void set_slot_to_item_id(int slot_id, int item_id) {
    // find the right slot
    for (int i = 0; i < ITEM_WHEEL_SLOTS; i++) {
        if (slot_items[i].slot_id == slot_id) {
            // set it to the new item id passed in
            slot_items[i].item_id = item_id;
        } else {
            continue;
        }
    }
}

void increment_slot_item(uint8_t& current_internal_item_id, int slot_id) {
    current_internal_item_id = slot_items[slot_id].item_id;
    do {
        current_internal_item_id++;
    } while (IsInItemIDEnum(current_internal_item_id) == false);
    set_slot_to_item_id(slot_id, current_internal_item_id);
}

void decrement_slot_item(uint8_t& current_internal_item_id, int slot_id) {
    current_internal_item_id = slot_items[slot_id].item_id;
    do {
        --current_internal_item_id;
    } while (IsInItemIDEnum(current_internal_item_id) == false);
    set_slot_to_item_id(slot_id, current_internal_item_id);
}

uint8_t find_next_empty_slot() {
    for (size_t i = 0; i < ITEM_WHEEL_SLOTS; ++i) {
        if (tp_gameInfo.inventory.item_wheel.slot[i] == 0xFF) {
            return i;
        }
    }
    return 0xFF;
}

void try_add_item(uint8_t inventory_slot) {
    auto item_wheel = tp_gameInfo.inventory.item_wheel.slot;
    uint8_t slot = 0xFF;
    bool item_already_in_wheel = false;
    if (inventory_slot >= ITEM_WHEEL_SLOTS) {
        return;
    }
    for (size_t i = 0; i < ITEM_WHEEL_SLOTS; ++i) {
        if (slot == 0xFF && item_wheel[i] == 0xFF) {
            slot = i;
        }
        if (item_wheel[i] == inventory_slot) {
            item_already_in_wheel = true;
            break;
        }
    }
    if (!item_already_in_wheel && slot != 0xFF) {
        item_wheel[slot] = inventory_slot;
    }
}

void try_remove_item(uint8_t inventory_slot) {
    auto item_wheel = tp_gameInfo.inventory.item_wheel.slot;
    uint8_t slot = 0xFF;
    if (inventory_slot >= ITEM_WHEEL_SLOTS) {
        return;
    }
    for (size_t i = 0; i < ITEM_WHEEL_SLOTS; ++i) {
        if (item_wheel[i] == inventory_slot) {
            slot = i;
            break;
        }
    }
    if (slot != 0xFF) {
        uint8_t last_slot = find_next_empty_slot();
        if (last_slot > ITEM_WHEEL_SLOTS) {
            last_slot = ITEM_WHEEL_SLOTS;
        }
        if (last_slot > 0) {
            last_slot--;
        }
        item_wheel[slot] = item_wheel[last_slot];
        item_wheel[last_slot] = 0xFF;
    }
}

const ItemLookup lookup_table[TOTAL_ITEMS] = {
    {OOCCOO_SR, "ooccoo sr."},
    {OOCCOO_JR, "ooccoo jr."},
    {OOCCOOS_NOTE, "ooccoo's note"},
    {HAWKEYE, "hawkeye"},
    {GALE_BOOMERANG, "gale boomerang"},
    {SPINNER, "spinner"},
    {BALL_AND_CHAIN, "ball and chain"},
    {HEROS_BOW, "hero's bow"},
    {CLAWSHOT, "clawshot"},
    {IRON_BOOTS, "iron boots"},
    {DOMINION_ROD, "dominion rod"},
    {DOUBLE_CLAWSHOT, "double clawshot"},
    {LANTERN, "lantern"},
    {SLINGSHOT, "slingshot"},
    {FISHING_ROD, "fishing rod"},
    {EMPTY_BOMBBAG, "empty bomb bag"},
    {ROD_BEE_LARVA, "fishing rod (bee larva)"},
    {ROD_CORAL_EARRING, "fishing rod (coral earring)"},
    {ROD_WORM, "fishing rod (worm)"},
    {ROD_CORAL_EARRING_BEE_LARVA, "fishing rod (coral earring/bee larva)"},
    {ROD_CORAL_EARRING_WORM, "fishing rod (coral earring/worm)"},
    {EMPTY_BOTTLE, "empty bottle"},
    {RED_POTION, "red potion"},
    {MAGIC_POTION, "magic potion"},
    {BLUE_POTION, "blue potion"},
    {MILK, "milk"},
    {HALF_MILK, "half milk"},
    {LANTERN_OIL, "lantern oil"},
    {WATER, "water"},
    {NASTY_SOUP, "nasty soup"},
    {HOT_SPRING_WATER, "hot spring water"},
    {FAIRY, "fairy"},
    {REGULAR_BOMBS, "regular bombs"},
    {WATER_BOMBS, "water bombs"},
    {BOMBLINGS, "bomblings"},
    {FAIRY_TEARS, "fairy tears"},
    {WORM, "worm"},
    {BEE_LARVA, "bee larva"},
    {RARE_CHU, "rare chu"},
    {RED_CHU, "red chu"},
    {BLUE_CHU, "blue chu"},
    {GREEN_CHU, "green chu"},
    {YELLOW_CHU, "yellow chu"},
    {PURPLE_CHU, "purple chu"},
    {SIMPLE_SOUP, "simple soup"},
    {GOOD_SOUP, "good soup"},
    {SUPERB_SOUP, "superb soup"},
    {RENADOS_LETTER, "renados letter"},
    {INVOICE, "invoice"},
    {WOODEN_STATUE, "wooden statue"},
    {ILIAS_CHARM, "ilia's charm"},
    {HORSE_CALL, "horse call"},
    {AURUS_MEMO, "auru's memo"},
    {ASHEIS_SKETCH, "ashei's sketch"},
    {ANCIENT_SKY_BOOK_EMPTY, "ancient sky book (empty)"},
    {ANCIENT_SKY_BOOK_PARTIAL, "ancient sky book (partial)"},
    {ANCIENT_SKY_BOOK_FILLED, "ancient sky book (filled)"},
    {NO_ITEM, "no item"}};

Line lines[LINES] = {
    {"", SLOT_0, "", false, nullptr, false},
    {"", SLOT_1, "", false, nullptr, false},
    {"", SLOT_2, "", false, nullptr, false},
    {"", SLOT_3, "", false, nullptr, false},
    {"", SLOT_4, "", false, nullptr, false},
    {"", SLOT_5, "", false, nullptr, false},
    {"", SLOT_6, "", false, nullptr, false},
    {"", SLOT_7, "", false, nullptr, false},
    {"", SLOT_8, "", false, nullptr, false},
    {"", SLOT_9, "", false, nullptr, false},
    {"", SLOT_10, "", false, nullptr, false},
    {"", SLOT_11, "", false, nullptr, false},
    {"", SLOT_12, "", false, nullptr, false},
    {"", SLOT_13, "", false, nullptr, false},
    {"", SLOT_14, "", false, nullptr, false},
    {"", SLOT_15, "", false, nullptr, false},
    {"", SLOT_16, "", false, nullptr, false},
    {"", SLOT_17, "", false, nullptr, false},
    {"", SLOT_18, "", false, nullptr, false},
    {"", SLOT_19, "", false, nullptr, false},
    {"", SLOT_20, "", false, nullptr, false},
    {"", SLOT_21, "", false, nullptr, false},
    {"", SLOT_22, "", false, nullptr, false},
    {"", SLOT_23, "", false, nullptr, false}};

void ItemWheelMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        item_wheel_visible = false;
        inventory_visible = true;
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    // populate the default line name and description
    for (int i = 0; i < LINES; i++) {
        for (int k = 0; k < ITEM_WHEEL_SLOTS; k++) {
            // find the right slot to pull the value from
            if (slot_items[k].slot_id == i) {
                new_int_item_id = slot_items[k].item_id;
            }
        }
        for (int j = 0; j < TOTAL_ITEMS; j++) {
            if (lookup_table[j].item_id == new_int_item_id) {
                sprintf(lines[i].line, "slot %d: %s", default_items[i].slot_id, lookup_table[j].item_description);
            }
            if (lookup_table[j].item_id == default_items[i].item_id) {
                sprintf(lines[i].description, "slot %d default: %s. Press Z to set to default", i, lookup_table[j].item_description);
            } else {
                continue;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES);

    // update to current items
    for (size_t i = 0; i < ITEM_WHEEL_SLOTS; ++i) {
        slot_items[i].item_id = tp_gameInfo.inventory.item_values.value[i];
    }

    // check selected slot
    uint8_t current_item_slot = ITEM_WHEEL_SLOTS;
    if (cursor.y >= 0 && cursor.y < ITEM_WHEEL_SLOTS) {
        current_item_slot = cursor.y;
    }

    if (Controller::button_is_pressed(Controller::DPAD_RIGHT)
        || Controller::button_is_pressed(Controller::DPAD_LEFT)) {
        auto change_slot_item = Controller::button_is_pressed(Controller::DPAD_RIGHT) ? increment_slot_item : decrement_slot_item;
        uint8_t current_internal_item_id;
        if (current_item_slot < ITEM_WHEEL_SLOTS) {
            change_slot_item(current_internal_item_id, current_item_slot);
            tp_gameInfo.inventory.item_values.value[current_item_slot] = current_internal_item_id;
            if (current_internal_item_id != 0xFF) {
                try_add_item(current_item_slot);
            } else {
                try_remove_item(current_item_slot);
            }
        }
    }

    if (Controller::button_is_down(Controller::Z) && !Controller::button_is_held(Controller::Z)) {
        if (current_item_slot < ITEM_WHEEL_SLOTS) {
            tp_gameInfo.inventory.item_values.value[current_item_slot] = default_items[current_item_slot].item_id;
            set_slot_to_item_id(current_item_slot, default_items[current_item_slot].item_id);
            if (default_items[current_item_slot].item_id != 0xFF) {
                try_add_item(current_item_slot);
            } else {
                try_remove_item(current_item_slot);
            }
        }
    }
};