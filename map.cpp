/*
 * map.cpp
 *
 *  Created on: 2015/06/05
 *      Author: Koizumi
 */


#include"map.h"

//map_wall(x,y,RIGHT)->1or0

void map::remember_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < 32) {
			set_maze_wall(&x_wall_exist[set_y], set_x, TRUE);	//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標に壁の存在を作ろうとしています\n\r");
			myprintf("remember_exist関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < 32) {
			set_maze_wall(&y_wall_exist[set_x], set_y, TRUE);	//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標に壁の存在を作ろうとしています\n\r");
			myprintf("remember_exist関数内\n\r");
		}

	}

}
void map::forget_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < 32) {
			set_maze_wall(&x_wall_exist[set_y], set_x, FALSE);//x_maze_wall[y]のx番目の右壁にfalseを代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標の壁の存在を消そうとしています\n\r");
			myprintf("forget_exist関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < 32) {
			set_maze_wall(&y_wall_exist[set_x], set_y, FALSE);//x_maze_wall[y]のx番目の上壁に1false代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標の壁の存在を消そうとしています\n\r");
			myprintf("forget_exist関数内\n\r");
		}

	}

}
unsigned char map::check_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char target_x = wall_x, target_y = wall_y;

	//x座標方向を見るするとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return TRUE;
			} else {
				target_x = wall_x - 1;	//必ず右壁を見るように、座標を変える
			}
		}
		if (target_x < 32) {
			return get_maze_wall(x_wall_exist[target_y], target_x);
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標の壁の存在を読もうとしています\n\r");
			myprintf("check_exist関数内\n\r");
			return FALSE;
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は常に壁が存在
				return TRUE;
			} else {
				target_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (target_y < 32) {
			return get_maze_wall(y_wall_exist[target_x], target_y);
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標の壁の存在を読もうとしています\n\r");
			myprintf("check_exist関数内\n\r");
		}
	}

	return FALSE;
}

void map::create_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < 32) {
			set_maze_wall(&x_maze_wall[set_y], set_x, TRUE);	//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標に壁を作ろうとしています\n\r");
			myprintf("create_wall関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < 32) {
			set_maze_wall(&y_maze_wall[set_x], set_y, TRUE);	//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標に壁を作ろうとしています\n\r");
			myprintf("create_wall関数内\n\r");
		}

	}

}
void map::destroy_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < 32) {
			set_maze_wall(&x_maze_wall[set_y], set_x, FALSE);//x_maze_wall[y]のx番目の右壁にfalseを代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標に壁を作ろうとしています\n\r");
			myprintf("destroy_wall関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < 32) {
			set_maze_wall(&y_maze_wall[set_x], set_y, FALSE);//x_maze_wall[y]のx番目の上壁に1false代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標に壁を作ろうとしています\n\r");
			myprintf("destroy_wall関数内\n\r");
		}

	}

}
unsigned char map::get_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char target_x = wall_x, target_y = wall_y;

	//x座標方向を見るするとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return TRUE;
			} else {
				target_x = wall_x - 1;	//必ず右壁を見るように、座標を変える
			}
		}
		if (target_x < 32) {
			return get_maze_wall(x_maze_wall[target_y], target_x);
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標の壁を読もうとしています\n\r");
			myprintf("get_wall関数内\n\r");
			return FALSE;
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は常に壁が存在
				return TRUE;
			} else {
				target_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (target_y < 32) {
			return get_maze_wall(y_maze_wall[target_x], target_y);
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標の壁を読もうとしています\n\r");
			myprintf("get_wall関数内\n\r");
		}
	}

	return FALSE;
}

//target_wallのedit_number目にset_numberを代入する関数
void map::set_maze_wall(MAZE_WALL *maze_wall, unsigned char edit_number,
		unsigned char set_number) {
	switch (edit_number) {
	case 0:
		maze_wall->bit.B0 = set_number;
		break;
	case 1:
		maze_wall->bit.B1 = set_number;
		break;
	case 2:
		maze_wall->bit.B2 = set_number;
		break;
	case 3:
		maze_wall->bit.B3 = set_number;
		break;
	case 4:
		maze_wall->bit.B4 = set_number;
		break;
	case 5:
		maze_wall->bit.B5 = set_number;
		break;
	case 6:
		maze_wall->bit.B6 = set_number;
		break;
	case 7:
		maze_wall->bit.B7 = set_number;
		break;
	case 8:
		maze_wall->bit.B8 = set_number;
		break;
	case 9:
		maze_wall->bit.B9 = set_number;
		break;
	case 10:
		maze_wall->bit.B10 = set_number;
		break;
	case 11:
		maze_wall->bit.B11 = set_number;
		break;
	case 12:
		maze_wall->bit.B12 = set_number;
		break;
	case 13:
		maze_wall->bit.B13 = set_number;
		break;
	case 14:
		maze_wall->bit.B14 = set_number;
		break;
	case 15:
		maze_wall->bit.B15 = set_number;
		break;
	case 16:
		maze_wall->bit.B16 = set_number;
		break;
	case 17:
		maze_wall->bit.B17 = set_number;
		break;
	case 18:
		maze_wall->bit.B18 = set_number;
		break;
	case 19:
		maze_wall->bit.B19 = set_number;
		break;
	case 20:
		maze_wall->bit.B20 = set_number;
		break;
	case 21:
		maze_wall->bit.B21 = set_number;
		break;
	case 22:
		maze_wall->bit.B22 = set_number;
		break;
	case 23:
		maze_wall->bit.B23 = set_number;
		break;
	case 24:
		maze_wall->bit.B24 = set_number;
		break;
	case 25:
		maze_wall->bit.B25 = set_number;
		break;
	case 26:
		maze_wall->bit.B26 = set_number;
		break;
	case 27:
		maze_wall->bit.B27 = set_number;
		break;
	case 28:
		maze_wall->bit.B28 = set_number;
		break;
	case 29:
		maze_wall->bit.B29 = set_number;
		break;
	case 30:
		maze_wall->bit.B30 = set_number;
		break;
	case 31:
		maze_wall->bit.B31 = set_number;
		break;

	}
}

unsigned char map::get_maze_wall(MAZE_WALL maze_wall,
		unsigned char edit_number) {
	unsigned char maze_check = FALSE;

	switch (edit_number) {
	case 0:
		maze_check = maze_wall.bit.B0;
		break;
	case 1:
		maze_check = maze_wall.bit.B1;
		break;
	case 2:
		maze_check = maze_wall.bit.B2;
		break;
	case 3:
		maze_check = maze_wall.bit.B3;
		break;
	case 4:
		maze_check = maze_wall.bit.B4;
		break;
	case 5:
		maze_check = maze_wall.bit.B5;
		break;
	case 6:
		maze_check = maze_wall.bit.B6;
		break;
	case 7:
		maze_check = maze_wall.bit.B7;
		break;
	case 8:
		maze_check = maze_wall.bit.B8;
		break;
	case 9:
		maze_check = maze_wall.bit.B9;
		break;
	case 10:
		maze_check = maze_wall.bit.B10;
		break;
	case 11:
		maze_check = maze_wall.bit.B11;
		break;
	case 12:
		maze_check = maze_wall.bit.B12;
		break;
	case 13:
		maze_check = maze_wall.bit.B13;
		break;
	case 14:
		maze_check = maze_wall.bit.B14;
		break;
	case 15:
		maze_check = maze_wall.bit.B15;
		break;
	case 16:
		maze_check = maze_wall.bit.B16;
		break;
	case 17:
		maze_check = maze_wall.bit.B17;
		break;
	case 18:
		maze_check = maze_wall.bit.B18;
		break;
	case 19:
		maze_check = maze_wall.bit.B19;
		break;
	case 20:
		maze_check = maze_wall.bit.B20;
		break;
	case 21:
		maze_check = maze_wall.bit.B21;
		break;
	case 22:
		maze_check = maze_wall.bit.B22;
		break;
	case 23:
		maze_check = maze_wall.bit.B23;
		break;
	case 24:
		maze_check = maze_wall.bit.B24;
		break;
	case 25:
		maze_check = maze_wall.bit.B25;
		break;
	case 26:
		maze_check = maze_wall.bit.B26;
		break;
	case 27:
		maze_check = maze_wall.bit.B27;
		break;
	case 28:
		maze_check = maze_wall.bit.B28;
		break;
	case 29:
		maze_check = maze_wall.bit.B29;
		break;
	case 30:
		maze_check = maze_wall.bit.B30;
		break;
	case 31:
		maze_check = maze_wall.bit.B31;
		break;
	}

	return maze_check;
}

