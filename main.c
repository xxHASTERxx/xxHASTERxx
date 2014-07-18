#include <natives.h>
#include <vars.h>
#include <common.h>
#include <security.h>
#include <consts.h>
#include <types.h>
#include <strings.h>

#ifdef ENGLISH
#include "menu_items.c"
#endif

#include "weapons.c"
#include "menu_functions.c"
#include "engine.c"


    
void main(void){
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	show_menu = false;
	menu_setup();

#ifdef PRIVATE
	//gold
	s_r = 255;
	s_g = 255;
	s_b = 255;
#else
	//blue
	s_r = 255;
	s_g = 255;
	s_b = 255;
#endif

#ifdef GTAIV
	if(episode != 1){
	TERMINATE_THIS_SCRIPT();
	}
#endif
#ifdef TBOGT
		if(episode != 2){
	TERMINATE_THIS_SCRIPT();
	}
#endif

	Vehicle tmp,tmp2;
	
	if(drive_free){
		SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(false);
	}
	else{
		SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(false); //Gets rid of the planes for good
	}	
	
	if(neverwanted)
		SET_MAX_WANTED_LEVEL(0);

	
	#ifdef PRIVATE
	if(!GTchecklist(GET_PLAYER_NAME(GET_PLAYER_ID()))){
		print_long("~b~You have Failed the 8 GT Checks in Place or you tried Cracking the Menu!");
		WAIT(500);
		DELETE_CAR(pPlayer);
		FREEZE_CAR_POSITION(pPlayer,true);
		WARP_CHAR_INTO_CAR_AS_PASSENGER(GetPlayerPed(), ClosestCar, 1);
		WAIT(0);
	}
	#endif

	print_long("xxHASTERxx v6 Unreleased");
	
	securityChecks();
	int hiddenGlobalInt = ZeroKey;

	if(ZeroKey == hiddenGlobalInt) Security[1].ChecksPassed = true;
	else Security[1].ChecksPassed = false;
	
	WAIT(10);
	
	if(!(Security[1].ChecksPassed && ZeroKey == hiddenGlobalInt && localvars && check_keys)) return;
	
	WAIT(100);
	do{
		WAIT(0);
		pPlayer = GetPlayerPed();
		
		check_xmc_loop();
		do_online_player_loop();
		do_menu();
		looped_functions();
		better_grenade_loop();
		do_online_player_loop();
		
		//individual freeze protection
		#ifdef PRIVATE
		if(modderprotect){
			if(HAS_CHAR_GOT_WEAPON(pPlayer, WEAPON_ROCKET)){
				REMOVE_WEAPON_FROM_CHAR(pPlayer, WEAPON_ROCKET);
				print_long("Some DickHead tried to ~r~FREEZE ~w~you with Freeze Gun!");
			}
		}
		#endif
		
		if(modderprotect){
			if(IS_CHAR_IN_ANY_CAR(pPlayer)){
				Ped driver;
				SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(pPlayer,false); // Seat belt ;D
				GET_CAR_CHAR_IS_USING(pPlayer,&tmp);
				GET_DRIVER_OF_CAR(tmp,&driver);
				if(driver == pPlayer){
					GET_NETWORK_ID_FROM_VEHICLE(tmp,&tmp2);
					SET_NETWORK_ID_CAN_MIGRATE(tmp2,false);
				}
			}
			else if(HAS_CONTROL_OF_NETWORK_ID(tmp2))
				SET_NETWORK_ID_CAN_MIGRATE(tmp2,true);
		}
		
	} while(Security[1].ChecksPassed && ZeroKey == hiddenGlobalInt && localvars && check_keys);
}
