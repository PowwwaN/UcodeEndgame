#include "../inc/minilibmx.h"

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(renderer, filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void blit2(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest2;

	dest2.x = x;
	dest2.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest2.w, &dest2.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest2);
}
