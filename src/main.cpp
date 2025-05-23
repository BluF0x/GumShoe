#include <SDL3/SDL_stdinc.h>
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "Note.h"
#include "EntityManager.h"
#include "User.h"

//TODO the user selection isn't being updated, which is the likely cause of the error 
//with the note not being properly selected.
//-Activate timer when mouse isn't hovering the selection, and update both user and selection

/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static int win_height = 720;
static int win_width = 1080;
static SDL_Color backgroundColor = { 138, 121, 81, 255 };

/* Test notes. If needed delete comment.
static Note* testNote = new Note(backgroundColor, {150.0, 150.0}, 200.0, 400.0, { 0.89, 0.639, 0.737, 1.0f });
static Note* testNote2 = new Note(backgroundColor, {300.0, 300.0}, 300.0, 400.0, {0.89, 0.875, 0.035, 1.0f});
static Note* testNote3 = new Note(backgroundColor, {500.0, 300.0}, 200.0, 200.0, { 0.89, 0.639, 0.737, 1.0f });
*/
static EntityManager* entityManager = new EntityManager();

static User* user = new User(backgroundColor);


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    /* Teste notes. If needed delete comment.
    entityManager->addEntity(testNote);
    entityManager->addEntity(testNote2);
    entityManager->addEntity(testNote3);
    */


    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", win_width, win_height, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) 
    {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    } 

    // key press 
    else if (event->type == SDL_EVENT_KEY_DOWN) 
    {
        if (event->key.key == SDLK_1) {
            user->changeTool(Tools::SELECTION);
        }
        else if (event->key.key == SDLK_2) {
            user->changeTool(Tools::NOTE);
        }
        else if (event->key.key == SDLK_DELETE) {
            if (user->getSelection()) {
                if(entityManager->removeEntity(user->getSelection())){
                    delete user->getSelection();
                    user->setSelection(nullptr);
                }else{
                    std::cout << "Failed to remove entity" << std::endl;
                };
            }
        }
        //std::cout << "Current tool: " << user->currentTool << std::endl;
    }

    // mouse movement 
    else if (event->type == SDL_EVENT_MOUSE_MOTION) 
    {
        SDL_FPoint mousePos = {
            mousePos.x = event->motion.x + event->motion.xrel,
            mousePos.y = event->motion.y + event->motion.yrel,
        };

        (user->isButtonDown) ? user->isDragging = true : user->isDragging = false;

		user->setMousePos(mousePos.x, mousePos.y);

		//if (user->isButtonDown && user->getSelection() != nullptr && user->currentTool == Tools::SELECTION) {
        if (user->isDragging) {
            if (user->currentTool == Tools::SELECTION && user->getSelection() != nullptr) {
			    // When dragging, update position without altering hover state.
				user->getSelection()->moveTo(user->getMousePos(), false);
            }
            else if (user->currentTool == Tools::NOTE) {
                user->getSelection()->resize(7, user->getMousePos());

            }
            else if (user->currentTool == Tools::RESIZE) {
                Entity* userSelection = user->getSelection();
                userSelection->resize(user->resizeNumber, user->getMousePos());
            }
		}
        else {
            if (user->currentTool != Tools::NOTE){
                user->setHover(entityManager->checkMouse(user->getMousePos()));
                Entity* userHover = user->getHover();

                userHover ? user->resizeNumber = userHover->checkResize(mousePos)
                          : user->resizeNumber = -1;

                (user->resizeNumber > -1) ? user->changeTool(Tools::RESIZE) 
                                          : user->changeTool(Tools::SELECTION);
            }
        }
	}

    // mouse button down
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
    {
        if (event->button.button == 1) {
			user->isButtonDown = true;

            switch (user->currentTool) {
                // Selection Tool
                case Tools::SELECTION:
                    user->setSelection();
                    entityManager->forwardEntity(user->getSelection());
                    if (user->getSelection()) {
                        user->getSelection()->setRelativeDistance(user->getMousePos());
                    }
                    break;

                // Place note tool
                case Tools::NOTE:{
                    SDL_FColor updatedColor = user->templateNote->primaryColor;
                    updatedColor.a = 1.0f;
                    entityManager->addEntity(new Note(*user->templateNote));
                    Entity* addedNote = entityManager->getLastEntity();
                    addedNote->setColor(updatedColor);
                    user->setSelection(addedNote);
                    break;

                }
                case Tools::RESIZE:
                    user->setSelection();
                    entityManager->forwardEntity(user->getSelection());
                    break;
            }
        }
    }

    // mouse button release
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event->button.button == 1) {
            user->isButtonDown = false;
            if (user->currentTool == Tools::NOTE || user->currentTool == Tools::RESIZE) {
                user->getSelection()->correctSize();
                user->changeTool(Tools::SELECTION);
            }
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

    entityManager->renderEntities(renderer);
    user->renderToolPreview(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
