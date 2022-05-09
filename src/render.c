#include "../inc/render.h"

////////////////////////////////////////////////////////////////
// Clean funktions
////////////////////////////////////////////////////////////////

int cleanSurfacesMainScreen()
{
    SDL_FreeSurface(datumSurface);
    SDL_FreeSurface(uhrzeitSurface);

    return 0;
}

int cleanSurfacesLoginScreen()
{
    SDL_FreeSurface(datumSurface);
    SDL_FreeSurface(uhrzeitSurface);

    return 0;
}

int cleanSurfacesLogoutScreen()
{
    SDL_FreeSurface(datumSurface);
    SDL_FreeSurface(uhrzeitSurface);

    return 0;
}

int cleanSurfacesFehlerScreen()
{
    SDL_FreeSurface(datumSurface);
    SDL_FreeSurface(uhrzeitSurface);

    return 0;
}

int readScreenInfo()
{
    FILE *fptr;

    if ((fptr = fopen("/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/screen.txt","r")) == NULL)
    {
        printf("Error! opening file");
    }

    fscanf(fptr,"%d %d",&wD, &hD);
    w = wD;
    h = hD;

    printf("Screen resolution: %d x %d\n",wD,hD);
    
    fclose (fptr);

    return 0;       
}

////////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////////

int updateUhrzeit(SDL_Renderer *renderer)
{
    t = time(NULL);
    uhrzeit = *localtime(&t);

    snprintf(uhr, 10, "%02d:%02d", uhrzeit.tm_hour, uhrzeit.tm_min);

    uhrzeitSurface = TTF_RenderText_Solid(Sans100, uhr, Black);
    uhrzeitTexture = SDL_CreateTextureFromSurface(renderer, uhrzeitSurface);

    return 0;
}

int updateDatum(SDL_Renderer *renderer)
{
    snprintf(date, 15, "%02d/%02d/%02d", uhrzeit.tm_mday, uhrzeit.tm_mon + 1, uhrzeit.tm_year - 100);

    datumSurface = TTF_RenderText_Solid(Sans100, date, Black);
    datumTexture = SDL_CreateTextureFromSurface(renderer, datumSurface);

    return 0;
}

///////////////////////////////////////////////////////////////
// Render Objects
///////////////////////////////////////////////////////////////

int render(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    return 0;
}

///////////////////////////////////////////////////////////////
// Init Objects
///////////////////////////////////////////////////////////////

int initLogo(SDL_Renderer *renderer)
{
    logoTexture = IMG_LoadTexture(renderer, LOGO_PATH);
    SDL_QueryTexture(logoTexture, NULL, NULL, &w, &h);

    logoRect.w = LOGO_W;
    logoRect.h = LOGO_H;
    logoRect.x = wD - LOGO_ABSTAND_X - LOGO_W;
    logoRect.y = LOGO_ABSTAND_Y;

    return 0;
}

int initUberschrift(SDL_Renderer *renderer)
{
    uberschriftSurface = TTF_RenderText_Solid(Sans100, "Zeiterfassung", Black); 
    uberschriftTexture = SDL_CreateTextureFromSurface(renderer, uberschriftSurface);

    uberschriftRect.w = UBERSCHRIFT_W; // controls the width of the rect
    uberschriftRect.h = UBERSCHRIFT_H; // controls the height of the rect
    uberschriftRect.x = logoRect.x;
    uberschriftRect.y = logoRect.y + LOGO_H + 10;

    SDL_FreeSurface(uberschriftSurface);

    return 0;
}

int initHotsplotsInfo(SDL_Renderer *renderer)
{
    hotsplotsinfoSurface = TTF_RenderText_Solid(Sans100, "Bei fragen oder Hinweisen, wendest du dich bitte an", Black); 
    hotsplotsinfoTexture = SDL_CreateTextureFromSurface(renderer, hotsplotsinfoSurface);

    hotsplotsinfoRect.w = HOTSPLOTSINFO_W; // controls the width of the rect
    hotsplotsinfoRect.h = HOTSPLOTSINFO_H; // controls the height of the rect
    hotsplotsinfoRect.x = (wD - HOTSPLOTSINFO_W) / 2;
    hotsplotsinfoRect.y = uhrzeitRect.y + UHRZEIT_H * 1.5;

    SDL_FreeSurface(hotsplotsinfoSurface);

    return 0;
}

