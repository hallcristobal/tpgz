#include "utils/card.hpp"
#include "libtp_c/include/system.h"
#include "fifo_queue.h"

namespace Utilities {
    void load_mem_card(MemCard::Card &card) {
        card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
        if (card.card_result == Ready) {
            uint8_t buff[8192] __attribute__((aligned(32)));
            card.card_result = CARDRead(&card.card_info, buff, card.sector_size, 0x0000);
            if (card.card_result == Ready) {
                tp_osReport("loaded card!");
                FIFOQueue::push("loaded card!", Queue);
                SaveLayout& save_layout_ptr = *(SaveLayout*)buff;
                tp_memcpy(CheatItems, save_layout_ptr.CheatItems, sizeof(CheatItems));
                tp_memcpy(ToolItems, save_layout_ptr.ToolItems, sizeof(ToolItems));
                tp_memcpy(SceneItems, save_layout_ptr.SceneItems, sizeof(SceneItems));
                tp_memcpy(Watches, save_layout_ptr.Watches, sizeof(Watches));
                tp_memcpy(sprite_offsets, save_layout_ptr.sprite_offsets, sizeof(sprite_offsets));
                g_drop_shadows = save_layout_ptr.g_drop_shadows;
                g_area_reload_behavior = save_layout_ptr.g_area_reload_behavior;
                g_cursor_color = save_layout_ptr.g_cursor_color;
            } else {
                tp_osReport("failed to load");
                FIFOQueue::push("failed to load", Queue);
            }
            card.card_result = CARDClose(&card.card_info);
        }
    }

    void load_gz_card(bool &card_load) {
        uint8_t frame_count = TP::get_frame_count();
        if (card_load && frame_count > 200) {
            static MemCard::Card card;
            card.file_name = "tpgz01";
            card.sector_size = SECTOR_SIZE;
            sprintf(card.file_name_buffer, card.file_name);
            card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
            if (card.card_result == Ready) {
                Utilities::load_mem_card(card);
                card_load = false;
            } else {
                card_load = false;
            }
        }
    }
}