#include <SDL/SDL.h> 
#include <iostream>
#include <string>
#include "Game.h"
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>

#include <GL/freeglut.h>


#define SCREEN_W�DTH  1366
#define SCREEN_HEIGHT  768

Game* oyun = NULL; // Game nesnemiz

using namespace std;

int main(int argc, char** argv) 
{
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,true);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	Game* oyun = new Game(); // Game s�n�f�ndan oyun nesnesi olu�turuyoruz

	oyun->init("TEMEL KIRCI", 10 , 30 , SCREEN_W�DTH , SCREEN_HEIGHT , SDL_WINDOW_RESIZABLE); // temel bile�enleri y�kle
	
	// OYUN BA�LAT
		while(1) // Oyun �al��t��� s�rece devam et
		{
			// MEN�Y� G�STER
			if(oyun->oyun_baslat == false)
			{
				oyun->menu_goster(oyun->renderer , 0 , 0 , 1366 , 768); // Men�y� s�rekli �iz
				oyun->oyun_baslat = oyun->klavye_mouse(false); // Men�deki keyboard ve mouse olaylar�n� dinle
				
				if(oyun->oyun_baslat == true)
				{
					oyun->health = 70;
					oyun->load_barbaros(oyun->renderer); // barbarosu y�kle(ana karakter)
					oyun->load_Resim(oyun->renderer);    // Sol �stteki can bar� , mermi durumu ve karakter bilgilerini y�kle
					oyun->load_textures(oyun->renderer); // Toplanabilir nesneleri y�klr
				}
				
			}
			// OYUNA BA�LA
			else
			{
				oyun->klavye(oyun->renderer , oyun->camera.x , oyun->camera.y); // Klavye ve mouse i�lemleri						
				oyun->render(oyun->renderer , oyun->oyun_baslat); // �izim olaylar�		
			}
		}
		
	SDL_Quit(); // T�m SDL sistemlerini kapat
	delete oyun; 
	system("pause");
    return 0;
}
