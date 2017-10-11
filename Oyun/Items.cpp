#include <iostream>
#include "Items.h"
#include "SDL/SDL.h"
#include <string>
#include <tuple>

Items :: Items()
{
		Collectible_Size = 10;
		Uncollectible_Size = 10;
		Solid_Size = 10;

		Collectible_Items = new Item[Collectible_Size];
		Uncollectible_Items = new Item[Uncollectible_Size];
		Solid_Items = new Item[Solid_Size];

		temp_rect.x = 900;
		temp_rect.y = 300;
		temp_rect.w = 100;
		temp_rect.h = 100;

		Solid_Items[0].item_name = "huge_box";
		Solid_Items[0].item_blendmode = "blend";
		Solid_Items[0].item_id = 0;
		Solid_Items[0].number_item = 1;
		Solid_Items[0].item_health = 100;
		Solid_Items[0].item_active = true;
		Solid_Items[0].item_rect = temp_rect;
		Solid_Items[0].item_texture = NULL;

		temp_rect.x = 650;
		temp_rect.y = 350;
		temp_rect.w = 50;
		temp_rect.h = 30;

		Collectible_Items[0].item_name = "rifle";
		Collectible_Items[0].item_blendmode = "blend";
		Collectible_Items[0].item_id = 0;
		Collectible_Items[0].number_item = 1;
		Collectible_Items[0].item_health = 100;
		Collectible_Items[0].item_active = false;
		Collectible_Items[0].item_rect = temp_rect;
		Collectible_Items[0].item_texture = NULL;

		temp_rect.x = 750;
		temp_rect.y = 350;
		temp_rect.w = 50;
		temp_rect.h = 30;

		Collectible_Items[1].item_name = "soup";
		Collectible_Items[1].item_blendmode = "blend";
		Collectible_Items[1].item_id = 1;
		Collectible_Items[1].number_item = 1;
		Collectible_Items[1].item_health = 100;
		Collectible_Items[1].item_active = false;
		Collectible_Items[1].item_rect = temp_rect;
		Collectible_Items[1].item_texture = NULL;

		Uncollectible_Items[9].item_name = "bullet_rifle";
		Uncollectible_Items[9].item_blendmode = "blend";
		Uncollectible_Items[9].item_id = 9;
		Uncollectible_Items[9].number_item = 1;
		Uncollectible_Items[9].item_health = 100;
		Uncollectible_Items[9].item_active = false;
		Uncollectible_Items[9].item_rect = temp_rect;
		Uncollectible_Items[9].item_texture = NULL;

		Uncollectible_Items[8].item_name = "bullet_handgun";
		Uncollectible_Items[8].item_blendmode = "blend";
		Uncollectible_Items[8].item_id = 8;
		Uncollectible_Items[8].number_item = 1;
		Uncollectible_Items[8].item_health = 100;
		Uncollectible_Items[8].item_active = false;
		Uncollectible_Items[8].item_rect = temp_rect;
		Uncollectible_Items[8].item_texture = NULL;

		Uncollectible_Items[7].item_name = "bullet_shotgun";
		Uncollectible_Items[7].item_blendmode = "blend";
		Uncollectible_Items[7].item_id = 7;
		Uncollectible_Items[7].number_item = 1;
		Uncollectible_Items[7].item_health = 100;
		Uncollectible_Items[7].item_active = false;
		Uncollectible_Items[7].item_rect = temp_rect;
		Uncollectible_Items[7].item_texture = NULL;

		inf = "";

		
}

Items :: ~Items()
{
	
	for(int i=0 ; i<Collectible_Size ; i++)
		Collectible_Items[i];
	for(int i=0 ; i<Uncollectible_Size ; i++)
		Collectible_Items[i];
	for(int i=0 ; i<Solid_Size ; i++)
		Collectible_Items[i];
		
}

void Items :: item_information(SDL_Renderer* item_render , string item_name)
{
	if(item_name == "health_bag")
	{
		inf = "Bu saglik cantasi karakterinizin sagligini 20 arttirir";
	}
	else if(item_name == "handgun")
	{
		inf = "Bu silah zayif gorunuyor ama bununla kendimi bir sure koruyabilirim";
	}
	else if(item_name == "shotgun")
	{
		inf = "Saldiri gucu yuksek bir silah . Yaratiklar benden korkacak";
	}
	else if(item_name == "rifle")
	{
		inf = "Bu silah ile hizli ates edebilirim";
	}
	else if(item_name == "kuru_agac")
	{
		inf = "Bu agac kurumus . Hicbir isime yaramaz";
	}
	else if(item_name == "bread")
	{
		inf = "Bununla acligimi bir süre azaltabilirim";
	}
	else if(item_name == "rock_1")
	{
		inf = "Ise yarar bir kaya parcasi";
	}
	else if(item_name == "water")
	{
		inf = "Su temiz gorunuyor";
	}
	else if(item_name == "soup")
	{
		inf = "Soguk corba.Bugun sansli gunumdeyim";
	}
}