int initMail(SDL_Renderer *renderer)
{
    mailSurface = TTF_RenderText_Solid(Sans100, "zeiterfassung@hotsplots.de", Black); 
    mailTexture = SDL_CreateTextureFromSurface(renderer, mailSurface);

    mailRect.w = MAIL_W * 1.5; // controls the width of the rect
    mailRect.h = MAIL_H; // controls the height of the rect
    mailRect.x = (wD - mailRect.w) / 2;
    mailRect.y = hotsplotsinfoRect.y + HOTSPLOTSINFO_H + 5;

    SDL_FreeSurface(mailSurface);

    return 0;
}

int initUhrzeit(SDL_Renderer *renderer)
{
    uhrzeitRect.w = UHRZEIT_W; // controls the width of the rect
    uhrzeitRect.h = UHRZEIT_H; // controls the height of the rect
    uhrzeitRect.x = (wD - UHRZEIT_W) / 2; //controls the rect's x coordinate     // W ersetzen
    uhrzeitRect.y = (hD - UHRZEIT_H) / 2; // controls the rect's y coordinte

    return 0;
}

int initDatum(SDL_Renderer *renderer)
{
    datumRect.w = DATUM_W; // controls the width of the rect
    datumRect.h = DATUM_H; // controls the height of the rect
    datumRect.x = (wD - DATUM_W) / 2;  //controls the rect's x coordinate    // W ersetzen
    datumRect.y = hD - DATUM_H; // controls the rect's y coordinte

    return 0;
}

int initArrow(SDL_Renderer *renderer)
{
    arrowTexture = IMG_LoadTexture(renderer, ARROW_PATH);
    SDL_QueryTexture(arrowTexture, NULL, NULL, &w, &h);

    arrowRect.w = ARROW_W;
    arrowRect.h = ARROW_H;
    arrowRect.x = (wD - ARROW_W) / 2;
    arrowRect.y = CLOCK_ABSTAND;

    return 0;
}

int initClock(SDL_Renderer *renderer)
{
    clockTexture = IMG_LoadTexture(renderer, CLOCK_PATH);
    SDL_QueryTexture(clockTexture, NULL, NULL, &w, &h);

    clockRect.w = CLOCK_W;
    clockRect.h = CLOCK_H;
    clockRect.x = CLOCK_ABSTAND;
    clockRect.y = CLOCK_ABSTAND;

    return 0;
}

int initBox(SDL_Renderer *renderer)
{
    boxTexture = IMG_LoadTexture(renderer, BOX_PATH);
    SDL_QueryTexture(boxTexture, NULL, NULL, &w, &h);

    boxRect.w = BOX_W;
    boxRect.h = BOX_H;
    boxRect.x = wD / 2 - BOX_W / 2;
    boxRect.y = hD / 2 - BOX_H / 2;

    return 0;
}

