/*******************************************************************
*  Main Program File for Particle Simulation
*	by Josh Hayden
*
*
* Handles all the main logic and user input for the simulation. 
*******************************************************************/

#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_PARTICLES 10

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


typedef struct {
    int x, y; // position
    int vx, vy; // velocity
} Particle;

Particle particles[MAX_PARTICLES];
int numParticles = 0;


void renderParticles() {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render particles as filled rectangles (approximating circles)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    for (int i = 0; i < numParticles; i++) {
        SDL_Rect rect = { particles[i].x - 5, particles[i].y - 5, 10, 10 }; // Centered rectangles
        SDL_RenderFillRect(renderer, &rect);
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}


int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Creates the window and renderer
    window = SDL_CreateWindow("Particle Simulator",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Event Handling by .type
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
				
				case SDL_QUIT:
					quit = true;
					break;
					
				case SDL_MOUSEBUTTONDOWN:
					if (numParticles < MAX_PARTICLES) {
						// Create a new particle at the mouse position
						particles[numParticles].x = event.button.x;
						particles[numParticles].y = event.button.y;
						particles[numParticles].vx = 0;
						particles[numParticles].vy = 0;
						numParticles++;
					}
					break;		
            }
        }

        // Present the renderer
        renderParticles();
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
