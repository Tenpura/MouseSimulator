#include <stdio.h>
#include "user.h"
#include "define.h"
#include "path.h"

unsigned char create_path_number=0;		//path使用時にpathの配列番号を表す。

void add_path_turn(SAVE_DIRECTION next_direction, unsigned char path_number){	//次の進行マスの方向を与えるとパスを書き込む
	
	if( next_direction.element.right == 1 ){		//行きたい方向が右のとき
			if( direction_y == 1 )	path[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else					path[path_number].element.muki = MUKI_LEFT;		//左向き回転
	
	}else if( next_direction.element.left == 1 ){	//行きたい方向が左のとき
			if( direction_y == -1 )	path[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else					path[path_number].element.muki = MUKI_LEFT;		//左向き回転
	
	}else if( next_direction.element.down == 1 ){	//行きたい方向が下のとき
			if( direction_x == 1 )	path[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else					path[path_number].element.muki = MUKI_LEFT;		//左向き回転
		
	}else if( next_direction.element.up == 1 ){		//行きたい方向が上のとき
			if( direction_x == -1 )	path[path_number].element.muki = MUKI_RIGHT;	//右向き回転
			else					path[path_number].element.muki = MUKI_LEFT;		//左向き回転
	}	
	
	direction_turn(path[path_number].element.muki);		//directionを更新
	
	path[path_number].element.turn = 1;				//小回りターン
	
	return;
}

signed char add_path(SAVE_DIRECTION next_direction, unsigned char path_number, unsigned char priority){
	unsigned char temp_priority = priority;
	SAVE_DIRECTION temp_direction;			//次に行く方向を保存
	
	if( next_direction.element.left == 1 ){		//左に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (direction_x == -1) && (direction_y == 0) ){		//左を向いてるなら
				path[create_path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//左以外の選択肢を消す
				temp_direction.element.left = 1;	//		〃
				add_path_turn(temp_direction,create_path_number);	//ターン
				create_path_number++;
				
			}
			
			if( step[now_x][now_y] >= step[now_x-1][now_y] ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return ON;
		}	
	}
	
	if( next_direction.element.down == 1 ){		//下に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (direction_x == 0) && (direction_y == -1) ){		//下を向いてるなら
				path[create_path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//下以外の選択肢を消す
				temp_direction.element.down = 1;	//		〃
				add_path_turn(temp_direction,create_path_number);	//ターン
				create_path_number++;
			}
			
			if( step[now_x][now_y] >= step[now_x][now_y-1] ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return ON;
		}	
	}
	
	if( next_direction.element.right == 1 ){		//右に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (direction_x == 1) && (direction_y == 0) ){		//右を向いてるなら
				path[create_path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//右以外の選択肢を消す
				temp_direction.element.right = 1;	//		〃
				add_path_turn(temp_direction,create_path_number);	//ターン
				create_path_number++;
			}
			
			if( step[now_x][now_y] >= step[now_x+1][now_y] ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return ON;
		}	
	}
	
	
	if( next_direction.element.up == 1 ){		//上に行けるとき
		temp_priority--;	//優先度を下げる
		if( temp_priority == 0){		//優先度が0になったらそれをパスにする
			if( (direction_x == 0) && (direction_y == 1) ){		//上を向いてるなら
				path[create_path_number].element.distance += 2;	//180mm直進を追加
				
			}else{												//他の方向を向いてるなら
				temp_direction.all = 0;				//上以外の選択肢を消す
				temp_direction.element.up = 1;	//		〃
				add_path_turn(temp_direction,create_path_number);	//ターン
				create_path_number++;
			}
			
			if( step[now_x][now_y] >= step[now_x][now_y+1] ){				//歩数マップに逆らうなら
				count_opposite_step++;	//逆らった記憶をつける
			}
			return ON;
		}	
	}
	
	//ここまでたどり着いたということはパスが生成できてないので、OFFを返す
	return OFF;
}

void create_path(){
	char tekitou;
	SAVE_DIRECTION save_direction;				//次に行くマスの方向を保存		
	unsigned char count=0;	//数を数えるだけの変数
	
	path_reset();

	direction_x = 0;	//方向を初期化
	direction_y = 1;
	
	now_x = 0;		//位置を初期化
	now_y = 0;
	
	create_map_for_shortest_close_dead_end(GOAL_x,GOAL_y);
	
	path[count].element.distance += 1;	//最初は必ず半区画直進する
	
	while(1){
	
		save_direction.all = 0;		//次に行く方向初期化
		
		now_x = now_x + direction_x; 		//位置修正
		now_y = now_y + direction_y; 
		
		if( (now_x == GOAL_x) && (now_y == GOAL_y))	break;	//GOALにたどり着いたら終了

		
		if( (now_x - 1) >= 0 ){		//now_x-1,now_yの座標が迷路内(0以上)である
			if( step[now_x-1][now_y] == (step[now_x][now_y] - 1) ){				//歩数の小さいほうへ
				if( (map[now_x-1][now_y].known.right == 0) && (map[now_x][now_y].known.left == 0) ){	//壁がないなら
					save_direction.element.left=1;		//次に進む方向の選択肢に追加
				}
			}
			
		}
	
		if( (now_x + 1) < MAX_x ){	//now_x+1,now_yの座標が迷路内(16未満)である
			if( step[now_x+1][now_y] == (step[now_x][now_y] - 1) ){				//歩数の小さいほうへ
				if( (map[now_x+1][now_y].known.left == 0) && (map[now_x][now_y].known.right == 0) ){	//壁がないなら
					save_direction.element.right=1;		//次に進む方向の選択肢に追加
				}
			}
		}
	
		if( (now_y - 1) >= 0 ){		//now_x,now_y-1の座標が迷路内(0以上)である
			if( step[now_x][now_y-1] == (step[now_x][now_y] - 1) ){				//歩数の小さいほうへ
				if( (map[now_x][now_y-1].known.up == 0) && (map[now_x][now_y].known.down == 0) ){	//壁がないなら
					save_direction.element.down=1;		//次に進む方向の選択肢に追加
				}
			}
		}
	
		if( (now_y + 1) < MAX_y ){	//now_x,now_y+1の座標が迷路内(16以下)である
			if( step[now_x][now_y+1] == (step[now_x][now_y] - 1) ){				//歩数の小さいほうへ
				if( (map[now_x][now_y+1].known.down == 0) && (map[now_x][now_y].known.up == 0) ){	//壁がないなら
					save_direction.element.up=1;		//次に進む方向の選択肢に追加
				}				
			} 
		}
		
		//現在向いてる方向を判別
		if( (direction_x == 1) && (direction_y == 0) ){
			save_direction.element.now=2;	//右 2^1
		}else if( (direction_x == -1) && (direction_y == 0) ){
			save_direction.element.now=8;	//左 2^3
		}else if( (direction_x == 0) && (direction_y == -1) ){
			save_direction.element.now=4;	//下 2^2
		}else if( (direction_x == 0) && (direction_y == 1) ){
			save_direction.element.now=1;	//上 2^0
		}
		
		if( (save_direction.all & save_direction.element.now) > 0 ){	//直進できるなら
			path[count].element.distance += 2;	//180mm直進を追加

		}else{															//ターンするなら
			add_path_turn(save_direction,count);
			count++;
		}
	
	}
	
	
	path[count].element.distance += 1;	//90mm直進を追加	ゴールに入りきるため
	
}

signed char create_some_path(JUNCTION *junction){
	SAVE_DIRECTION save_direction;				//次に行くマスの方向を保存		
	unsigned char junc_count=0;		//数を数えるだけの変数
	unsigned char temp_direction_count = 0;		//行ける方向がいくつあるか(分岐路かチェック用)
	unsigned char junction_number = 0;			//分岐路の個数を数える用
	unsigned char temp_opposite_count=0;	//歩数に逆らった回数の一時的保存用
	
	path_reset();
	
	direction_x = 0;	//方向を初期化
	direction_y = 1;
	
	now_x = 0;		//位置を初期化
	now_y = 0;
	
	count_opposite_step = 0;	//リセット
	
	create_map_for_shortest_close_dead_end(GOAL_x,GOAL_y);
	
	create_path_number = 0;
	path[create_path_number].element.distance += 1;	//最初は必ず半区画直進する
	
	while(1){
	
		save_direction.all = 0;		//次に行く方向初期化
		
		now_x = now_x + direction_x; 		//位置修正
		now_y = now_y + direction_y; 
		
		temp_direction_count = 0;

		if( (now_x == GOAL_x) && (now_y == GOAL_y))	break;	//GOALにたどり着いたら終了
		
		
		
		if( (direction_x == 1) && (direction_y == 0) ){				//左のマスから来たのであれば何もしない
			save_direction.element.now=3;		//現在向いてる方向だけ記録
		}else{
			if( (now_x - 1) >= 0 ){		//now_x-1,now_yの座標が迷路内(0以上)である
				if( (map[now_x-1][now_y].known.right == 0) && (map[now_x][now_y].known.left == 0) ){	//壁がないなら
					if( step[now_x-1][now_y] != 255 ){					//歩数が初期化されてない
						save_direction.element.left=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす
						
					}
				}
			}
		}
		
		if( (direction_x == -1) && (direction_y == 0) ){			//右のマスから来たのであれば何もしない
			save_direction.element.now=1;		//現在向いてる方向だけ記録
		}else{
			if( (now_x + 1) < MAX_x ){	//now_x+1,now_yの座標が迷路内(16未満)である
				if( (map[now_x+1][now_y].known.left == 0) && (map[now_x][now_y].known.right == 0) ){	//壁がないなら
					if( step[now_x+1][now_y] != 255 ){				//歩数が初期化されてない
						save_direction.element.right=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす
						
					}
				}
			}
		}
	
		if( (direction_x == 0) && (direction_y == -1) ){				//上のマスから来たのであれば何もしない
			save_direction.element.now=2;		//現在向いてる方向だけ記録
		}else{
			if( (now_y + 1) < MAX_y ){	//now_x,now_y+1の座標が迷路内(16以下)である
				if( (map[now_x][now_y+1].known.down == 0) && (map[now_x][now_y].known.up == 0) ){	//壁がないなら
					if( step[now_x][now_y+1] != 255 ){				//歩数が初期化されてない
						save_direction.element.up=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす
							
					}				
				} 
			}
		}
		
		if( (direction_x == 0) && (direction_y == 1) ){				//下のマスから来たのであれば何もしない
			save_direction.element.now=0;		//現在向いてる方向だけ記録
		}else{
			if( (now_y - 1) >= 0 ){		//now_x,now_y-1の座標が迷路内(0以上)である
				if( (map[now_x][now_y-1].known.up == 0) && (map[now_x][now_y].known.down == 0) ){	//壁がないなら
					if( step[now_x][now_y-1] != 255 ){				//歩数が初期化されてない
						save_direction.element.down=1;		//次に進む方向の選択肢に追加
						temp_direction_count++;				//1増やす
						
					}
				}
			}
		}
		/////////////////分岐点チェック////////////////////////////////////////
	
		if( temp_direction_count >= 2 ){	//行ける方向が2以上 ＝ 分岐路のとき
			
			if( save_direction.element.left == 1 ){		//左に行ける場合
				if( step[now_x][now_y] <= step[now_x-1][now_y] ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.left = 0;		//次に進む方向の選択肢から消去
					}
				}
				
			}
			if( save_direction.element.right == 1 ){		//右に行ける場合
				if( step[now_x][now_y] <= step[now_x+1][now_y] ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.right = 0;		//次に進む方向の選択肢から消去
					}
				}
				
			}
			if( save_direction.element.up == 1 ){		//上に行ける場合
				if( step[now_x][now_y] <= step[now_x][now_y+1] ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.up = 0;			//次に進む方向の選択肢から消去
					}
				}
			}
			if( save_direction.element.down == 1 ){		//下に行ける場合
				if( step[now_x][now_y] <= step[now_x][now_y-1] ){			//今いる場所より歩数が増えるなら = 歩数マップに逆らうなら 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//歩数マップに逆らうことが許されるなら
						//何もしない
					}else{
						save_direction.element.down = 0;		//次に進む方向の選択肢から消去
					}
				}
			}
			
			if( junction[junction_number].all == 0 ){			//まだ何も入ってなければ
				for(junc_count = 0; junction[junc_count].all != 0; junc_count++){		//junctionが終わるまでまわす
					if( (junction[junc_count].element.junction_x == now_x) && (junction[junc_count].element.junction_y == now_y) ){
						return -1;	//既に保存してる分岐路だった場合 -1を返して関数終了
					}
				}
				junction[junction_number].element.junction_x = now_x;						//x座標を記録
				junction[junction_number].element.junction_y = now_y;						//y座標を記録
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
					return OFF;
				}	
			}	
			
			//pathを追加する
			if( add_path(save_direction,create_path_number,junction[junction_number].element.try_number) == OFF ){
				return -1;		//パス生成できなかったらエラー(-1)を返す
			}	
			
			junction_number++;	//カウントを進める
		
		}else{		//分岐点じゃない時
			
			temp_opposite_count = count_opposite_step;	//歩数に逆らった回数の一時的保存
			//pathを追加する
			add_path(save_direction,create_path_number,1);	
			count_opposite_step = temp_opposite_count;	//歩数に逆らった回数を戻す　直線時は歩数に逆らうとか考えない。次の分岐点まで行く
			
		}
		
	
	}
	
	path[create_path_number].element.distance += 1;	//90mm直進を追加	ゴールに入りきるため
	
	//improve_path();		//大回りターンを作る
	improve_advance_path();		//大回りターンを作る
	
	return ON;
	
}

