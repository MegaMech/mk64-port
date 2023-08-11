#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 320
#define HEIGHT 240
#define BOX_SIZE 6

typedef unsigned short u16;
typedef int s32;

void crash_screen_draw_square(u16 *framebuffer, SDL_Window *window, SDL_Surface *surface16);
void blit16To32(SDL_Surface *src, SDL_Surface *dest);

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Draw Square", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Surface *surface16 = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 16, 0xF800, 0x07E0, 0x001F, 0);

    if (!screenSurface || !surface16) {
        printf("Error creating surfaces: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    u16 *framebuffer = (u16*)surface16->pixels;

    // Call the function to draw squares 
    crash_screen_draw_square(framebuffer, window, surface16);

    SDL_FreeSurface(surface16);  // Don't forget to free the 16-bit surface
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void crash_screen_draw_square(u16 *framebuffer, SDL_Window *window, SDL_Surface *surface16) {
    s32 var_s0 = 46;
    s32 var_s2 = 40;
    s32 var_s3 = 44;
     s32 s0_end;
    s32 s2_start;
    s32 row, column;
    s32 i = 0;

      for (s2_start = 0x28, s0_end = s2_start + 6; s0_end != 0x2C; s0_end--, s2_start++) {
        for (row = s2_start; row < s0_end; row++) {
            for (column = s2_start; column < s0_end; column++) {
                framebuffer[row * 320 + column] = s0_end - s2_start == 6 ? 0xF801 : 0xFFFF;


                blit16To32(surface16, SDL_GetWindowSurface(window));
                SDL_UpdateWindowSurface(window);

                int waitingForSpace = 1;
                while (waitingForSpace) {
                    SDL_Event event;
                     while (SDL_PollEvent(&event)) {
                         if (event.type == SDL_QUIT) {
                             waitingForSpace = 0;
                             SDL_Quit();
                             exit(0);
                         } else if (event.type == SDL_KEYDOWN) {
                             if (event.key.keysym.sym == SDLK_SPACE) {
                                 waitingForSpace = 0;
                             }
                         }
                     }
                 }

            }
        }
    }


    // do {
    //     printf("\nLOOP\n");
    //     row = 46 - i;
    //     for (row = var_s2; row < var_s0; ++row) {
    //         printf("\ncolumn\n  height: %d\n  curr: %d\n", var_s0, row);
    //         for (column = var_s2; column < var_s0; ++column) {
    //             framebuffer[row * WIDTH + column] = i == 0 ? 0xF801 : 0xFFFF;
    //             printf("row: %d", i);
    //             blit16To32(surface16, SDL_GetWindowSurface(window));
    //             SDL_UpdateWindowSurface(window);

    //             int waitingForSpace = 1;
    //             while (waitingForSpace) {
    //                 SDL_Event event;
    //                 while (SDL_PollEvent(&event)) {
    //                     if (event.type == SDL_QUIT) {
    //                         waitingForSpace = 0;
    //                         SDL_Quit();
    //                         exit(0);
    //                     } else if (event.type == SDL_KEYDOWN) {
    //                         if (event.key.keysym.sym == SDLK_SPACE) {
    //                             waitingForSpace = 0;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     var_s0--;
    //     var_s2 = 6 + i;
    // } while(var_s0 != var_s3);
}

void blit16To32(SDL_Surface *src, SDL_Surface *dest) {
    SDL_BlitSurface(src, NULL, dest, NULL);
}
