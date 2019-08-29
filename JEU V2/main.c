#include "head.h"

void render()
{
  int i,j;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // couleur de l'ecran ( blanc)
  SDL_RenderClear(renderer); // appliquer la fonction SDL_SetRenderDrawColor à tous l'ecran
  for(i=0;i<30;i++)
  {
    for(j=0;j<30;j++)
    {
      switch(matrice[i][j].type_point)
      {
        case 0 :
          SDL_SetRenderDrawColor(renderer,0,0,255,255); // couleur des carres = noire
          SDL_RenderDrawRect(renderer, &rectangle[i][j]);
        break;

        case 1 :
          SDL_SetRenderDrawColor(renderer,0,0,0,255); // les obstacles = noire
          SDL_RenderFillRect(renderer, &rectangle[i][j]);
        break;

        case 2 :
          SDL_SetRenderDrawColor(renderer, 250, 150, 55, 255); // le chemin = orange
          SDL_RenderFillRect(renderer, &rectangle[i][j]);
        break;
      }
    }
  }

  if(Xpointdepart != -1 && Ypointdepart != -1)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // point depart
    SDL_RenderFillRect(renderer, &rectangle[Xpointdepart][Ypointdepart]);
  }

  if(Xpointarrive != -1 && Ypointarrive != -1)
  {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // point d'arrivee
    SDL_RenderFillRect(renderer, &rectangle[Xpointarrive][Ypointarrive]);
  }

  SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{

  SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO);


   if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)!=0);
   {
       SDL_Log("Initialisation SDL %s\n",SDL_GetError());
        exit -1;
   }

   Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

   Mix_Music *backgroundSound = Mix_LoadMUS("music.mp3");

  int x,y;
  window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450, 450, SDL_WINDOW_SHOWN); // la fenetre
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // renderer c'est le contenu de la fenetre

  for(x=0;x<30;x++)
  {
    for(y=0;y<30;y++)
    {
      matrice[x][y].type_point = 0; // type par default
      matrice[x][y].disponible = 0; // pas choisir pour le chemin
      matrice[x][y].xpoint = -1; // hors l'ecran
      matrice[x][y].ypoint = -1; // hors l'ecran
      matrice[x][y].distance = -1; // distance calculer par l'alg de dijkstra sqrt(x^2+y^2)

      rectangle[x][y].x = x * 15;
      rectangle[x][y].y = y * 15;
      rectangle[x][y].w = 11;
      rectangle[x][y].h = 11;
    }
  }
  changeTypePoint = 0;
  Xpointdepart = -1;
  Ypointdepart = -1;
  Xpointarrive = -1;
  Ypointarrive = -1;
  LastPointX= -1;
  LastPointY = -1;
  disponible= 0;

  SDL_WaitEvent(&event);

  Mix_PlayMusic(backgroundSound,-1);
  while(event.type != SDL_QUIT)
  {
      // utilisation de la souris pour selectionner les carres
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      if(event.button.button == SDL_BUTTON_LEFT) // button droite de la souris
      {
        if(event.button.x <= 443) // ne depasse pas la capacite de la matrice
        {
          int Xclique = event.button.x / 15; // x de carre
          int Yclique= event.button.y / 15; // y de carre

          if(changeTypePoint == 0) // si le carre deja selectionner
          {
                  // si un carre deja selectionner soit par point de depart soit par point d'arrive (selectionner le point d'obstacle)
            if((Xclique != Xpointdepart || Yclique!= Ypointdepart) && (Xclique != Xpointarrive || Yclique!= Ypointarrive))
            {
              matrice[Xclique][Yclique].type_point = 1; //obstacle -- 0 pour rien -- 1 pour le noir -- 2 pour le chemin

              render();
            }
          }
          else if(changeTypePoint == 1) // point depart
          {
            // s'il ne s'agit pas d'un obstacle ou bien point d'arrive (selectionner le point de depart)
            if(matrice[Xclique][Yclique].type_point != 1 && (Xclique != Xpointarrive || Yclique!= Ypointarrive))
            {
              Xpointdepart = Xclique;
              Ypointdepart = Yclique;

              render();
            }
          }
          else if(changeTypePoint == 2) // point d'arrivee
          {
            // s'il ne s'agit pas d'un obstacle ou bien point de depart (selectionner le point d'arrive)
            if(matrice[Xclique][Yclique].type_point != 1 && (Xclique != Xpointdepart || Yclique!= Ypointdepart))
            {
              Xpointarrive = Xclique;
              Ypointarrive = Yclique;
              render();
            }
          }
        }
      }
    else if(event.type == SDL_MOUSEMOTION && event.button.x <= 443) // pour ne depasse pas la taille d'ecran
    {
      int Xclique = event.button.x / 15;
      int Yclique= event.button.y / 15;
    }
    }
   // si vous avez utilise le clavier
    else if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym==SDLK_o) // le button 'o'
        {
          changeTypePoint = 0;
          render();
        }
        else if(event.key.keysym.sym==SDLK_PAGEUP) // le button 'PAGE UP'
        {
          changeTypePoint = 1;
          render();
        }
        else if(event.key.keysym.sym==SDLK_PAGEDOWN) // le button 'PAGE DOWN'
        {
          changeTypePoint = 2;
          render();
        }
        else if(event.key.keysym.sym==SDLK_SPACE) // le button 'ESPACE'
        {
          dj(); // appel de fonction de dijkstra
          system("pause");
          break; // quitter
        }
    }
    render();
    SDL_WaitEvent(&event); // attendre jusqu'a l'utilisateur cree un evenement ( souris /clavier/quitter /etc...)
  }
 /// liberer la memoire
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
