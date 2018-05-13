#include <SDL2/SDL.h>
#include <iostream>
class Player {
	public:
		float X = 2.0f;
		float Y = 2.0f;
		float angle = 0.0f;
		float fov = 3.14159265 / 4.0;

		int health = 100;
		int ammo = 100;
} mPlayer;

class Map {
	public: 
		int height= 16;
		int width = 16;


	std::string dMap;


} nMap;


class Screen {
	public: 
		int h = 600;
		int w = 800;
} mScreen;

class SDLThings {
	public:
		SDL_Event event;
		SDL_Window* window;
		SDL_Renderer* renderer;

		SDL_Rect gui_bg;
		SDL_Rect healthbar;
		SDL_Rect maptile;

} nvideo;

int main(int argc, char* argv[]) {
	unsigned int currTime, lastTime = 0;
	

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(mScreen.w,mScreen.h,SDL_WINDOW_RESIZABLE,&nvideo.window,&nvideo.renderer);

	nMap.dMap += "WWWWWWWWWWWWWWWW";
	nMap.dMap += "W..W.W.........W";
	nMap.dMap += "W..W.W.........W";
	nMap.dMap += "W..W.W.........W";
	nMap.dMap += "W....W.........W";
	nMap.dMap += "W.WW.W.........W";
	nMap.dMap += "W.W..W.........W";
	nMap.dMap += "W.W.WW.........W";
	nMap.dMap += "W..............W";
	nMap.dMap += "W.W.W....W.....W";
	nMap.dMap += "W.W......W.....W";
	nMap.dMap += "W.W......W.....W";
	nMap.dMap += "W.W.W..........W";
	nMap.dMap += "W.W.W..........W";
	nMap.dMap += "W.W.W..........W";
	nMap.dMap += "WWWWWWWWWWWWWWWW";
	
	while (nvideo.event.type != SDL_QUIT) { //game loop
		SDL_PollEvent(&nvideo.event);
		currTime = SDL_GetTicks();
		SDL_GetWindowSize(nvideo.window,&mScreen.w,&mScreen.h);
		if (currTime > lastTime + (1000/30)) { //30 fps lock
			lastTime = currTime;
	

		/* actually the beginning of the game */
		for (int x = 0; x < mScreen.w; x++) { // begin of 3d rendering things
				//for each column, calculate the ray angle into worldspace
				float fRayAngle = (mPlayer.angle - mPlayer.fov/2.0f) + ((float)x / (float)mScreen.w) * mPlayer.fov;
				float fDistanceToWall = 0.0f;
				bool bHitWall = false;

				float fEyeX = sinf(fRayAngle);	
				float fEyeY = cosf(fRayAngle);
				while (!bHitWall && fDistanceToWall < 16.0f) {
					fDistanceToWall += 0.1f;

					int nTestX = (int)(mPlayer.X + fEyeX * fDistanceToWall);
					int nTestY = (int)(mPlayer.Y + fEyeY * fDistanceToWall);

					if (nTestX < 0 || nTestX >= nMap.width || nTestY < 0 || nTestY >= nMap.height) {
						bHitWall = true;
						fDistanceToWall = 16.0f;
					} else {
						if (nMap.dMap[nTestX * nMap.width + nTestY] == 'W') {
							bHitWall = true;
						}	
					}
				}

				int nCeiling = (mScreen.h/2)-mScreen.h/fDistanceToWall;	
				int nFloor = mScreen.h - nCeiling;
				char wallColor = 256-(fDistanceToWall*16);
				
				SDL_SetRenderDrawColor(nvideo.renderer,130,177,255,255); //sky
				SDL_RenderDrawLine(nvideo.renderer,x,0,x,nCeiling);
				
				// TODO: split walls into 128 px wide slices, and get x,y coordinates for each corner 

				SDL_SetRenderDrawColor(nvideo.renderer,wallColor,wallColor,wallColor,255);
				SDL_RenderDrawLine(nvideo.renderer,x,nCeiling,x,nFloor); //wall

				SDL_SetRenderDrawColor(nvideo.renderer,205,133,63,255); //floor
				SDL_RenderDrawLine(nvideo.renderer,x,nFloor,x,mScreen.h);				



		} // end of 3d rendering things*/

		/* begin of 2d things, like gui */
		nvideo.gui_bg.w = mScreen.w;
		nvideo.gui_bg.h = mScreen.h/8;
		nvideo.gui_bg.x = 0;
		nvideo.gui_bg.y = mScreen.h-(nvideo.gui_bg.h);
		SDL_SetRenderDrawColor(nvideo.renderer,23,61,122,255);
		SDL_RenderDrawRect(nvideo.renderer,&nvideo.gui_bg);
		SDL_RenderFillRect(nvideo.renderer,&nvideo.gui_bg);


		// HEALTH 
		nvideo.healthbar.x = nvideo.gui_bg.x + 20;
		nvideo.healthbar.y = nvideo.gui_bg.y + 20;
		nvideo.healthbar.w = nvideo.gui_bg.w / 16;
		nvideo.healthbar.h = nvideo.gui_bg.h /  8;
		SDL_SetRenderDrawColor(nvideo.renderer,mPlayer.health*2.55f,0,0,255);
		SDL_RenderDrawRect(nvideo.renderer,&nvideo.healthbar);
		SDL_RenderFillRect(nvideo.renderer,&nvideo.healthbar);

		if (mPlayer.health <= 0) {
		std::cout << "You are dead. exiting..." << std::endl;
		SDL_Quit();
		}
		//EOF HEALTH



		// DRAW MAP 

		nvideo.maptile.w = nvideo.maptile.h = 3;
		int mStartX = (mScreen.h/2);
		int mStartY = nvideo.gui_bg.y + (nvideo.gui_bg.h/16);
		for (int mx = 0; mx < nMap.width; mx++) {
			for (int my = 0; my < nMap.height; my++) {
				if (nMap.dMap[(int)mx * nMap.width + (int)my] == 'W') {
					nvideo.maptile.x = mStartX + (mx*3); nvideo.maptile.y = mStartY + (my*3);
					SDL_SetRenderDrawColor(nvideo.renderer,255,255,255,255);
					SDL_RenderFillRect(nvideo.renderer,&nvideo.maptile);
				}
				//draw the player on map
				SDL_SetRenderDrawColor(nvideo.renderer,255,0,0,255);
				nvideo.maptile.x = mStartX + (mPlayer.X*3); nvideo.maptile.y = mStartY + (mPlayer.Y*3);
				SDL_RenderFillRect(nvideo.renderer,&nvideo.maptile);
			}
		}

		//EOF MAP
		/* end of 2d things */

		
		/* input */
		switch(nvideo.event.type){
		    /* Look for a keypress */
		    case SDL_KEYDOWN:
		        /* Check the SDLKey values and move change the coords */
		        switch( nvideo.event.key.keysym.sym ){
		            case SDLK_LEFT:
		                mPlayer.angle -= 0.1f;
		                break;
		            case SDLK_RIGHT:
		                mPlayer.angle += 0.1f;
		                break;
			    case SDLK_UP:
				mPlayer.X += sinf(mPlayer.angle) * 0.1f;
				mPlayer.Y += cosf(mPlayer.angle) * 0.1f;
				if (nMap.dMap[(int)mPlayer.X * nMap.width + (int)mPlayer.Y] == 'W') {
					mPlayer.X -= sinf(mPlayer.angle) * 0.2f;
					mPlayer.Y -= cosf(mPlayer.angle) * 0.2f;
				}
				break;
			    case SDLK_DOWN:
				mPlayer.X -= sinf(mPlayer.angle) * 0.1f;
				mPlayer.Y -= cosf(mPlayer.angle) * 0.1f;
				if (nMap.dMap[(int)mPlayer.X * nMap.width + (int)mPlayer.Y] == 'W') {
					mPlayer.X += sinf(mPlayer.angle) * 0.2f;
					mPlayer.Y += cosf(mPlayer.angle) * 0.2f;
				}
				break;
		            default:
		                break;
		        }
		    }
        
	
		SDL_RenderPresent(nvideo.renderer);
	} 
	}
	SDL_Quit();
}
