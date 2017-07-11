/*
 * map.h
 *
 *  Created on: 2015/06/05
 *      Author: Koizumi
 */

#ifndef INCLUDED_MAP
#define INCLUDED_MAP

#include"iodefine.h"
#include"define.h"
//#include"extern_c.h"


extern init_slalom slalom_turn_90_right;		//90°右回転スラローム
extern init_slalom slalom_turn_90_left;			//90°左回転スラローム
extern init_slalom slalom_turn_90_right_shortest;		//90°右回転スラローム	最短用
extern init_slalom slalom_turn_90_left_shortest;		//90°左回転スラローム　最短用
extern init_slalom slalom_big_turn_90_left[2];		//90°左回転大回りスラローム
extern init_slalom slalom_big_turn_90_right[2];	//90°右回転大回りスラローム
extern init_slalom slalom_turn_135_start_left[2];		//90°左回転大回りスラローム
extern init_slalom slalom_turn_135_start_right[2];	//90°右回転大回りスラローム
extern init_slalom slalom_turn_135_end_left[2];		//90°左回転大回りスラローム
extern init_slalom slalom_turn_135_end_right[2];	//90°右回転大回りスラローム
extern init_slalom slalom_turn_45_start_left[2];		//90°左回転大回りスラローム
extern init_slalom slalom_turn_45_start_right[2];	//90°右回転大回りスラローム
extern init_slalom slalom_turn_45_end_left[2];		//90°左回転大回りスラローム
extern init_slalom slalom_turn_45_end_right[2];	//90°右回転大回りスラローム
extern init_slalom slalom_turn_90_oblique_left[2];		//90°左回転大回りスラローム
extern init_slalom slalom_turn_90_oblique_right[2];		//90°右回転大回りスラローム
extern init_slalom slalom_big_turn_180_left[2];	//180°左回転大回りスラローム
extern init_slalom slalom_big_turn_180_right[2];	//180°右回転大回りスラローム

typedef union {
	unsigned long all;		//全て一括で変更する用
	struct {
		unsigned short high	:16;
		unsigned short low	:16;
	}SHORT;
	struct {
		//trueなら壁が存在、falseなら存在しない
		unsigned char B0 :1;		//x座標0と1の間の壁　or　y座標0と1の間の壁
		unsigned char B1 :1;
		unsigned char B2 :1;
		unsigned char B3 :1;
		unsigned char B4 :1;
		unsigned char B5 :1;
		unsigned char B6 :1;
		unsigned char B7 :1;
		unsigned char B8 :1;
		unsigned char B9 :1;
		unsigned char B10 :1;
		unsigned char B11 :1;
		unsigned char B12 :1;
		unsigned char B13 :1;
		unsigned char B14 :1;
		unsigned char B15 :1;
		unsigned char B16 :1;		//x座標0と1の間の壁　or　y座標0と1の間の壁
		unsigned char B17 :1;
		unsigned char B18 :1;
		unsigned char B19 :1;
		unsigned char B20 :1;
		unsigned char B21 :1;
		unsigned char B22 :1;
		unsigned char B23 :1;
		unsigned char B24 :1;
		unsigned char B25 :1;
		unsigned char B26 :1;
		unsigned char B27 :1;
		unsigned char B28 :1;
		unsigned char B29 :1;
		unsigned char B30 :1;
		unsigned char B31 :1;

	}bit;
} MAZE_WALL;

typedef struct{
	MAZE_WALL x_wall[MAZE_SIZE],y_wall[MAZE_SIZE];	//壁情報保存用
	MAZE_WALL x_known[MAZE_SIZE],y_known[MAZE_SIZE];	//壁情報を見たかどうか判別用
} MAP_DATA;

class map {

//メンバ変数
private:
	//unsigned char x,y;//座標
	MAZE_WALL x_maze_wall[MAZE_SIZE],y_maze_wall[MAZE_SIZE];	//壁情報保存用
	MAZE_WALL x_wall_exist[MAZE_SIZE],y_wall_exist[MAZE_SIZE];	//壁情報を見たかどうか判別用

