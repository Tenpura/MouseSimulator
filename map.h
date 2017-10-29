/*
 * map.h
 *
 *  Created on: 2015/06/05
 *      Author: Koizumi
 */

#ifndef INCLUDED_MAP
#define INCLUDED_MAP

#include<stdint.h>
#include"iodefine.h"
#include"define.h"
//#include"extern_c.h"
#include <queue>
#include <array>


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

extern int g_sum_queue_size_cell;		//キューサイズの最大を管理（マスに歩数を置く方用）
extern int g_mouse_x, g_mouse_y;		//マウスの座標

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
	void convert_mapdata(unsigned char (*hiramatu_data)[32]);		//平松先輩のマップデータ形式をノノホ式に変換
	unsigned char output_Hiramatu(int x, int y);					//(x,y)マスの壁情報を平松形式で出力

	void input_map_data(MAP_DATA *input_data);			//外部に保存したデータの入力
	void output_map_data(MAP_DATA *output_data);		//外部にデータ出力

	void init_map(int maze_size);	//maze_wallの初期化
	
	map();
	map(int maze_size);	
	~map();


};




#define STEP_INIT 9999		//歩数の初期値

typedef struct {
	uint8_t x;
	uint8_t y;
} MAZE_GOAL;


class step:public map{
//追加部分
private:
	float node_step[2 * MAZE_SIZE][MAZE_SIZE];	//ノード単位で歩数記録　X方向に倍になってる　区画境界は横と縦の2つあるから
	//node_step[0][0]が(0,0)の北、node_step[1][0]が(0,0)の東
	void set_step_adachi(MAZE_GOAL *target);		//Goalを配列で指定すると足立法する
	

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
	unsigned int simple_step[MAZE_SIZE][MAZE_SIZE];
	unsigned int head,tail;		//
	unsigned char x_coordinate[1965];//キューの座標を管理するための配列
	unsigned char y_coordinate[1965];//キューの座標を管理するための配列
	
	void step_reset();
	void step_reset_all_search();
	void close_one_dead_end(unsigned char target_x, unsigned char target_y);


public:
	void set_step(unsigned char target_x,unsigned char target_y);			//target_x,yを基準に歩数マップ作製(等高線)
	void set_step_by_known(unsigned char target_x,unsigned char target_y);	//見ていない壁は、壁があると見なす
	void set_step_all_search(unsigned char target_x,unsigned char target_y);//不完全全面探査用歩数マップ作製

	unsigned int get_step(unsigned char target_x,unsigned char target_y);	//ある座標(x,y)の歩数を返す

	void close_dead_end();		//マップ上の袋小路をつぶす


	step();
	~step();

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

class path:public step{
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



typedef enum {
	east=0, west=1, north=2, south=3, num 
} compas;

class node_step :public map{
private:
	std::vector<PATH> path;		
	static const uint16_t x_size=64;
	static const uint16_t y_size=32;
	static uint16_t step[x_size][y_size];			//ノードに配置する歩数	x,y xは横壁と縦壁の両方を表現するために2倍	[0][0]は(0,0)の西壁
	virtual bool able_set_step(uint8_t x, uint8_t y, compas muki, uint16_t step_val, bool by_known);	//歩を伸ばせるならTrue　壁がないか、その壁を見ているのか、step_valより歩数が大きいかチェック
	bool is_outside_array(uint8_t x_index, uint8_t y_index);		//配列の添え字でみた座標系（X方向だけ倍）で迷路外（配列外）に出ているか

public:
	static const uint16_t init_step = 60000;
	virtual bool set_step(uint8_t x, uint8_t y, compas muki, uint16_t step_val, bool by_known);
	uint16_t get_step(uint8_t x, uint8_t y, compas muki);
	compas get_min_compas(uint8_t x, uint8_t y);			//（x,y）の4つの歩数の内、最小の歩数がどの方角か
	compas get_max_compas(uint8_t x, uint8_t y);			//（x,y）の4つの歩数の内、最小の歩数がどの方角か

	void reset_step(uint16_t reset_val);		//全ての歩数をreset_valでリセット

	uint8_t compas_to_define(compas muki);			//列挙型のcompasをDefineされたMUKIに変換する　統一できてないから仕方なく

	node_step();
	node_step(uint16_t reset_val);
	~node_step();
};

typedef struct {
	uint8_t distance;
	SLALOM_TYPE turn;
	bool is_right;	//ターンが右か？

}  path_element;

class node_path :virtual public node_step {
private:
	static std::vector<path_element> path;

	static PATH to_PATH(path_element from);
	bool is_right_turn(compas now, compas next);		//次のターンが右向きならtrue
	static void push_straight(int half);	//何半区間進むか
	static void push_small_turn(bool is_right);		//小回りでどちらに曲がるか

public:
	static void format();
	static PATH get_path(uint16_t index);	//PATHを直接返す

protected:	//歩数をひいてから実行するのを前提としているので外部アクセス禁止にしておく
	bool create_path(std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//initマスの中心からfinishマスの中心までのPath　道がふさがってたらFasle
	//mouse_direction が引数になっている理由
	//基本的には最短走行か既知区間加速で使うので歩数の小さい方が今行くべき方向と一致しているが、最小歩数が複数あるとヤバいので最初の向きを要求している
	void improve_path();		//既存のPathを大回り斜めに変更

public:
	node_path();
	~node_path();

};

extern int g_need_queue_size;
extern uint32_t g_sum_queue_size_node;

typedef enum {
	adachi, based_distance, priority_straight,T_Wataru_method
} weight_algo;

class node_search :virtual public node_step, virtual public  node_path {
private:
	bool set_step_double(uint8_t double_x, uint8_t double_y, uint16_t step_val, bool by_known);	//XY方向両方に倍取った座標軸での歩数代入関数
	bool set_step_double(std::pair<uint8_t, uint8_t> xy, uint16_t step_val, bool by_known);		//XY方向両方に倍取った座標軸での歩数代入関数
	uint16_t get_step_double(uint8_t double_x, uint8_t double_y);		//2倍座標系から歩数を取り出す
	weight_algo algo;		//重みづけの方法を管理する

public:
	void set_weight_algo(weight_algo weight);		//歩数マップの重みづけを変更する
	weight_algo get_weight_algo();

	//set_weight_algoで指定された重みづけに従って歩数を敷き詰める
	void spread_step(std::vector< std::pair<uint8_t, uint8_t> > finish, bool by_known);		//複数マスゴール対応　もちろん1マスでもおｋ

	bool create_small_path(std::vector< std::pair<uint8_t, uint8_t> > finish, std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//initマスの中心からfinishマスの中心までのPath　道がふさがってたらFasle
	//mouse_direction が引数になっている理由
	//基本的には最短走行か既知区間加速で使うので歩数の小さい方が今行くべき方向と一致しているが、最小歩数が複数あるとヤバいので最初の向きを要求している
	bool create_big_path(std::vector< std::pair<uint8_t, uint8_t> > finish, std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//大回りパス作製


	node_search();
	node_search(uint16_t init_step);
	~node_search();

};


int cal_Manhattan(int _dx, int _dy);	//マンハッタン距離を計算


#endif /* MAP_H_ */