void map::draw_map() {
	signed char tekitou_x=0,tekitou_y=MAZE_SIZE-1;

	myprintf("\n-----start draw_map-------\n\r");

	//上辺
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++)
		myprintf("+---");
	myprintf("+\n\r");

	myprintf("|");	//左端の壁
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE - 1; tekitou_x++) {

		//myprintf("%3d", step[tekitou_x][tekitou_y]);
		myprintf("   ");

		if ((get_wall(tekitou_x,tekitou_y,MUKI_RIGHT)==TRUE)
				|| (get_wall(tekitou_x+1,tekitou_y,MUKI_LEFT) == TRUE)) {//今書いたマスの右の壁があれば壁を書く
			myprintf("|");
		} else {
			myprintf(" ");	//なければ壁は書かない
		}
	}

	//myprintf("%3d", step[tekitou_x][tekitou_y]);
	myprintf("   ");

	myprintf("|\n\r");	//右端の壁

	for (tekitou_y = MAZE_SIZE - 2; tekitou_y >= 0; tekitou_y--) {
		//////////////////////////////////////////迷路の壁の行
		for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++) {
			myprintf("+");	//柱
			if ((get_wall(tekitou_x,tekitou_y,MUKI_UP)== TRUE)
					|| (get_wall(tekitou_x,tekitou_y+1,MUKI_DOWN) == TRUE)) {	//壁があるなら
				myprintf("---");
			} else {
				myprintf("   ");
			}
		}
		myprintf("+\n\r");

		/////////////////////////////////////////迷路のマス目の行
		myprintf("|");	//左端の壁
		for (tekitou_x = 0; tekitou_x < MAZE_SIZE - 1; tekitou_x++) {

			//myprintf("%3d", step[tekitou_x][tekitou_y]);
			myprintf("   ");

			if ((get_wall(tekitou_x,tekitou_y,MUKI_RIGHT) == TRUE)
					|| (get_wall(tekitou_x+1,tekitou_y,MUKI_LEFT) == TRUE)) {//今書いたマスの右の壁があれば壁を書く
				myprintf("|");
			} else {
				myprintf(" ");	//なければ壁は書かない
			}
		}
		//myprintf("%3d", step[tekitou_x][tekitou_y]);
		myprintf("   ");

		myprintf("|\n\r");	//右端の壁
	}

	//下辺
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++)
		myprintf("+---");
	myprintf("+\n\r");

}

void map::convert_mapdata(unsigned char (*hiramatu_data)[16]){
	for(char x=0;x<16;x++){
		for(char y=0;y<16;y++){
			if((hiramatu_data[x][y] & 2) == 2){		//東壁があれば
				create_wall(x,y,MUKI_RIGHT);
			}else{
				destroy_wall(x,y,MUKI_RIGHT);
			}

			if((hiramatu_data[x][y] & 1) == 1){		//南壁があれば
				create_wall(x,y,MUKI_UP);
			}else{
				destroy_wall(x,y,MUKI_UP);
			}
		}
	}

}

unsigned char map::output_Hiramatu(int x, int y){
	unsigned char output = 0;
	if(get_wall(x,y,MUKI_UP))	output += 1;	//北に壁があれば1足す
	if(get_wall(x,y,MUKI_DOWN))	output += 8;	//南に壁があれば1足す
	if(get_wall(x,y,MUKI_LEFT))	output += 4;	//西に壁があれば1足す
	if(get_wall(x,y,MUKI_RIGHT))	output += 2;	//東に壁があれば1足す
	return output;
}

void map::input_map_data(MAP_DATA *input_data){
	//データ入力
	for(int i=0; i<MAZE_SIZE;i++){
		x_maze_wall[i].all = input_data->x_wall[i].all;	
		y_maze_wall[i].all = input_data->y_wall[i].all;	
		x_wall_exist[i].all = input_data->x_known[i].all;
		y_wall_exist[i].all = input_data->y_known[i].all;
	}
}


void map::output_map_data(MAP_DATA *output_data){
	//データ出力
	for(int i=0; i<MAZE_SIZE;i++){
		output_data->x_wall[i].all = x_maze_wall[i].all;	
		output_data->y_wall[i].all = y_maze_wall[i].all;
		output_data->x_known[i].all = x_wall_exist[i].all;
		output_data->y_known[i].all = y_wall_exist[i].all;
	}
}

void map::init_map(int maze_size){
	for(int i=0;i<maze_size;i++){
		x_maze_wall[i].all=0;
		y_maze_wall[i].all=0;
		x_wall_exist[i].all=0;
		y_wall_exist[i].all=0;
	}
	for(int i=0;i<maze_size;i++){
		create_wall(0,i,MUKI_LEFT);
		remember_exist(0,i,MUKI_LEFT);
		create_wall(MAZE_SIZE-1,i,MUKI_RIGHT);
		remember_exist(MAZE_SIZE-1,i,MUKI_RIGHT);
		create_wall(i,0,MUKI_DOWN);
		remember_exist(i,0,MUKI_DOWN);
		create_wall(i,MAZE_SIZE-1,MUKI_UP);
		remember_exist(i,MAZE_SIZE-1,MUKI_UP);

	}
}

map::map(){
	init_map(MAZE_SIZE);
}

map::map(int maze_size){
	init_map(maze_size);
}

map::~map(){

}


void adachi::step_reset(){
	for(char i=0;i<MAZE_SIZE;i++){
		for(char j=0;j<MAZE_SIZE;j++){
			step[i][j]=STEP_INIT;
		}
	}
}

void adachi::step_reset_all_search(){
	bool known_flag=false;	//未知区間か既知区間かチェック用
	for(char i=0;i<MAZE_SIZE;i++){
		for(char j=0;j<MAZE_SIZE;j++){
			known_flag=false;
			if( check_exist(i,j,MUKI_UP) == FALSE){				//上を見てないなら
			}else if( check_exist(i,j,MUKI_DOWN) == FALSE){		//下を見てないなら			
			}else if( check_exist(i,j,MUKI_LEFT) == FALSE){		//左を見てないなら			
			}else if( check_exist(i,j,MUKI_RIGHT) == FALSE){	//右を見てないなら			
			}else{		//全方向を見てる
				known_flag=true;
				step[i][j]=STEP_INIT;
			}
			if(known_flag==false){
				step[i][j]=0;
				x_coordinate[head] = i;
				y_coordinate[head] = j;
				head++;
			}
		}
	}
}