void close_dead_end(char target_x, char target_y){
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
	if( (map[target_x][target_y].known.left == 1) ){			//左壁があるなら
		dead_end.direction.left = 1;	//左フラグを建てる
		dead_end.direction.count++;		//1足す	
	}else if( (target_x-1) >= 0 ){		//座標が迷路内(x-1が0以上)にあり
		if( (step[target_x-1][target_y] == 255) || (map[target_x-1][target_y].known.right == 1) ){		//左のマスに行けない（入ってる歩数が255 または ）
			dead_end.direction.left = 1;	//左フラグオン
			dead_end.direction.count++;		//1足す	
		}	
	}
						
	//右マス
	if( (map[target_x][target_y].known.right == 1) ){			//右壁があるなら
		dead_end.direction.right = 1;		//右フラグを建てる
		dead_end.direction.count++;			//1足す	
	}else if( (target_x+1) < MAX_x ){	//座標が迷路内(x+1がMax_x未満)にあり
		if( (step[target_x+1][target_y] == 255) || (map[target_x+1][target_y].known.left == 1)){			//右のマスに行けない（入ってる歩数が255 または 壁がある）
			dead_end.direction.right = 1;	//右フラグを建てる
			dead_end.direction.count++;		//1足す	
		}
	}
				
	//下マス
	if( (map[target_x][target_y].known.down == 1) ){			//下壁があるなら
		dead_end.direction.down = 1;		//下フラグを建てる
		dead_end.direction.count++;			//1足す	
	}else if( (target_y-1 >= 0) ){		//座標が迷路内(y-1が0以上)にあり
		if( (step[target_x][target_y-1] == 255) || (map[target_x][target_y-1].known.up == 1) ){		//下のマスに行けない（入ってる歩数が255 または 壁がある）
			dead_end.direction.down = 1;	//下フラグを建てる
			dead_end.direction.count++;		//1足す	
		}
	}
				
	//上マス
	if( (map[target_x][target_y].known.up == 1) ){			//上壁があるなら
		dead_end.direction.up = 1;			//上フラグを建てる
		dead_end.direction.count++;			//1足す	
	}else if( (target_y+1 < MAX_y) ){	//x,y+1の座標が迷路内(MAX_y未満)である
		if( (step[target_x][target_y+1] == 255) || (map[target_x][target_y+1].known.down == 1) ){		//上のマスに行けない（入ってる歩数が255　または　壁がある）
			dead_end.direction.up = 1;		//上フラグを建てる
			dead_end.direction.count++;		//1足す	
		}
	}
	
	
	//袋小路をふさぐ
	if( dead_end.direction.count >= 3 ){		//行けない方向が3以上 = 袋小路なら
		if( (target_x == 0) && (target_y == 0) ){		//それがスタートなら何もしない
		}else if( (target_x == GOAL_x) && (target_y == GOAL_y) ){		//それがゴールでも何もしない
		}else{							//上記以外なら袋小路を潰す
			step[target_x][target_y] = 255;	//歩数を初期化
			//袋小路のあいてる方向についてもう一回同じことを行う
			if( dead_end.direction.left == 0 )	close_dead_end(target_x-1,target_y);
			if( dead_end.direction.right == 0)	close_dead_end(target_x+1,target_y);
			if( dead_end.direction.down == 0)	close_dead_end(target_x,target_y-1);
			if( dead_end.direction.up == 0)		close_dead_end(target_x,target_y+1);
		}
	}
}

