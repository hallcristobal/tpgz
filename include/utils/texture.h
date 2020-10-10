#pragma once

#include <stdint.h>

enum TexCode {
    TEX_OK = 0,
    TEX_ERR_FILE = -1,
    TEX_ERR_READ = -2,
    TEX_ERR_INVALID_FORMAT = -3,
    TEX_ERR_MEM = -4,
};

struct TexHeader {
    uint32_t magic;
    uint32_t channels;
    uint32_t width;
    uint32_t height;
} __attribute__((packed));

struct Texture {
    TexHeader header;
    uint8_t* data;
    GXTexObj _texObj;
};

#ifdef __cplusplus
extern "C" {
#endif

int32_t load_texture(const char* path, Texture* tex);
void free_texture(Texture* tex);

#ifdef __cplusplus
}
#endif