void adachi::set_step(unsigned char target_x,unsigned char target_y){
	unsigned char x_count=0,y_count=0;	//一時的に座標をもっとくよう
	

	step_reset();
	step[target_x][target_y]=0;

	//coordinate  [tail][][][] -> [][][head]
	
	head = 1;
	tail = 0;

	//Qの最初には目標の座標を入れとく
	x_coordinate[tail] = target_x;
	y_coordinate[tail] = target_y;

	while(head != tail){
		//座標を代入
		x_count = x_coordinate[tail];
		y_count = y_coordinate[tail];

		tail++;		
					
			//左マス
			if( (x_count-1) >= 0 ){		//座標が迷路内(x-1が0以上)にあり
				if( (step[x_count-1][y_count] == STEP_INIT) ){		//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_LEFT)==FALSE ){		//元のマスの左壁がないなら
						step[x_count-1][y_count] = step[x_count][y_count]+1;		//歩数を代入
						//この座標を保持
						x_coordinate[head] = (x_count - 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
						
			//右マス
			if( (x_count+1) < MAZE_SIZE ){	//座標が迷路内(x+1がMAZE_SIZE未満)にあり
				if( (step[x_count+1][y_count] == STEP_INIT) ){	//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_RIGHT)==FALSE ){		//元のマスの右壁がない
						step[x_count+1][y_count] = step[x_count][y_count]+1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = (x_count + 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
						
			//下マス
			if( (y_count-1) >= 0 ){		//座標が迷路内(y-1が0以上)にあり
				if( (step[x_count][y_count-1] == STEP_INIT) ){		//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_DOWN)==FALSE ){		//元のマスの下壁がない
						step[x_count][y_count-1] = step[x_count][y_count]+1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count - 1);
						head++;
					}
				}
			}
						
			//上マス
			if( (y_count+1) < MAZE_SIZE ){	//x,y+1の座標が迷路内(MAZE_SIZE未満)である
				if( (step[x_count][y_count+1] == STEP_INIT) ){	//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_UP)==FALSE ){		//元のマスの上壁がない
						step[x_count][y_count+1] = step[x_count][y_count]+1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count + 1);
						head++;
					}
				}
			}
		

		if(head>965){		//配列越えたらエラー
			myprintf("エラー!\n\radachi::set_step()内\n\r");
			break;
		}
	
	}


}

void adachi::set_step_by_known(unsigned char target_x,unsigned char target_y){
	unsigned char x_count=0,y_count=0;	//一時的に座標をもっとくよう


	step_reset();
	step[target_x][target_y]=0;

	//coordinate  [tail][][][] -> [][][head]
	
	head = 1;
	tail = 0;

	//Qの最初には目標の座標を入れとく
	x_coordinate[tail] = target_x;
	y_coordinate[tail] = target_y;

	while(head != tail){
		//座標を代入
		x_count = x_coordinate[tail];
		y_count = y_coordinate[tail];

		tail++;		
					
			//左マス
			if( (x_count-1) >= 0 ){		//座標が迷路内(x-1が0以上)にあり
				if( (step[x_count-1][y_count] == STEP_INIT) ){		//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_LEFT)==FALSE ){		//元のマスの左壁がないなら
						if( check_exist(x_count,y_count,MUKI_LEFT)==TRUE ){		//左壁を見ているなら
							step[x_count-1][y_count] = step[x_count][y_count]+1;		//歩数を代入
							//この座標を保持
							x_coordinate[head] = (x_count - 1);
							y_coordinate[head] = y_count;
							head++;
						}
					}
				}
			}
						
			//右マス
			if( (x_count+1) < MAZE_SIZE ){	//座標が迷路内(x+1がMAZE_SIZE未満)にあり
				if( (step[x_count+1][y_count] == STEP_INIT) ){	//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_RIGHT)==FALSE ){		//元のマスの右壁がない
						if( check_exist(x_count,y_count,MUKI_RIGHT)==TRUE ){	//右壁を見ているなら
							step[x_count+1][y_count] = step[x_count][y_count]+1;	//歩数を代入
							//この座標を保持
							x_coordinate[head] = (x_count + 1);
							y_coordinate[head] = y_count;
							head++;
						}
					}
				}
			}
						
			//下マス
			if( (y_count-1) >= 0 ){		//座標が迷路内(y-1が0以上)にあり
				if( (step[x_count][y_count-1] == STEP_INIT) ){		//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_DOWN)==FALSE ){		//元のマスの下壁がない
						if( check_exist(x_count,y_count,MUKI_DOWN)==TRUE ){		//下壁が既知なら
							step[x_count][y_count-1] = step[x_count][y_count]+1;	//歩数を代入
							//この座標を保持
							x_coordinate[head] = x_count;
							y_coordinate[head] = (y_count - 1);
							head++;
						}
					}
				}
			}
						
			//上マス
			if( (y_count+1) < MAZE_SIZE ){	//x,y+1の座標が迷路内(MAZE_SIZE未満)である
				if( (step[x_count][y_count+1] == STEP_INIT) ){	//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_UP)==FALSE ){		//元のマスの上壁がない
						if( check_exist(x_count,y_count,MUKI_UP)==TRUE ){		//上壁が既知なら
							step[x_count][y_count+1] = step[x_count][y_count]+1;	//歩数を代入
							//この座標を保持
							x_coordinate[head] = x_count;
							y_coordinate[head] = (y_count + 1);
							head++;
						}
					}
				}
			}
		

		if(head>965){		//配列越えたらエラー
			myprintf("エラー!\n\radachi::set_step()内\n\r");
			break;
		}
	
	}

}

