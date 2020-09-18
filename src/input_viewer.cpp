#include <stdio.h>
#define GXFlush_addr 0x8035becc
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/flag.h"
#include "controller.h"
#include "font.h"
#include "input_viewer.h"
#include "menu.h"
#include "gcn_c/include/gfx.h"

#define tp_mPadAStick (*(Vec2*)(0x804344E0))
#define tp_mPadACStick (*(Vec2*)(0x80434520))

#define LINE_WIDTH 1.0f

bool iv_visible;
GXTexObj _ivTexObj;
uint8_t _iv_text_data[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

struct Vec2 {
    float x, y;
};

namespace InputViewer {
    void init() {
        memset(&_ivTexObj, 0x0, sizeof(GXTexObj));
        GX_InitTexObj(&_ivTexObj, (void*)_iv_text_data, 4, 4, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    }

    void add_vertex(uint32_t color, Vec2 p) {
        GX_Position2f32(p.x, p.y);
        GX_Color1u32(color);
        GX_TexCoord2f32(0.0f, 1.0f);
    }

    void display_quad(uint32_t color, Vec2 p[4]) {
        GX_SetLineWidth(0x10, GX_TO_ZERO);
        GX_Begin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            add_vertex(color, p[0]);
            add_vertex(color, p[1]);
            add_vertex(color, p[3]);
            add_vertex(color, p[2]);
        GX_End();
    }

    void display_stick(uint32_t color, Vec2 pos, float size) {
        float s2 = size / 2;
        Vec2 positions[4];
        positions[0] = {pos.x - s2, pos.y};
        positions[1] = {pos.x - s2 * 0.7071f, pos.y - s2 * 0.7071f};
        positions[2] = {pos.x, pos.y - s2};
        positions[3] = {pos.x, pos.y};
        display_quad(color, positions);
        positions[0] = {pos.x, pos.y - s2};
        positions[1] = {pos.x + s2 * 0.7071f, pos.y - s2 * 0.7071f};
        positions[2] = {pos.x + s2, pos.y};
        positions[3] = {pos.x, pos.y};
        display_quad(color, positions);
        positions[0] = {pos.x + s2, pos.y};
        positions[1] = {pos.x + s2 * 0.7071f, pos.y + s2 * 0.7071f};
        positions[2] = {pos.x, pos.y + s2};
        positions[3] = {pos.x, pos.y};
        display_quad(color, positions);
        positions[0] = {pos.x, pos.y + s2};
        positions[1] = {pos.x - s2 * 0.7071f, pos.y + s2 * 0.7071f};
        positions[2] = {pos.x - s2, pos.y};
        positions[3] = {pos.x, pos.y};
        display_quad(color, positions);
    }

    void display_stick_outline(uint32_t color, Vec2 pos, float size) {
        float s2 = size / 2;
        float s2_line = (s2 - LINE_WIDTH);
        Vec2 positions[4];
        positions[0] = {pos.x - s2, pos.y};
        positions[1] = {pos.x - s2 * 0.7071f, pos.y - s2 * 0.7071f};
        positions[2] = {pos.x - s2_line * 0.7071f, pos.y - s2_line * 0.7071f};
        positions[3] = {pos.x - s2_line, pos.y};
        display_quad(color, positions);
        positions[0] = {pos.x - s2 * 0.7071f, pos.y - s2 * 0.7071f};
        positions[1] = {pos.x, pos.y - s2};
        positions[2] = {pos.x, pos.y - s2_line};
        positions[3] = {pos.x - s2_line * 0.7071f, pos.y - s2_line * 0.7071f};
        display_quad(color, positions);

        positions[0] = {pos.x, pos.y - s2};
        positions[1] = {pos.x + s2 * 0.7071f, pos.y - s2 * 0.7071f};
        positions[2] = {pos.x + s2_line * 0.7071f, pos.y - s2_line * 0.7071f};
        positions[3] = {pos.x, pos.y - s2_line};
        display_quad(color, positions);
        positions[0] = {pos.x + s2 * 0.7071f, pos.y - s2 * 0.7071f};
        positions[1] = {pos.x + s2, pos.y};
        positions[2] = {pos.x + s2_line, pos.y};
        positions[3] = {pos.x + s2_line * 0.7071f, pos.y - s2_line * 0.7071f};
        display_quad(color, positions);

        positions[0] = {pos.x + s2, pos.y};
        positions[1] = {pos.x + s2 * 0.7071f, pos.y + s2 * 0.7071f};
        positions[2] = {pos.x + s2_line * 0.7071f, pos.y + s2_line * 0.7071f};
        positions[3] = {pos.x + s2_line, pos.y};
        display_quad(color, positions);
        positions[0] = {pos.x + s2 * 0.7071f, pos.y + s2 * 0.7071f};
        positions[1] = {pos.x, pos.y + s2};
        positions[2] = {pos.x, pos.y + s2_line};
        positions[3] = {pos.x + s2_line * 0.7071f, pos.y + s2_line * 0.7071f};
        display_quad(color, positions);

        positions[0] = {pos.x, pos.y + s2};
        positions[1] = {pos.x - s2 * 0.7071f, pos.y + s2 * 0.7071f};
        positions[2] = {pos.x - s2_line * 0.7071f, pos.y + s2_line * 0.7071f};
        positions[3] = {pos.x, pos.y + s2_line};
        display_quad(color, positions);
        positions[0] = {pos.x - s2 * 0.7071f, pos.y + s2 * 0.7071f};
        positions[1] = {pos.x - s2, pos.y};
        positions[2] = {pos.x - s2_line, pos.y};
        positions[3] = {pos.x - s2_line * 0.7071f, pos.y + s2_line * 0.7071f};
        display_quad(color, positions);
    }

    void render(Font& font) {
        using namespace Controller;

        if (button_is_down(A)) {
            font.renderChars("A", 550.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0x00CC00FF);
        }

        if (button_is_down(B)) {
            font.renderChars("B", 535.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xDC143CFF);
        }

        if (button_is_down(X)) {
            font.renderChars("X", 565.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(Y)) {
            font.renderChars("Y", 550.f + viewer_x_offset, 425.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(Z)) {
            font.renderChars("Z", 565.f + viewer_x_offset, 425.0f + viewer_y_offset, 0x8A2BE2FF);
        }

        if (button_is_down(START)) {
            font.renderChars("S", 500.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_LEFT)) {
            font.renderChars("DL", 432.f + viewer_x_offset, 427.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_DOWN)) {
            font.renderChars("DD", 450.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_RIGHT)) {
            font.renderChars("DR", 470.f + viewer_x_offset, 427.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_UP)) {
            font.renderChars("DU", 450.f + viewer_x_offset, 414.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(L)) {
            font.renderChars("L", 500.f + viewer_x_offset, 425.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(R)) {
            font.renderChars("R", 515.f + viewer_x_offset, 425.0f + viewer_y_offset, 0xFFFFFFFF);
        }

		// stick inputs
        char control_x[5];  // control stick x
        char control_y[5];  // control stick y
        char c_x[5];        // c stick x
        char c_y[5];        // c stick y

        sprintf(control_x, "%d", tp_mPadSticks.control_x);
        sprintf(control_y, "%d", tp_mPadSticks.control_y);
        sprintf(c_x, "%d", tp_mPadSticks.c_x);
        sprintf(c_y, "%d", tp_mPadSticks.c_y);

        font.gz_renderChars(control_x, 295.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(control_y, 330.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(c_x, 365.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);
        font.gz_renderChars(c_y, 400.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);

		// analog input viewer
        // font.gz_renderChars(".", 313.0f + viewer_x_offset, 405.0f + viewer_y_offset, 0xFFFFFFFF, g_drop_shadows);
        // font.gz_renderChars("o", (310.0f + viewer_x_offset) + (tp_mPadSticks.control_x * 0.20), (408.0f + viewer_y_offset) - (tp_mPadSticks.control_y * 0.20), 0xFFFFFFFF, g_drop_shadows);  // radius decreased to 20%
        // font.gz_renderChars(".", 383.0f + viewer_x_offset, 405.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);
        // font.gz_renderChars("o", (380.0f + viewer_x_offset) + (tp_mPadSticks.c_x * 0.20), (408.0f + viewer_y_offset) - (tp_mPadSticks.c_y * 0.20), 0xFFD138FF, g_drop_shadows);  // radius decreased to 20%
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        display_stick(0xFFFFFFFF, {320.0f + tp_mPadAStick.x * 15, 405.0f - tp_mPadAStick.y * 15}, 30.0f);
        display_stick_outline(0xFFFFFFFF, {320.0f, 405.0f}, 45.0f);
        display_stick(0xFFD138FF, {390.0f + tp_mPadACStick.x * 12, 405.0f - tp_mPadACStick.y * 12}, 24.0f);
        display_stick_outline(0xFFD138FF, {390.0f, 405.0f}, 36.0f);
    }
}  // namespace InputViewer