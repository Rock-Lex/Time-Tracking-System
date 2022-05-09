#include "../inc/gui.h"

int initSDLSystems()
{
    printf("Initializing SDL Systems... \n");
    appState = 1;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        appState = 0;
        return 1;
    }
    TTF_Init();
}

void toggleFullscreen(SDL_Window* Window) 
{
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
    SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
}

void clean() // clean up resources before exiting
{
    printf("Killing app... \n");

    SDL_DestroyTexture(uhrzeitTexture);
    SDL_DestroyTexture(uberschriftTexture); 
    SDL_DestroyTexture(datumTexture);
    SDL_DestroyTexture(boxTexture);
    SDL_DestroyTexture(logoTexture);
    SDL_DestroyTexture(arrowTexture);
    SDL_DestroyTexture(clockTexture);

    SDL_TLSCleanup();

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);  
    SDL_Quit();
    IMG_Quit();

    printf("App is dead :( \n");
}

void cleanForFrame()
{
    SDL_TLSCleanup();

    if (appState == 1)
    {
        SDL_DestroyTexture(uhrzeitTexture);
        SDL_DestroyTexture(datumTexture);
    }

    if (appState == 2)
    {
        SDL_DestroyTexture(uhrzeitTexture);
        SDL_DestroyTexture(datumTexture);
    }

    if (appState == 3)
    {
        SDL_DestroyTexture(datumTexture);
        SDL_DestroyTexture(uhrzeitTexture);
    }

    if (appState == 4)
    {
        SDL_DestroyTexture(datumTexture);
    }
}

void createWindow() 
{
    printf("Creating Window... \n");

    win = SDL_CreateWindow("Zeiterfassung", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 480, 0);
    if (!win)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
    }

    //toggleFullscreen(win);
    //SDL_MaximizeWindow(win);
}

void createRenderer()
{
    printf("Creating renderer... \n");
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(win, -1, render_flags);

    if (!renderer)
    {
      printf("Error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
    }
}

void renderApp()
{   
    updateUhrzeit(renderer);
    updateDatum(renderer);

    switch (appState) 
    {
        case 1:     // main screen
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // firma white 
            SDL_RenderClear(renderer);      
            renderMainScreen(renderer);
            break; 
        
        case 2:     // willkommen
            SDL_SetRenderDrawColor(renderer, 207, 214, 0, 255);   // firma grun
            SDL_RenderClear(renderer);
            renderLoginScreen(renderer);
            break;
        
        case 3:     // auf widersehen
            SDL_SetRenderDrawColor(renderer, 26, 177, 161, 255);   // firma blau 
            SDL_RenderClear(renderer);
            renderLogoutScreen(renderer);
            break;
        
        case 4:     // error screen
            SDL_SetRenderDrawColor(renderer, 227, 6, 19, 255);   // firma rot 
            SDL_RenderClear(renderer);
            renderFehlerScreen(renderer);
            break;

        default:
            printf("%s\n", "App: appState error");
            break;
    }
}

int main(void)
{
    initSDLSystems();

    createWindow();

    createRenderer();

    initRenderAll(renderer);
    
    SDL_StartTextInput();

    //  Programm loop
    while (appState != 0)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDL_QUIT:
                            appStatePast = appState;
				            appState = 0;
				            break;

//////////////////////////////////////////////////////////////////
//                            Debug
//////////////////////////////////////////////////////////////////
                        case SDLK_ESCAPE: 
                            appStatePast = appState;
                            appState = 0;
                            break;
                        case SDLK_F1:
                            appStatePast = appState;
                            appState = 1;
                            break;
                        case SDLK_F2:
                            appStatePast = appState;           
                            appState = 2;
                            break;
                        case SDLK_F3:
                            appStatePast = appState;
                            appState = 3;
                            break;
                        case SDLK_F4:
                            appStatePast = appState;
                            appState = 4;
                            break;
                        case SDLK_F5:
                            break;
/////////////////////////////////////////////////////////////////                            
                    }
                    break;
                case SDL_TEXTINPUT:
                    strcat(employeeIDlesen, event.text.text);
                    if (strlen(employeeIDlesen) == 14) 
                    {
                        memset(employeeID, 0, strlen(employeeID));
                        strcat(employeeID, employeeIDlesen);
                        memset(employeeIDlesen, 0, strlen(employeeIDlesen));

                        SDL_StopTextInput();

                        interractWithUser(employeeID);

                        result = jsonParse();
                        
                        char *info = result.display;

                        if (info == NULL)
                        {  
                            initRenderScan(renderer, 1, "Siehe /build/fehler.txt", 0);
                            appState = 4;
                        }
                        else if (result.worked_hours == 0) 
                        {
                            initRenderScan(renderer, 1, result.display, result.worked_hours);
                            appState = 2;
                        }
                        else if (result.worked_hours > 0)
                        {
                            initRenderScan(renderer, 2, result.display, result.worked_hours);
                            appState = 3;
                        }
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
        renderApp();
        SDL_RenderPresent(renderer);

        if (appState == 1)
        {
            SDL_StartTextInput();
        }

        else if (appState == 2 || appState == 3 || appState == 4)
        {
            appState = 1;   
            SDL_Delay(3000);
        }

        cleanForFrame();
        SDL_Delay(100);
    }

    clean();
}