void adachi::set_step_all_search(unsigned char target_x,unsigned char target_y){
	unsigned char x_count=0,y_count=0;	//一時的に座標をもっとくよう
	
	head = 0;
	tail = 0;
	step_reset_all_search();

	if( get_step(target_x,target_y) == 0){	//既に歩数が初期化されていれば何もしない
	}else{
		//Qには目標の座標を入れとく
		x_coordinate[head] = target_x;
		y_coordinate[head] = target_y;
		step[target_x][target_y] = 0;
		head++;
	}

	//coordinate  [tail][][][] -> [][][head]
	
	
	while(head != tail){
		//座標を代入
		x_count = x_coordinate[tail];
		y_count = y_coordinate[tail];

		tail++;		
					
			//左マス
			if( (x_count-1) >= 0 ){		//座標が迷路内(x-1が0以上)にあり
				if( (step[x_count-1][y_count] == STEP_INIT) ){		//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_LEFT)==FALSE ){		//元のマスの左壁がないなら
						step[x_count-1][y_count] = step[x_count][y_count]+1;		//歩数を代入
						//この座標を保持
						x_coordinate[head] = (x_count - 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
						
			//右マス
			if( (x_count+1) < MAZE_SIZE ){	//座標が迷路内(x+1がMAZE_SIZE未満)にあり
				if( (step[x_count+1][y_count] == STEP_INIT) ){	//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_RIGHT)==FALSE ){		//元のマスの右壁がない
						step[x_count+1][y_count] = step[x_count][y_count]+1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = (x_count + 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
						
			//下マス
			if( (y_count-1) >= 0 ){		//座標が迷路内(y-1が0以上)にあり
				if( (step[x_count][y_count-1] == STEP_INIT) ){		//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_DOWN)==FALSE ){		//元のマスの下壁がない
						step[x_count][y_count-1] = step[x_count][y_count]+1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count - 1);
						head++;
					}
				}
			}
						
			//上マス
			if( (y_count+1) < MAZE_SIZE ){	//x,y+1の座標が迷路内(MAZE_SIZE未満)である
				if( (step[x_count][y_count+1] == STEP_INIT) ){	//歩数を入れてない（入ってる歩数がSTEP_INIT）
					if( get_wall(x_count,y_count,MUKI_UP)==FALSE ){		//元のマスの上壁がない
						step[x_count][y_count+1] = step[x_count][y_count]+1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count + 1);
						head++;
					}
				}
			}
		

		if(head>965){		//配列越えたらエラー
			myprintf("エラー!\n\radachi::set_step_all_search()内\n\r");
			break;
		}
	
	}

}

unsigned int adachi::get_step(unsigned char target_x,unsigned char target_y){
	return step[target_x][target_y];
}


void adachi::close_one_dead_end(unsigned char target_x, unsigned char target_y){
	union {
		unsigned char all;				//一括
		struct {
			unsigned char count	:4;		//		行けない方向の個数
			unsigned char up	:1;		//↑	x=0,y=1の方向
			unsigned char down	:1;		//↓	x=0,y=-1の方向
			unsigned char left	:1;		//←	x=-1,y=0の方向
			unsigned char right	:1;		//→	x=1,y=0の方向
		} direction;
	} dead_end;
	
	dead_end.all = 0;	//初期化
	
	//左マス
	if( (get_wall(target_x,target_y,MUKI_LEFT) == TRUE) ){			//左壁があるなら
		dead_end.direction.left = 1;	//左フラグを建てる
		dead_end.direction.count++;		//1足す	
	}else if( (target_x-1) >= 0 ){		//座標が迷路内(x-1が0以上)にあり
		if( (step[target_x-1][target_y] == STEP_INIT) || (check_exist(target_x,target_y,MUKI_LEFT) == FALSE) ){		//左のマスに行けない（入ってる歩数が255 または ）
			dead_end.direction.left = 1;	//左フラグオン
			dead_end.direction.count++;		//1足す	
		}	
	}
						
	//右マス
	if( (get_wall(target_x,target_y,MUKI_RIGHT) == TRUE) ){			//右壁があるなら
		dead_end.direction.right = 1;		//右フラグを建てる
		dead_end.direction.count++;			//1足す	
	}else if( (target_x+1) < MAZE_SIZE ){	//座標が迷路内(x+1がMax_x未満)にあり
		if( (step[target_x+1][target_y] == STEP_INIT) || (check_exist(target_x,target_y,MUKI_RIGHT) == FALSE)){			//右のマスに行けない（入ってる歩数が255 または 壁がある）
			dead_end.direction.right = 1;	//右フラグを建てる
			dead_end.direction.count++;		//1足す	
		}
	}
				
	//下マス
	if( (get_wall(target_x,target_y,MUKI_DOWN) == TRUE) ){			//下壁があるなら
		dead_end.direction.down = 1;		//下フラグを建てる
		dead_end.direction.count++;			//1足す	
	}else if( (target_y-1 >= 0) ){		//座標が迷路内(y-1が0以上)にあり
		if( (step[target_x][target_y-1] == STEP_INIT) || (check_exist(target_x,target_y,MUKI_DOWN) == FALSE) ){		//下のマスに行けない（入ってる歩数が255 または 壁がある）
			dead_end.direction.down = 1;	//下フラグを建てる
			dead_end.direction.count++;		//1足す	
		}
	}
				
	//上マス
	if( (get_wall(target_x,target_y,MUKI_UP) == TRUE) ){			//上壁があるなら
		dead_end.direction.up = 1;			//上フラグを建てる
		dead_end.direction.count++;			//1足す	
	}else if( (target_y+1 < MAZE_SIZE) ){	//x,y+1の座標が迷路内(MAX_y未満)である
		if( (step[target_x][target_y+1] == STEP_INIT) || (check_exist(target_x,target_y,MUKI_UP) == FALSE) ){		//上のマスに行けない（入ってる歩数が255　または　壁がある）
			dead_end.direction.up = 1;		//上フラグを建てる
			dead_end.direction.count++;		//1足す	
		}
	}
	
	
	//袋小路をふさぐ
	if( dead_end.direction.count >= 3 ){		//行けない方向が3以上 = 袋小路なら
		if( (target_x == 0) && (target_y == 0) ){		//それがスタートなら何もしない
		}else if( (target_x == GOAL_x) && (target_y == GOAL_y) ){		//それがゴールでも何もしない
		}else{							//上記以外なら袋小路を潰す
			step[target_x][target_y] = STEP_INIT;	//歩数を初期化
			//袋小路のあいてる方向についてもう一回同じことを行う
			if( dead_end.direction.left == 0 ){
				create_wall(target_x,target_y,MUKI_LEFT);
				remember_exist(target_x,target_y,MUKI_LEFT);
				close_one_dead_end(target_x-1,target_y);

			}
			if( dead_end.direction.right == 0){
				create_wall(target_x,target_y,MUKI_RIGHT);
				remember_exist(target_x,target_y,MUKI_RIGHT);
				close_one_dead_end(target_x+1,target_y);
			}
			if( dead_end.direction.down == 0){
				create_wall(target_x,target_y,MUKI_DOWN);
				remember_exist(target_x,target_y,MUKI_DOWN);
				close_one_dead_end(target_x,target_y-1);
			}
			if( dead_end.direction.up == 0){
				create_wall(target_x,target_y,MUKI_UP);
				remember_exist(target_x,target_y,MUKI_UP);
				close_one_dead_end(target_x,target_y+1);
			}
		}
	}
}

void adachi::close_dead_end(){
	for(int i=0;i<MAZE_SIZE;i++){
		for(int j=0;j<MAZE_SIZE;j++){
			close_one_dead_end(i,j);
		}
	}
}

adachi::adachi(){
	create_wall(0,0,MUKI_RIGHT);
	create_wall(0,0,MUKI_LEFT);
	create_wall(0,0,MUKI_DOWN);
	
	remember_exist(0,0,MUKI_RIGHT);
	remember_exist(0,0,MUKI_LEFT);
	remember_exist(0,0,MUKI_UP);
	remember_exist(0,0,MUKI_DOWN);

	step_reset();

}

adachi::~adachi(){

}




void path::set_step_for_shortest(unsigned char target_x,unsigned char target_y){
	set_step_by_known(target_x,target_y);		//既知の壁だけで歩数マップを作成
	close_dead_end();							//袋小路を潰す
}

void path::displace_path(unsigned int path_number){
	//1個ずらす
	for( unsigned int number = path_number; path_memory[number].element.flag == FALSE; number++){
		path_memory[number].all = path_memory[number+1].all;
	}
}


void path::improve_path(){
	unsigned int count=0;
	unsigned char naname_flag = FALSE;	//現在機体が斜めかを判断	ONなら斜め走行中
	
	while( path_memory[count].element.flag == FALSE ){		//pathが終われば終了
		
		if( path_memory[count].element.distance >= 1 ){		//90mm以上直進するなら
			
			if( path_memory[count+1].element.distance >= 1 ){		//ターン後も90mm以上直進するなら	大回りのチェックを行う
				path_memory[count].element.turn = 2;					//大回りターンに変更
				path_memory[count].element.distance -= 1;				//直線距離を90mm減らす
				path_memory[count+1].element.distance -= 1;			//直線距離を90mm減らす
			
			}else{											//ターン後90mm直進はしないなら
				
				if( path_memory[count].element.muki == path_memory[count+1].element.muki ){	//同じ方向に曲がるなら(Uターン)
					
					if( path_memory[count+2].element.distance >= 1 ){		//Uターン後90mm直進するなら
						path_memory[count].element.turn = 3;					//180°ターンに変更
						path_memory[count].element.distance -= 1;				//直線距離を90mm減らす
						path_memory[count+2].element.distance -= 1;			//直線距離を90mm減らす
						
						//1個ずらす
						displace_path(count+1);
						
					}else{											//Uターン後すぐ曲がるなら
						
						if( path_memory[count+2].element.flag == FALSE ){					//pathが終わってないかチェック　終わってなければ逆方向にターンのはず
							//ナナメの処理なので何もしない
						}
						
					}
				
				}else{		//違う方法に曲がるなら
					//ナナメの処理なので何もしない
				}
								
			}
		
		}
		
		count++;
	}

}

void path::improve_advance_path(){
	unsigned int count=0;
	unsigned char temp_distance=0;	//一時的な距離保存		
	unsigned char naname_flag = FALSE;	//現在機体が斜めかを判断	ONなら斜め走行中
	
	while( path_memory[count].element.flag == FALSE ){		//pathが終われば終了
		
		if( naname_flag == TRUE){							//斜め走行中なら	確実に直進距離(distance)が0のはず
				
			if( path_memory[count+1].element.distance >= 1 ){			//次のターン後90mm以上直進(斜め終わり)
				
				path_memory[count].element.turn = 4;							//45°ターンに変更
				path_memory[count+1].element.distance -= 1;					//直線距離を90mm減らす
				naname_flag = FALSE;
				count++;												//配列を次へ
				
			}else if( path_memory[count+2].element.distance >= 1 ){	//次の次のターン後90mm以上直進(斜め終わり)
				
				if( path_memory[count].element.muki == path_memory[count+1].element.muki ){		//同じ方向の2回ターン
					
					path_memory[count].element.turn = 5;					//135°ターンに変更
					displace_path(count+1);							//一個ずらす
					path_memory[count+1].element.distance -= 1;			//ターン後の直線距離を90mm減らす
					naname_flag = FALSE;
					count++;										//配列を次へ
					
				}else{																//交互のターン(ギザギザ)
					
					path_memory[count].element.distance += 1;				//斜めの直線距離を1増やす
					temp_distance = path_memory[count].element.distance;	//距離を一時的に持っておく
					displace_path(count);							//一個ずらす
					path_memory[count].element.distance = temp_distance;	//距離を入れなおす
						
				}
				
			}else{												//まだまだ斜めは続くなら
					
				if( path_memory[count].element.muki == path_memory[count+1].element.muki ){		//同じ方向の2回ターン	コの字
					
					path_memory[count].element.turn = 6;					//斜め90°ターンに変更
					displace_path(count+1);							//一個ずらす
					count++;										//配列を次へ
					
				}else{																//違う方向の2回ターン	ギザギザ
					
					path_memory[count].element.distance += 1;				//斜めの直線距離を1増やす
					temp_distance = path_memory[count].element.distance;	//距離を一時的に持っておく
					displace_path(count);							//一個ずらす
					path_memory[count].element.distance = temp_distance;	//距離を入れなおす
				
				}
			}
		
		}else {										//斜めじゃなければ
			
			if( path_memory[count+1].element.distance >= 1 ){		//ターン後も90mm以上直進するなら	大回りのチェックを行う
			
				if( (count != 0) || (path_memory[0].element.distance > 1) ){		//初っ端のターンじゃなければ
			
					path_memory[count].element.turn = 2;					//大回りターンに変更
					path_memory[count].element.distance -= 1;				//直線距離を90mm減らす
					path_memory[count+1].element.distance -= 1;			//直線距離を90mm減らす
			
				}
			
			}else{											//ターン後90mm直進はしないなら
				
				if( path_memory[count].element.muki == path_memory[count+1].element.muki ){	//同じ方向に曲がるなら(Uターン)
					
					if( path_memory[count+2].element.distance >= 1 ){		//Uターン後90mm直進するなら
			
						path_memory[count].element.turn = 3;					//180°ターンに変更
						path_memory[count].element.distance -= 1;				//直線距離を90mm減らす
						path_memory[count+2].element.distance -= 1;			//直線距離を90mm減らす
						displace_path(count+1);							//一個ずらす
						
					}else{											//Uターン後すぐ曲がるなら
						
						if( path_memory[count+2].all != 0 ){					//pathが終わってないかチェック　終わってなければ逆方向にターンのはず
			
							path_memory[count].element.turn = 5;					//135°ターンに変更
							path_memory[count].element.distance -= 1;				//直線距離を90mm減らす
							displace_path(count+1);							//一個ずらす
							naname_flag = TRUE;
							
						}
						
					}
				
				}else{		//違う方法に曲がるなら
					
					path_memory[count].element.turn = 4;							//45°ターンに変更
					path_memory[count].element.distance -= 1;						//直線距離を90mm減らす
					naname_flag = TRUE;
					
				}
								
			}	
			count++;		//配列を次へ
		}
	}
	
}


void path::create_path(){
	signed char straight_flag;			//直線できるかどうか判別用フラグ
	SAVE_DIRECTION save_direction;				//次に行くマスの方向を保存		
	unsigned int count=0;	//数を数えるだけの変数
	
	set_step_for_shortest(GOAL_x,GOAL_y);

	path_reset();

	path_direction_x = 0;	//方向を初期化
	path_direction_y = 1;
	
	path_x = 0;		//位置を初期化
	path_y = 0;
	
	straight_flag	= FALSE;	//フラグは折っておく

	
	path_memory[count].element.distance += 1;	//最初は必ず半区画直進する
	
	while(1){
	
		save_direction.all = 0;		//次に行く方向初期化
		straight_flag	= FALSE;	//フラグは折っておく

		path_x += path_direction_x; 		//位置修正
		path_y += path_direction_y; 
		
		if( (path_x == GOAL_x) && (path_y == GOAL_y))	break;	//GOALにたどり着いたら終了

		//左
		if( (path_x - 1) >= 0 ){		//path_x-1,path_yの座標が迷路内(0以上)である
			if( get_step(path_x-1,path_y) == (get_step(path_x,path_y) - 1) ){				//1歩,歩数の小さいほうへ
				if( (get_wall(path_x,path_y,MUKI_LEFT) == FALSE) ){	//壁がないなら
					save_direction.element.left=1;		//次に進む方向の選択肢に追加
					if( (path_direction_x==-1)&&(path_direction_y==0)){		//左を向いてるとき（直進できるとき）
						straight_flag = TRUE;	//直進フラグをたてる
					}
				}
			}
			
		}

		//右
		if( (path_x + 1) < MAZE_SIZE ){	//path_x+1,path_yの座標が迷路内である
			if( get_step(path_x+1,path_y) == (get_step(path_x,path_y) - 1) ){				//歩数の小さいほうへ
				if( (get_wall(path_x,path_y,MUKI_RIGHT) == FALSE) ){	//壁がないなら
					save_direction.element.right=1;		//次に進む方向の選択肢に追加
					if( (path_direction_x==1)&&(path_direction_y==0)){		//右を向いてるとき（直進できるとき）
						straight_flag = TRUE;	//直進フラグをたてる
					}
				}
			}
		}
	
		//下
		if( (path_y - 1) >= 0 ){		//path_x,path_y-1の座標が迷路内(0以上)である
			if( get_step(path_x,path_y-1) == (get_step(path_x,path_y) - 1) ){				//歩数の小さいほうへ
				if( (get_wall(path_x,path_y,MUKI_DOWN) == FALSE) ){	//壁がないなら
					save_direction.element.down=1;		//次に進む方向の選択肢に追加
					if( (path_direction_x==0)&&(path_direction_y==-1)){		//下を向いてるとき（直進できるとき）
						straight_flag = TRUE;	//直進フラグをたてる
					}
				}
			}
		}
	
		//上
		if( (path_y + 1) < MAZE_SIZE ){	//path_x,path_y+1の座標が迷路内(16以下)である
			if( get_step(path_x,path_y+1) == (get_step(path_x,path_y) - 1) ){				//歩数の小さいほうへ
				if( (get_wall(path_x,path_y,MUKI_UP) == FALSE) ){	//壁がないなら
					save_direction.element.up=1;		//次に進む方向の選択肢に追加
					if( (path_direction_x==0)&&(path_direction_y==1)){		//上を向いてるとき（直進できるとき）
						straight_flag = TRUE;	//直進フラグをたてる
					}
				}				
			} 
		}
		
		if(straight_flag == TRUE){			//直進できるなら
			path_memory[count].element.distance += 2;	//180mm直進を追加
		
		}else{								//ターンするなら
			path_memory[count].element.turn = 1;	//小回りターン
			if(path_direction_x == 0){						//上か下向きのとき
				//右に行きたい
				if(save_direction.element.right == 1 ){					
					if( path_direction_y == 1){	//上を向いてる							
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x,&path_direction_y,MUKI_RIGHT);
					}else{					//下を向いてる									
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;		
						direction_turn(&path_direction_x,&path_direction_y,MUKI_LEFT);
					}
				//左に行きたい
				}else{
					if( path_direction_y == -1){	//下を向いてる							
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x,&path_direction_y,MUKI_RIGHT);
					}else{					//上を向いてる				
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;		
						direction_turn(&path_direction_x,&path_direction_y,MUKI_LEFT);
					}
				}


			}else{											//右か左向きのとき
				//上に行きたい
				if(save_direction.element.up == 1 ){					
					if( path_direction_x == -1){	//左を向いてる							
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x,&path_direction_y,MUKI_RIGHT);
					}else{					//右を向いてる									
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;		
						direction_turn(&path_direction_x,&path_direction_y,MUKI_LEFT);
					}
				//下に行きたい
				}else{
					if( path_direction_x == 1){	//右を向いてる							
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x,&path_direction_y,MUKI_RIGHT);
					}else{					//左を向いてる				
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;		
						direction_turn(&path_direction_x,&path_direction_y,MUKI_LEFT);
					}
				}
			}
			
			count++;	
		}

	
	}
	
	
	path_memory[count].element.distance += 1;	//90mm直進を追加	ゴールに入りきるため
	path_memory[count].element.flag = TRUE;		//終了フラグを建てておく

}

