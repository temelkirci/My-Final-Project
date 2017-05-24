#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include "Player.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

Player :: Player()
{
	oyun_baslat = false;
	speed = 1;
	arti_x_speed = speed;
	eksi_y_speed = speed;

	arti_y_speed = speed;
	eksi_x_speed = speed;

	thirtsy = 80;
	health = 70;
	hunger = 90;
	
	hunger_time = 0;
	thirsty_time = 0;

	handgun_mermi = 30;
	rifle_mermi = 50;
	shotgun_mermi = 20;
	
	angle = 0;
	player_time = 0;
	
	player_barbaros.x = 625;
	player_barbaros.y = 300;
	player_barbaros.w = 100;
	player_barbaros.h = 100;

	information.x = 0;
	information.y = 250;
	information.w = 200;
	information.h = 300;

	playerColor.r = 0;
	playerColor.g = 0;
	playerColor.b = 0;
	playerColor.a = 150;

	playerPoint.x = 50;
	playerPoint.y = 50;

	active_bullet = false;
	barbaros_durum = "move"; // move olarak baþlayacak
	barbaros_guns = "knife"; // barbaros elinde knife ile baþlayacak
}

Player :: ~Player()
{
	SDL_FreeSurface(surface_barbaros);
	SDL_DestroyTexture(texture_barbaros);

	surface_barbaros = NULL ;
	texture_barbaros = NULL ;
}

bool Player :: barbaros_yukle_weapon(string dosya_yolu , SDL_Renderer* rend , char* barbaros_parca)
{
	surface_barbaros = IMG_Load(dosya_yolu.c_str());
	if(surface_barbaros == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "Weapon yuklenemedi..!" , NULL);
		exit(0);
	}

	texture_barbaros = SDL_CreateTextureFromSurface(rend , surface_barbaros);
	SDL_FreeSurface(surface_barbaros);

	if(texture_barbaros != 0)
	{
		barbaros_weapon[barbaros_parca] = texture_barbaros; 
		return true;
	}
	return false;
}

void Player :: player_information(SDL_Renderer* render_barbaros)
{
	SDL_Surface* daySurface;
	SDL_Texture* dayTexture;

	SDL_Surface* hourSurface;
	SDL_Texture* hourTexture;

		SDL_Rect day_yazi;
			day_yazi.x = 1200;
			day_yazi.y = 0;
			day_yazi.h = 30;

			// DAY
			string day_text = to_string(day);
			string gün = "Day : " + day_text;
			day_yazi.w = 10*(gün.length());
			daySurface = TTF_RenderText_Blended( timer_font , gün.c_str() , playerColor );
			dayTexture = SDL_CreateTextureFromSurface( render_barbaros, daySurface );

			SDL_RenderCopyEx(render_barbaros , dayTexture , NULL , &day_yazi , 0 , 0 , SDL_FLIP_NONE);

			// TIME
		SDL_Rect time_yazi;
			time_yazi.x = 1200;
			time_yazi.y = 40;
			time_yazi.h = 30;

			string saat_text = to_string(saat);
			string saat_string = "Hour : ";
			string saat = "Hour : " + saat_text + " . 00";
			time_yazi.w = 120;
			hourSurface = TTF_RenderText_Blended( timer_font , saat.c_str() , playerColor );
			hourTexture = SDL_CreateTextureFromSurface( render_barbaros, hourSurface );

			SDL_RenderCopyEx(render_barbaros , hourTexture , NULL , &time_yazi , 0 , 0 , SDL_FLIP_NONE);			
			

	SDL_FreeSurface(daySurface);
	SDL_DestroyTexture(dayTexture);

	SDL_FreeSurface(hourSurface);
	SDL_DestroyTexture(hourTexture);
	
}