	void set_maze_wall(MAZE_WALL *maze_wall,unsigned char edit_number,unsigned char set_number);//maze_wallに値を代入する用
	unsigned char get_maze_wall(MAZE_WALL maze_wall,unsigned char edit_number);					//maze_wallの値を読む用

public:
	void create_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);		//(x,y)のmuki方向の壁を作る
	void destroy_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	unsigned char get_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);		//壁があればTRUE、なければFALSE

	void remember_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);		//(x,y)のmuki方向の壁を作る
	void forget_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	unsigned char check_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);	//既に見ていればTRUE、見てなければFALSE

	void draw_map();		//myprintfで迷路を描画
	void convert_mapdata(unsigned char (*hiramatu_data)[16]);		//平松先輩のマップデータ形式をノノホ式に変換
	unsigned char output_Hiramatu(int x, int y);					//(x,y)マスの壁情報を平松形式で出力

	void input_map_data(MAP_DATA *input_data);			//外部に保存したデータの入力
	void output_map_data(MAP_DATA *output_data);		//外部にデータ出力

	void init_map(int maze_size);	//maze_wallの初期化
	
	map();
	map(int maze_size);	
	~map();


};





#define STEP_INIT 1024		//歩数の初期値


class adachi:public map{
private:
	union {
		unsigned char all;				//一括
		struct {
			unsigned char 		:4;		//
		//	unsigned char now	:2;		//現在の方向を管理、この数、save_directionをビットシフトすると現在の向きに対応	
			unsigned char up	:1;		//↑	x=0,y=1の方向
			unsigned char down	:1;		//↓	x=0,y=-1の方向
			unsigned char left	:1;		//←	x=-1,y=0の方向
			unsigned char right	:1;		//→	x=1,y=0の方向
		} element;
	}save_direction;				//次に行くマスの方向を保存		
	unsigned int step[MAZE_SIZE][MAZE_SIZE];
	unsigned int head,tail;		//
	unsigned char x_coordinate[965];//キューの座標を管理するための配列
	unsigned char y_coordinate[965];//キューの座標を管理するための配列
	
	void step_reset();
	void step_reset_all_search();
	void close_one_dead_end(unsigned char target_x, unsigned char target_y);


public:
	void set_step(unsigned char target_x,unsigned char target_y);			//target_x,yを基準に歩数マップ作製(等高線)
	void set_step_by_known(unsigned char target_x,unsigned char target_y);	//見ていない壁は、壁があると見なす
	void set_step_all_search(unsigned char target_x,unsigned char target_y);//不完全全面探査用歩数マップ作製

	unsigned int get_step(unsigned char target_x,unsigned char target_y);	//ある座標(x,y)の歩数を返す

	void close_dead_end();		//マップ上の袋小路をつぶす


	adachi();
	~adachi();

};


typedef union {
		unsigned short all;				//一括
		struct {
			unsigned char					:2;
			unsigned char	junction_y		:5;		//この分岐路のy座標
			unsigned char	junction_x		:5;		//この分岐路のx座標		
			unsigned char	max_direction	:2;		//何方向へ行けるのか
			unsigned char	try_number		:2;		//この分岐路の何番目の方向を選ぶのか
		} element;
} JUNCTION;				//分岐路を保存		

class path:public adachi{
private:
	typedef union {
		unsigned char all;				//一括
		struct {
			unsigned char up	:1;		//→	x=1,y=0の方向
			unsigned char right	:1;		//←	x=-1,y=0の方向
			unsigned char down	:1;		//↓	x=0,y=-1の方向
			unsigned char left	:1;		//↑	x=0,y=1の方向
			unsigned char now	:4;		//現在の方向を管理、この数、save_directionをビットシフトすると現在の向きに対応	
		} element;
	}SAVE_DIRECTION;				//次に行くマスの方向を保存
	PATH path_memory[PATH_MAX];
	unsigned char path_x,path_y;						//位置管理用
	signed char path_direction_x,path_direction_y;		//方向管理用
	
	
	void set_step_for_shortest(unsigned char target_x,unsigned char target_y);		//最短用の歩数マップ作製
	void displace_path(unsigned int path_number);	//path_number目のpathを消してからpathを一個ずらす
	