void create_map_for_shortest_close_dead_end(char target_x,char target_y){			//最短用歩数マップ生成。単に未探索区間を省くだけ
	char x_count,y_count;	//何でもいい、カウントするだけの変数
	unsigned short head;		//
	unsigned short tail;		//
	unsigned char coordinate[MAX_x*MAX_y+2]={0};			//座標を保管する配列
	
	step_reset();	//歩数マップを255に
	step[target_x][target_y]=0;		//目標の座標の歩数を0にする

	coordinate[0] = target_x*16 + target_y;		//上位4bitにx座標を、下位4bitにy座標
	
	//coordinate  [tail][][][] -> [][][head]
	
	head = 1;
	tail = 0;
	
	while( head != tail ){
		
		y_count = (coordinate[tail] & 0x0f);	//下位4bitの値をy_countに代入
		x_count = (coordinate[tail] >> 4);	//上位4bitの値をx_countに代入
		tail++;		
				//左マス
				if( (x_count-1) >= 0 ){		//座標が迷路内(x-1が0以上)にあり
					if( map[x_count-1][y_count].check.up && map[x_count-1][y_count].check.down && map[x_count-1][y_count].check.left && map[x_count-1][y_count].check.right ){
						//探索済みであれば
						if( (step[x_count-1][y_count] == 255) ){		//x-1,yの座標が迷路内(0以上)であり　かつ　歩数を入れてない（入ってる歩数が255）
							if( (map[x_count][y_count].known.left == 0) && (map[x_count-1][y_count].known.right == 0) ){		//元のマスの左壁がない かつ　左のマスの右壁がない
								step[x_count-1][y_count] = step[x_count][y_count]+1;
								coordinate[head] = (x_count - 1) * 16 + y_count;
								head++;
							}
						}
					}
				}
						
				//右マス
				if( (x_count+1) < MAX_x ){	//座標が迷路内(x+1がMax_x未満)にあり
					if( map[x_count+1][y_count].check.up && map[x_count+1][y_count].check.down && map[x_count+1][y_count].check.left && map[x_count+1][y_count].check.right ){
						//探索済みであれば
						if( (step[x_count+1][y_count] == 255) ){	//x+1,yの座標が迷路内(16未満)である　かつ　歩数を入れてない（入ってる歩数が255）
							if( (map[x_count][y_count].known.right == 0) && (map[x_count+1][y_count].known.left == 0) ){		//元のマスの右壁がない かつ 右のマスの左壁がない
								step[x_count+1][y_count] = step[x_count][y_count]+1;
								coordinate[head] = (x_count + 1) * 16 + y_count;
								head++;
							}
						}
					}
				}
						
				//下マス
				if( (y_count-1 >= 0) ){		//座標が迷路内(y-1が0以上)にあり
					if( map[x_count][y_count-1].check.up && map[x_count][y_count-1].check.down && map[x_count][y_count-1].check.left && map[x_count][y_count-1].check.right ){
						//探索済みであれば
						if( (step[x_count][y_count-1] == 255) ){		//x,y-1の座標が迷路内(0以上)である　かつ　歩数を入れてない（入ってる歩数が255）
							if( (map[x_count][y_count].known.down == 0) && (map[x_count][y_count-1].known.up == 0) ){		//元のマスの下壁がない かつ　下のマスの上壁がない
								step[x_count][y_count-1] = step[x_count][y_count]+1;
								coordinate[head] = x_count * 16 + (y_count - 1);
								head++;
							}
						}
					}
				}
						
				//上マス
				if( (y_count+1 < MAX_y) ){	//x,y+1の座標が迷路内(MAX_y未満)である
					if( map[x_count][y_count+1].check.up && map[x_count][y_count+1].check.down && map[x_count][y_count+1].check.left && map[x_count][y_count+1].check.right ){
						//探索済みであれば
						if( (step[x_count][y_count+1] == 255) ){	//x,y+1の座標が迷路内(16以下)である 　かつ　歩数を入れてない（入ってる歩数が255）
							if( (map[x_count][y_count].known.up == 0) && (map[x_count][y_count+1].known.down == 0) ){		//元のマスの上壁がない かつ 上のマスの下壁がない
								step[x_count][y_count+1] = step[x_count][y_count]+1;
								coordinate[head] = x_count * 16 + (y_count + 1);
								head++;
							}
						}
					}
				}
				
				
	}
	
	
	
	tail = 0;

	for( tail = 0; tail != head; tail++ ){
		y_count = (coordinate[tail] & 0x0f);	//下位4bitの値をy_countに代入
		x_count = (coordinate[tail] >> 4);	//上位4bitの値をx_countに代入
	
		if( step[x_count][y_count] == 255 ){		//既に歩数が初期化されていればスルー
		}else{
			close_dead_end( x_count, y_count);	
		}	
		
	}
	
}

