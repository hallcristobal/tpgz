#include <stdio.h>
#define GXFlush_addr 0x8035becc
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/flag.h"
#include "controller.h"
#include "libtp_c/include/controller.h"
#include "font.h"
#include "input_viewer.h"
#include "menu.h"
#include "gcn_c/include/gfx.h"

#define tp_mPadTriggers (*(Triggers*)(0x80434430))
#define tp_mPadAStick (*(Vec2*)(0x804344E0))
#define tp_mPadACStick (*(Vec2*)(0x80434520))

bool iv_visible;
GXTexObj _ivTexObj;
uint8_t _iv_text_data[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

struct Vec2 {
    float x, y;
};

struct Triggers {
    float l, r;
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

    void draw_quad(uint32_t color, Vec2 p[4]) {
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_Begin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            add_vertex(color, p[0]);
            add_vertex(color, p[1]);
            add_vertex(color, p[3]);
            add_vertex(color, p[2]);
        GX_End();
    }

    void draw_quad_outline(uint32_t color, Vec2 p[4]) {
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_SetLineWidth(0x10, GX_TO_ZERO);
        GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 5);
            add_vertex(color, p[0]);
            add_vertex(color, p[1]);
            add_vertex(color, p[2]);
            add_vertex(color, p[3]);
            add_vertex(color, p[0]);
        GX_End();
    }

    void draw_stick(uint32_t color, Vec2 pos, float size) {
        float s2 = size / 2;
        float dx1 = 0;
        float dy1 = -s2;
        float dx2 = s2 * 0.7071f;
        float dy2 = - s2 * 0.7071f;
        float tmp;
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 8);
            for (uint8_t i = 0; i < 4; ++i) {
                add_vertex(color, {pos.x + dx1, pos.y + dy1});
                add_vertex(color, {pos.x + dx2, pos.y + dy2});
                tmp = dx1;
                dx1 = -dy1;
                dy1 = tmp;
                tmp = dx2;
                dx2 = -dy2;
                dy2 = tmp;
            }
        GX_End();
    }

    void draw_stick_outline(uint32_t color, Vec2 pos, float size) {
        float s2 = size / 2;
        float dx1 = 0;
        float dy1 = -s2;
        float dx2 = s2 * 0.7071f;
        float dy2 = - s2 * 0.7071f;
        float tmp;
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_SetLineWidth(0x10, GX_TO_ZERO);
        GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 9);
            for (uint8_t i = 0; i < 4; ++i) {
                add_vertex(color, {pos.x + dx1, pos.y + dy1});
                add_vertex(color, {pos.x + dx2, pos.y + dy2});
                tmp = dx1;
                dx1 = -dy1;
                dy1 = tmp;
                tmp = dx2;
                dx2 = -dy2;
                dy2 = tmp;
            }
            add_vertex(color, {pos.x + dx1, pos.y + dy1});
        GX_End();
    }

    void draw_rect(uint32_t color, Vec2 pos, Vec2 dim) {
        Vec2 vertices[4] = {
            {pos.x - dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y + dim.y / 2},
            {pos.x - dim.x / 2, pos.y + dim.y / 2}};
        draw_quad(color, vertices);
    }

    void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim) {
        Vec2 vertices[4] = {
            {pos.x - dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y + dim.y / 2},
            {pos.x - dim.x / 2, pos.y + dim.y / 2}};
        draw_quad_outline(color, vertices);
    }

    void draw_cross(uint32_t color, Vec2 pos, float size) {
        int branch_width = 4.f * size;
        int branch_length = 5.f * size;
        int branch_offset = (branch_width / 2 + branch_length / 2);
        draw_rect_outline(color, {pos.x - branch_offset + viewer_x_offset, pos.y + viewer_y_offset}, {branch_length, branch_width});
        if (Controller::button_is_down(Controller::DPAD_LEFT)) {
            draw_rect(color, {pos.x - branch_offset + viewer_x_offset, pos.y + viewer_y_offset}, {branch_length, branch_width});
        }

        draw_rect_outline(color, {pos.x + viewer_x_offset, pos.y + branch_offset + viewer_y_offset}, {branch_width, branch_length});
        if (Controller::button_is_down(Controller::DPAD_DOWN)) {
            draw_rect(color, {pos.x + viewer_x_offset, pos.y + branch_offset + viewer_y_offset}, {branch_width, branch_length});
        }

        draw_rect_outline(color, {pos.x + branch_offset + viewer_x_offset, pos.y + viewer_y_offset}, {branch_length, branch_width});
        if (Controller::button_is_down(Controller::DPAD_RIGHT)) {
            draw_rect(color, {pos.x + branch_offset + viewer_x_offset, pos.y + viewer_y_offset}, {branch_length, branch_width});
        }

        draw_rect_outline(color, {pos.x + viewer_x_offset, pos.y - branch_offset + viewer_y_offset}, {branch_width, branch_length});
        if (Controller::button_is_down(Controller::DPAD_UP)) {
            draw_rect(color, {pos.x + viewer_x_offset, pos.y - branch_offset + viewer_y_offset}, {branch_width, branch_length});
        }
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

        draw_cross(0xFFFFFFFF, {430.f + viewer_x_offset, 420.f + viewer_y_offset}, 2.f);

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
        font.gz_renderChars(c_x, 355.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);
        font.gz_renderChars(c_y, 390.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);

		// analog input viewer
        draw_stick_outline(0xFFFFFFFF, {320.0f + viewer_x_offset, 405.0f + viewer_y_offset}, 45.0f);
        draw_stick_outline(0xFFD138FF, {385.0f + viewer_x_offset, 405.0f + viewer_y_offset}, 36.0f);
        draw_stick(0xFFFFFFFF, {320.0f + tp_mPadAStick.x * 15 + viewer_x_offset, 405.0f - tp_mPadAStick.y * 15 + viewer_y_offset}, 30.0f);
        draw_stick(0xFFD138FF, {385.0f + tp_mPadACStick.x * 12 + viewer_x_offset, 405.0f - tp_mPadACStick.y * 12 + viewer_y_offset}, 24.0f);
    }
}  // namespace InputViewer