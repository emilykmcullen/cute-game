#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../Utils.h"
#include "../Game.h"

class TransformComponent: public Component {
public:
    vec2 position;
    vec2 velocity;
    int width;
    int height;
    int scale;
    bool isCentered;

    TransformComponent(float posX, float posY, float velX, float velY, int w, int h, int s, bool isCentered){
        position = vec2{posX, posY};
        velocity = vec2{velX, velY};
        width = w;
        height = h;
        scale = s;
        this->isCentered = isCentered;
    }

    void Initialize() override {
    }

    SDL_Rect CalculateNextPosition(SDL_Rect rect, float deltaTime)
    {
        // Clamp to right edge of map
        if ((rect.x + (velocity.x * deltaTime)) > (WINDOW_WIDTH * Game::scroll) - (width * scale))
        {
            rect.x = (WINDOW_WIDTH * Game::scroll) - (width * scale);
        }
            // Clamp to left edge
        else if ((rect.x + (velocity.x * deltaTime)) < 0)
        {
            rect.x = 0;
        }
        else
        {
            rect.x += velocity.x * deltaTime;
        }

        // Clamp to bottom of map
        if ((rect.y + (velocity.y * deltaTime)) > (WINDOW_HEIGHT * Game::scroll) - (height * scale))
        {
            rect.y = (WINDOW_HEIGHT* Game::scroll) - (height * scale);
        }
        else if ((rect.y + (velocity.y * deltaTime)) < 0)
        {
            rect.y = 0;
        }
        else
        {
            rect.y += velocity.y * deltaTime;
        }

        return rect;
    }

    void Update(float deltaTime) override
    {

        if (!Game::suspendMovement)
        {
            // Is centered for when we want the sprite to appear in the centre of the screen at all times
            if (isCentered)
            {
                position.x = Game::camera.x + ((WINDOW_WIDTH - (width * scale)))/2;
                position.y = Game::camera.y + ((WINDOW_HEIGHT - (height * scale)))/2;
            }

            // Reset position is used for collisions,
            // If we are going to collide with something we set reset position to true
            // So that we avoid moving it this frame
            else if (!owner->resetPosition)
            {
                // Clamp to right edge of map
                if ((position.x + (velocity.x * deltaTime)) > (WINDOW_WIDTH * Game::scroll) - (width * scale))
                {
                    position.x = (WINDOW_WIDTH * Game::scroll) - (width * scale);
                }
                    // Clamp to left edge
                else if ((position.x + (velocity.x * deltaTime)) < 0)
                {
                    position.x = 0;
                }
                else
                {
                    position.x += velocity.x * deltaTime;
                }

                // Clamp to bottom of map
                if ((position.y + (velocity.y * deltaTime)) > (WINDOW_HEIGHT * Game::scroll) - (height * scale))
                {
                    position.y = (WINDOW_HEIGHT* Game::scroll) - (height * scale);
                }
                else if ((position.y + (velocity.y * deltaTime)) < 0)
                {
                    position.y = 0;
                }
                else
                {
                    position.y += velocity.y * deltaTime;
                }
            }
            owner->resetPosition = false;
        }
    }

    void Render() override {
        SDL_SetRenderDrawColor(Game::renderer, 255,255,0,255);
        int x = position.x;
        int y = position.y;
        SDL_Rect transform{x, y, width * scale, height*scale };
        //SDL_RenderDrawRect(Game::renderer, &sourceRectangle);
        SDL_RenderDrawRect(Game::renderer, &transform);
    }
};

#endif
