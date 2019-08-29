#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


typedef struct point{ int type_point,disponible,xpoint,ypoint,distance;}Point;

SDL_Window *window; // la fenetre
SDL_Renderer *renderer;
SDL_Event event; // les evenement
SDL_Rect rectangle[30][30];
Point matrice[30][30];
// point de depart
int Xpointdepart;
int Ypointdepart;
// point d'arrivee
int Xpointarrive;
int Ypointarrive;

int is_selectionner;

//dernier point selectionner par la souris
int LastPointX;
int LastPointY;

// pour savoir le type de carre et sa disponibilte
int changeTypePoint,disponible;

// algorithme de dijkstra
void dj()
{
  if(Xpointdepart != -1 && Ypointdepart != -1 && Xpointarrive != -1 && Ypointarrive != -1)
  {
    matrice[Xpointarrive][Ypointarrive].distance = 0;

    int actualPointX = Xpointarrive;
    int actualPointY = Ypointarrive;

    while((actualPointX != Xpointdepart || actualPointY != Ypointdepart) && (actualPointX != -1 || actualPointY != -1))
    {
      matrice[actualPointX][actualPointY].disponible = 1;

      if(actualPointX + 1 >= 0 && actualPointX + 1 < 30)
      {
        if(matrice[actualPointX + 1][actualPointY].type_point != 1 && !matrice[actualPointX + 1][actualPointY].disponible)
        {
          if(matrice[actualPointX][actualPointY].distance + 10 < matrice[actualPointX + 1][actualPointY].distance || matrice[actualPointX + 1][actualPointY].distance == -1)
          {
            matrice[actualPointX + 1][actualPointY].xpoint = actualPointX;
            matrice[actualPointX + 1][actualPointY].ypoint = actualPointY;

            matrice[actualPointX + 1][actualPointY].distance = matrice[actualPointX][actualPointY].distance + 10;
          }
        }
      }

      if(actualPointY + 1 >= 0 && actualPointY + 1 < 30)
      {
        if(matrice[actualPointX][actualPointY + 1].type_point != 1 && !matrice[actualPointX][actualPointY + 1].disponible)
        {
          if(matrice[actualPointX][actualPointY].distance + 10 < matrice[actualPointX][actualPointY + 1].distance || matrice[actualPointX][actualPointY + 1].distance == -1)
          {
            matrice[actualPointX][actualPointY + 1].xpoint = actualPointX;
            matrice[actualPointX][actualPointY + 1].ypoint = actualPointY;

            matrice[actualPointX][actualPointY + 1].distance = matrice[actualPointX][actualPointY].distance + 10;
          }
        }
      }

      if(actualPointX - 1 >= 0 && actualPointX - 1 < 30)
      {
        if(matrice[actualPointX - 1][actualPointY].type_point != 1 && !matrice[actualPointX - 1][actualPointY].disponible)
        {
          if(matrice[actualPointX][actualPointY].distance + 10 < matrice[actualPointX - 1][actualPointY].distance || matrice[actualPointX - 1][actualPointY].distance == -1)
          {
            matrice[actualPointX - 1][actualPointY].xpoint = actualPointX;
            matrice[actualPointX - 1][actualPointY].ypoint = actualPointY;

            matrice[actualPointX - 1][actualPointY].distance = matrice[actualPointX][actualPointY].distance + 10;
          }
        }
      }

      if(actualPointY - 1 >= 0 && actualPointY - 1 < 30)
      {
        if(matrice[actualPointX][actualPointY - 1].type_point != 1 && !matrice[actualPointX][actualPointY - 1].disponible)
        {
          if(matrice[actualPointX][actualPointY].distance + 10 < matrice[actualPointX][actualPointY - 1].distance || matrice[actualPointX][actualPointY - 1].distance == -1)
          {
            matrice[actualPointX][actualPointY - 1].xpoint = actualPointX;
            matrice[actualPointX][actualPointY - 1].ypoint = actualPointY;

            matrice[actualPointX][actualPointY - 1].distance = matrice[actualPointX][actualPointY].distance + 10;
          }
        }
      }


      if(actualPointX + 1 >= 0 && actualPointX + 1 <30 && actualPointY + 1 >= 0 && actualPointY + 1 < 30)
      {
        if(matrice[actualPointX + 1][actualPointY + 1].type_point != 1 && !matrice[actualPointX + 1][actualPointY + 1].disponible && matrice[actualPointX + 1][actualPointY].type_point != 1 && matrice[actualPointX][actualPointY + 1].type_point != 1)
        {
          if(matrice[actualPointX][actualPointY].distance + 14 < matrice[actualPointX + 1][actualPointY + 1].distance || matrice[actualPointX + 1][actualPointY + 1].distance == -1)
          {
            matrice[actualPointX + 1][actualPointY + 1].xpoint = actualPointX;
            matrice[actualPointX + 1][actualPointY + 1].ypoint = actualPointY;

            matrice[actualPointX + 1][actualPointY + 1].distance = matrice[actualPointX][actualPointY].distance + 14;
          }
        }
      }

      if(actualPointX - 1 >= 0 && actualPointX - 1 < 30 && actualPointY + 1 >= 0 && actualPointY + 1 < 30)
      {
        if(matrice[actualPointX - 1][actualPointY + 1].type_point != 1 && !matrice[actualPointX - 1][actualPointY + 1].disponible && matrice[actualPointX - 1][actualPointY].type_point != 1 && matrice[actualPointX][actualPointY + 1].type_point != 1)
        {
          if(matrice[actualPointX][actualPointY].distance + 14 < matrice[actualPointX - 1][actualPointY + 1].distance || matrice[actualPointX - 1][actualPointY + 1].distance == -1)
          {
            matrice[actualPointX - 1][actualPointY + 1].xpoint = actualPointX;
            matrice[actualPointX - 1][actualPointY + 1].ypoint = actualPointY;

            matrice[actualPointX - 1][actualPointY + 1].distance = matrice[actualPointX][actualPointY].distance + 14;
          }
        }
      }

      if(actualPointX + 1 >= 0 && actualPointX + 1 < 30 && actualPointY - 1 >= 0 && actualPointY - 1 < 30)
      {
        if(matrice[actualPointX + 1][actualPointY - 1].type_point != 1 && !matrice[actualPointX + 1][actualPointY - 1].disponible && matrice[actualPointX + 1][actualPointY].type_point != 1 && matrice[actualPointX][actualPointY - 1].type_point != 1)
        {
          if(matrice[actualPointX][actualPointY].distance + 14 < matrice[actualPointX + 1][actualPointY - 1].distance || matrice[actualPointX + 1][actualPointY - 1].distance == -1)
          {
            matrice[actualPointX + 1][actualPointY - 1].xpoint = actualPointX;
            matrice[actualPointX + 1][actualPointY - 1].ypoint = actualPointY;

            matrice[actualPointX + 1][actualPointY - 1].distance = matrice[actualPointX][actualPointY].distance + 14;
          }
        }
      }

      if(actualPointX - 1 >= 0 && actualPointX - 1 < 30 && actualPointY - 1 >= 0 && actualPointY - 1 < 30)
      {
        if(matrice[actualPointX - 1][actualPointY - 1].type_point != 1 && !matrice[actualPointX - 1][actualPointY - 1].disponible && matrice[actualPointX - 1][actualPointY].type_point != 1 && matrice[actualPointX][actualPointY - 1].type_point != 1)
        {
          if(matrice[actualPointX][actualPointY].distance + 14 < matrice[actualPointX - 1][actualPointY - 1].distance || matrice[actualPointX - 1][actualPointY - 1].distance == -1)
          {
            matrice[actualPointX - 1][actualPointY - 1].xpoint = actualPointX;
            matrice[actualPointX - 1][actualPointY - 1].ypoint = actualPointY;

            matrice[actualPointX - 1][actualPointY - 1].distance = matrice[actualPointX][actualPointY].distance + 14;
          }
        }
      }

      actualPointX = -1;
      actualPointY = -1;

      int x,y;
      for(x=0;x<30;x++)
      {
        for(y=0;y<30;y++)
        {
          if(matrice[x][y].distance != -1 && !matrice[x][y].disponible && matrice[x][y].type_point != 1)
          {
            if(actualPointX == -1 || actualPointY == -1)
            {
              actualPointX = x;
              actualPointY = y;
            }
            else if(matrice[x][y].distance < matrice[actualPointX][actualPointY].distance)
            {
              actualPointX = x;
              actualPointY = y;
            }
          }
        }
      }
    }

    if(actualPointX == Xpointdepart && actualPointY == Ypointdepart)
    {
      int nextPointX;
      int nextPointY;

      while(actualPointX != Xpointarrive || actualPointY != Ypointarrive)
      {
        matrice[actualPointX][actualPointY].type_point = 2;

        nextPointX = matrice[actualPointX][actualPointY].xpoint;
        nextPointY = matrice[actualPointX][actualPointY].ypoint;

        actualPointX = nextPointX;
        actualPointY = nextPointY;

        SDL_Delay(80);

        render();
      }
    }
    else
    {
     printf("il n'existe pas un chemin entre les deux points\n");
      exit -1;
    }

    disponible= 1;
  }
  else
  {
    printf("Vous n'avez pas choisi les deux points\n");
    exit -1;
  }
}
