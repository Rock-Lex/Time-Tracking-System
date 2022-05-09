// C Library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <curl/curl.h>

// SDL Library
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

// Screen info
#include <X11/Xlib.h>

// Internal functions
#include "./render.h"

#include "../src/render.c"
#include "../src/odoo.c"
#include "../src/json.c"

SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

int appState = 0;   // 0 - quit, 1 - main screen, 2 - willkommen, 3 - auf widersehen, 4 - fehler, 5 - zeitinfo?
int appStatePast = 1;
char employeeID[14];
char employeeIDlesen[14];

struct result result;