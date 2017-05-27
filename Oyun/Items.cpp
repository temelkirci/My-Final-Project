#include <iostream>
#include "Items.h"
#include "SDL/SDL.h"
#include <string>
#include <tuple>

Items :: Items()
{
		Collectible_Size = 100;
		Uncollectible_Size = 100;
		Solid_Size = 100;

		Collectible_Items = new Item[Collectible_Size];
		Uncollectible_Items = new Item[Uncollectible_Size];
		Solid_Items = new Item[Solid_Size];

		inf = "";

	////////   Collectible_Items   ////////

		temp_rect.x = 800;
		temp_rect.y = 300;
		temp_rect.w = 50;
		temp_rect.h = 30;

		Collectible_Items[0].item_name = "handgun";
		Collectible_Items[0].item_blendmode = "blend";
		Collectible_Items[0].item_id = 0;
		Collectible_Items[0].number_item = 1;
		Collectible_Items[0].item_health = 100;
		Collectible_Items[0].item_active = true;
		Collectible_Items[0].item_rect = temp_rect;
		Collectible_Items[0].item_texture = NULL;

		temp_rect.x = 1000;
		temp_rect.y = 600;
		temp_rect.w = 50;
		temp_rect.h = 50;

		Collectible_Items[1].item_name = "rock_1";
		Collectible_Items[1].item_blendmode = "blend";
		Collectible_Items[1].item_id = 1;
		Collectible_Items[1].number_item = 1;
		Collectible_Items[1].item_health = 100;
		Collectible_Items[1].item_active = true;
		Collectible_Items[1].item_rect = temp_rect;
		Collectible_Items[1].item_texture = NULL;

		temp_rect.x = 100;
		temp_rect.y = 600;
		temp_rect.w = 30;
		temp_rect.h = 40;

		Collectible_Items[2].item_name = "energy_water";
		Collectible_Items[2].item_blendmode = "blend";
		Collectible_Items[2].item_id = 2;
		Collectible_Items[2].number_item = 1;
		Collectible_Items[2].item_health = 100;
		Collectible_Items[2].item_active = true;
		Collectible_Items[2].item_rect = temp_rect;
		Collectible_Items[2].item_texture = NULL;

		temp_rect.x = 1000;
		temp_rect.y = 200;
		temp_rect.w = 35;
		temp_rect.h = 45;

		Collectible_Items[3].item_name = "water";
		Collectible_Items[3].item_blendmode = "blend";
		Collectible_Items[3].item_id = 3;
		Collectible_Items[3].number_item = 1;
		Collectible_Items[3].item_health = 100;
		Collectible_Items[3].item_active = true;
		Collectible_Items[3].item_rect = temp_rect;
		Collectible_Items[3].item_texture = NULL;

		temp_rect.x = 1200;
		temp_rect.y = 300;
		temp_rect.w = 50;
		temp_rect.h = 50;

		Collectible_Items[4].item_name = "full_bag";
		Collectible_Items[4].item_blendmode = "blend";
		Collectible_Items[4].item_id = 4;
		Collectible_Items[4].number_item = 1;
		Collectible_Items[4].item_health = 100;
		Collectible_Items[4].item_active = true;
		Collectible_Items[4].item_rect = temp_rect;
		Collectible_Items[4].item_texture = NULL;

		temp_rect.x = 900;
		temp_rect.y = 300;
		temp_rect.w = 50;
		temp_rect.h = 50;

		Collectible_Items[5].item_name = "soup";
		Collectible_Items[5].item_blendmode = "blend";
		Collectible_Items[5].item_id = 5;
		Collectible_Items[5].number_item = 1;
		Collectible_Items[5].item_health = 100;
		Collectible_Items[5].item_active = true;
		Collectible_Items[5].item_rect = temp_rect;
		Collectible_Items[5].item_texture = NULL;

		temp_rect.x = 400;
		temp_rect.y = 700;
		temp_rect.w = 50;
		temp_rect.h = 50;

		Collectible_Items[6].item_name = "12_bag";
		Collectible_Items[6].item_blendmode = "blend";
		Collectible_Items[6].item_id = 6;
		Collectible_Items[6].number_item = 1;
		Collectible_Items[6].item_health = 100;
		Collectible_Items[6].item_active = true;
		Collectible_Items[6].item_rect = temp_rect;
		Collectible_Items[6].item_texture = NULL;

		temp_rect.x = 1000;
		temp_rect.y = 800;
		temp_rect.w = 70;
		temp_rect.h = 40;

		Collectible_Items[7].item_name = "rifle";
		Collectible_Items[7].item_blendmode = "blend";
		Collectible_Items[7].item_id = 7;
		Collectible_Items[7].number_item = 1;
		Collectible_Items[7].item_health = 100;
		Collectible_Items[7].item_active = true;
		Collectible_Items[7].item_rect = temp_rect;
		Collectible_Items[7].item_texture = NULL;

		temp_rect.x = 1000;
		temp_rect.y = 700;
		temp_rect.w = 70;
		temp_rect.h = 30;

		Collectible_Items[8].item_name = "shotgun";
		Collectible_Items[8].item_blendmode = "blend";
		Collectible_Items[8].item_id = 8;
		Collectible_Items[8].number_item = 1;
		Collectible_Items[8].item_health = 100;
		Collectible_Items[8].item_active = true;
		Collectible_Items[8].item_rect = temp_rect;
		Collectible_Items[8].item_texture = NULL;

		temp_rect.x = 800;
		temp_rect.y = 600;
		temp_rect.w = 50;
		temp_rect.h = 50;

		Collectible_Items[9].item_name = "health_bag";
		Collectible_Items[9].item_blendmode = "blend";
		Collectible_Items[9].item_id = 9;
		Collectible_Items[9].number_item = 1;
		Collectible_Items[9].item_health = 100;
		Collectible_Items[9].item_active = true;
		Collectible_Items[9].item_rect = temp_rect;
		Collectible_Items[9].item_texture = NULL;

		////////  UnCollectible_Items    ////////

		temp_rect.x = 900;
		temp_rect.y = 300;
		temp_rect.w = 150;
		temp_rect.h = 100;

		Uncollectible_Items[0].item_name = "krater1";
		Uncollectible_Items[0].item_blendmode = "blend";
		Uncollectible_Items[0].item_id = 0;
		Uncollectible_Items[0].number_item = 1;
		Uncollectible_Items[0].item_health = 100;
		Uncollectible_Items[0].item_active = true;
		Uncollectible_Items[0].item_rect = temp_rect;
		Uncollectible_Items[0].item_texture = NULL;

		
		Uncollectible_Items[99].item_name = "bullet_rifle";
		Uncollectible_Items[99].item_blendmode = "blend";
		Uncollectible_Items[99].item_id = 100;
		Uncollectible_Items[99].number_item = 1;
		Uncollectible_Items[99].item_health = 100;
		Uncollectible_Items[99].item_active = false;
		Uncollectible_Items[99].item_rect = temp_rect;
		Uncollectible_Items[99].item_texture = NULL;

		Uncollectible_Items[98].item_name = "bullet_handgun";
		Uncollectible_Items[98].item_blendmode = "blend";
		Uncollectible_Items[98].item_id = 99;
		Uncollectible_Items[98].number_item = 1;
		Uncollectible_Items[98].item_health = 100;
		Uncollectible_Items[98].item_active = false;
		Uncollectible_Items[98].item_rect = temp_rect;
		Uncollectible_Items[98].item_texture = NULL;

		Uncollectible_Items[97].item_name = "bullet_shotgun";
		Uncollectible_Items[97].item_blendmode = "blend";
		Uncollectible_Items[97].item_id = 98;
		Uncollectible_Items[97].number_item = 1;
		Uncollectible_Items[97].item_health = 100;
		Uncollectible_Items[97].item_active = false;
		Uncollectible_Items[97].item_rect = temp_rect;
		Uncollectible_Items[97].item_texture = NULL;

		////////   Solid_Items   ////////

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
	else if(item_name == "dag")
	{
		inf = "Volkanik bir dag . Sonmus olmali";
	}
	else if(item_name == "rock_1")
	{
		inf = "Ise yarar bir kaya parcasi";
	}
}
