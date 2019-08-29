#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIDTH=800;
const int HEIGHT=600;
const int POSITION_X=100;
const int POSITION_Y=100;

typedef struct rectangleElement{
SDL_Rect *rect;
struct rectangleElement *next;
}rectangleElement;

rectangleElement *createRectangleElement(SDL_Rect *rec)
{
    rectangleElement *newElement;
    newElement=(rectangleElement*)malloc(sizeof(rectangleElement));
    newElement->rect=rec;
    newElement->next=NULL;
    return newElement;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

void insertBeginning(rectangleElement **rectangles,SDL_Rect *rect)
{
    rectangleElement *newElement;
    newElement=createRectangleElement(rect);
    newElement->next=*rectangles;
    *rectangles=newElement;
}

void DrawRectangles(SDL_Renderer *renderer,rectangleElement *rec)
{
    rectangleElement *pt;
    for(pt=rec;pt!=NULL;pt=pt->next)
    SDL_RenderFillRect(renderer,pt->rect);
}

int main(int argc, char* argv[])
{
    int ok=0;
    if (SDL_Init(SDL_INIT_EVERYTHING)<0){
       printf("%s\n",SDL_GetError());
       exit(-1);
    }
    rectangleElement *rectangles=NULL;
    SDL_Window *window;
    window=SDL_CreateWindow("MAAZAZ ZAKARIA - GLSID1",POSITION_X,POSITION_Y,WIDTH,HEIGHT,SDL_WINDOW_OPENGL);
    SDL_Rect rectangle,rectangle2,rectangle0;
    SDL_Rect *rect1, *rect2;
    rect1=(SDL_Rect*)malloc(sizeof(SDL_Rect));
    rect2=(SDL_Rect*)malloc(sizeof(SDL_Rect));
    rectangle.x=1; rectangle2.x=698;
    rectangle.y=2; rectangle2.y=579;
    rectangle.h=50; rectangle2.h=20;
    rectangle.w=100; rectangle2.w=100;

    rectangle0.x=1;
    rectangle0.y=2;
    rectangle0.h=20;
    rectangle0.w=100;

    if(window==NULL){ printf("%s",SDL_GetError()); exit(-1);}

    /// dessiner composants graphiques
    SDL_Event windowEvent;
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

     // Initialize support for loading PNG and JPEG images
     IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture * image_texture = initialize_texture_from_file("DEBUT.bmp", renderer);
    SDL_Texture * image_texture2 = initialize_texture_from_file("FIN.bmp", renderer);
    SDL_Texture * image_texture3 = initialize_texture_from_file("18.jpg", renderer);
    SDL_Texture * image_texture4 = initialize_texture_from_file("bomb.bmp", renderer);


    int image_width, image_height;

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);
    SDL_QueryTexture(image_texture2, NULL, NULL, &image_width, &image_height);
    SDL_QueryTexture(image_texture3, NULL, NULL, &image_width, &image_height);
    SDL_QueryTexture(image_texture4, NULL, NULL, &image_width, &image_height);

    while(1)
    {
        if(SDL_PollEvent(&windowEvent)){
            if(windowEvent.type==SDL_QUIT) break;
        if(SDL_KEYDOWN==windowEvent.type){
            switch(windowEvent.key.keysym.sym)
            {
                case SDLK_LEFT: rectangle.x=rectangle.x-8; break;
                case SDLK_RIGHT: rectangle.x=rectangle.x+8; break;
                case SDLK_UP: rectangle.y=rectangle.y-8; break;
                case SDLK_DOWN: rectangle.y=rectangle.y+8; break;
            }
        }


         SDL_Rect *rect;
         rect=(SDL_Rect*)malloc(sizeof(SDL_Rect));
        if(windowEvent.type==SDL_MOUSEBUTTONDOWN)
        {
            /// destine un rectangle
            printf("%d - %d\n",windowEvent.button.x,windowEvent.button.y);
            rect->x=windowEvent.button.x;
            rect->y=windowEvent.button.y;
            rect->h=5;
            rect->w=5;
            insertBeginning(&rectangles,rect);
        }
        }
              if( ( windowEvent.button.x >= 300 && windowEvent.button.x <= 380 ) && ( windowEvent.button.y >= 300 && windowEvent.button.y <= 380 ) )
               {
              rect1->x=300;
              rect1->y=300;
              rect1->h=80;
              rect1->w=80;
              insertBeginning(&rectangles,rect1);
              }

              if((  windowEvent.button.x >= 100 && windowEvent.button.x <= 200 ) && ( windowEvent.button.y >= 100 && windowEvent.button.y <= 200) )
              {
              rect2->x=100;
              rect2->y=100;
              rect2->h=100;
              rect2->w=100;
              insertBeginning(&rectangles,rect2);
              }

                 // Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &rectangle0);
        SDL_RenderCopy(renderer, image_texture2, NULL, &rectangle2);
        SDL_RenderCopy(renderer, image_texture3, NULL, &rectangle);
        SDL_RenderCopy(renderer, image_texture4, NULL, &rect1);
        SDL_RenderCopy(renderer, image_texture4, NULL, &rect2);

    SDL_SetRenderDrawColor(renderer,255,0,98,255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,0,198,255);
    SDL_RenderFillRect(renderer,&rectangle);
    SDL_RenderFillRect(renderer,&rectangle2);
    DrawRectangles(renderer,rectangles);
    SDL_RenderPresent(renderer);
    }

    //SDL_Delay(5000);
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