int initWillkommen(SDL_Renderer *renderer)
{
    willkommenSurface = TTF_RenderText_Solid(Sans35, "Willkommen!", Black); 
    willkommenTexture = SDL_CreateTextureFromSurface(renderer, willkommenSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(willkommenTexture, NULL, NULL, &texW, &texH);

    willkommenRect.w = texW; 
    willkommenRect.h = texH; 

    willkommenRect.x = (wD - willkommenRect.w) / 2;
    willkommenRect.y = boxRect.y + willkommenRect.h;

    SDL_FreeSurface(willkommenSurface);

    return 0;
}

int initAufwiedersehen(SDL_Renderer *renderer)
{
    aufwiedersehenSurface = TTF_RenderText_Solid(Sans35, "Auf wiedersehen!", Black); 
    aufwiedersehenTexture = SDL_CreateTextureFromSurface(renderer, aufwiedersehenSurface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(aufwiedersehenTexture, NULL, NULL, &texW, &texH);


    aufwiedersehenRect.w = texW; // controls the width of the rect
    aufwiedersehenRect.h = texH; // controls the height of the r

    aufwiedersehenRect.x = (wD - aufwiedersehenRect.w) / 2;
    aufwiedersehenRect.y = boxRect.y + aufwiedersehenRect.h;
    
    SDL_FreeSurface(aufwiedersehenSurface);

    return 0;
}

int initFehler(SDL_Renderer *renderer)
{
    fehlerSurface = TTF_RenderText_Solid(Sans35, "Fehler!", Black); 
    fehlerTexture = SDL_CreateTextureFromSurface(renderer, fehlerSurface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(fehlerTexture, NULL, NULL, &texW, &texH);

    fehlerRect.w = texW; // controls the width of the rect
    fehlerRect.h = texH; // controls the height of the rect
    
    fehlerRect.x = (wD - fehlerRect.w) / 2;
    fehlerRect.y = boxRect.y + fehlerRect.h;

    SDL_FreeSurface(fehlerSurface);

    return 0;
}

int initVorNachname(SDL_Renderer * renderer, char *display, double worked_hours, TTF_Font * font)
{
    vornachnameSurface = TTF_RenderText_Solid(font, display, Black); 
    vornachnameTexture = SDL_CreateTextureFromSurface(renderer, vornachnameSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(vornachnameTexture, NULL, NULL, &texW, &texH);

    vornachnameRect.w = texW; // controls the width of the rect
    vornachnameRect.h = texH; // controls the height of the rect
    vornachnameRect.x = (wD - vornachnameRect.w) / 2;
    vornachnameRect.y = (hD - vornachnameRect.h) / 2;

    SDL_FreeSurface(vornachnameSurface);

    return 0;
}

int initVorNachnameStart(SDL_Renderer * renderer)
{
    vornachnameSurface = TTF_RenderText_Solid(Sans15, "Fehler", Black); 
    vornachnameTexture = SDL_CreateTextureFromSurface(renderer, vornachnameSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(vornachnameTexture, NULL, NULL, &texW, &texH);

    vornachnameRect.w = texW; // controls the width of the rect
    vornachnameRect.h = texH; // controls the height of the rect
    vornachnameRect.x = (wD - vornachnameRect.w) / 2;
    vornachnameRect.y = (hD - vornachnameRect.h) / 2;
    
    SDL_FreeSurface(vornachnameSurface);

    return 0;
}

int initVonUhr(SDL_Renderer *renderer)
{
    vonSurface = TTF_RenderText_Solid(Sans100, "Von: 13:20", Black); 
    vonTexture = SDL_CreateTextureFromSurface(renderer, vonSurface);

    vonRect.w = UBERSCHRIFT_W - UBERSCHRIFT_W * 0.3; // controls the width of the rect
    vonRect.h = UBERSCHRIFT_H; // controls the height of the rect
    vonRect.x = (wD - vonRect.w) / 2;
    vonRect.y = vornachnameRect.y + vonRect.h;

    return 0;
}

int initBisUhr(SDL_Renderer *renderer)
{
    bisSurface = TTF_RenderText_Solid(Sans100, "Bis: 16:20", Black); 
    bisTexture = SDL_CreateTextureFromSurface(renderer, bisSurface);

    bisRect.w = UBERSCHRIFT_W - UBERSCHRIFT_W * 0.3; // controls the width of the rect
    bisRect.h = UBERSCHRIFT_H; // controls the height of the rect
    bisRect.x = (wD - bisRect.w) / 2;
    bisRect.y = vonRect.y + bisRect.h;
    
    return 0;
}

int initInsgesamt(SDL_Renderer *renderer, double worked_hours, TTF_Font *font)
{
    char str[50];
    snprintf(str, 50, "%.02f", worked_hours);
    strcat(str, " Stunden");

    insgesamtSurface = TTF_RenderText_Solid(font, str, Black); 
    insgesamtTexture = SDL_CreateTextureFromSurface(renderer, insgesamtSurface);
    
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(insgesamtTexture, NULL, NULL, &texW, &texH);

    insgesamtRect.w = texW; // controls the width of the rect
    insgesamtRect.h = texH; // controls the height of the rect
    insgesamtRect.x = (wD - insgesamtRect.w) / 2;
    insgesamtRect.y = bisRect.y + insgesamtRect.h;

    SDL_FreeSurface(insgesamtSurface);

    return 0;
}

int initInsgesamtStart(SDL_Renderer *renderer)
{
    insgesamtSurface = TTF_RenderText_Solid(Sans100, "(3 Stunden 0 Minuten)", Black); 
    insgesamtTexture = SDL_CreateTextureFromSurface(renderer, insgesamtSurface);
    
    insgesamtRect.w = UBERSCHRIFT_W; // controls the width of the rect
    insgesamtRect.h = UBERSCHRIFT_H; // controls the height of the rect
    insgesamtRect.x = (wD - insgesamtRect.w) / 2;
    insgesamtRect.y = bisRect.y + insgesamtRect.h;

    SDL_FreeSurface(insgesamtSurface);

    return 0;
}

////////////////////////////////////////////////////////////////
// Render Functions
////////////////////////////////////////////////////////////////

int renderMainScreen(SDL_Renderer *renderer)
{
    render(renderer, logoTexture, logoRect);
    render(renderer, uberschriftTexture, uberschriftRect);
    render(renderer, hotsplotsinfoTexture, hotsplotsinfoRect);
    render(renderer, mailTexture, mailRect);
    render(renderer, uhrzeitTexture, uhrzeitRect);
    render(renderer, datumTexture, datumRect);
    render(renderer, arrowTexture, arrowRect);
    render(renderer, clockTexture, clockRect);

    cleanSurfacesMainScreen();

    return 0;
}

int renderLoginScreen(SDL_Renderer *renderer)
{
    render(renderer, logoTexture, logoRect);
    render(renderer, datumTexture, datumRect);
    render(renderer, boxTexture, boxRect);
    render(renderer, willkommenTexture, willkommenRect);
    render(renderer, vornachnameTexture, vornachnameRect);

    cleanSurfacesLoginScreen();

    return 0;
}

int renderLogoutScreen(SDL_Renderer *renderer)
{
    render(renderer, logoTexture, logoRect);
    render(renderer, datumTexture, datumRect);
    render(renderer, boxTexture, boxRect);
    render(renderer, aufwiedersehenTexture, aufwiedersehenRect);
    render(renderer, vornachnameTexture, vornachnameRect);
    render(renderer, insgesamtTexture, insgesamtRect);

    cleanSurfacesLogoutScreen();

    return 0;
}

int renderFehlerScreen(SDL_Renderer *renderer)
{
    render(renderer, logoTexture, logoRect);
    render(renderer, boxTexture, boxRect);
    render(renderer, fehlerTexture, fehlerRect);
    render(renderer, vornachnameTexture, vornachnameRect);
    
    cleanSurfacesFehlerScreen();

    return 0;
}

////////////////////////////////////////////////////////////////
// Init Functions
////////////////////////////////////////////////////////////////

int initRenderAll(SDL_Renderer *renderer)
{
    readScreenInfo();

    Sans100 = TTF_OpenFont("/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/fonts/futura.ttf", 100);
    Sans35 = TTF_OpenFont("/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/fonts/futura.ttf", 35);
    Sans30 = TTF_OpenFont("/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/fonts/futura.ttf", 25);
    Sans15 = TTF_OpenFont("/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/fonts/futura.ttf", 22);

    initLogo(renderer);
    initUberschrift(renderer);
    initUhrzeit(renderer);
    initHotsplotsInfo(renderer);
    initMail(renderer);
    initDatum(renderer);
    initArrow(renderer);
    initClock(renderer);
    initBox(renderer);  
    initWillkommen(renderer);
    initAufwiedersehen(renderer);
    initFehler(renderer);
    initVorNachnameStart(renderer);
    initVonUhr(renderer);
    initBisUhr(renderer);
    initInsgesamtStart(renderer);

    return 0;
}

int initRenderScan(SDL_Renderer *renderer, int mode, char *display, double worked_hours)
{
    if (mode == 1)
    {
        initVorNachname(renderer, display, worked_hours, Sans30);
    }

    if (mode == 2)
    {
        initVorNachname(renderer, display, worked_hours, Sans15);
        initInsgesamt(renderer, worked_hours, Sans30);
    }

    return 0;
}