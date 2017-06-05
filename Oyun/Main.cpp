#include <SDL/SDL.h> 
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
#include "Game.h"

#define SCREEN_WÝDTH  1366
#define SCREEN_HEIGHT  768

Game* oyun = NULL; // Game nesnemiz

using namespace std;

int main(int argc, char** argv) 
{
	Game* oyun = new Game(); // Game sýnýfýndan oyun nesnesi oluþturuyoruz

	oyun->init("TEMEL KIRCI", 10 , 30 , SCREEN_WÝDTH , SCREEN_HEIGHT , SDL_WINDOW_RESIZABLE); // temel bileþenleri yükle
	
	// OYUN BAÞLAT
		while(1) // Oyun çalýþtýðý sürece devam et
		{
			// MENÜYÜ GÖSTER
			if(oyun->oyun_baslat == false)
			{
				oyun->menu_goster(oyun->renderer , 0 , 0 , 1366 , 768); // Menüyü sürekli çiz
				oyun->oyun_baslat = oyun->klavye_mouse(false); // Menüdeki keyboard ve mouse olaylarýný dinle
				
				if(oyun->oyun_baslat == true)
				{
					oyun->health = 70;
					oyun->load_barbaros(oyun->renderer); // barbarosu yükle(ana karakter)
					oyun->load_Resim(oyun->renderer);    // Sol üstteki can barý , mermi durumu ve karakter bilgilerini yükle
					oyun->load_textures(oyun->renderer); // Toplanabilir nesneleri yüklr
				}
				
			}
			// OYUNA BAÞLA
			else
			{
				oyun->klavye(oyun->renderer , oyun->camera.x , oyun->camera.y); // Klavye ve mouse iþlemleri						
				oyun->render(oyun->renderer , oyun->oyun_baslat); // Çizim olaylarý		
			}
		}

	SDL_Quit(); // Tüm SDL sistemlerini kapat
	delete oyun; 
	system("pause");
    return 0;
}
