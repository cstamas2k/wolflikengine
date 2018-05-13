#include <SDL2/SDL.h>

class Player {
	public:
		float X = 8.0f;
		float Y = 8.0f;
		float angle = 0.0f;
		float fov = 3.14159265 / 4.0;
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

} nvideo;

int main(int argc, char* argv[]) {
	unsigned int currTime, lastTime = 0;

	nMap.dMap += "WWWWWWWWWWWWWWWW";
	nMap.dMap += "W              W";
	nMap.dMap += "WWWWWWWWW      W";
	nMap.dMap += "W              W";
	nMap.dMap += "W              W";
	nMap.dMap += "W              W";
	nMap.dMap += "W              W";
	nMap.dMap += "W           WWWW";
	nMap.dMap += "W           W  W";
	nMap.dMap += "W         W W  W";
	nMap.dMap += "W         W W  W";
	nMap.dMap += "W         W    W";
	nMap.dMap += "W         WWW  W";
	nMap.dMap += "W    WWWWWWWW WW";
	nMap.dMap += "W              W";
	nMap.dMap += "WWWWWWWWWWWWWWWW";
	

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(mScreen.w,mScreen.h,SDL_WINDOW_RESIZABLE,&nvideo.window,&nvideo.renderer);
	
	while (nvideo.event.type != SDL_QUIT) { //game loop
		SDL_PollEvent(&nvideo.event);
		currTime = SDL_GetTicks();
		SDL_GetWindowSize(nvideo.window,&mScreen.w,&mScreen.h);
		if (currTime > lastTime + (1000/30)) { //30 fps lock
			lastTime = currTime;
	

		/* actually the beginning of the game */
		for (int x = 0; x < mScreen.w; x++) {
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

				SDL_SetRenderDrawColor(nvideo.renderer,wallColor,wallColor,wallColor,255); //wall
				SDL_RenderDrawLine(nvideo.renderer,x,nCeiling,x,nFloor);

				SDL_SetRenderDrawColor(nvideo.renderer,205,133,63,255); //floor
				SDL_RenderDrawLine(nvideo.renderer,x,nFloor,x,mScreen.h);				



		} // */
		
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
				break;
			    case SDLK_DOWN:
				mPlayer.X -= sinf(mPlayer.angle) * 0.5f;
				mPlayer.Y -= cosf(mPlayer.angle) * 0.5f;
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
