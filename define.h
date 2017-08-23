/*
 * define.h
 *
 *  Created on: 2015/06/02
 *      Author: Koizumi
 */


#ifndef DEFINE_H_
#define DEFINE_H_

//同じ機体を使ってる限り変わらないdefineはココに書く

#define MAZE_MODE	1	//ハーフorクラシック。ハーフなら1,クラシックなら2

#define MAZE_SIZE	32
#define PATH_MAX	1024
#define JUNCTION_MAX 1024		//最大いくつ分岐点があると考えるか
#define ALLOW_OPPOSITE_STEP  99	//時間ベース経路探索で何回まで歩数に逆らってよいか

#define GOAL_x	7
#define GOAL_y	7

#define myprintf	//

#define MIN_SPEED 500	//最低速度[mm/s]








////////////////////////////////////////////////////////////////////////////////////////////
//定義ゾーン
#define PI		3.1415		//π　円周率

#define dt	1					//微小時間[ms]

//便利ゾーン/////////////////////////////////////////////////////////////////////////////////////////////////////
#define SQRT2 1.414	//√2

#define ABS(x)		((x) < 0 ? -(x) : (x))	//絶対値
#define	SINGN(x)	((x) < 0 ? -1 : 1 )		//符合
#define	MAX(a,b)	((a) > (b) ? (a) : (b))	//最大値
#define	MIN(a,b)	((a) < (b) ? (a) : (b))	//最小値



//疑似真偽値
#define ON	1
#define OFF	0
#define TRUE	1
#define FALSE	0

#define MUKI_RIGHT	0
#define MUKI_LEFT	1
#define MUKI_UP		2
#define MUKI_DOWN	3

//スイッチ。押すとtrue,離すとfalse
#define SWITCH_LEFT (1-PORT7.PORT.BIT.B5)
#define SWITCH_RIGHT (1-PORT7.PORT.BIT.B6)




typedef union{
	//unsigned char all;				//一括
	struct {
		unsigned char	semiton	:2;			//半音あげるか下げるかを表す	また曲のおわりも示す(ここがMELODY_ENDのとき終わり)
		unsigned char	octave	:1;			//オクターブを1つあげるかどうか
		unsigned char	beat	:2;			//拍数を表す
		unsigned char	scale	:3;			//音階を表す　0←ドレミファソラシ休→7
	} bit;

} MELODY;


typedef struct{
	volatile char muki;						//向き
	volatile float slalom_velocity;			//重心速度
	volatile float slalom_target_angle;		//何度のターンをするのか
	volatile float slalom_clothoid_angle;	//何度までクロソイドするのか
	volatile float before_distance;			//前距離[mm]
	volatile float after_distance;			//後距離[mm]
	volatile float slalom_accel_value;		//加速度を求めるための定数
	volatile float time;					//どれだけ時間がかかるのか[s]
} init_slalom;

typedef union {
	unsigned short all;					//一括で見る
	struct{
		unsigned char 			:3;		//
		unsigned char flag		:1;		//配列の最後かチェック用
		unsigned char turn		:3;		//ターンの種類を判別
		unsigned char muki		:1;		//ターンの方向を判別	
		unsigned char distance	:8;		//直進する距離を判別
	}	element;
} PATH;
	
//スラモームの種類
typedef enum {
	none = 0,
	s_small = 1,
	big_90 = 2,
	big_180 = 3,
	begin_45 = 4,
	end_45 = 5,
	begin_135 = 6,
	end_135 = 7,
	oblique_90 = 8,
	spin_turn = 9,
	slalom_type_count		//要素数を表す
} SLALOM_TYPE;
		
	
	
#endif /* DEFINE_H_ */
