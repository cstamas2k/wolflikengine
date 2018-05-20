#include <SDL.h>
#include <string>

#include <fstream>

SDL_Renderer *s_r;
SDL_Window *s_w;

SDL_Rect tile;
SDL_Rect selected;

SDL_Event event;

int mapX = 16;
int mapY = 16;

std::string mapData;

struct {
	int x = 0;
	int y = 0;
} selection;

void loadMap() {
	std::ifstream inFile("map1.dat");
	inFile >> mapData;
}

void saveMap() {
	std::ofstream outFile("map1.dat");
	outFile << mapData;
}

int main(int argc, char* argv[]) {

	/* base map*/

	mapData += "################";
	mapData += "#..............#";
	mapData += "#.......########";
	mapData += "#..............#";
	mapData += "#......##......#";
	mapData += "#......##......#";
	mapData += "#..............#";
	mapData += "###............#";
	mapData += "##.........DD..#";
	mapData += "#......####HH###";
	mapData += "#......#...DD..#";
	mapData += "#......#.......#";
	mapData += "#..............#";
	mapData += "#......#########";
	mapData += "#..............#";
	mapData += "################";


	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(mapX * 32 + 16, mapY * 32 + 16, SDL_WINDOW_SHOWN, &s_w, &s_r);

	tile.h = tile.w = 32;
	selected.w = selected.h = 32;

	while (event.type != SDL_QUIT) {
		SDL_PollEvent(&event);

		for (int x = 0; x < 16; x++) { //rows
			for (int y = 0; y < 16; y++) { //columns
				if (mapData[x * 16 + y] == 'S') SDL_SetRenderDrawColor(s_r, 255, 0, 0, 255);
				if (mapData[x * 16 + y] == '#') SDL_SetRenderDrawColor(s_r, 128, 128, 128, 255); //wall is grey
				if (mapData[x * 16 + y] == 'H') SDL_SetRenderDrawColor(s_r, 192, 192, 128, 255); //door
				if (mapData[x * 16 + y] == 'D') SDL_SetRenderDrawColor(s_r, 192, 192, 192, 255); //door entry
				if (mapData[x * 16 + y] == '.') SDL_SetRenderDrawColor(s_r, 0, 0, 0, 0); //walkable space
				tile.x = x * 32;
				tile.y = y * 32;
				SDL_RenderFillRect(s_r, &tile);
			}
		}

		/* draw selection */
		selected.x = selection.x * 32;
		selected.y = selection.y * 32;

		SDL_SetRenderDrawColor(s_r, 255, 255, 255, 255);
		SDL_RenderDrawRect(s_r, &selected);

		/*input handling*/
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_LEFT) selection.x--;
			if (event.key.keysym.sym == SDLK_RIGHT) selection.x++;
			if (event.key.keysym.sym == SDLK_UP)   selection.y--;
			if (event.key.keysym.sym == SDLK_DOWN) selection.y++;

			/* block placing*/

			if (event.key.keysym.sym == SDLK_w) mapData[selection.x * 16 + selection.y] = '#'; //wall placing
			if (event.key.keysym.sym == SDLK_d) mapData[selection.x * 16 + selection.y] = 'H'; //door placing
			if (event.key.keysym.sym == SDLK_e) mapData[selection.x * 16 + selection.y] = 'D'; //door entry placing
			if (event.key.keysym.sym == SDLK_q) mapData[selection.x * 16 + selection.y] = '.'; //delete block

			if (event.key.keysym.sym == SDLK_s) mapData[selection.x * 16 + selection.y] = 'S'; //spawnpoint

			/* save & load*/
			if (event.key.keysym.sym == SDLK_1) loadMap();
			if (event.key.keysym.sym == SDLK_2) saveMap();
		}
	SDL_Delay(100);
	SDL_RenderPresent(s_r);
	}
	SDL_Quit();
	return 0;
}