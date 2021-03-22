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

static void loadTiles(void);
static void loadMap(const char *filename);
int isInsideMap(int x, int y);

static SDL_Texture *tiles[MAX_TILES];

void initMap(void)
{
	if(level.currentLevel == 0) {
		memset(&stage.map, 0, sizeof(int) * level.mapWidth * level.mapHeight);
		loadTiles();
		loadMap("data/Level1/map01.dat");
	} else if(level.currentLevel == 1) {
		memset(&stage.map, 0, sizeof(int) * level.mapWidth * level.mapHeight);
		loadTiles();
		loadMap("data/Level2/map02.dat");
	} else if(level.currentLevel == 2) {
		memset(&stage.map, 0, sizeof(int) * level.mapWidth * level.mapHeight);
		loadTiles();
		loadMap("data/Level3/map03.dat");
	} else if(level.currentLevel == 3) {
		memset(&stage.map, 0, sizeof(int) * level.mapWidth * level.mapHeight);
		loadTiles();
		loadMap("data/Level4/map04.dat");
	} else if(level.currentLevel == 4) {
		memset(&stage.map, 0, sizeof(int) * level.mapWidth * level.mapHeight);
		loadTiles();
		loadMap("data/Level5/map05.dat");
	} else {
		memset(&stage.map, 0, sizeof(int) * level.mapWidth * level.mapHeight);
		loadTiles();
		loadMap("data/FinalScene/finalSceneMap.dat");
	}
}

void drawMap(void)
{
	int x, y, n, x1, x2, y1, y2, mx, my;

	x1 = (stage.camera.x % TILE_SIZE) * -1;
	x2 = x1 + MAP_RENDER_WIDTH * TILE_SIZE + (x1 == 0 ? 0 : TILE_SIZE);

	y1 = (stage.camera.y % TILE_SIZE) * -1;
	y2 = y1 + MAP_RENDER_HEIGHT * TILE_SIZE + (y1 == 0 ? 0 : TILE_SIZE);

	mx = stage.camera.x / TILE_SIZE;
	my = stage.camera.y / TILE_SIZE;

	for (y = y1 ; y < y2 ; y += TILE_SIZE)
	{
		for (x = x1 ; x < x2 ; x += TILE_SIZE)
		{
			if (isInsideMap(mx, my))
			{
				n = stage.map[mx][my];

				if (n > 0)
				{
					blit(tiles[n], x, y, 0);
				}
			}

			mx++;
		}

		mx = stage.camera.x / TILE_SIZE;

		my++;
	}
}

static void loadTiles(void)
{
	int i;
	char filename[MAX_FILENAME_LENGTH];

	for (i = 1 ; i <= MAX_TILES ; i++)
	{
		sprintf(filename, "gfx/tile%d.png", i);

		tiles[i] = loadTexture(filename);
	}
}

static void loadMap(const char *filename)
{
	char *data, *p;
	int x, y;

	data = readFile(filename);

	p = data;

	for (y = 0 ; y < level.mapHeight ; y++)
	{
		for (x = 0 ; x < level.mapWidth ; x++)
		{
			sscanf(p, "%d", &stage.map[x][y]);

			do {p++;} while (*p != ' ' && *p != '\n');
		}
	}

	free(data);
}

int isInsideMap(int x, int y)
{
	return x >= 0 && y >= 0 && x < level.mapWidth && y < level.mapHeight;
}
