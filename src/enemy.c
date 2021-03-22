#include "common.h"

static void move(void);
static void touch(Entity *other);
static void calculateDist(Entity *e);
static void tick(void);

//X, Y, speed, range
void initEnemy(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f %f %f", &e->x, &e->y, &e->speed, &e->range);

	calculateDist(e);

	e->health = 1;

	e->moveForward = 1;

	e->move = move;
	e->touch = touch;
	e->tick = tick;

	e->texture = loadTexture("gfx/enemy.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_SOLID;
}

static void tick(void)
{
	self->count++;
	self->value += 0.1;
	self->y += sin(self->value);
}

static void move(void) {

	if(self->moveForward == 1) {
		self->x += self->speed;
		self->texture = loadTexture("gfx/enemy.png");
	} else if(self->moveBackwards == 1) {
		self->x -= self->speed;
		self->texture = loadTexture("gfx/enemy-reversed.png");
	}

	if(self->x >= self->maxDist) {
		self->moveForward = 0;
		self->moveBackwards = 1;
	} else if(self->x <= self->minDist) {
		self->moveForward = 1;
		self->moveBackwards = 0;
	}

}

static void calculateDist(Entity *e) {
	e->maxDist = e->x + e->range;
	e->minDist = e->x - e->range;
}

static void touch(Entity *other)
{
	if (other == player)
	{
		int h = other->health - 1;

		if(h >= 1 && self->count >= self->timer) {
			playSound(SND_OOF, CH_PLAYER);
			other->health--;
			player->turnRed = 1;
			self->timer = self->count + 30;
		}
	}
}
