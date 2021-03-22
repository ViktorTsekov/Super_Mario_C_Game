#include "common.h"

void initPipe(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;

  e->flags = EF_SOLID;

	e->texture = loadTexture("gfx/pipe.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
}