void Player :: barbaros_çiz(SDL_Renderer* render_barbaros , string barbaros_gun , int *x , int *y , int xcamera , int ycamera , string barbaros_stat , Uint32 süre)
{
	
	player_barbaros.x=(*x)+xcamera;
	player_barbaros.y=(*y)+ycamera;
	player_barbaros.w=100;
	player_barbaros.h=100;
	
	if(SDL_HasIntersection(&player_barbaros , &meteor_rect))
	{
		health = health - 20;
		meteor_x = -100;
		meteor_y = rand() % 500;
	}
	// Y EKSENÝ ÝÇÝN SINIR BELÝRLEME
	if(player_barbaros.y <= 0)
	{
		player_barbaros.y=0;
		
		eksi_x_speed = speed;
		arti_x_speed = speed;
		eksi_y_speed = speed;
		arti_y_speed = 0;
	}

	if(player_barbaros.x <= 0)
	{
		player_barbaros.x=0;
		
		eksi_x_speed = 0;
		arti_x_speed = speed;
		eksi_y_speed = speed;
		arti_y_speed = speed;
		
	}

	if(player_barbaros.x <= 0 && player_barbaros.y <= 0)
	{
		player_barbaros.x = 0;
		player_barbaros.y = 0;

		eksi_x_speed = 0;
		arti_x_speed = speed;
		eksi_y_speed = speed;
		arti_y_speed = 0;
		
	}

	if(player_barbaros.y >= 1400)
	{	
		eksi_x_speed = speed;
		arti_x_speed = speed;
		eksi_y_speed = 0;
		arti_y_speed = speed;
	}
	
	if(player_barbaros.x >= 5900)
	{
		eksi_x_speed = speed;
		arti_x_speed = 0;
		eksi_y_speed = speed;
		arti_y_speed = speed;
	}

	if(((player_barbaros.x > 0) && (player_barbaros.x < 5900)) && ((player_barbaros.y > 0) && (player_barbaros.y < 1400)))
	{		
		eksi_x_speed = speed;
		arti_x_speed = speed;
		eksi_y_speed = speed;
		arti_y_speed = speed;
	}

	if((barbaros_stat == "move") && (barbaros_gun == "flashlight"))
	{
		if(player_time == 0 && barbaros_durum == "move")
		{
			player_time = 300 + süre;
		}
		
		if(current_time <= player_time && barbaros_durum == "move") // 50 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["move_flashlight_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 300)) && barbaros_durum == "move") 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["move_flashlight_1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 300) && (current_time <= (player_time + 600)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["move_flashlight_2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 600) && (current_time <= (player_time + 900)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["move_flashlight_3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 900) && (current_time <= (player_time + 1200)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["move_flashlight_4"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else
		{
			player_time = 0;
			barbaros_durum ="move";
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["move_flashlight_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}	
	}
	if((barbaros_stat == "attack") && (barbaros_gun == "knife"))
	{		
		
		if(player_time == 0 && barbaros_durum == "attack")
		{
			player_time = 50 + süre;
		}
		
		if(current_time <= player_time && barbaros_durum == "attack") // 50 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["knife1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 50)) && barbaros_durum == "attack") 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["knife2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 50) && (current_time <= (player_time + 100)) && barbaros_durum == "attack")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["knife3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 100) && (current_time <= (player_time + 150)) && barbaros_durum == "attack")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["knife4"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 150) && (current_time <= (player_time + 200)) && barbaros_durum == "attack")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["knife5"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else
		{
			player_time = 0;
			barbaros_durum ="move";
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["knife1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}	
	}

	if((barbaros_stat == "move") && (barbaros_gun == "knife"))
	{		
		
		if(player_time == 0 )
		{
			player_time = 50 + süre;
		}
		
		if(current_time <= player_time && barbaros_durum == "move") // 100 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 50)) && barbaros_durum == "move") 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 50) && (current_time <= (player_time + 100)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 100) && (current_time <= (player_time + 150)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 150) && (current_time <= (player_time + 200)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_4"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 200) && (current_time <= (player_time + 250)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_5"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 250) && (current_time <= (player_time + 300)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_6"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 300) && (current_time <= (player_time + 350)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_7"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 350) && (current_time <= (player_time + 400)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_8"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 400) && (current_time <= (player_time + 450)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_9"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 450) && (current_time <= (player_time + 500)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_10"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 500) && (current_time <= (player_time + 550)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_11"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 550) && (current_time <= (player_time + 600)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_12"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 600) && (current_time <= (player_time + 650)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_13"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 650) && (current_time <= (player_time + 700)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_14"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 700) && (current_time <= (player_time + 750)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_15"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 750) && (current_time <= (player_time + 800)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_16"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 800) && (current_time <= (player_time + 850)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_17"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 850) && (current_time <= (player_time + 900)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_18"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 900) && (current_time <= (player_time + 950)) && barbaros_durum == "move")
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_19"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else
		{
			player_time = 0;
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_knife_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
			if(barbaros_durum == "attack")
				barbaros_stat = "attack";
		}
	}

	if((barbaros_stat == "attack") && (barbaros_gun == "handgun"))
	{
		
		if(player_time == 0)
		{
			player_time = 100 + süre;
		}
		
		if(current_time <= player_time) // 100 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["handgun1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 100))) 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["handgun2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 100) && (current_time <= (player_time + 200)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["handgun3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else
		{
			player_time = 0;
			barbaros_durum ="move";
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["handgun1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	}

	if((barbaros_stat == "move") && (barbaros_gun == "handgun"))
	{
		if(player_time == 0 )
		{
			player_time = 200 + süre;
		}
		
		if(current_time <= player_time) // 200 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_handgun_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 200)) ) 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_handgun_1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 200) && (current_time <= (player_time + 400)) )
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_handgun_2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 400) && (current_time <= (player_time + 600)) )
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_handgun_3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 600) && (current_time <= (player_time + 800)) )
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_handgun_4"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	
		else
		{
			player_time = 0;
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_handgun_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	}
	if((barbaros_stat == "attack") && (barbaros_gun == "shotgun"))
	{
	
		if(player_time == 0)
		{
			player_time = 200 + süre;
		}
		
		if(current_time <= player_time) // 200 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["shotgun1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
			cout<<"shotgun1"<<endl;
		}
		else if((current_time > player_time) && (current_time <= (player_time + 200))) 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["shotgun2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
			cout<<"shotgun2"<<endl;
		}
		else if((current_time > player_time + 200) && (current_time <= (player_time + 400)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["shotgun3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
			cout<<"shotgun3"<<endl;
		}
		else
		{
			player_time = 0;
			barbaros_durum ="move";
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["shotgun1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
			cout<<"son shotgun1"<<endl;
		}
	}

	if((barbaros_stat == "move") && (barbaros_gun == "shotgun"))
	{
		if(player_time == 0)
		{
			player_time = 200 + süre;
		}
		
		if(current_time <= player_time) // 200 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_shotgun_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 200))) 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_shotgun_1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 200) && (current_time <= (player_time + 400)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_shotgun_2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 400) && (current_time <= (player_time + 600)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_shotgun_3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 600) && (current_time <= (player_time + 800)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_shotgun_4"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	
		else
		{
			player_time = 0;
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_shotgun_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	}

	if((barbaros_stat == "attack") && (barbaros_gun == "rifle"))
	{
		
		if(player_time == 0)
		{
			player_time = 100 + süre;
		}
		
		if(current_time <= player_time) // 100 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["rifle1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 100))) 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["rifle2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 100) && (current_time <= (player_time + 200)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["rifle3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else
		{
			player_time = 0;
			barbaros_durum ="move";
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["rifle1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	}

	if((barbaros_stat == "move") && (barbaros_gun == "rifle"))
	{
		if(player_time == 0)
		{
			player_time = 200 + süre;
		}
		
		if(current_time <= player_time) // 100 ms sayarsa
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_rifle_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time) && (current_time <= (player_time + 200))) 
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_rifle_1"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 200) && (current_time <= (player_time + 400)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_rifle_2"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 400) && (current_time <= (player_time + 600)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_rifle_3"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
		else if((current_time > player_time + 600) && (current_time <= (player_time + 800)))
		{
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_rifle_4"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	
		else
		{
			player_time = 0;
			SDL_RenderCopyEx(render_barbaros , barbaros_weapon["idle_rifle_0"] , NULL , &player_barbaros , angle , &playerPoint , SDL_FLIP_NONE);
		}
	}

}

void Player :: barbaros_güncelle(SDL_Renderer* render , Uint32 time_barbaros)
{
	if(health <= 0)
	{
		Write(render , current_time , "You are dead ..! ");
		oyun_baslat = false; // burasý düzeltilecek
	}
	else
	{
		if(health > 100)
			health = 100;
		if(thirtsy > 100)
			thirtsy = 100;
		if(hunger > 100)
			hunger = 100;

		if(hunger_time == 0)
			hunger_time = time_barbaros + 7000; // açlýk her 7 saniyede 1 azalacak

		if(thirsty_time == 0)
			thirsty_time = time_barbaros + 5000; // susuzluk her 5 saniyede 1 azalacak

		if(current_time >= hunger_time)
		{
			hunger--;
			if(hunger <= 0)
				hunger = 0;
			
			hunger_time = 0;
			if(hunger <= 25)
				health--;

		}

		if(current_time >= thirsty_time)
		{
			thirtsy--;
			if(thirtsy <= 0)
				thirtsy = 0;

			thirsty_time = 0;
			if(thirtsy <= 25)
				health--;

		}

		if((handgun_mermi <= 0) && (barbaros_guns == "handgun"))
		{		
			Write(render , current_time , "Tabanca mermisi bitti");
		}
		else if((rifle_mermi <= 0) && (barbaros_guns == "rifle"))
		{		
			Write(render , current_time , "Tüfek mermisi bitti");
		}
		else if((shotgun_mermi <= 0) && (barbaros_guns == "shotgun"))
		{		
			Write(render , current_time , "Pompalý tüfek mermisi bitti");
		}

		
	}
}
                
void Player :: load_barbaros(SDL_Renderer* renderer)
{
	
	barbaros_yukle_weapon("assets/barbaros/flashlight/move/survivor-move_flashlight_0.png" ,renderer, "move_flashlight_0");
	barbaros_yukle_weapon("assets/barbaros/flashlight/move/survivor-move_flashlight_5.png" ,renderer, "move_flashlight_1");
	barbaros_yukle_weapon("assets/barbaros/flashlight/move/survivor-move_flashlight_10.png" ,renderer, "move_flashlight_2");
	barbaros_yukle_weapon("assets/barbaros/flashlight/move/survivor-move_flashlight_15.png" ,renderer, "move_flashlight_3");
	barbaros_yukle_weapon("assets/barbaros/flashlight/move/survivor-move_flashlight_19.png" ,renderer, "move_flashlight_4");

	barbaros_yukle_weapon("assets/barbaros/handgun/shoot/handgun_1.png" ,renderer, "handgun1");
	barbaros_yukle_weapon("assets/barbaros/handgun/shoot/handgun_2.png" ,renderer, "handgun2");
	barbaros_yukle_weapon("assets/barbaros/handgun/shoot/handgun_3.png" ,renderer, "handgun3");

	barbaros_yukle_weapon("assets/barbaros/handgun/idle/idle_handgun_0.png" ,renderer, "idle_handgun_0");
	barbaros_yukle_weapon("assets/barbaros/handgun/idle/idle_handgun_5.png" ,renderer, "idle_handgun_1");
	barbaros_yukle_weapon("assets/barbaros/handgun/idle/idle_handgun_10.png" ,renderer, "idle_handgun_2");
	barbaros_yukle_weapon("assets/barbaros/handgun/idle/idle_handgun_15.png" ,renderer, "idle_handgun_3");
	barbaros_yukle_weapon("assets/barbaros/handgun/idle/idle_handgun_19.png" ,renderer, "idle_handgun_4");
	
	barbaros_yukle_weapon("assets/barbaros/shotgun/shoot/shoot_shotgun_0.png" ,renderer, "shotgun1");
	barbaros_yukle_weapon("assets/barbaros/shotgun/shoot/shoot_shotgun_1.png" ,renderer, "shotgun2");
	barbaros_yukle_weapon("assets/barbaros/shotgun/shoot/shoot_shotgun_2.png" ,renderer, "shotgun3");

	barbaros_yukle_weapon("assets/barbaros/shotgun/idle/idle_shotgun_0.png" ,renderer, "idle_shotgun_0");
	barbaros_yukle_weapon("assets/barbaros/shotgun/idle/idle_shotgun_5.png" ,renderer, "idle_shotgun_1");
	barbaros_yukle_weapon("assets/barbaros/shotgun/idle/idle_shotgun_10.png" ,renderer, "idle_shotgun_2");
	barbaros_yukle_weapon("assets/barbaros/shotgun/idle/idle_shotgun_15.png" ,renderer, "idle_shotgun_3");
	barbaros_yukle_weapon("assets/barbaros/shotgun/idle/idle_shotgun_19.png" ,renderer, "idle_shotgun_4");

	barbaros_yukle_weapon("assets/barbaros/rifle/shoot/shoot_rifle_0.png" ,renderer, "rifle1");
	barbaros_yukle_weapon("assets/barbaros/rifle/shoot/shoot_rifle_1.png" ,renderer, "rifle2");
	barbaros_yukle_weapon("assets/barbaros/rifle/shoot/shoot_rifle_2.png" ,renderer, "rifle3");

	barbaros_yukle_weapon("assets/barbaros/rifle/idle/idle_rifle_0.png" ,renderer, "idle_rifle_0");
	barbaros_yukle_weapon("assets/barbaros/rifle/idle/idle_rifle_5.png" ,renderer, "idle_rifle_1");
	barbaros_yukle_weapon("assets/barbaros/rifle/idle/idle_rifle_10.png" ,renderer, "idle_rifle_2");
	barbaros_yukle_weapon("assets/barbaros/rifle/idle/idle_rifle_15.png" ,renderer, "idle_rifle_3");
	barbaros_yukle_weapon("assets/barbaros/rifle/idle/idle_rifle_19.png" ,renderer, "idle_rifle_4");

	barbaros_yukle_weapon("assets/barbaros/knife/meleeattack/meleeattack_knife_0.png" ,renderer, "knife1");
	barbaros_yukle_weapon("assets/barbaros/knife/meleeattack/meleeattack_knife_3.png" ,renderer, "knife2");
	barbaros_yukle_weapon("assets/barbaros/knife/meleeattack/meleeattack_knife_6.png" ,renderer, "knife3");
	barbaros_yukle_weapon("assets/barbaros/knife/meleeattack/meleeattack_knife_9.png" ,renderer, "knife4");
	barbaros_yukle_weapon("assets/barbaros/knife/meleeattack/meleeattack_knife_12.png" ,renderer, "knife5");

	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_0.png" ,renderer, "idle_knife_0");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_1.png" ,renderer, "idle_knife_1");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_2.png" ,renderer, "idle_knife_2");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_3.png" ,renderer, "idle_knife_3");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_4.png" ,renderer, "idle_knife_4");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_5.png" ,renderer, "idle_knife_5");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_6.png" ,renderer, "idle_knife_6");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_7.png" ,renderer, "idle_knife_7");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_8.png" ,renderer, "idle_knife_8");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_9.png" ,renderer, "idle_knife_9");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_10.png" ,renderer, "idle_knife_10");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_11.png" ,renderer, "idle_knife_11");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_12.png" ,renderer, "idle_knife_12");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_13.png" ,renderer, "idle_knife_13");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_14.png" ,renderer, "idle_knife_14");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_15.png" ,renderer, "idle_knife_15");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_16.png" ,renderer, "idle_knife_16");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_17.png" ,renderer, "idle_knife_17");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_18.png" ,renderer, "idle_knife_18");
	barbaros_yukle_weapon("assets/barbaros/knife/idle/idle_knife_19.png" ,renderer, "idle_knife_19");
}