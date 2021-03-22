#include "common.h"

void playConfetti(void) {
  Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

  e->texture = loadTexture("gfx/particle.png");

  e->x = rand() % SCREEN_WIDTH * 3 + 1;
	e->y = 10;

	e->health = 1;

	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_NONE;
}

void deleteOldConfetti(void) {
  Entity *e, *prev;
	prev = &stage.entityHead;

	for (e = stage.entityHead.next ; e != NULL ; e = e->next)
	{
		self = e;
    e->count++;

    if(e->count >= 420 && e != player) {

      if (e == stage.entityTail)
			{
				stage.entityTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
    }

		prev = e;
	}

}
