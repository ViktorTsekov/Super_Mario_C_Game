#include "common.h"

static void touch(Entity *other);
static void tick(void);

//X, Y, dealSuperDamage
void initSpikes(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f %d", &e->x, &e->y, &e->dealSuperDamage);

	e->health = 1;

	e->touch = touch;
	e->tick = tick;

	e->texture = loadTexture("gfx/spikes.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_SOLID;
}

static void tick(void)
{
	self->count++;
	self->value += 0.1;
	self->y += sin(self->value);
}

static void touch(Entity *other)
{
	if (other == player)
	{
		int h = other->health - 1;

		if(h >= 1 && self->count >= self->timer) {
			if(self->dealSuperDamage == 1) {
				playSound(SND_OOF, CH_PLAYER);
				player->health = 1;
				player->dy = -20;
			} else {
				playSound(SND_OOF, CH_PLAYER);
				other->health--;
				player->dy = -20;
				player->turnRed = 1;
				self->timer = self->count + 30;
			}
		}
	}
}
