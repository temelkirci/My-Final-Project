#include <iostream>
#include "Items.h"
#include "SDL/SDL.h"
#include <string>
#include <tuple>
#include <algorithm>
#include <vector>

void FindInVector(vector<int> v , int search)
{
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		if (v[i] == search)
		{
			cout << "Found: " << v[i] << " at position: " << i << endl;
		}
	}
	cout<<endl<<endl;
}

bool Descending(int first, int second)
{
	return first > second;
}

void SortVector(vector<int> v)
{
	sort(v.begin(), v.end()); // küçükten büyüðe sýralar
	//sort(v.begin(), v.end() , Descending); // büyükten küçüðe sýralar

	for (auto& value : v)
	{
		cout << value << endl;
	}
}

Items :: Items()
{
	SDL_Rect temp_rect = {900,300,100,100};
	setSolidItems("huge_box" , "blend" , 1 , 100 , true , temp_rect , NULL);

	
	// COLLECTÝBLE ITEMS
	temp_rect.x = 650;
	temp_rect.y = 350;
	temp_rect.w = 50;
	temp_rect.h = 30;
	
	setColItems("rifle" , "blend" , 1 , 100 , true , temp_rect , NULL);

	
	temp_rect.x = 50;
	temp_rect.y = 350;
	temp_rect.w = 50;
	temp_rect.h = 30;
	
	setColItems("handgun" , "blend" , 1 , 100 , true , temp_rect , NULL);
	

	temp_rect.x = 150;
	temp_rect.y = 650;
	temp_rect.w = 50;
	temp_rect.h = 30;

	setColItems("shotgun" , "blend" , 1 , 100 , true , temp_rect , NULL);
	

	temp_rect.x = 750;
	temp_rect.y = 350;
	temp_rect.w = 50;
	temp_rect.h = 30;

	setColItems("soup" , "blend" , 1 , 100 , true , temp_rect , NULL);


	temp_rect.x = 950;
	temp_rect.y = 550;
	temp_rect.w = 50;
	temp_rect.h = 30;

	setColItems("health_bag" , "blend" , 1 , 100 , true , temp_rect , NULL);

	bullet_handgun.bullet_name = "bullet_handgun";
	bullet_handgun.bullet_active = false;
	
	bullet_rifle.bullet_name = "bullet_rifle";
	bullet_rifle.bullet_active = false;

	bullet_shotgun.bullet_name = "bullet_shotgun";
	bullet_shotgun.bullet_active = false;

	// UNCOLLECTÝBLE ITEMS
	temp_rect.x = 450;
	temp_rect.y = 550;
	temp_rect.w = 100;
	temp_rect.h = 100;

	setUncolItems("crater" , "blend" , 1 , 100 , true , temp_rect , NULL);

	inf = "";		
}

Items :: ~Items()
{
	col.empty();
	uncol.empty();
	solid.empty();
}

void Items :: setColItems(string name , string mode , int number , int health , bool isActive , SDL_Rect position , SDL_Texture* texture)
{
	esya.item_name = name;
	esya.item_blendmode = mode;
	esya.number_item = number;
	esya.item_health = health;
	esya.item_active = isActive;
	esya.item_rect = position;
	esya.item_texture = texture;

	rect.push_back(position);
	col.push_back(esya);
}

void Items :: setUncolItems(string name , string mode , int number , int health , bool isActive , SDL_Rect position , SDL_Texture* texture)
{
	esya.item_name = name;
	esya.item_blendmode = mode;
	esya.number_item = number;
	esya.item_health = health;
	esya.item_active = isActive;
	esya.item_rect = position;
	esya.item_texture = texture;

	rect.push_back(position);
	uncol.push_back(esya);
}

void Items :: setSolidItems(string name , string mode , int number , int health , bool isActive , SDL_Rect position , SDL_Texture* texture)
{
	esya.item_name = name;
	esya.item_blendmode = mode;
	esya.number_item = number;
	esya.item_health = health;
	esya.item_active = isActive;
	esya.item_rect = position;
	esya.item_texture = texture;

	rect.push_back(position);
	solid.push_back(esya);
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
