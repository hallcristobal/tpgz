from PIL import Image
import struct
import argparse
import sys

def write_header(out_file, image):
    # If the picture doesn't have opacity, we add it
    chn = len(image.getbands())
    if chn == 3:
        chn = 4

    out_file.write(struct.pack(">4s", "TEX0".encode("ascii"))) # channel count
    out_file.write(chn.to_bytes(4, 'big', signed=False)) # channel count
    out_file.write(image.width.to_bytes(4, 'big', signed=False))
    out_file.write(image.height.to_bytes(4, 'big', signed=False))

def write_tile(out_file, image, tile_x, tile_y, pair):
    for j in range(4):
        for i in range(4):
            pixel = image.getpixel((tile_x * 4 + i, tile_y * 4 + j))
            r = g = b = a = 0
            if len(pixel) == 3:
                r, g, b = pixel
                a = 255
            elif len(pixel) == 4:
                r, g, b, a = pixel
            if pair == 0:
                out_file.write(struct.pack(">BB", a, r))
            elif pair == 1:
                out_file.write(struct.pack(">BB", g, b))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Converts an image into a texture file.')
    parser.add_argument('-V', '--version', action='version', version='%(prog)s 0.1')
    parser.add_argument('image_file', type=str,
                        help='Path to the image file')
    parser.add_argument('out_tex', type=argparse.FileType('wb'), nargs='?', default="out.tex",
                        help='Name of the output file')
    params = parser.parse_args()

    # We fetch the picture, and make sure that it has a valid size
    image = Image.open(params.image_file)
    if image.width % 4 != 0 or image.height % 4 != 0:
        raise RuntimeError("image size has to be a multiple of 4")

    write_header(params.out_tex, image)

    # We save each 4x4 tile one at a time.
    for j in range(image.height // 4):
        for i in range(image.width // 4):
            # 'p' stands for "pair", since each there are two 4x4 tiles saved for
            # each 4x4 tile of the picture, one for the pair (a, r), and one for the pair (g, b).
            for p in range(2):
                write_tile(params.out_tex, image, i, j, p)
