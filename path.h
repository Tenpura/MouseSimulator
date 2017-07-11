#ifndef DEF_PATH_H
#define DEF_PATH_H

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

void add_path_turn(SAVE_DIRECTION next_direction, unsigned char path_number);		//次の進行マスの方向といくつ目のpathかを与えるとpathのターン部分(向きと小回り)を書き込む

signed char add_path(SAVE_DIRECTION next_direction, unsigned char path_number, unsigned char priority);	//いくつ目のpathかと優先度(選択肢の何番目を選択するのか）を与えるとpathを追加する
//優先度はleft->down->right->upの順とする
//パス生成できるとON、できないとOFFを返す

void create_path();				//path生成、歩数が同じなら直進優先。小回りターンのみ

signed char create_some_path(JUNCTION *junction);
//経路選択ようのpath生成。分岐点の配列を与えるとそれに応じたpath生成,分岐点の配列は繰り返し使用したいため引数として渡す（グローバルの代わり）。　
//pathが生成できた場合ONを、すべて網羅した場合OFFを返す。パスを生成できなかった場合(円環)-1を返す。

void close_dead_end(char target_x, char target_y);			//目標の(x,y)が袋小路か確かめて、袋小路なら閉じる関数　閉じた場合再起処理に入る

void create_map_for_shortest_close_dead_end(char target_x,char target_y);	//最短用歩数マップ生成。未探索区間を省き袋小路をふさぐ

float calculate_run_time(int n_mm, int accel_value, int de_accel_value, float max_velocity, float syo_sokudo, float end_velocity);	//台形加減速で走行したときの、走行時間を求める関数
//引数　n_mm:目標距離[mm]	accel_value:加速度[mm/s/s]	de_accel_value:減速度[mm/s/s]	
//		max_velcoty:最高速度[mm/s]	start_velocity:初速度[mm/s]	end_velocity:終端速度[mm/s]

float calculate_path_time(float path_velocity, unsigned char run_mode);		//今あるpathの走行時間を計算する。引数として最高速とターンのモードを与えると、時間を返す。

void selection_root(float path_velocity, unsigned char run_mode);			//最短経路選択　何回か歩数マップに逆らう

void improve_path();			//pathに大回りターンとか追加

void improve_advance_path();	//pathに大回りターンと斜めを追加

void run_by_path(float path_velocity, unsigned char run_mode);	//どのくらいの速度で走るのかを指定すると、pathどおりに走る modeが上がるほどターン速度UP

void displace_path(unsigned int path_number);	//path_number目の要素を消去して、一個ずつ詰める
	
void path_reset();				//pathをリセット

void auto_start();				//オートスタート用

#endif