void path::create_path_advance(){
	create_path();
	improve_path();
}

void path::create_path_naname(){
	create_path();
	improve_advance_path();
}

void path::path_reset(){
	unsigned int reset_count;
	for(reset_count=0;reset_count<PATH_MAX;reset_count++){
		path_memory[reset_count].all=0;
	}
	path_memory[PATH_MAX-1].element.flag = 1;
}


unsigned char path::get_path_flag(unsigned int index_number){
	return path_memory[index_number].element.flag;
}

unsigned char path::get_path_straight(unsigned int index_number){
	return path_memory[index_number].element.distance;
}

unsigned char path::get_path_turn_type(unsigned int index_number){
	return path_memory[index_number].element.turn;
}

unsigned char path::get_path_turn_muki(unsigned int index_number){
	return path_memory[index_number].element.muki;
}


float path::calculate_straight_time(int n_mm, int accel_value, int de_accel_value, float max_velocity, float syo_sokudo, float end_velocity){
	float temp_run_time=0.0;	//走行時間をもっとくための変数
	float temp_velocity=0.0;	//速度を計算する用
	int temp_count=0;			//数を数える
	unsigned short temp_distance=0;		//距離をもっとく用の
	
	//初期速度から終端速度まで変化させるためにはどれだけ距離が必要か計算する
	if( syo_sokudo >= end_velocity){
		temp_distance =(int) ( syo_sokudo * syo_sokudo - end_velocity * end_velocity ) / (2 * accel_value);
	}else{
		temp_distance =(int) ( end_velocity * end_velocity - syo_sokudo * syo_sokudo ) / (2 * de_accel_value);
	}
	
	
	//終端速度に近づくだけで終わる場合（加速or減速のみ）
	if( temp_distance >= n_mm ){
		//t=Δv/a
		if( syo_sokudo >= end_velocity){
			temp_run_time = ( syo_sokudo - end_velocity ) / accel_value;
		}else{
			temp_run_time = ( end_velocity - syo_sokudo ) / de_accel_value;
		}
	
	//台形または三角加減速を行う場合
	}else{
		//最高速まで出した時、どのくらい距離が必要か計算する（等速部分はなし）
		temp_distance = ABS( ( max_velocity * max_velocity - syo_sokudo * syo_sokudo ) / (2 * accel_value));
		temp_distance += ABS( ( max_velocity * max_velocity - end_velocity * end_velocity ) / (2 * de_accel_value));
		
		//三角のとき
		if( temp_distance > n_mm ){
			
			for( temp_velocity = syo_sokudo; temp_distance < n_mm; temp_count++){
				temp_velocity = syo_sokudo + ((dt/1000) * accel_value) * temp_count;	//temp_velocity = 初速度＋加速度×時間
		
				//temp_velocityまで出した時、どれほどの距離が必要か計算
				temp_distance = ABS( ( temp_velocity * temp_velocity - syo_sokudo * syo_sokudo ) / (2 * accel_value));
				temp_distance += ABS( ( temp_velocity * temp_velocity - end_velocity * end_velocity ) / (2 * de_accel_value));
			}
			
			temp_run_time += ABS((temp_velocity - syo_sokudo) / accel_value);	//加速にかかる時間
			temp_run_time += ABS((temp_velocity - end_velocity) / accel_value);		//減速にかかる時間
			
		//台形のとき
		}else{
			temp_run_time += ABS((max_velocity - syo_sokudo) / accel_value);	//加速にかかる時間
			temp_run_time += ABS((max_velocity - end_velocity) / accel_value);		//減速にかかる時間
			temp_run_time += (n_mm - temp_distance) / max_velocity;					//等速にかかる時間
			
		}
		
	}
	
	return temp_run_time;
}

