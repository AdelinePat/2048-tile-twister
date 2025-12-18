#include "TileView.hpp"
#include <cmath>
#include <string>

TileView::TileView(SDL_Renderer* renderer, std::shared_ptr<Tile> tile, 
                   float x, float y, float size)
    : GameObject(renderer, x, y, size, size), tile(tile) {
}

void TileView::render() {
    if (!tile) return;
    
    SDL_Color bgColor, textColor;
    getColorForValue(tile->getValue(), bgColor, textColor);
    
    // Draw tile background with rounded corners
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    renderRoundedRect(x, y, width, height, 8.0f);
    
    // Draw the number if tile is not empty
    if (!tile->isEmpty()) {
        std::string valueStr = std::to_string(tile->getValue());
        renderText(valueStr, x + width / 2, y + height / 2, textColor);
    }
}

void TileView::getColorForValue(int value, SDL_Color& bgColor, SDL_Color& textColor) {
    // Classic 2048 color scheme
    switch (value) {
        case 0:
            bgColor = {205, 193, 180, 255};  // Empty tile
            textColor = {119, 110, 101, 255};
            break;
        case 2:
            bgColor = {238, 228, 218, 255};
            textColor = {119, 110, 101, 255};
            break;
        case 4:
            bgColor = {237, 224, 200, 255};
            textColor = {119, 110, 101, 255};
            break;
        case 8:
            bgColor = {242, 177, 121, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 16:
            bgColor = {245, 149, 99, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 32:
            bgColor = {246, 124, 95, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 64:
            bgColor = {246, 94, 59, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 128:
            bgColor = {237, 207, 114, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 256:
            bgColor = {237, 204, 97, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 512:
            bgColor = {237, 200, 80, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 1024:
            bgColor = {237, 197, 63, 255};
            textColor = {249, 246, 242, 255};
            break;
        case 2048:
            bgColor = {237, 194, 46, 255};
            textColor = {249, 246, 242, 255};
            break;
        default:  // For values > 2048
            bgColor = {60, 58, 50, 255};
            textColor = {249, 246, 242, 255};
            break;
    }
}

void TileView::renderRoundedRect(float x, float y, float w, float h, float radius) {
    // Simple filled rectangle (SDL3 doesn't have built-in rounded rect)
    // For a production version, you'd want to draw actual rounded corners
    SDL_FRect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void TileView::renderText(const std::string& text, float centerX, float centerY, 
                         const SDL_Color& color) {
    // Note: This is a simplified version. In a real implementation,
    // you'd want to use SDL_ttf for proper text rendering
    // For now, we'll skip text rendering to keep dependencies minimal
    // You can add SDL_ttf support later
    
    // TODO: Add SDL_ttf integration for proper text rendering
    // For basic testing, the colored tiles will be enough to see the game working
}