#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int SCREEN_WIDTH = 256;
int SCREEN_HEIGHT = 192;

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

    double x = 0;
    double y = 0;
	int oldx = x;    		

    for (int i = 0; i < 100000; i++) {
    	int r = rand() % 100;
    	if (r == 0) {
    		x = 0; 
    		y = 0.16 * y;
    	} else if ((r > 0) && (r < 86)) {
    		oldx = x;    		
			x = 0.85 * x + 0.04 * y; 
			y = -0.04 * oldx + 0.85 * y + 1.6;
    	} else if ((r >=86 ) && (r < 93)) {
			oldx = x;
    		x = 0.2 * x - 0.26 * y; 
    		y = 0.23 * oldx + 0.22 * y + 1.6;
    	} else {
    		oldx = x;
    		x = -0.15 * x + 0.28 * y; 
    		y = 0.26 * oldx + 0.24 * y + 0.44;
    	}
    	SDL_RenderDrawPoint(ren, (int) (y * 25), (int) (x * 20 + 96) );
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