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
#include <time.h>

static SDL_Texture *mario[3];
static SDL_Texture *marioReversed[3];
static SDL_Texture *idle;
static SDL_Texture *idleReversed;
static SDL_Texture *jump;
static SDL_Texture *jumpReversed;
static SDL_Texture *death;
static int walkCycleLenght;

static void initPlayerSprites(void);

static void initPlayerSprites(void) {
	mario[0] = loadTexture("gfx/player-sprites/walk01.png");
	mario[1] = loadTexture("gfx/player-sprites/walk02.png");
	mario[2] = loadTexture("gfx/player-sprites/walk03.png");

	marioReversed[0] = loadTexture("gfx/player-sprites/walk-reversed01.png");
	marioReversed[1] = loadTexture("gfx/player-sprites/walk-reversed02.png");
	marioReversed[2] = loadTexture("gfx/player-sprites/walk-reversed03.png");

	walkCycleLenght = 3;

	idle = loadTexture("gfx/player-sprites/idle.png");
	idleReversed = loadTexture("gfx/player-sprites/idle-reversed.png");

	jump = loadTexture("gfx/player-sprites/jump.png");
	jumpReversed = loadTexture("gfx/player-sprites/jump-reversed.png");

	death = loadTexture("gfx/player-sprites/death.png");
}

void turnCharacterRed(void) {
	SDL_SetTextureColorMod(idle, 255, 0, 0);
	SDL_SetTextureColorMod(idleReversed, 255, 0, 0);
	SDL_SetTextureColorMod(jump, 255, 0, 0);
	SDL_SetTextureColorMod(jumpReversed, 255, 0, 0);
	SDL_SetTextureColorMod(death, 255, 0, 0);

	for(int i = 0; i <= 2; i++) {
		SDL_SetTextureColorMod(mario[i], 255, 0, 0);
		SDL_SetTextureColorMod(marioReversed[i], 255, 0, 0);
	}
}

void turnCharacterNormal(void) {
	SDL_SetTextureColorMod(idle, 255, 255, 255);
	SDL_SetTextureColorMod(idleReversed, 255, 255, 255);
	SDL_SetTextureColorMod(jump, 255, 255, 255);
	SDL_SetTextureColorMod(jumpReversed, 255, 255, 255);
	SDL_SetTextureColorMod(death, 255, 255, 255);

	for(int i = 0; i <= 2; i++) {
		SDL_SetTextureColorMod(mario[i], 255, 255, 255);
		SDL_SetTextureColorMod(marioReversed[i], 255, 255, 255);
	}
}

void initPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;

	initPlayerSprites();

	player->health = 4;

	player->texture = idle;

	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void doPlayer(void)
{
	printf("X:%f, Y:%f\n", player->x, player->y);
	static int co = 0;
	static int timer = 0;

	player->dx = 0;
	co++;

	if(co > timer) {
		turnCharacterNormal();
	} else {
		turnCharacterRed();
	}

	if(player->turnRed == 1) {
		player->turnRed = 0;
		timer = co + 30;
	}

	if (app.keyboard[SDL_SCANCODE_ESCAPE])
	{
		exit(1);
	}

	if (app.keyboard[SDL_SCANCODE_RETURN])
	{
		level.theGameHasStarted = 1;
	}

	//Backward button
	if (app.keyboard[SDL_SCANCODE_A] && level.theGameHasStarted == 1 && level.thePlayerIsDead == 0)
	{
		static int frame = 0;
		static int spriteIndex = 0;
		player->dx = -PLAYER_MOVE_SPEED;
		frame++;
		player->isReversed = 1;

		if(frame % ANIMATION_UPDATE_VALUE == 0) {
			player->texture = marioReversed[spriteIndex];
			spriteIndex++;

			if(spriteIndex == walkCycleLenght) {spriteIndex = 0;}
		}

	}

	//Forward button
	if (app.keyboard[SDL_SCANCODE_D] && level.theGameHasStarted == 1 && level.thePlayerIsDead == 0)
	{
		static int frame = 0;
		static int spriteIndex = 0;
		player->dx = PLAYER_MOVE_SPEED;
		frame++;
		player->isReversed = 0;

		if(frame % ANIMATION_UPDATE_VALUE == 0) {
			player->texture = mario[spriteIndex];
			spriteIndex++;

			if(spriteIndex == walkCycleLenght) {spriteIndex = 0;}
		}

	}

	//Jump button
	if ((app.keyboard[SDL_SCANCODE_SPACE] || app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_I]) && player->isOnGround && level.theGameHasStarted == 1 && level.thePlayerIsDead == 0)
	{
		player->riding = NULL;

		player->dy = -20;

		playSound(SND_JUMP, CH_PLAYER);
	}

	//Death sprite
	if(level.thePlayerIsDead == 1) {
		static int count = 0;
		count++;

		if(count == 1) {
			player->dy = -30;
		}

		player->texture = death;
	}

	//Idle sprite
	if(app.keyboard[SDL_SCANCODE_D] == 0 && app.keyboard[SDL_SCANCODE_A] == 0 && player->isOnGround == 1 && level.thePlayerIsDead == 0) {
		if(player->isReversed == 0) {
			player->texture = idle;
		} else {
			player->texture = idleReversed;
		}
	}

	//Jump sprite
	if(player->isOnGround == 0 && level.thePlayerIsDead == 0) {
		if(player->isReversed == 0) {
			player->texture = jump;
		} else {
			player->texture = jumpReversed;
		}
	}

}