float calculate_run_time(int n_mm, int accel_value, int de_accel_value, float max_velocity, float syo_sokudo, float end_velocity){
	float temp_run_time=0.0;		//走行時間をもっとくための変数
	float temp_velocity=0.0;	//速度を計算する用
	int temp_count=0;			//数を数える
	int temp_distance=0;		//距離をもっとく用の
	
	//初期速度から終端速度まで変化させるためにはどれだけ距離が必要か計算する
	if( syo_sokudo >= end_velocity){
		temp_distance = ( syo_sokudo * syo_sokudo - end_velocity * end_velocity ) / (2 * accel_value);
	}else{
		temp_distance = ( end_velocity * end_velocity - syo_sokudo * syo_sokudo ) / (2 * de_accel_value);
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

float calculate_path_time(float path_velocity, unsigned char run_mode){
	float path_time=0.0;			//path走行にかかる時間
	float temp_velocity=MIN_SPEED;	//マウスの速度
	unsigned char path_count=0;			//配列の番号
	char naname_flag = OFF;				//斜め中かどうか判断　ONなら斜め走行中
	float end_velocity = 0.0;		//次とその次のターンの速度を保存
	int accel_value=18000;


		for( path_count=0; (path_count < PATH_MAX) && (flag.bit.end == OFF); path_count++ ){
	
			if( path[path_count].all == 0){				//pathに値が入ってなければそこで終了
				break;
			}
			
			
			//終端速度決定
			switch( path[path_count].element.turn ){
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
					
			if( naname_flag == OFF ){		//斜め走行中ではない
				//直線走行にかかる時間を加算
				path_time += calculate_run_time(( 90 * (path[path_count].element.distance) ), accel_value, accel_value, path_velocity, temp_velocity, end_velocity);
				temp_velocity = end_velocity;	//ターンには理想の速度で入れているとする
				
			}else{							//斜め走行中である
				//直線走行にかかる時間を加算
				path_time += calculate_run_time(( 90 * (path[path_count].element.distance) * SQRT2 ), accel_value, accel_value, path_velocity, temp_velocity, end_velocity);
				temp_velocity = end_velocity;	//ターンには理想の速度で入れているとする
				
			}
			
			
			
			//ターンに応じて時間を加算
			switch( path[path_count].element.turn ){
				case 1:	
					//小回り
					if( path[path_count].element.muki == MUKI_LEFT){
						path_time += slalom_turn_90_left.time;		//左旋回
					}else{
						path_time += slalom_turn_90_right.time;		//右旋回
					}
					break;

				case 2:	
					//大回り
					if( path[path_count].element.muki == MUKI_LEFT){
						path_time += slalom_big_turn_90_left[run_mode].time;		//左旋回
					}else{
						path_time += slalom_big_turn_90_right[run_mode].time;		//右旋回
					}
					break;

				case 3:	
					//180°ターン
					if( path[path_count].element.muki == MUKI_LEFT){
						path_time += slalom_big_turn_180_left[run_mode].time;		//左旋回
					}else{
						path_time += slalom_big_turn_180_right[run_mode].time;		//右旋回
					}
					break;

				case 4:	
					//45°ターン
					if( naname_flag == OFF ){		//斜め中ではない			
						flag.bit.posture_control = OFF;	
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_45_start_left[run_mode].time;		//左旋回
						}else{
							path_time +=  slalom_turn_45_start_right[run_mode].time;		//右旋回
						}
						naname_flag = ON;
						
					}else{							//斜め中である
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_45_end_left[run_mode].time;		//左旋回
						}else{
							path_time +=  slalom_turn_45_end_right[run_mode].time;		//右旋回
						}
						naname_flag = OFF;
					}
					break;

				case 5:	
					//135°ターン
					if( naname_flag == OFF ){		//斜め中ではない
						flag.bit.posture_control = OFF;	
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_135_start_left[run_mode].time;		//左旋回
						}else{
							path_time +=  slalom_turn_135_start_right[run_mode].time;		//右旋回
						}
						naname_flag = ON;
						
					}else{							//斜め中である
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_135_end_left[run_mode].time;		//左旋回
						}else{
							path_time +=  slalom_turn_135_end_right[run_mode].time;		//右旋回
						}
						naname_flag = OFF;
					}
					break;

				case 6:	
					//斜め90°ターン
					if( path[path_count].element.muki == MUKI_LEFT){
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

void selection_root(float path_velocity, unsigned char run_mode){
	JUNCTION junction[JUNCTION_MAX];	//分岐点保存用配列
	unsigned long try_count=0;	//試行回数をカウントする変数
	unsigned long fast_path=0;	//最も速い走行をした試行回数を記録する変数
	float temp_time=0.0;			//パスの走行にどれだけかかるかを保存する変数
	float fast_time=100.0;			//パスの走行にかかった時間のうち最短の時間を保存する変数
	signed char roop_flag = ON;
	int i;	//数を数えるだけ
	
	//初期化
	for( i=0; i < JUNCTION_MAX; i++){
		junction[i].all = 0;
	}
	
	//まず1回パスを作る
	roop_flag = create_some_path(junction);		//create_some_pathはパス生成できないとOFFを返すので,そうするとループを抜ける
	
	for( try_count = 0; roop_flag != OFF ; try_count++){			
		if( roop_flag == -1 ){		//パス生成できなかったときは計算しない
			//何もしない
		}else{
			temp_time = calculate_path_time(path_velocity,run_mode);//生成したパスの時間を計算
			if( temp_time < fast_time ){			//今までのパスと比べ、はやいのかチェック
				//速ければ、try_countを記録し時間を更新
				fast_path = try_count;
				fast_time = temp_time;
			}
		}
		roop_flag = create_some_path(junction);		//create_some_pathはパス生成できないとOFFを返すので,そうするとループを抜ける
	}
	printf("try %d,  fast %d\n",try_count,fast_path);
		
	//junctionをリセット
	for( try_count= 0; try_count < JUNCTION_MAX; try_count++){
		junction[try_count].all = 0;
	}
	
	//try_countまで上のループをもう一度まわして、目的のパスを取得
	for( try_count = 0; try_count < fast_path; try_count++){
		create_some_path(junction);		//パス生成
	}
	
	//1回足りない分、生成して終わり
	create_some_path(junction);		//パス生成
	
}

void improve_path(){
	unsigned char count=0;
	unsigned char number=0;		//数を数えるだけ
	unsigned char naname_flag = OFF;	//現在機体が斜めかを判断	ONなら斜め走行中
	
	while( path[count].all != 0 ){		//pathが終われば終了
		
		if( naname_flag == ON ){							//斜め走行中なら	確実に直進距離(distance)が0のはず
			if( path[count].element.distance == 0 ){
				naname_flag = OFF;
			
			}else{
				
				if( path[count+1].element.distance >= 1 ){			//次のターン後90mm以上直進(斜め終わり)
					path[count+1].element.turn = 4;							//45°ターンに変更
					path[count+1].element.distance -= 1;					//直線距離を90mm減らす
					naname_flag = OFF;
				
				}else if( path[count+2].element.distance >= 1 ){	//次の次のターン後90mm以上直進(斜め終わり)
					
					if( path[count].element.muki == path[count+1].element.muki ){		//同じ方向の2回ターン
						path[count].element.turn = 5;					//135°ターンに変更
						
						path[count+1].all = path[count+2].all;
						//1個ずらす
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
						
						path[count+1].element.distance -= 1;				//直線距離を90mm減らす
						naname_flag = ON;
						
						
					}else{																//交互のターン(ギザギザ)
						path[count].element.distance += 1;				//斜めの直線距離を1増やす
						
						path[count+1].all = path[count+2].all;
						//1個ずらす
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
					}
					
				}else{												//まだまだ斜めは続くなら
					if( path[count].element.muki == path[count+1].element.muki ){		//同じ方向の2回ターン	コの字
						path[count].element.turn = 6;					//斜め90°ターンに変更
					
						path[count+1].all = path[count+2].all;
						//1個ずらす
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}					
					
					}else{																//違う方向の2回ターン	ギザギザ
						path[count].element.distance += 1;				//斜めの直線距離を1増やす
						
						path[count+1].all = path[count+2].all;
						//1個ずらす
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
							
					}
				}
				
			}
		
		
		}else if( path[count].element.distance >= 1 ){		//90mm以上直進するなら
			
			if( path[count+1].element.distance >= 1 ){		//ターン後も90mm以上直進するなら	大回りのチェックを行う
				path[count].element.turn = 2;					//大回りターンに変更
				path[count].element.distance -= 1;				//直線距離を90mm減らす
				path[count+1].element.distance -= 1;			//直線距離を90mm減らす
			
			}else{											//ターン後90mm直進はしないなら
				
				if( path[count].element.muki == path[count+1].element.muki ){	//同じ方向に曲がるなら(Uターン)
					
					if( path[count+2].element.distance >= 1 ){		//Uターン後90mm直進するなら
						path[count].element.turn = 3;					//180°ターンに変更
						path[count].element.distance -= 1;				//直線距離を90mm減らす
						path[count+2].element.distance -= 1;			//直線距離を90mm減らす
						
						path[count+1].all = path[count+2].all;
						//1個ずらす
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
						
					}else{											//Uターン後すぐ曲がるなら
						
						if( path[count+2].all != 0 ){					//pathが終わってないかチェック　終わってなければ逆方向にターンのはず
							/*
							path[count].element.turn = 5;					//135°ターンに変更
							path[count].element.distance -= 1;				//直線距離を90mm減らす
							
							path[count+1].all = path[count+2].all;
							//1個ずらす
							for( number = count+1; path[number].all != 0; number++){
								path[number].all = path[number+1].all;
							}
							naname_flag = ON;
							*/
						}
						
					}
				
				}else{		//違う方法に曲がるなら
					/*
					path[count].element.turn = 4;							//45°ターンに変更
					path[count].element.distance -= 1;						//直線距離を90mm減らす
					naname_flag = ON;
					*/
				}
								
			}
		
		}
		
		count++;
	}
	
}

void improve_advance_path(){
	unsigned char count=0;			//数を数えるだけ
	unsigned char temp_distance=0;	//一時的な距離保存		
	unsigned char naname_flag = OFF;	//現在機体が斜めかを判断	ONなら斜め走行中
	
	while( path[count].all != 0 ){		//pathが終われば終了
		
		if( naname_flag == ON ){							//斜め走行中なら	確実に直進距離(distance)が0のはず
				
			if( path[count+1].element.distance >= 1 ){			//次のターン後90mm以上直進(斜め終わり)
				
				path[count].element.turn = 4;							//45°ターンに変更
				path[count+1].element.distance -= 1;					//直線距離を90mm減らす
				naname_flag = OFF;
				count++;												//配列を次へ
				
			}else if( path[count+2].element.distance >= 1 ){	//次の次のターン後90mm以上直進(斜め終わり)
				
				if( path[count].element.muki == path[count+1].element.muki ){		//同じ方向の2回ターン
					
					path[count].element.turn = 5;					//135°ターンに変更
					displace_path(count+1);							//一個ずらす
					path[count+1].element.distance -= 1;			//ターン後の直線距離を90mm減らす
					naname_flag = OFF;
					count++;										//配列を次へ
					
				}else{																//交互のターン(ギザギザ)
					
					path[count].element.distance += 1;				//斜めの直線距離を1増やす
					temp_distance = path[count].element.distance;	//距離を一時的に持っておく
					displace_path(count);							//一個ずらす
					path[count].element.distance = temp_distance;	//距離を入れなおす
						
				}
				
			}else{												//まだまだ斜めは続くなら
					
				if( path[count].element.muki == path[count+1].element.muki ){		//同じ方向の2回ターン	コの字
					
					path[count].element.turn = 6;					//斜め90°ターンに変更
					displace_path(count+1);							//一個ずらす
					count++;										//配列を次へ
					
				}else{																//違う方向の2回ターン	ギザギザ
					
					path[count].element.distance += 1;				//斜めの直線距離を1増やす
					temp_distance = path[count].element.distance;	//距離を一時的に持っておく
					displace_path(count);							//一個ずらす
					path[count].element.distance = temp_distance;	//距離を入れなおす
				
				}
			}
		
		}else {										//斜めじゃなければ
			
			if( path[count+1].element.distance >= 1 ){		//ターン後も90mm以上直進するなら	大回りのチェックを行う
			
				if( (count != 0) || (path[0].element.distance > 1) ){		//初っ端のターンじゃなければ
			
					path[count].element.turn = 2;					//大回りターンに変更
					path[count].element.distance -= 1;				//直線距離を90mm減らす
					path[count+1].element.distance -= 1;			//直線距離を90mm減らす
			
				}
			
			}else{											//ターン後90mm直進はしないなら
				
				if( path[count].element.muki == path[count+1].element.muki ){	//同じ方向に曲がるなら(Uターン)
					
					if( path[count+2].element.distance >= 1 ){		//Uターン後90mm直進するなら
			
						path[count].element.turn = 3;					//180°ターンに変更
						path[count].element.distance -= 1;				//直線距離を90mm減らす
						path[count+2].element.distance -= 1;			//直線距離を90mm減らす
						displace_path(count+1);							//一個ずらす
						
					}else{											//Uターン後すぐ曲がるなら
						
						if( path[count+2].all != 0 ){					//pathが終わってないかチェック　終わってなければ逆方向にターンのはず
			
							path[count].element.turn = 5;					//135°ターンに変更
							path[count].element.distance -= 1;				//直線距離を90mm減らす
							displace_path(count+1);							//一個ずらす
							naname_flag = ON;
							
						}
						
					}
				
				}else{		//違う方法に曲がるなら
					
					path[count].element.turn = 4;							//45°ターンに変更
					path[count].element.distance -= 1;						//直線距離を90mm減らす
					naname_flag = ON;
					
				}
								
			}	
			count++;		//配列を次へ
		}
		
	}
	
}



void displace_path(unsigned int path_number){
	unsigned char temp_count;
	for( temp_count = path_number; path[temp_count+1].element.flag == 0; temp_count++ ){
		path[temp_count].all = path[temp_count+1].all;
	}
}



void path_reset(){
	unsigned char reset_count;
	for(reset_count=0;reset_count<255;reset_count++){
		path[reset_count].all=0;
	}
	path[PATH_MAX-1].element.flag = 1;
}

