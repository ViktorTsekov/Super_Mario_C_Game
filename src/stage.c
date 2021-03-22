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

static void logic(void);
static void draw(void);
static void drawHud(void);
static void drawStartScreen(void);
static void drawEndScreen(void);
static void drawDeathScreen(void);
static void drawHearts(void);

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));

	stage.entityTail = &stage.entityHead;

	initEntities();

	initMap();

	initPlayer();
}

static void logic(void)
{
	doPlayer();

	doEntities();

	doCamera();
}

static void draw(void)
{
	SDL_SetRenderDrawColor(app.renderer, 128, 192, 255, 255);
	SDL_RenderFillRect(app.renderer, NULL);

	drawMap();

	drawEntities();

	if(level.theGameHasStarted == 0) {
		drawStartScreen();
	}

	if(level.theGameHasEnded == 1) {
		drawEndScreen();
		playConfetti();
		deleteOldConfetti();
	}

	if(level.thePlayerIsDead == 1) {
		static int count = 0;
		count++;

		if(count >= 40) {
			drawDeathScreen();
		}
	}

	if(level.theGameHasStarted == 1 && level.theGameHasEnded == 0 && level.thePlayerIsDead == 0) {
		drawHud();
	}

}

static void drawStartScreen(void) {
	SDL_Rect r;
	int spaceBetweenSenctences = 40;
	int value = 0;
	int offset = 100;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "OH NO, MARIO IS MAKING A PARTY AND HE NEEDS HIS PIZZA."); value += spaceBetweenSenctences;
	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "CAN YOU HELP HIM COLLECT ALL OF THE PIZZAS?"); value += spaceBetweenSenctences;
	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "A,D: MOVE LEFT AND RIGHT"); value += spaceBetweenSenctences;
	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "SPACE,W,I: JUMP"); value += spaceBetweenSenctences;
	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "ESC: EXIT"); value += spaceBetweenSenctences;
	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "PRESS ENTER TO START"); value += spaceBetweenSenctences;
}

static void drawEndScreen(void) {
	SDL_Rect r;
	int spaceBetweenSenctences = 40;
	int value = 0;
	int offset = 100;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "CONGRATULATIONS YOU BEAT THE GAME!"); value += spaceBetweenSenctences;
}

static void drawDeathScreen(void) {
	SDL_Rect r;
	int spaceBetweenSenctences = 40;
	int value = 0;
	int offset = 100;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "OH NO, YOU DIED!"); value += spaceBetweenSenctences;
	drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + value - offset, 255, 255, 255, TEXT_CENTER, "PRESS ESCAPE TO TRY AGAIN."); value += spaceBetweenSenctences;
}

static void drawHearts(void) {
	SDL_Rect r;
	SDL_Texture *heartTexture = loadTexture("gfx/heart.png");

	r.y = 5;
	r.w = 30;
	r.h = 30;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(app.renderer, NULL);

	if(player->health == 4) {
		r.x = 200;
		SDL_RenderCopy(app.renderer, heartTexture, NULL, &r);
		r.x = 240;
		SDL_RenderCopy(app.renderer, heartTexture, NULL, &r);
		r.x = 280;
		SDL_RenderCopy(app.renderer, heartTexture, NULL, &r);
	} else if(player->health == 3) {
		r.x = 200;
		SDL_RenderCopy(app.renderer, heartTexture, NULL, &r);
		r.x = 240;
		SDL_RenderCopy(app.renderer, heartTexture, NULL, &r);
	} else if(player->health == 2) {
		r.x = 200;
		SDL_RenderCopy(app.renderer, heartTexture, NULL, &r);
	} else {
		level.thePlayerIsDead = 1;
	}

}

static void drawHud(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	drawText(SCREEN_WIDTH - 10, 5, 255, 255, 255, TEXT_RIGHT, "PIZZA %d/%d", stage.pizzaFound, stage.pizzaTotal - 3);
	drawText(10, 5, 255, 255, 255, TEXT_LEFT, "LEVEL %d/%d", level.currentLevel + 1, level.maxLevels);
	drawHearts();
}
