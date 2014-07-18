int projectile; 
float aimx;
float aimy;
float aimz;     
float playx;
float playy;
float playz;	
float velx;
float vely;
float velz;
float dist;
 
Vector3 aim_tmp;
Vector3 play_tmp;

void fire_tele_gun(void){
	if(!DOES_OBJECT_EXIST(projectile)){
				
		aimx = aim_tmp.x;
		aimy = aim_tmp.y;
		aimz = aim_tmp.z;
								
		playx = play_tmp.x;
		playy = play_tmp.y;
		playz = play_tmp.z;
                       
		GET_DISTANCE_BETWEEN_COORDS_3D(aim_tmp.x,aim_tmp.y,aim_tmp.z,play_tmp.x,play_tmp.y,play_tmp.z,&dist);
		#define SPEED 2000
		velx = SPEED * (aim_tmp.x - play_tmp.x) / dist;
		vely = SPEED * (aim_tmp.y - play_tmp.y) / dist;
		velz = SPEED * (aim_tmp.z - play_tmp.z) / dist;
						
		CREATE_OBJECT(0x501811B6,play_tmp.x,play_tmp.y,play_tmp.z,&projectile,true);
		SET_OBJECT_RECORDS_COLLISIONS(projectile,true);
		FREEZE_OBJECT_POSITION(projectile,false);
		SET_OBJECT_VISIBLE(projectile,false);
		SET_OBJECT_COLLISION(projectile,false);
		SET_OBJECT_INITIAL_VELOCITY(projectile,velx,vely,velz);

		run_tele = true;
		return;
	}
}
 
void set_tele_gun(void){
	if(DOES_OBJECT_EXIST(projectile)){
		if(HAS_OBJECT_COLLIDED_WITH_ANYTHING(projectile) || dist > 300){
			FREEZE_OBJECT_POSITION(projectile,true);
			GET_OBJECT_COORDINATES(projectile,&aimx,&aimy,&aimz);
			SET_CHAR_COORDINATES(pPlayer,aimx,aimy,aimz);
			DELETE_OBJECT(&projectile);
			MARK_OBJECT_AS_NO_LONGER_NEEDED(&projectile);
			run_tele = false;
		}
		else{
			GET_OBJECT_COORDINATES(projectile,&aimx,&aimy,&aimz);				
			GET_DISTANCE_BETWEEN_COORDS_3D(aimx,aimy,aimz,playx,playy,playz,&dist);
			SET_OBJECT_INITIAL_VELOCITY(projectile,velx,vely,velz);
			SET_OBJECT_COLLISION(projectile,true);                 
		}
	}
	return;
}

void get_tele_data(void){	
	if(run_tele){
		int bone = BONE_RIGHT_HAND;
		GET_PED_BONE_POSITION(pPlayer,bone,5.0,0.0,0.0,&play_tmp);
		GET_PED_BONE_POSITION(pPlayer,bone,100.0,0.0,0.0,&aim_tmp);
	}
				   
	if(IS_CHAR_SHOOTING(pPlayer)){
		int weapon;
		int bone = BONE_RIGHT_HAND;
		GET_PED_BONE_POSITION(pPlayer,bone,5.0,0.0,0.0,&play_tmp);
		GET_PED_BONE_POSITION(pPlayer,bone,100.0,0.0,0.0,&aim_tmp);
		GET_CURRENT_CHAR_WEAPON(pPlayer,&weapon);
		if(weapon == WEAPON_PISTOL) fire_tele_gun();
	}
	if(run_tele) set_tele_gun();
	return;
}
