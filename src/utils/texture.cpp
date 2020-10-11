#include "libtp_c/include/system.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/addrs.h"
#include "gcn_c/include/gfx.h"
#include "gcn_c/include/dvd.h"
#include "utils/texture.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Like DVDReadPrio, but allows for arbitrary sizes and offsets.
 */
int32_t dvd_read(DVDFileInfo* file_info, void* data, int32_t size, int32_t offset) {
    constexpr const uint32_t buf_size = 0x20;
    uint8_t* buf = (uint8_t*)tp_memalign(-32, buf_size);
    int32_t read_bytes = 0;

    while (size > 0) {
        int32_t result = DVDReadPrio(file_info, buf, buf_size, (offset & ~(buf_size - 1)), 2);
        if (result <= 0) {
            break;
        }
        int32_t rem_size = buf_size - (offset & (buf_size - 1));
        tp_memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (buf_size - 1)), MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tp_free(buf);
    return read_bytes;
}

int32_t load_texture(const char* path, Texture* tex) {
    DVDFileInfo fileInfo;
    int32_t readsize;

    if(!DVDOpen(path, &fileInfo)) {
        return TexCode::TEX_ERR_FILE;
    }
    readsize = dvd_read(&fileInfo, &tex->header, sizeof(TexHeader), 0);
    if (readsize < (int32_t)sizeof(TexHeader)) {
        DVDClose(&fileInfo);
        return TexCode::TEX_ERR_READ;
    }

    uint8_t fmt = GX_TF_I8;
    switch (tex->header.channels) {
        case 1: {
            fmt = GX_TF_I8;
            break;
        }
        case 2: {
            fmt = GX_TF_RGB565; // Doesn't work atm
        }
        case 4: {
            fmt = GX_TF_RGBA8;
            break;
        }
        default: {
            DVDClose(&fileInfo);
            return TexCode::TEX_ERR_INVALID_FORMAT;
        }
    }

    uint32_t size = tex->header.channels * tex->header.width * tex->header.height;
    tex->data = (uint8_t*)tp_memalign(-32, size);
    if (tex->data == nullptr) {
        DVDClose(&fileInfo);
        return TexCode::TEX_ERR_MEM;
    }

    if (DVDReadPrio(&fileInfo, tex->data, size, sizeof(tex->header), 2) < (int32_t)size) {
        tp_free(tex->data);
        DVDClose(&fileInfo);
        return TexCode::TEX_ERR_READ;
    }
    DVDClose(&fileInfo);

    tp_memset(&tex->_texObj, 0, sizeof(GXTexObj));
    GX_InitTexObj(&tex->_texObj, tex->data, tex->header.width, tex->header.height, fmt, GX_CLAMP, GX_CLAMP, GX_FALSE);
    tex->isLoaded = true;
    return TexCode::TEX_OK;
}

void free_texture(Texture* tex) {
    tp_free(tex->data);
    tex->isLoaded = false;
}

#ifdef __cplusplus
}
#endif