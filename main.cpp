#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Can't init SDL: " << SDL_GetError() << endl;
    }

    win = SDL_CreateWindow("Примитивы", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        cout << "Can't create window: " << SDL_GetError() << endl;
        ok = false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        ok = false;
    }
    return ok;
}

void quit() {
    SDL_DestroyWindow(win);
    win = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_Quit;    
}

int main (int arhc, char ** argv) {
    if (!init()) {
        quit();
        cout << "Error ! " << SDL_GetError() << endl;
        return 1;
    }

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

    double a = 0; 
    double b = 0; 
    double c = 0; 
    double d = 0.16; 
    double e = 0; 
    double f = 0;
    double x = 0;
    double y = 0;
    double x1 = 0;
    double y1 = 0;

	int oldx = x;    		

    for (int i = 0; i < 100000; i++) {
    	int r = rand() % 100;
    	if (r == 0) {
    		 a = 0; b = 0; c = 0; d = 0.16; e = 0; f = 0;
    	} else if ((r > 0) && (r < 86)) {
    		a = 0.85; b = 0.04; c = -0.04; d = 0.85; e = 0; f = 1.6;
    	} else if ((r >=86 ) && (r < 93)) {
			a = 0.2; b = -0.26; c = 0.23; d = 0.22; e = 0; f = 1.6;
    	} else {
    		a = -0.15; b = 0.28; c = 0.26; d = 0.24; e = 0; f = 0.44;
    	}
        x1 = (a * x) + (b * y) + e;
        y1 = (c * x) + (d * y) + f;
        x = x1;
        y = y1;
    	SDL_RenderDrawPoint(ren, (int) (y * SCREEN_WIDTH / 10), (int) (x * SCREEN_HEIGHT / 10 + SCREEN_HEIGHT / 2) );
	}

    SDL_RenderPresent(ren);

    bool q = false;
    SDL_Event event;

	while(!q){
	    if(SDL_WaitEvent(&event)){
	        if(event.type == SDL_QUIT){
	            q = true;
	        }
	    }
	}

    quit();
    return 0;
}