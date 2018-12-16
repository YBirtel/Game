#include <SDL/SDL.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 540
#define VELOCITY 0.5

int main(int argc, char* argv[]){

  int gameover = 0, colorkey = 0;
  SDL_Event event;
  SDL_Surface *sprite, *temp, *caisse, *temp2;
  SDL_Rect spritePosition, caissePosition;
  int jump = 0;
  double saut_y = 0, dy = 0;
  int descente = 0;

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("Jeu Plateforme", "Jeu Plateforme");

  /* create window */
  SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  SDL_Surface* window = SDL_LoadBMP("fond.bmp");
  /* convert bitmap to display format */
  SDL_Surface* bg = SDL_DisplayFormat(window);

  /* free the temp surface */
  SDL_FreeSurface(window);
  colorkey = SDL_MapRGB(screen->format, 0, 0, 0);
  SDL_SetColorKey(bg, SDL_TRUE, colorkey);

  /*sprite*/

  temp   = SDL_LoadBMP("personnage.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  /* caisse */

  temp2   = SDL_LoadBMP("caisse.bmp");
  caisse = SDL_DisplayFormat(temp2);
  SDL_FreeSurface(temp2);

  /* setup sprite colorkey and turn on RLE */
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format,29,112,189));

  SDL_SetColorKey(caisse, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(caisse->format,256,256,256));

  spritePosition.x = 453;
  spritePosition.y = 435;

  SDL_Rect spriteImage;

  spriteImage.x = 96;
  spriteImage.y = 0;
  spriteImage.w = 49;
  spriteImage.h = 64;

  SDL_Rect caisseImage;

  caisseImage.x = 0;
  caisseImage.y = 0;
  caisseImage.w = 48;
  caisseImage.h = 48;

  caissePosition.x = 500;
  caissePosition.y = 447;

  SDL_EnableKeyRepeat(10,10);

  saut_y = spritePosition.y;

  while(!gameover){



/* look for an event */
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	gameover = 1;
	break;

	/* handle the keyboard */
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_ESCAPE:
	case SDLK_q:
	  gameover = 1;
	  break;
	default:
	case SDLK_RIGHT:
	  spritePosition.x = spritePosition.x + 1;
	  spriteImage.x = 96;
	  break;
	case SDLK_LEFT:
	  spritePosition.x = spritePosition.x -1;
	  spriteImage.x = 0;
	  break;
	case SDLK_SPACE:
	  jump = 1;
	  break;
	}
      }
    }

    if(spritePosition.y >= 350 && jump == 1){
      dy = VELOCITY * sin(0.5);
      saut_y -= dy;
      spritePosition.y = (int) saut_y;
    }
    if(spritePosition.y <= 350 || descente == 1){
      descente = 1;
      jump = 0;
      saut_y += dy;
      spritePosition.y = (int) saut_y;
    }
    if(spritePosition.y == 435){
      descente = 0;
    }

    if((spritePosition.x == 452 || spritePosition.x ==545) && spritePosition.y > 386){
        if(spritePosition.x == 452 && spritePosition.y > 386){
            spritePosition.x = 452;
        }else if(spritePosition.x == 545 && spritePosition.y > 386){
            spritePosition.x = 545;
        }else if((spritePosition.x == 452 || spritePosition.x == 545) && spritePosition.y < 386){
            spritePosition.y = 386;
        }
    }

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(bg, NULL, screen, NULL);

    /* draw the sprite */

    SDL_BlitSurface(sprite, &spriteImage, screen, &spritePosition);

    SDL_BlitSurface(caisse, &caisseImage, screen, &caissePosition);

    /* update the screen */
    SDL_UpdateRect(screen,0,0,0,0);
  }

  /* free the background surface */
  SDL_FreeSurface(bg);

  /* clean up */

  SDL_Quit();
  return 0;
}


