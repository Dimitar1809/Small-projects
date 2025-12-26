#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"tinyexpr.h"

#define WIDTH 900
#define HEIGHT 600
#define xMin -10
#define xMax 10
#define yScale 50 // scale factor for y-axis
#define thickness 1 // line thickness in pixels

void DrawExpression(SDL_Surface *psurface, const char *expr) {
    
    // set the color map the red color
    Uint32 color = SDL_MapRGB(psurface->format, 255, 0, 0);
    
    double x;
    te_variable vars[] = {{"x", &x, TE_VARIABLE, 0}};
    int err;
    te_expr *pexpr = te_compile(expr, vars, 1, &err);
    if (pexpr == NULL) {
        printf("Error compiling expression at position: %d\n", err);
        return;
    }
    // create an array to hold the pixel colors
    Uint32 *pixels = (Uint32 *)psurface->pixels;

    for (double x_val = xMin; x_val < xMax; x_val += 0.001) {
        // map pixel x coordinate to function x value
        x = x_val;
        // evaluate the function
        double y = te_eval(pexpr);

        // map x value to pixel coordinate
        int px = (int)((x_val - xMin) / (xMax - xMin) * WIDTH);
        // map y value to pixel coordinate (inverted y-axis)
        int py = HEIGHT /2 - (int)(y * yScale);

        // draw thickness by drawing neightboring pixels
        for (int dy = -thickness; dy <= thickness; dy++) {
            for (int dx = -thickness; dx <= thickness; dx++) {
                int draw_x = px + dx;
                int draw_y = py + dy;
                // check if the pixel is within the surface bounds
                if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT) {
                    // set the pixel color
                    pixels[draw_y * WIDTH + draw_x] = color;
                }
            }
        }
    }
    te_free(pexpr); 
}


void DrawGrid(SDL_Surface *psurface) {
    Uint32 gridColor = 0xCCCCCC; // Light gray color
    // draw the x-axis line
    SDL_Rect xAxis = {0, HEIGHT / 2, WIDTH, 2};
    SDL_FillRect(psurface, &xAxis, gridColor);

    // draw the y-axis line
    SDL_Rect yAxis = {WIDTH /2, 0, 2 , HEIGHT};
    SDL_FillRect(psurface, &yAxis, gridColor);

}


int main(int argc, char *argv[])

{
    if (argc != 2) {
    printf("Not enough arguments. Usage: %s \"expression\"\n", argv[0]);
    return 0;
}

    const char *expr = argv[1];
	printf("Hello again!\n");
	SDL_Window *pwindow = SDL_CreateWindow("Function plotter",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    DrawGrid(psurface);
    DrawExpression(psurface, expr);

    SDL_UpdateWindowSurface(pwindow);

    while (1) { SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {break;}
    }
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    printf("Goodbye, World!\n");
    return 0;
}