	void improve_path();			//小回りだけのpathに大回りを追加
	void improve_advance_path();	//小回りだけのpathに大回りと斜めを追加

	
public:
	void create_path();				//小回りだけのパス
	void create_path_advance();		//大回りを追加したパス(ナナメはナシ)
	void create_path_naname();		//大回りとナナメを追加したパス

	void path_reset();


	unsigned char get_path_flag(unsigned int index_number);
	unsigned char get_path_straight(unsigned int index_number);
	unsigned char get_path_turn_type(unsigned int index_number);
	unsigned char get_path_turn_muki(unsigned int index_number);

//ココより下は要検討　実機にはまだ早い
private:
	JUNCTION junction[JUNCTION_MAX];	//分岐点保存用配列
	signed char end_flag;
	signed char count_opposite_step;		//何回歩数に逆らうか
	float calculate_straight_time(int n_mm, int accel_value, int de_accel_value, float max_velocity, float syo_sokudo, float end_velocity);	//台形加減速で走行したときの、走行時間を求める関数
	//引数　n_mm:目標距離[mm]	accel_value:加速度[mm/s/s]	de_accel_value:減速度[mm/s/s]	
	//		max_velcoty:最高速度[mm/s]	start_velocity:初速度[mm/s]	end_velocity:終端速度[mm/s]
	signed char create_some_path(JUNCTION junction_[]);
	//経路選択ようのpath生成。分岐点の配列を与えるとそれに応じたpath生成,分岐点の配列は繰り返し使用したいため引数として渡す（グローバルの代わり）。　
	//pathが生成できた場合ONを、すべて網羅した場合OFFを返す。パスを生成できなかった場合(円環)-1を返す。
	signed char add_path(SAVE_DIRECTION next_direction, unsigned short *path_number, unsigned char priority);	//いくつ目のpathかと優先度(選択肢の何番目を選択するのか）を与えるとpathを追加する
	//優先度はleft->down->right->upの順とする
	//パス生成できるとTRUE、できないとFALSEを返す
	void add_path_turn(SAVE_DIRECTION next_direction, unsigned short path_number);		//次の進行マスの方向といくつ目のpathかを与えるとpathのターン部分(向きと小回り)を書き込む

public:
	void selection_root(float path_velocity, unsigned short path_accel, unsigned char run_mode);			//最短経路選択　何回か歩数マップに逆らう
	
	float calculate_path_time(float path_velocity, unsigned short cal_accel_value, unsigned char run_mode);
	//今あるpathの走行時間を計算する。引数として最高速と加速度[mm/s^2]とターンのモードを与えると、時間を返す。
	

};


//方向成分と回転する向きを与えると、機体の向きを90°そちらへ変える
void direction_turn(signed char *direction_x,signed char *direction_y, unsigned char direction_turn_muki);		




//現在座標、機体の向き、速度、角速度、加速度、角加速度
class status{
private:
	float velocity,velocity_right,velocity_left,accel;
	float angular_velocity,angular_accel;
	unsigned char now_x,now_y;
	signed char now_direction_x,now_direction_y;


public:


	unsigned char get_direction();
	void set_direction(unsigned char muki);

	unsigned char get_x_position();
	unsigned char get_y_position();
	void set_position(unsigned char set_x,unsigned char set_y);

	
	status();		//デフォルトは(0，0)の上向き
	status(unsigned char set_x,unsigned char set_y,unsigned char set_muki);
	~status();

};


#endif /* MAP_H_ */
