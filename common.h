#pragma once

#include "natives.h"
#include "consts.h"

void print(char* text){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_LITERAL_STRING("string",text,3000,true);
return;
}

void print_two(char* text, char* text2){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_TWO_LITERAL_STRINGS("string",text,text2,3000,true);
return;
}

void print_short(char* text){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_LITERAL_STRING("string",text,1000,true);
return;
}

void print_number(uint number){
CLEAR_PRINTS();//Clears already printed text
PRINT_WITH_NUMBER_NOW("string", number, 5000, true);
return;
}

void print_long(char* text){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_LITERAL_STRING("string",text,6000,true);
return;
}

Player GetPlayerIndex(void)
{
	return GET_PLAYER_ID();
}

Ped GetPlayerPed(void)
{
	Ped playerped = INVALID_HANDLE;
	if ( PLAYER_HAS_CHAR(GetPlayerIndex()) )
		GET_PLAYER_CHAR(GetPlayerIndex(), &playerped);
	return playerped;
}

void UpdateWeaponOfPed(Ped ped, Weapon weapon)
{
	if (HAS_CHAR_GOT_WEAPON(ped, weapon))
	{
		SET_CHAR_AMMO(ped, weapon, AMMO_MAX);    
	} 	else
	{
		GIVE_WEAPON_TO_CHAR(ped, weapon, AMMO_MAX, FALSE);	
	}
}