float path::calculate_path_time(float path_velocity, unsigned short cal_accel_value, unsigned char run_mode){
	float path_time=0.0;			//path走行にかかる時間
	float temp_velocity=MIN_SPEED;	//マウスの速度
	unsigned short path_count=0;			//配列の番号
	bool naname_flag = false;		//斜め中かどうか判断　TRUEなら斜め走行中
	float end_velocity = 0.0;		//次とその次のターンの速度を保存
	int accel_value=cal_accel_value;	//18000;

	//TODO end_flagがなんのフラグか忘れた　たぶん強制終了用とかだと思う
	for( path_count=0; (path_count < PATH_MAX)/* && (end_flag == FALSE)*/; path_count++ ){

		if( get_path_flag(path_count) == TRUE){		//pathが最後なら終了
			break;
		}
			
			
		//終端速度決定
		switch( path_memory[path_count].element.turn ){
			case 0:	
				//走行終了
				end_velocity = 0;
				break;
			
			case 1:
				//小回りターン
				end_velocity = slalom_turn_90_right.slalom_velocity;
				break;
				
			case 2:	
				//大回りターン
				end_velocity = slalom_big_turn_90_right[run_mode].slalom_velocity;
				break;
			
			case 3:
				//180°ターン
				end_velocity = slalom_big_turn_180_right[run_mode].slalom_velocity;
				break;
					
			case 4:
				//45°ターン
				end_velocity = slalom_turn_45_start_right[run_mode].slalom_velocity;
				break;
			
			case 5:
				//135°ターン
				end_velocity = slalom_turn_135_start_right[run_mode].slalom_velocity;
				break;
				
			case 6:
				//斜め90°ターン
				end_velocity = slalom_turn_90_oblique_right[run_mode].slalom_velocity;
				break;
				
		}
			
			
		//直進にかかる時間を加算
					
		if( !naname_flag){		//斜め走行中ではない
			//直線走行にかかる時間を加算
			path_time += calculate_straight_time(( 45 * MAZE_MODE * (path_memory[path_count].element.distance) ), accel_value, accel_value, path_velocity, temp_velocity, end_velocity);
			temp_velocity = end_velocity;	//ターンには理想の速度で入れているとする
				
		}else{							//斜め走行中である
			//直線走行にかかる時間を加算
			path_time += calculate_straight_time(( 45 * MAZE_MODE * (path_memory[path_count].element.distance) * SQRT2 ), accel_value, accel_value, path_velocity*0.7, temp_velocity, end_velocity);
			temp_velocity = end_velocity;	//ターンには理想の速度で入れているとする
				
		}
			
			
			
		//ターンに応じて時間を加算
		switch( path_memory[path_count].element.turn ){
			case 1:	
				//小回り
				if( path_memory[path_count].element.muki == MUKI_LEFT){
					path_time += slalom_turn_90_left.time;		//左旋回
				}else{
					path_time += slalom_turn_90_right.time;		//右旋回
				}
				break;

			case 2:	
				//大回り
				if( path_memory[path_count].element.muki == MUKI_LEFT){
					path_time += slalom_big_turn_90_left[run_mode].time;		//左旋回
				}else{
					path_time += slalom_big_turn_90_right[run_mode].time;		//右旋回
				}
				break;

			case 3:	
				//180°ターン
				if( path_memory[path_count].element.muki == MUKI_LEFT){
					path_time += slalom_big_turn_180_left[run_mode].time;		//左旋回
				}else{
					path_time += slalom_big_turn_180_right[run_mode].time;		//右旋回
				}
				break;

			case 4:	
				//45°ターン
				if( naname_flag == FALSE ){		//斜め中ではない			
					if( path_memory[path_count].element.muki == MUKI_LEFT){
						path_time +=  slalom_turn_45_start_left[run_mode].time;		//左旋回
					}else{
						path_time +=  slalom_turn_45_start_right[run_mode].time;		//右旋回
					}
					naname_flag = TRUE;
					
				}else{							//斜め中である
					if( path_memory[path_count].element.muki == MUKI_LEFT){
						path_time +=  slalom_turn_45_end_left[run_mode].time;		//左旋回
					}else{
						path_time +=  slalom_turn_45_end_right[run_mode].time;		//右旋回
					}
					naname_flag = TRUE;
				}
				break;

			case 5:	
				//135°ターン
				if( naname_flag == FALSE ){		//斜め中ではない
					if( path_memory[path_count].element.muki == MUKI_LEFT){
						path_time +=  slalom_turn_135_start_left[run_mode].time;		//左旋回
					}else{
						path_time +=  slalom_turn_135_start_right[run_mode].time;		//右旋回
					}
					naname_flag = TRUE;
					
				}else{							//斜め中である
					if( path_memory[path_count].element.muki == MUKI_LEFT){
						path_time +=  slalom_turn_135_end_left[run_mode].time;		//左旋回
					}else{
						path_time +=  slalom_turn_135_end_right[run_mode].time;		//右旋回
					}
					naname_flag = FALSE;
				}
				break;
			case 6:	
				//斜め90°ターン
				if( path_memory[path_count].element.muki == MUKI_LEFT){
					path_time +=  slalom_turn_90_oblique_left[run_mode].time;		//左旋回
				}else{
					path_time +=  slalom_turn_90_oblique_right[run_mode].time;		//右旋回
				}
				break;

			case 7:	
				//
				break;

			}
		}
	
	return path_time;

}


