#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

void SDL_ExitWithError(char *message)
{
    SDL_Log("ERREUR : %s > %s\n",message,SDL_GetError());
    SDL_Quit();
    exit -1;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

int main(int argc, char **argv)
{
   SDL_Window *window=NULL;
   SDL_Renderer *renderer=NULL;
   SDL_Rect rectangle;
   SDL_Surface *image=NULL;
   SDL_Texture *texture=NULL;
   int ok=0,k=1;

   if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)!=0);
   {
       SDL_Log("Initialisation SDL %s\n",SDL_GetError());
        exit -1;
   }

   Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

   Mix_Music *backgroundSound = Mix_LoadMUS("music.flac");

   /// creation fenetre :
   window =SDL_CreateWindow("GAME",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_OPENGL);
   if(window==NULL)
       SDL_ExitWithError("Creation de fenetre echoue");

    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

      if(renderer == NULL)
        SDL_ExitWithError("Creation de rendu echoue");

        rectangle.x=40;
        rectangle.y=20;
        rectangle.h=43;
        rectangle.w=50;

      if(SDL_RenderFillRect(renderer,&rectangle)!=0)
        SDL_ExitWithError("impossible de dessiner le rectangle");

        image=SDL_LoadBMP("Star.bmp");

        texture=SDL_CreateTextureFromSurface(renderer,image);

        SDL_Rect rectangle2;
        SDL_QueryTexture(texture,NULL,NULL,&rectangle2.w,&rectangle2.h);
        rectangle2.x=(800-rectangle2.w)/2;
        rectangle2.y=(600-rectangle2.h)/2;

        SDL_RenderCopy(renderer,texture,NULL,&rectangle2);

        SDL_RenderPresent(renderer);

        SDL_Rect rect1,rect2,rect3;
        SDL_Rect rectangle3,rectangle4;
        rectangle3.x=1; rectangle4.x=698;
        rectangle3.y=2; rectangle4.y=579;
        rectangle3.h=20; rectangle4.h=20;
        rectangle3.w=100; rectangle4.w=100;

        // Initialize support for loading PNG and JPEG images
        IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

        SDL_Texture * image_texture = initialize_texture_from_file("DEBUT.bmp", renderer);
        SDL_Texture * image_texture2 = initialize_texture_from_file("FIN.bmp", renderer);
        SDL_Texture * image_texture3 = initialize_texture_from_file("bird.png", renderer);
        SDL_Texture * image_texture4 = initialize_texture_from_file("bomb.png", renderer);

        int flags=IMG_INIT_JPG|IMG_INIT_PNG;
        int initted=IMG_Init(flags);
        if((initted&flags) != flags) {
         printf("IMG_Init: Failed to init required jpg and png support!\n");
         printf("IMG_Init: %s\n", IMG_GetError());
         // handle error
         }

        int image_width, image_height;

        // Get texture width/height
        SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);
        SDL_QueryTexture(image_texture2, NULL, NULL, &image_width, &image_height);
        SDL_QueryTexture(image_texture3, NULL, NULL, &image_width, &image_height);
        SDL_QueryTexture(image_texture4, NULL, NULL, &image_width, &image_height);

        Mix_PlayMusic(backgroundSound,-1);
        SDL_bool launch=SDL_TRUE;
        while(launch)
        {

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT) launch=SDL_FALSE;
        if(SDL_KEYDOWN==event.type){
            switch(event.key.keysym.sym)
            {
                case SDLK_LEFT: rectangle.x=rectangle.x-8; break;
                case SDLK_RIGHT: rectangle.x=rectangle.x+8; break;
                case SDLK_UP: rectangle.y=rectangle.y-8; break;
                case SDLK_DOWN: rectangle.y=rectangle.y+8; break;
            }
        }
        }
          x:

         if(ok==1)
        {
            printf("you lose -> %d\n",k);
            k++;
             rectangle.x=40;
             rectangle.y=20;
        }
        ok=0;


         if( ( rectangle.x>=400 && rectangle.x<=480 ) && ( rectangle.y>=400 && rectangle.y<=480) )
           {
              rect1.x=400;
              rect1.y=400;
              rect1.h=80;
              rect1.w=80;
              ok=1;
              goto x;
             }

              if((  rectangle.x >= 200 && rectangle.x <= 300 ) && ( rectangle.y>= 200 && rectangle.y<= 300) )
              {
              rect2.x=200;
              rect2.y=200;
              rect2.h=100;
              rect2.w=100;
              ok=1;
              goto x;
              }

               if((  rectangle.x >= 698 && rectangle.x <= 698+100 ) && ( rectangle.y>= 579 && rectangle.y<= 579+20) )
              {
              rect3.x=100;
              rect3.y=100;
              rect3.h=100;
              rect3.w=100;
              printf("you win !\n");
              SDL_WaitEvent(&event);
              }


        SDL_RenderCopy(renderer, image_texture, NULL, &rectangle3);
        SDL_RenderCopy(renderer, image_texture2, NULL, &rectangle4);
        SDL_RenderCopy(renderer, image_texture3, NULL, &rectangle);
        SDL_RenderCopy(renderer, image_texture4, NULL, &rect1);
        SDL_RenderCopy(renderer, image_texture4, NULL, &rect2);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        }
        Mix_CloseAudio();
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}
