#pragma once

#include <SDL.h>
#include "map.h"

class {
public:
	SDL_Window *w;
	SDL_Renderer *r;
	SDL_Event event;
	struct {
		int height = 600;
		int width = 800;
	} window;
	
	void drawLine(int x, int y1, int y2, unsigned char red, unsigned char green, unsigned char blue) {
		SDL_SetRenderDrawColor(r, red, green, blue, 255);
		SDL_RenderDrawLine(r, x, y1, x, y2);
	}
	void update() {
		SDL_RenderPresent(r);
	}

} sdl;

class {
public:
	double x;
	double y;
	int hp = 100;
	unsigned char w_curr; //current weapon
	double fov = 3.1415 / 4.0;
	double angle = 1.0;

	bool isPlayerColliding(std::string map) {
		if (map[x * 16 + y] == '#' || map[x * 16 + y] == 'H') { return true; } //TODO: read map size ( currently 16x16 tile)
		return false;
	}
	void moveFwd(bool isRunning = false) {
		double speed;
		if (isRunning) speed = 0.2;
		if (!isRunning) speed = 0.1;
		x += sin(angle) * speed;
		y += cos(angle) * speed;
	}
	void moveRwd(bool isRunning = false) {
		double speed;
		if (isRunning) speed = 0.2;
		if (!isRunning) speed = 0.1;
		x -= sin(angle) * speed;
		y -= cos(angle) * speed;
	}
	void moveLeft(bool isRunning = false) {
		double speed;
		if (isRunning) speed = 0.2;
		if (!isRunning) speed = 0.1;
		x -= cos(angle) * speed;
		y += sin(angle) * speed;
	}
	void moveRight(bool isRunning = false) {
		double speed;
		if (isRunning) speed = 0.2;
		if (!isRunning) speed = 0.1;
		x += cos(angle) * speed;
		y -= sin(angle) * speed;
	}
	void setSpawnPoint(std::string map) {
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) 
				if (map[x * 16 + y] == 'S') {
					player.x = x;
					player.y = y;
				}
		}
	}
}player;

void renderScene(int x, std::string map, int wSizeX, int wSizeY) {
	double rayAngle = player.angle - (player.fov / 2.0) + ((double)x / (double)wSizeX) * player.fov;
	double stepSize = 0.1; //smaller value = bigger detail
	double distToWall = 0.0;
	bool wallHit = false;
	bool doorHit = false; //for door coloring
	double eyeX = sin(rayAngle);
	double eyeY = cos(rayAngle);

	while ((!wallHit && !doorHit) && distToWall < 16.0) { //raycasting to walls
		distToWall += stepSize;
		int testCoordX = (int)(player.x + eyeX * distToWall);
		int testCoordY = (int)(player.y + eyeY * distToWall);
		int m_currLoc = testCoordX * 16 + testCoordY; //current location in map-space, in 1D array
		if (map[m_currLoc] == '#') wallHit = true;
		if (map[m_currLoc] == 'H') doorHit = true;
	}

	//finally begin drawing
	//TODO: texturing walls, maybe floor&ceiling
	int wallTop = (wSizeY / 2) - (wSizeY / distToWall);
	int wallBottom = wSizeY - wallTop;
	unsigned char wallColor;
	if (!doorHit) wallColor = 255 - distToWall * 16;
	if (doorHit) wallColor = 255 - distToWall * 8;
	sdl.drawLine(x, 0, wallTop, 64, 64, 64); //ceiling
	sdl.drawLine(x, wallTop, wallBottom, wallColor, wallColor, wallColor); //wall
	sdl.drawLine(x, wallBottom, wSizeY, 128, 128, 128); //floor

}