/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"

static void touch(Entity *other);
static void tick(void);

void initBlock(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;
	e->touch = touch;
	e->tick = tick;

	e->texture = loadTexture("gfx/block.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_SOLID + EF_WEIGHTLESS;
}

static void tick(void)
{
	self->count++;
	//self->value += 0.1;
	//self->y += sin(self->value);

	//if(self->destroy == 1 && self->count > self->timer) {
	//	self->health = 0;
	//}

}

static void touch(Entity *other)
{
	static int count = 0;

	if (other == player)
	{
		count++;
		//self->flags = EF_SOLID;
		//self->destroy = 1;

		//if(count == 1) {
			//self->timer = self->count + 30;
		//}

	}

}