signed char path::create_some_path(JUNCTION junction_[]){
	SAVE_DIRECTION save_direction;				//次に行くマスの方向を保存		
	unsigned short junc_count=0;		//数を数えるだけの変数
	unsigned char temp_direction_count = 0;		//行ける方向がいくつあるか(分岐路かチェック用)
	unsigned short junction_number = 0;			//分岐路の個数を数える用
	unsigned char temp_opposite_count=0;	//歩数に逆らった回数の一時的保存用
	unsigned short create_path_number;		//パスの配列の何番目か管理
	
	path_reset();
	
	path_direction_x = 0;	//方向を初期化
	path_direction_y = 1;
	
	path_x = 0;		//位置を初期化
	path_y = 0;
	
	count_opposite_step = 0;	//リセット
	
	set_step_for_shortest(GOAL_x,GOAL_y);
	
	create_path_number = 0;
	path_memory[create_path_number].element.distance += 1;	//最初は必ず半区画直進する
	
	while(1){
	
		save_direction.all = 0;		//次に行く方向初期化
		
		path_x += path_direction_x; 		//位置修正
		path_y += path_direction_y; 
		
		temp_direction_count = 0;

		if( (path_x == GOAL_x) && (path_y == GOAL_y))	break;	//GOALにたどり着いたら終了
		
		
		
		if( (path_direction_x == 1) && (path_direction_y == 0) ){				//左のマスから来たのであれば何もしない
			save_direction.element.now=3;		//現在向いてる方向だけ記録
		}else{
			if( (path_x - 1) >= 0 ){		//now_x-1,now_yの座標が迷路内(0以上)である
				if( get_wall(path_x,path_y,MUKI_LEFT) == FALSE ){	//壁がないなら
					if( get_step(path_x-1,path_y) != STEP_INIT ){					//歩数が初期化されてない
						save_direction.element.left=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす						
					}
				}
			}
		}
		
		if( (path_direction_x == -1) && (path_direction_y == 0) ){			//右のマスから来たのであれば何もしない
			save_direction.element.now=1;		//現在向いてる方向だけ記録
		}else{
			if( (path_x + 1) < MAZE_SIZE ){	//now_x+1,now_yの座標が迷路内(16未満)である
				if( get_wall(path_x,path_y,MUKI_RIGHT) == FALSE ){	//壁がないなら
					if( get_step(path_x+1,path_y) != STEP_INIT ){				//歩数が初期化されてない
						save_direction.element.right=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす
					}
				}
			}
		}
	
		if( (path_direction_x == 0) && (path_direction_y == -1) ){				//上のマスから来たのであれば何もしない
			save_direction.element.now=2;		//現在向いてる方向だけ記録
		}else{
			if( (path_y + 1) < MAZE_SIZE ){	//now_x,now_y+1の座標が迷路内(16以下)である
				if( get_wall(path_x,path_y,MUKI_UP) == FALSE ){	//壁がないなら
					if( get_step(path_x,path_y+1) != STEP_INIT ){				//歩数が初期化されてない
						save_direction.element.up=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす
					}				
				} 
			}
		}
		
		if( (path_direction_x == 0) && (path_direction_y == 1) ){				//下のマスから来たのであれば何もしない
			save_direction.element.now=0;		//現在向いてる方向だけ記録
		}else{
			if( (path_y - 1) >= 0 ){		//now_x,now_y-1の座標が迷路内(0以上)である
				if( get_wall(path_x,path_y,MUKI_DOWN) == FALSE ){	//壁がないなら
					if( get_step(path_x,path_y-1) != STEP_INIT ){				//歩数が初期化されてない
						save_direction.element.down=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす
						
					}
				}
			}
		}
		/////////////////分岐点チェック////////////////////////////////////////
	
		if( temp_direction_count >= 2 ){	//行ける方向が2以上 ＝ 分岐路のとき
			
			if( save_direction.element.left == 1 ){		//左に行ける場合
				if( get_step(path_x,path_y) <= get_step(path_x-1,path_y) ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.left = 0;		//次に進む方向の選択肢から消去
						temp_direction_count--;				//1減らす				
					}
				}
			}
			if( save_direction.element.right == 1 ){		//右に行ける場合
				if( get_step(path_x,path_y) <= get_step(path_x+1,path_y) ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.right = 0;		//次に進む方向の選択肢から消去
						temp_direction_count--;				//1減らす				
					}
				}
			}
			if( save_direction.element.up == 1 ){		//上に行ける場合
				if( get_step(path_x,path_y) <= get_step(path_x,path_y+1) ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.up = 0;			//次に進む方向の選択肢から消去
						temp_direction_count--;				//1減らす				
					}
				}
			}
			if( save_direction.element.down == 1 ){		//下に行ける場合
				if( get_step(path_x,path_y) <= get_step(path_x,path_x-1) ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.down = 0;		//次に進む方向の選択肢から消去
						temp_direction_count--;				//1減らす				
					}
				}
			}
			
			if( junction[junction_number].all == 0 ){			//まだ何も入ってなければ
				for(junc_count = 0; junction[junc_count].all != 0; junc_count++){		//junctionが終わるまでまわす
					if( (junction[junc_count].element.junction_x == path_x) && (junction[junc_count].element.junction_y == path_y) ){
						return -1;	//既に保存してる分岐路だった場合 -1を返して関数終了
					}
				}
				junction[junction_number].element.junction_x = path_x;						//x座標を記録
				junction[junction_number].element.junction_y = path_y;						//y座標を記録
				junction[junction_number].element.max_direction = temp_direction_count;		//分岐先の個数を記録
				junction[junction_number].element.try_number = 1;							//試行1回目なので1を入れる
			
			}else if( junction[junction_number+1].all == 0 ){	//次に何も入ってない = これが分岐路の最後のとき
				junction[junction_number].element.try_number++;								//試行回数を増やす
			
			}else{												//次に何か入ってるとき
				for(junc_count = (junction_number+1); junction[junc_count].all != 0; junc_count++){		//junctionが終わるまでまわす
					//行ける方向＞試行回数 = まだ行ける方向が残ってるならループ脱出 
					if( junction[junc_count].element.max_direction > junction[junc_count].element.try_number ){
						break;
					}
				}
				junc_count++;		//1つ足す
				if( junction[junc_count].all == 0){		//junctionが終わっている = もう行ける方向が残ってない
					junction[junction_number].element.try_number++;								//試行回数を増やす
					//分岐が変わりルートが変わるので、以後の分岐点をリセット
					for( junc_count = junction_number+1; junction[junc_count].all != 0; junc_count++){
						junction[junc_count].all = 0;
					}							
				}
				
				if( junction[junction_number].element.try_number > junction[junction_number].element.max_direction ){
					return FALSE;
				}	
			}	
			
			//pathを追加する
			if( add_path(save_direction,&create_path_number,junction[junction_number].element.try_number) == FALSE ){
				return -1;		//パス生成できなかったらエラー(-1)を返す
			}	
			
			junction_number++;	//カウントを進める
		
		}else{		//分岐点じゃない時
			
			temp_opposite_count = count_opposite_step;	//歩数に逆らった回数の一時的保存
			//pathを追加する
			add_path(save_direction,&create_path_number,1);	
			count_opposite_step = temp_opposite_count;	//歩数に逆らった回数を戻す　直線時は歩数に逆らうとか考えない。次の分岐点まで行く
			
		}
		
	
	}
	
	path_memory[create_path_number].element.distance += 1;	//90mm直進を追加	ゴールに入りきるため
	
	//improve_path();		//大回りターンを作る
	improve_advance_path();		//大回りターンを作る
	
	return TRUE;
	
}

