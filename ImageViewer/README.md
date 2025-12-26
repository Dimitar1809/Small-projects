# Image Viewer (PPM + SDL2)

Small C program that opens a PPM (P3/ascii) image and paints it pixel-by-pixel into an SDL2 window sized to the image.

## Requirements
- SDL2 development libraries installed (e.g. `libsdl2-dev` on Debian/Ubuntu).
- A P3 PPM file named `image.ppm` in the working directory.

## Build & Run
```sh
gcc iv.c -lSDL2 -o iv
./iv
```
Close the SDL window to exit.

## Files
- `iv.c` — main source; loads `image.ppm` and renders to an SDL window.
- `image.ppm` — sample image.
- `.gitignore` — ignores the built binary and object files.
