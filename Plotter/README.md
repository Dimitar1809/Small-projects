# Function Plotter (C + SDL2 + tinyexpr)

Small C program that plots a math expression in an SDL2 window using tinyexpr to evaluate the expression.

## Requirements
- SDL2 development libraries (e.g., `libsdl2-dev` on Debian/Ubuntu).
- Standard C toolchain.

## Build & Run
```sh
gcc function_plotter.c tinyexpr.c -lSDL2 -lm -o function_plotter
./function_plotter "sin(x) * x"
```
Close the window to exit.

## How It Works
- Parses the expression with tinyexpr (`tinyexpr.c`, `tinyexpr.h`).
- Draws axes on a 900x600 window, samples `x` from -10 to 10, and paints pixels for `y`.
- `function_plotter` is the built binary (ignored via `.gitignore`).
