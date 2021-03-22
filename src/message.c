#include "common.h"

//X, Y, textureType
void initMessage(char *line)
{
	Entity *e;
  int index;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f %d", &e->x, &e->y, &index);

	e->health = 1;

  if(index == 1) {
    e->texture = loadTexture("gfx/secret-message01.png");
  } else if(index == 2) {
    e->texture = loadTexture("gfx/secret-message02.png");
  }

	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
  e->flags = EF_WEIGHTLESS;
}
