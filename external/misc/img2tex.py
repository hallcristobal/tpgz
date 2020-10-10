from PIL import Image
import struct
import argparse
import sys

def to5bit(x):
    return int((x * 31) / 255)

def to6bit(x):
    return int((x * 63) / 255)

def to8bit(x):
    return int((x * 255) / 255)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Converts an image into a texture file.')
    parser.add_argument('-V', '--version', action='version', version='%(prog)s 0.1')
    parser.add_argument('image_file', type=str,
                        help='Path to the image file')
    parser.add_argument('out_tex', type=argparse.FileType('wb'), nargs='?', default="out.tex",
                        help='Name of the output file')
    params = parser.parse_args()
    image = Image.open(params.image_file)
    chn = len(image.getbands())
    if chn == 3:
        chn = 2
    params.out_tex.write(struct.pack(">4s", "TEX0".encode("ascii"))) # channel count
    params.out_tex.write(chn.to_bytes(4, 'big', signed=False)) # channel count
    params.out_tex.write(image.width.to_bytes(4, 'big', signed=False))
    params.out_tex.write(image.height.to_bytes(4, 'big', signed=False))
    for pixel in list(image.getdata()):
        if len(pixel) == 3:
            r, g, b = pixel
            val = (to5bit(b) | (to6bit(g) << 5) | (to5bit(r) << 11))
            params.out_tex.write(struct.pack(">H", val))
        elif len(pixel) == 4:
            r, g, b, a = pixel
            params.out_tex.write(struct.pack(">I", (to8bit(a) | (to8bit(b) << 8) | (to8bit(g) << 16) | (to8bit(r) << 24))))
