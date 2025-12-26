#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

int main() 
{
    printf("Hello, World!\n");

    //Read from a ppm file
    FILE *fp = fopen("image.ppm", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    char buff[30];
    fgets(buff, sizeof(buff), fp);
    printf("File format: %s", buff);
    // Read the image size information
    int width, height;
    fscanf(fp, "%d %d", &width, &height);
    printf("Image size: %d x %d\n", width, height);
    int max_color;
    fscanf(fp, "%d", &max_color);
    printf("Max color value: %d\n", max_color);


    // Load the image data
    int r,g,b;
    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,height, 0);
    
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    SDL_Rect pixel = { .w=1, .h=1 }; // single pixel
    // Fill the grid pixel by pixel
    for (int x =0; x < height; x++) {
        for (int y = 0; y< width; y++) {
            pixel.x = y;
            pixel.y = x;
            fscanf(fp, "%d %d %d", &r, &g, &b);
            Uint32 color = SDL_MapRGB(psurface->format, r, g, b);
            SDL_FillRect(psurface, &pixel, color);
        }
    }
    SDL_UpdateWindowSurface(pwindow);  // present the fill  
    
    // Wait until the user closes the window
    while (1) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {break;} 
    }
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    printf("Goodbye, World!\n");
    return 0;
    
}