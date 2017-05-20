#include <iostream>
#include <tuple>
#include <SDL/SDL.h>
#include "Animation.h"
#include <SDL/SDL_image.h>
#include <string>

using namespace std;

Animation::Animation()
{
	lamp_rect.x = 1000;
	lamp_rect.y = 200;
	lamp_rect.w = 250;
	lamp_rect.h = 300;

	temp.x = 1200;
	temp.y = 300;
	temp.w = 50;
	temp.h = 100;
	light[0] = make_tuple("lamp" , true, 0 , temp , lamp_rect);
}

Animation::~Animation()
{

}

void Animation :: Lamp(SDL_Renderer* render , int camerax , int cameray)
{
	for(int i=0;i<10;i++)
	{
		if(get<0>(light[i]) != "" && get<1>(light[i]) == true)
		{
			SDL_Rect hedef_texture;
				hedef_texture.x=(get<3>(light[i]).x + camerax);
				hedef_texture.y=(get<3>(light[i]).y + cameray);
				hedef_texture.w=(get<3>(light[i]).w);
				hedef_texture.h=(get<3>(light[i]).h);
			
				SDL_SetTextureBlendMode(map_animation[get<0>(light[i])] , SDL_BLENDMODE_ADD);
				SDL_RenderCopyEx(render , map_animation[get<0>(light[i])] , NULL , &hedef_texture , NULL , 0 , SDL_FLIP_NONE);
		}

	}
}

bool Animation :: load_anime(string dosya_adi , string animasyon_adi , SDL_Renderer* texture_render)
{
	SDL_Surface* load_surface = IMG_Load(dosya_adi.c_str());
	
	if(load_surface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Animation" , "Animation :: load_anime (load_surface yuklenemedi..!)" , NULL);
	}

	SDL_Texture* load_texture = SDL_CreateTextureFromSurface(texture_render , load_surface);	// yüzeyi renderleyerek texture oluþtur	
	SDL_FreeSurface(load_surface);
	if(load_texture != 0)
	{
		map_animation[animasyon_adi] = load_texture; // Tüm animasyonlarý saklayacaðýmýz yer
		
		return true;
	}
	return false;
}

void Animation :: load_animation(SDL_Renderer* render)
{
	load_anime("assets/torch.png","lamp", render);
}
