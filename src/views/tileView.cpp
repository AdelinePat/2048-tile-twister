
#include "tileView.hpp"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
TileView::TileView(int x, int y, int width, int height, int value)
    : GameObject(x, y, width, height), value(value) {}

void TileView::setValue(int newValue) { this->value = newValue; }
int TileView::getValue() { return this->value; }

void TileView::render(SDL_Renderer* renderer) {
  // Draw tile rectangle
  SDL_FRect rect = {static_cast<float>(x), static_cast<float>(y),
                    static_cast<float>(width), static_cast<float>(height)};
  SDL_SetRenderDrawColor(renderer, 200, 180, 140, 255);  // tile color
  SDL_RenderFillRect(renderer, &rect);
  SDL_SetRenderDrawColor(renderer, 120, 110, 90, 255);
  SDL_RenderRect(renderer, &rect);

  // Draw value as text (requires SDL_ttf)
  if (value > 0) {
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf", height / 2);
    if (!font) {
      std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
    }
    if (font) {
      SDL_Color textColor = {50, 50, 50, 255};
      std::string valStr = std::to_string(value);
      SDL_Surface* textSurface = TTF_RenderText_Blended(
          font, valStr.c_str(), valStr.length(), textColor);
      if (textSurface) {
        SDL_Texture* textTexture =
            SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
          int textW = textSurface->w;
          int textH = textSurface->h;
          SDL_FRect dstRect = {static_cast<float>(x + (width - textW) / 2),
                               static_cast<float>(y + (height - textH) / 2),
                               static_cast<float>(textW),
                               static_cast<float>(textH)};
          SDL_RenderTexture(renderer, textTexture, nullptr, &dstRect);
          SDL_DestroyTexture(textTexture);
        }
        SDL_DestroySurface(textSurface);
      }
      TTF_CloseFont(font);
    }
  }
}
