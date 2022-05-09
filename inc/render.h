#pragma once

#ifndef RENDER_H_
#define RENDER_H_

int w = 800, h = 480;  //screen resolution
int wD = 800, hD = 480;
 
////////////////////////////////
//    Position of elements    //
////////////////////////////////
// Logo
#define LOGO_PATH "/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/img/logoF.png"
#define LOGO_H hD * 0.065  //  94  //  94  //
#define LOGO_W wD * 0.195  //  500  //  500  //
#define LOGO_ABSTAND_X wD * 0.012  //  30 //
#define LOGO_ABSTAND_Y hD * 0.028  //  40 //

// Box
#define BOX_PATH "/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/img/white.png"
#define BOX_W wD  
#define BOX_H hD * 0.75  


// Arrow
#define ARROW_PATH "/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/img/arrow.png"
#define ARROW_H hD * 0.222  //  320  //  450  //  hD * 0.313
#define ARROW_W wD * 0.098  //  250  //  600  //  wD * 0.234

// Clock
#define CLOCK_PATH "/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/img/clock.png"
#define CLOCK_W wD * 0.05 * 2  //  128  //
#define CLOCK_H hD * 0.089 * 2  //  128  //
#define CLOCK_ABSTAND LOGO_ABSTAND_X

// Datum
#define DATUM_ABSTAND_Y 40
#define DATUM_W wD * 0.078 * 2 //  200 * 2   //  230 mit 2022  //  wD * 0.09 
#define DATUM_H hD * 0.038 * 2    //  55 //55

// Uhrzeit
#define UHRZEIT_W wD * 0.051 * 4  //  130 * 4   //  130 //  
#define UHRZEIT_H hD * 0.042 * 4  //  60 * 4   //  60 /60

// Uberschrift
#define UBERSCHRIFT_W LOGO_W
#define UBERSCHRIFT_H LOGO_H

// HotpslotsInfo
#define HOTSPLOTSINFO_W wD * 0.75
#define HOTSPLOTSINFO_H LOGO_H

// Mail
#define MAIL_W wD * 0.3
#define MAIL_H LOGO_H

////////////////////////////////
//         Libraries          //
////////////////////////////////

// SDL Library
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

// C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

////////////////////////////////
//         Variables          //
////////////////////////////////
time_t t;
struct tm uhrzeit;
char uhr[10] = "10:10";
char date[15] = "23.03.2022";


int switcher = 1;

////////////////////////////////
//      Render objects        //
////////////////////////////////
//Box
SDL_Texture* boxTexture = NULL;
SDL_Rect boxRect; 

// Logo
SDL_Texture *logoTexture = NULL;
SDL_Rect logoRect;

// Arrow
SDL_Texture *arrowTexture = NULL;
SDL_Rect arrowRect;

// Uberschrift
SDL_Surface* uberschriftSurface; 
SDL_Texture* uberschriftTexture;
SDL_Rect uberschriftRect; 

// HotsplotsInfo
SDL_Surface* hotsplotsinfoSurface; 
SDL_Texture* hotsplotsinfoTexture;
SDL_Rect hotsplotsinfoRect; 

// Mail
SDL_Surface* mailSurface; 
SDL_Texture* mailTexture;
SDL_Rect mailRect; 

// Uhrzeit
SDL_Surface* uhrzeitSurface; 
SDL_Texture* uhrzeitTexture;
SDL_Rect uhrzeitRect; 

// Datum
SDL_Surface* datumSurface; 
SDL_Texture* datumTexture;
SDL_Rect datumRect; 

// Clock
SDL_Texture *clockTexture = NULL;
SDL_Rect clockRect;

//Text in Box
// Willkommen
SDL_Surface* willkommenSurface; 
SDL_Texture* willkommenTexture;
SDL_Rect willkommenRect; 

// Auf wiedersehen
SDL_Surface* aufwiedersehenSurface; 
SDL_Texture* aufwiedersehenTexture;
SDL_Rect aufwiedersehenRect; 

// Fehler
SDL_Surface* fehlerSurface; 
SDL_Texture* fehlerTexture;
SDL_Rect fehlerRect; 

// Name
SDL_Surface* vornachnameSurface; 
SDL_Texture* vornachnameTexture;
SDL_Rect vornachnameRect; 

// Von
SDL_Surface* vonSurface; 
SDL_Texture* vonTexture;
SDL_Rect vonRect; 

// Bis
SDL_Surface* bisSurface; 
SDL_Texture* bisTexture;
SDL_Rect bisRect; 

// Ingesamt
SDL_Surface* insgesamtSurface; 
SDL_Texture* insgesamtTexture;
SDL_Rect insgesamtRect; 

////////////////////////////////
// Schrift
TTF_Font* Sans100;
TTF_Font* Sans35;
TTF_Font* Sans30;
TTF_Font* Sans15;   

// Colors
SDL_Color Black = {0, 0, 0, 255};
SDL_Color White = {255, 255, 255, 255};
////////////////////////////////

////////////////////////////////
//         Functions          //
////////////////////////////////

#endif