#include"tictactoe.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
int main()
{
	int boocle=1 , repitition=0 ;
	SDL_Surface *screen;
	SDL_Event event;
	xo t;
	rotozoom z;
	background back;
	image im;
	Mix_Music *son;
	Mix_Chunk *rebh;
	Mix_Chunk *khsara;
	TTF_Init();
	InitialiserBackground(&back);
	InitialiserXO(&t);
	Init_rotozoom(&z);
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	screen = SDL_SetVideoMode( 754 , 501 , 32 , SDL_HWSURFACE | SDL_DOUBLEBUF );
	son=Mix_LoadMUS("song/son.mp3");
	Mix_PlayMusic(son,-1);
	rebh=Mix_LoadWAV("song/gagner.wav");
	khsara=Mix_LoadWAV("song/bankeji.wav");
	if(screen != NULL ) printf("helloo\n");
	while(boocle == 1 ){
			
			AfficherBackground(screen , back);
			AfficherXO( screen , t );
			AfficheNavigation(screen , t);
			AfficherRoto(screen,&z);
			Annimation(&back);
			if(Atilganger(t.tab) == 1 || egalite(t.tab) != 0)
			{	
				z.t=Atilganger(t.tab);
				repitition=1;		
				if(repitition==1)
				{
					Mix_PlayChannel( -1,rebh,0);
					repitition=0;
				}
				clearTable(&t);
			}
			else if(Atilganger(t.tab) == 2 || egalite(t.tab) != 0)
			{	
				z.t=Atilganger(t.tab);
				repitition=1;		
				if(repitition==1)
				{
					Mix_PlayChannel( -1,khsara,0);
					repitition=0;
				}
				clearTable(&t);
			}
			while( SDL_PollEvent (&event) ){
				
				switch(event.type){
					
					case SDL_QUIT:
						boocle = 0;
					break;
					case SDL_MOUSEBUTTONUP:
						for(int i=0; i<3;i++){
							for(int j=0;j<3;j++){
								if(event.motion.x > t.pos[i][j].x && event.motion.x < t.pos[i][j].x + t.pos[i][j].w
								&&event.motion.y > t.pos[i][j].y && event.motion.y < t.pos[i][j].y + t.pos[i][j].h ){
									
									if(t.tab[i][j] == 0){
										if(t.n==0){
											t.tab[i][j] = 1;//X
											t.n=1;
											
										}
									}
									
								}
							}
						}
						if(t.n==1){
							ia(&t);
							t.n=0;	
									
						}
						
					break;
					case SDL_KEYDOWN:
						
						if(event.key.keysym.sym == SDLK_RIGHT ){
								
							t.selection++;
							if( t.selection == 9 ){
								t.selection = 0;
							}
						}
						else if(event.key.keysym.sym == SDLK_LEFT ){
								
							t.selection--;
							if( t.selection <= -1 ){
								t.selection = 8;
							}
						}
						else if(event.key.keysym.sym == SDLK_DOWN ){
								
							t.selection += 3 ;
							if( t.selection == 9   ){
								t.selection -= 9 ;
							}
						}
						else if(event.key.keysym.sym == SDLK_UP ){
								
							t.selection -= 3 ;
							if( t.selection <= -1   ){
								t.selection += 9 ;
							}
						}
					else if(event.key.keysym.sym == SDLK_RETURN){
						
						if(t.selection >= 0 && t.selection <= 2 ){
							if( t.tab[0][t.selection] == 0 ){
								t.tab[0][t.selection] = t.n+1;
								if(t.n==1){
									t.n=0;
								}
								else t.n=1;
							}
							z.t=Atilganger(t.tab);
						}
						else if(t.selection >= 3 && t.selection <= 5){
							
							if( t.tab[1][t.selection -3 ] == 0 ){
								t.tab[1][t.selection - 3 ] = t.n+1;
								if(t.n==1){
									t.n=0;
								}
								else t.n=1;
							}
							z.t=Atilganger(t.tab);

						}
						else {
							if( t.tab[2][t.selection - 6 ] == 0 ){
								t.tab[2][t.selection - 6 ] = t.n+1;
								if(t.n==1){
									t.n=0;
								}
								else t.n=1;
							}
							z.t=Atilganger(t.tab);
						}
					}
											
											

					break;

				}				
				
			}
	
		SDL_Flip(screen);
		SDL_Delay(70);

	}
	//LibererTous(&back,&im);
	Mix_FreeMusic(son);
}
