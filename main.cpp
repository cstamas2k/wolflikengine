#include <iostream>
#include <SDL2/SDL.h>

int wsizex = 800;
int wsizey = 600;

float playerx = 8.0f;
float playery = 8.0f;
float playera = 0.0f;
float fov = 3.14159265 / 4.0f;

int mapsizex = 16;
int mapsizey = 16;

std::string map;

unsigned int t_start, t_elapsed = 0;

SDL_Renderer *s_r;
SDL_Window *s_w;

SDL_Event event;

int main(int argc, char* argv[]) {
	/* define map */
	map += "################";
	map += "#.......#......#";
	map += "#.......#......#";
	map += "#.......#......#";
	map += "#......##......#";
	map += "#......#.......#";
	map += "#......#.......#";
	map += "#....####D#....#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "################";

	/* init video things */
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(wsizex,wsizey,SDL_WINDOW_SHOWN,&s_w,&s_r);
	//SDL_SetRelativeMouseMode(SDL_TRUE);


	while (event.type != SDL_QUIT) { //game loop
		SDL_PollEvent(&event);
		t_start = SDL_GetTicks();
		if (t_start > t_elapsed + 1000/60) { //60fps lock
 		t_elapsed = t_start;
	

		for (int x = 0; x < wsizex; x++) {//actually the rendering loop
			float raya = (playera - fov/2.0f) + ((float)x / (float)wsizex) * fov;
			
			float stepsize = 0.05f;
			float disttowall = 0.0f;
			bool wallhit = false;

			bool doorhit = false;
			float disttodoor = 0.0f;
			int doorstartx = 0;

			float eyex = sinf(raya);
			float eyey = cosf(raya);
			
			/* walls & doors */
			while ((!wallhit && !doorhit) && disttowall < 16.0f) {
				
					disttowall += stepsize;
					int testx = (int)(playerx + eyex * disttowall);
					int testy = (int)(playery + eyey * disttowall);
					
				if (map[testx*mapsizex+testy] == '#')  wallhit = true; ;
				if (map[testx*mapsizex+testy] == 'D')  doorhit = true; //TODO: working door animation
				
			}
			

			int ceilingh = (wsizey/2)-wsizey/disttowall;
			int floorh = wsizey - ceilingh;
			char wallcolor = 256-disttowall*16;


			SDL_SetRenderDrawColor(s_r,135,206,235,255);
			SDL_RenderDrawLine(s_r,x,0,x,ceilingh); //sky

			if (!doorhit) {SDL_SetRenderDrawColor(s_r,wallcolor,wallcolor,wallcolor,255);SDL_RenderDrawLine(s_r,x,ceilingh,x,floorh); } //wall
			if (doorhit) { //door TODO: door is "in" the wall, like in wolf3d
				SDL_SetRenderDrawColor(s_r,wallcolor,32,128,255); 
				SDL_RenderDrawLine(s_r,x,ceilingh,x,floorh);
			} 

			 


			SDL_SetRenderDrawColor(s_r,64,64,64,255);
			SDL_RenderDrawLine(s_r,x,floorh,x,wsizey);//floor

		}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) playera -= 0.1f;
		if (event.key.keysym.sym == SDLK_RIGHT) playera += 0.1f;

		if (event.key.keysym.sym == SDLK_UP) { playerx += sinf(playera) * 0.1f; playery += cosf(playera) * 0.1f; 
		if (map[(int)playerx * mapsizex + (int)playery] != '.') { playerx -= sinf(playera) * 0.1f; playery -= cosf(playera) * 0.1f; }
		}
		if (event.key.keysym.sym == SDLK_DOWN) { playerx -= sinf(playera) * 0.1f; playery -= cosf(playera) * 0.1f; 
		if (map[(int)playerx * mapsizex + (int)playery] != '.') { playerx += sinf(playera) * 0.3f; playery += cosf(playera) * 0.3f; }
		}
		//if (event.key.keysym.sym == SDLK_DOWN) { /* TODO: door opening */ if (map[(int)playerx * mapsizex + (int)playery] == 'D') map[(int)playerx * mapsizex + (int)playery] = '.'; }

	std::cout << map[(int)playerx * mapsizex + (int)playery] << std::endl;
	}

	
	/* TODO: mouse look */
	
	//playera = event.motion.xrel/10;


	SDL_RenderPresent(s_r);
	}
	}

SDL_Quit();

}