signed char path::add_path(SAVE_DIRECTION next_direction, unsigned short *path_number, unsigned char priority){
	unsigned char temp_priority = priority;
	SAVE_DIRECTION temp_direction;			//次に行く方向を保存
	
	if( next_direction.element.left == 1 ){		//左に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (path_direction_x == -1) && (path_direction_y == 0) ){		//左を向いてるなら
				path_memory[*path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//左以外の選択肢を消す
				temp_direction.element.left = 1;	//		〃
				add_path_turn(temp_direction,*path_number);	//ターン
				(*path_number)++;
				
			}
			
			if( get_step(path_x,path_y) >= get_step(path_x-1,path_y) ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return TRUE;
		}	
	}
	
	if( next_direction.element.down == 1 ){		//下に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (path_direction_x == 0) && (path_direction_y == -1) ){		//下を向いてるなら
				path_memory[*path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//下以外の選択肢を消す
				temp_direction.element.down = 1;	//		〃
				add_path_turn(temp_direction,*path_number);	//ターン
				(*path_number)++;
			}
			
			if( get_step(path_x,path_y) >= get_step(path_x,path_y-1) ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return TRUE;
		}	
	}
	
	if( next_direction.element.right == 1 ){		//右に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (path_direction_x == 1) && (path_direction_y == 0) ){		//右を向いてるなら
				path_memory[*path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//右以外の選択肢を消す
				temp_direction.element.right = 1;	//		〃
				add_path_turn(temp_direction,*path_number);	//ターン
				(*path_number)++;
			}
			
			if( get_step(path_x,path_y) >= get_step(path_x+1,path_y) ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return TRUE;
		}	
	}
	
	
	if( next_direction.element.up == 1 ){		//上に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (path_direction_x == 0) && (path_direction_y == 1) ){		//上を向いてるなら
				path_memory[*path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//上以外の選択肢を消す
				temp_direction.element.up = 1;	//		〃
				add_path_turn(temp_direction,*path_number);	//ターン
				(*path_number)++;
			}
			
			if( get_step(path_x,path_y) >= get_step(path_x,path_y+1) ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return TRUE;
		}	
	}
	
	//ここまでたどり着いたということはパスが生成できてないので、OFFを返す
	return FALSE;
}

void path::add_path_turn(SAVE_DIRECTION next_direction, unsigned short path_number){
	
	if( next_direction.element.right == 1 ){		//行きたい方向が右のとき
			if( path_direction_y == 1 )	path_memory[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else						path_memory[path_number].element.muki = MUKI_LEFT;		//左向き回転
	
	}else if( next_direction.element.left == 1 ){	//行きたい方向が左のとき
			if( path_direction_y == -1 )	path_memory[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else							path_memory[path_number].element.muki = MUKI_LEFT;		//左向き回転
	
	}else if( next_direction.element.down == 1 ){	//行きたい方向が下のとき
			if( path_direction_x == 1 )	path_memory[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else						path_memory[path_number].element.muki = MUKI_LEFT;		//左向き回転
		
	}else if( next_direction.element.up == 1 ){		//行きたい方向が上のとき
			if( path_direction_x == -1 )	path_memory[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else							path_memory[path_number].element.muki = MUKI_LEFT;		//左向き回転
	}	
	
	direction_turn(&path_direction_x,&path_direction_y,path_memory[path_number].element.muki);		//directionを更新
	
	path_memory[path_number].element.turn = 1;				//小回りターン
	
	return;


}


void path::selection_root(float path_velocity, unsigned short path_accel,unsigned char run_mode){
	unsigned long try_count=0;	//試行回数をカウントする変数
	unsigned long fast_path=0;	//最も速い走行をした試行回数を記録する変数
	float temp_time=0.0;			//パスの走行にどれだけかかるかを保存する変数
	float fast_time=100.0;			//パスの走行にかかった時間のうち最短の時間を保存する変数
	signed char roop_flag = TRUE;
	
	//初期化
	for(int i=0; i < JUNCTION_MAX; i++){
		junction[i].all = 0;
	}
	
	//まず1回パスを作る
	roop_flag = create_some_path(junction);		//create_some_pathはパス生成できないとOFFを返すので,そうするとループを抜ける
	
	for( try_count = 0; roop_flag != FALSE ; try_count++){			
		if( roop_flag == -1 ){		//パス生成できなかったときは計算しない
			//何もしない
		}else{
			temp_time = calculate_path_time(path_velocity,path_accel,1);//生成したパスの時間を計算
			if( temp_time < fast_time ){			//今までのパスと比べ、はやいのかチェック
				//速ければ、try_countを記録し時間を更新
				fast_path = try_count;
				fast_time = temp_time;
			}
		}

		roop_flag = create_some_path(junction);		//create_some_pathはパス生成できないとOFFを返すので,そうするとループを抜ける
	}
		
	//junctionをリセット
	for(int i = 0; i < JUNCTION_MAX; i++){
		junction[i].all = 0;
	}
	
	//try_countまで上のループをもう一度まわして、目的のパスを取得
	for( try_count = 0; try_count < fast_path; try_count++){
		create_some_path(junction);		//パス生成
	}
	
	//1回足りない分、生成して終わり
	create_some_path(junction);		//パス生成

}

void direction_turn(signed char *direction_x,signed char *direction_y, unsigned char direction_turn_muki){
	signed char temp_direction_x = (*direction_x);		//他の場所に保存しないと変換途中で参照する羽目になる 
	signed char temp_direction_y = (*direction_y);
	if(direction_turn_muki == MUKI_LEFT){
		*direction_x = (temp_direction_x)*0 + (temp_direction_y)*(-1);		//回転行列のθ=90の計算
		*direction_y = (temp_direction_x)*1 + (temp_direction_y)*0;		//回転行列のθ=90の計算
	}else{
		*direction_x = (temp_direction_x)*0 + (temp_direction_y)*1;		//回転行列のθ=-90の計算
		*direction_y = (temp_direction_x)*(-1) + (temp_direction_y)*0;		//回転行列のθ=-90の計算		
	}

}		


unsigned char status::get_direction(){
	if( now_direction_x == 1){
		return MUKI_RIGHT;
	}else if( now_direction_x == -1 ){
		return MUKI_LEFT;
	}
	
	if( now_direction_y == 1){
		return MUKI_UP;
	}else if( now_direction_y == -1 ){
		return MUKI_DOWN;
	}

	return 255;	//	エラー
}

void status::set_direction(unsigned char muki){
	switch(muki){

	case MUKI_UP:
		now_direction_x = 0;
		now_direction_y = 1;
		break;

	case MUKI_DOWN:
		now_direction_x = 0;
		now_direction_y = -1;
		break;

	case MUKI_RIGHT:
		now_direction_x = 1;
		now_direction_y = 0;
		break;

	case MUKI_LEFT:
		now_direction_x = -1;
		now_direction_y = 0;
		break;

	}
}

unsigned char status::get_x_position(){
	return now_x;
}

unsigned char status::get_y_position(){
	return now_y;
}

void status::set_position(unsigned char set_x,unsigned char set_y){
	now_x = set_x;
	now_y = set_y;
}

status::status(){
	set_position(0,0);		//初期座標を(0,0)に
	set_direction(MUKI_UP);	//初期の向きは上向きに
}

status::status(unsigned char set_x, unsigned char set_y, unsigned char muki){
	set_position(set_x,set_y);		//座標をあわせる
	set_direction(muki);			//向きをあわせる
}

status::~status(){
}