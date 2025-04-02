#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <iostream>
#include <string>
#include "Note.h"
#include "Node.h"
#include "EntityManager.h"
#include "User.h"


/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static int win_height = 720;
static int win_width = 1080;
static SDL_Color backgroundColor = { 138, 121, 81, 255 };

static Note* testNote = new Note(backgroundColor, {150.0, 150.0}, 200.0, 400.0, { 0.89, 0.639, 0.737 });
static Note* testNote2 = new Note(backgroundColor, {300.0, 300.0}, 300.0, 400.0, {0.89, 0.875, 0.035});
static Note* testNote3 = new Note(backgroundColor, {500.0, 300.0}, 200.0, 200.0, { 0.89, 0.639, 0.737 });
static EntityManager* entityManager = new EntityManager();

static User* user = new User();


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    entityManager->addEntity(testNote);
    entityManager->addEntity(testNote2);
    entityManager->addEntity(testNote3);


    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", win_width, win_height, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) 
    {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    } 
    else if (event->type == SDL_EVENT_MOUSE_MOTION) 
    {
        SDL_FPoint mousePos = {
            mousePos.x = event->motion.x + event->motion.xrel,
            mousePos.y = event->motion.y + event->motion.yrel,
        };

		user->setMousePos(mousePos.x, mousePos.y);

		if (user->isActive && user->getSelection() != nullptr) {
			// When dragging, update position without altering hover state.
			user->getSelection()->moveTo(user->getMousePos(), false);
		}
		else {
			// Only update hover state when not dragging.
			user->setHover(entityManager->checkMouse(user->getMousePos()));
		}
	}
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
    {
        if (event->button.button == 1) {
            std::cout << "click 1" << std::endl;
            user->isActive = true;
            user->setSelection();
            entityManager->forwardEntity(user->getSelection());
            if (user->getSelection()) {
                user->getSelection()->setRelativeDistance(user->getMousePos());
            }
        }
    }
    else if (event->type = SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event->button.button == 1) {
            user->isActive = false;
        }
    }
    else if (event->type == SDL_EVENT_KEY_DOWN) 
    {
        if (event->key.key == SDLK_U) {
            std::cout << "Hello World" << std::endl;
        }
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    
    /* clear the window to the draw color. */
    SDL_SetRenderDrawColor(renderer, 138, 121, 81, 255);
    SDL_RenderClear(renderer);

    std::string deltaPosStr = std::to_string(user->getMousePos().x);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 272, 100, deltaPosStr.c_str());

    entityManager->renderEntities(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
