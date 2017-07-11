#include <stdio.h>
#include "user.h"
#include "define.h"
#include "path.h"

unsigned char create_path_number=0;		//path�g�p����path�̔z��ԍ���\���B

void add_path_turn(SAVE_DIRECTION next_direction, unsigned char path_number){	//���̐i�s�}�X�̕�����^����ƃp�X����������
	
	if( next_direction.element.right == 1 ){		//�s�������������E�̂Ƃ�
			if( direction_y == 1 )	path[path_number].element.muki = MUKI_RIGHT;	//�E������]
			else					path[path_number].element.muki = MUKI_LEFT;		//��������]
	
	}else if( next_direction.element.left == 1 ){	//�s���������������̂Ƃ�
			if( direction_y == -1 )	path[path_number].element.muki = MUKI_RIGHT;	//�E������]
			else					path[path_number].element.muki = MUKI_LEFT;		//��������]
	
	}else if( next_direction.element.down == 1 ){	//�s���������������̂Ƃ�
			if( direction_x == 1 )	path[path_number].element.muki = MUKI_RIGHT;	//�E������]
			else					path[path_number].element.muki = MUKI_LEFT;		//��������]
		
	}else if( next_direction.element.up == 1 ){		//�s��������������̂Ƃ�
			if( direction_x == -1 )	path[path_number].element.muki = MUKI_RIGHT;	//�E������]
			else					path[path_number].element.muki = MUKI_LEFT;		//��������]
	}	
	
	direction_turn(path[path_number].element.muki);		//direction���X�V
	
	path[path_number].element.turn = 1;				//�����^�[��
	
	return;
}

signed char add_path(SAVE_DIRECTION next_direction, unsigned char path_number, unsigned char priority){
	unsigned char temp_priority = priority;
	SAVE_DIRECTION temp_direction;			//���ɍs��������ۑ�
	
	if( next_direction.element.left == 1 ){		//���ɍs����Ƃ�
		temp_priority--;	//�D��x��������
		if( temp_priority == 0){		//�D��x��0�ɂȂ����炻����p�X�ɂ���
			if( (direction_x == -1) && (direction_y == 0) ){		//���������Ă�Ȃ�
				path[create_path_number].element.distance += 2;	//180mm���i��ǉ�
				
			}else{												//���̕����������Ă�Ȃ�
				temp_direction.all = 0;				//���ȊO�̑I����������
				temp_direction.element.left = 1;	//		�V
				add_path_turn(temp_direction,create_path_number);	//�^�[��
				create_path_number++;
				
			}
			
			if( step[now_x][now_y] >= step[now_x-1][now_y] ){				//�����}�b�v�ɋt�炤�Ȃ�
				count_opposite_step++;	//�t������L��������
			}
			return ON;
		}	
	}
	
	if( next_direction.element.down == 1 ){		//���ɍs����Ƃ�
		temp_priority--;	//�D��x��������
		if( temp_priority == 0){		//�D��x��0�ɂȂ����炻����p�X�ɂ���
			if( (direction_x == 0) && (direction_y == -1) ){		//���������Ă�Ȃ�
				path[create_path_number].element.distance += 2;	//180mm���i��ǉ�
				
			}else{												//���̕����������Ă�Ȃ�
				temp_direction.all = 0;				//���ȊO�̑I����������
				temp_direction.element.down = 1;	//		�V
				add_path_turn(temp_direction,create_path_number);	//�^�[��
				create_path_number++;
			}
			
			if( step[now_x][now_y] >= step[now_x][now_y-1] ){				//�����}�b�v�ɋt�炤�Ȃ�
				count_opposite_step++;	//�t������L��������
			}
			return ON;
		}	
	}
	
	if( next_direction.element.right == 1 ){		//�E�ɍs����Ƃ�
		temp_priority--;	//�D��x��������
		if( temp_priority == 0){		//�D��x��0�ɂȂ����炻����p�X�ɂ���
			if( (direction_x == 1) && (direction_y == 0) ){		//�E�������Ă�Ȃ�
				path[create_path_number].element.distance += 2;	//180mm���i��ǉ�
				
			}else{												//���̕����������Ă�Ȃ�
				temp_direction.all = 0;				//�E�ȊO�̑I����������
				temp_direction.element.right = 1;	//		�V
				add_path_turn(temp_direction,create_path_number);	//�^�[��
				create_path_number++;
			}
			
			if( step[now_x][now_y] >= step[now_x+1][now_y] ){				//�����}�b�v�ɋt�炤�Ȃ�
				count_opposite_step++;	//�t������L��������
			}
			return ON;
		}	
	}
	
	
	if( next_direction.element.up == 1 ){		//��ɍs����Ƃ�
		temp_priority--;	//�D��x��������
		if( temp_priority == 0){		//�D��x��0�ɂȂ����炻����p�X�ɂ���
			if( (direction_x == 0) && (direction_y == 1) ){		//��������Ă�Ȃ�
				path[create_path_number].element.distance += 2;	//180mm���i��ǉ�
				
			}else{												//���̕����������Ă�Ȃ�
				temp_direction.all = 0;				//��ȊO�̑I����������
				temp_direction.element.up = 1;	//		�V
				add_path_turn(temp_direction,create_path_number);	//�^�[��
				create_path_number++;
			}
			
			if( step[now_x][now_y] >= step[now_x][now_y+1] ){				//�����}�b�v�ɋt�炤�Ȃ�
				count_opposite_step++;	//�t������L��������
			}
			return ON;
		}	
	}
	
	//�����܂ł��ǂ蒅�����Ƃ������Ƃ̓p�X�������ł��ĂȂ��̂ŁAOFF��Ԃ�
	return OFF;
}

void create_path(){
	char tekitou;
	SAVE_DIRECTION save_direction;				//���ɍs���}�X�̕�����ۑ�		
	unsigned char count=0;	//���𐔂��邾���̕ϐ�
	
	path_reset();

	direction_x = 0;	//������������
	direction_y = 1;
	
	now_x = 0;		//�ʒu��������
	now_y = 0;
	
	create_map_for_shortest_close_dead_end(GOAL_x,GOAL_y);
	
	path[count].element.distance += 1;	//�ŏ��͕K������撼�i����
	
	while(1){
	
		save_direction.all = 0;		//���ɍs������������
		
		now_x = now_x + direction_x; 		//�ʒu�C��
		now_y = now_y + direction_y; 
		
		if( (now_x == GOAL_x) && (now_y == GOAL_y))	break;	//GOAL�ɂ��ǂ蒅������I��

		
		if( (now_x - 1) >= 0 ){		//now_x-1,now_y�̍��W�����H��(0�ȏ�)�ł���
			if( step[now_x-1][now_y] == (step[now_x][now_y] - 1) ){				//�����̏������ق���
				if( (map[now_x-1][now_y].known.right == 0) && (map[now_x][now_y].known.left == 0) ){	//�ǂ��Ȃ��Ȃ�
					save_direction.element.left=1;		//���ɐi�ޕ����̑I�����ɒǉ�
				}
			}
			
		}
	
		if( (now_x + 1) < MAX_x ){	//now_x+1,now_y�̍��W�����H��(16����)�ł���
			if( step[now_x+1][now_y] == (step[now_x][now_y] - 1) ){				//�����̏������ق���
				if( (map[now_x+1][now_y].known.left == 0) && (map[now_x][now_y].known.right == 0) ){	//�ǂ��Ȃ��Ȃ�
					save_direction.element.right=1;		//���ɐi�ޕ����̑I�����ɒǉ�
				}
			}
		}
	
		if( (now_y - 1) >= 0 ){		//now_x,now_y-1�̍��W�����H��(0�ȏ�)�ł���
			if( step[now_x][now_y-1] == (step[now_x][now_y] - 1) ){				//�����̏������ق���
				if( (map[now_x][now_y-1].known.up == 0) && (map[now_x][now_y].known.down == 0) ){	//�ǂ��Ȃ��Ȃ�
					save_direction.element.down=1;		//���ɐi�ޕ����̑I�����ɒǉ�
				}
			}
		}
	
		if( (now_y + 1) < MAX_y ){	//now_x,now_y+1�̍��W�����H��(16�ȉ�)�ł���
			if( step[now_x][now_y+1] == (step[now_x][now_y] - 1) ){				//�����̏������ق���
				if( (map[now_x][now_y+1].known.down == 0) && (map[now_x][now_y].known.up == 0) ){	//�ǂ��Ȃ��Ȃ�
					save_direction.element.up=1;		//���ɐi�ޕ����̑I�����ɒǉ�
				}				
			} 
		}
		
		//���݌����Ă�����𔻕�
		if( (direction_x == 1) && (direction_y == 0) ){
			save_direction.element.now=2;	//�E 2^1
		}else if( (direction_x == -1) && (direction_y == 0) ){
			save_direction.element.now=8;	//�� 2^3
		}else if( (direction_x == 0) && (direction_y == -1) ){
			save_direction.element.now=4;	//�� 2^2
		}else if( (direction_x == 0) && (direction_y == 1) ){
			save_direction.element.now=1;	//�� 2^0
		}
		
		if( (save_direction.all & save_direction.element.now) > 0 ){	//���i�ł���Ȃ�
			path[count].element.distance += 2;	//180mm���i��ǉ�

		}else{															//�^�[������Ȃ�
			add_path_turn(save_direction,count);
			count++;
		}
	
	}
	
	
	path[count].element.distance += 1;	//90mm���i��ǉ�	�S�[���ɓ��肫�邽��
	
}

signed char create_some_path(JUNCTION *junction){
	SAVE_DIRECTION save_direction;				//���ɍs���}�X�̕�����ۑ�		
	unsigned char junc_count=0;		//���𐔂��邾���̕ϐ�
	unsigned char temp_direction_count = 0;		//�s����������������邩(����H���`�F�b�N�p)
	unsigned char junction_number = 0;			//����H�̌��𐔂���p
	unsigned char temp_opposite_count=0;	//�����ɋt������񐔂̈ꎞ�I�ۑ��p
	
	path_reset();
	
	direction_x = 0;	//������������
	direction_y = 1;
	
	now_x = 0;		//�ʒu��������
	now_y = 0;
	
	count_opposite_step = 0;	//���Z�b�g
	
	create_map_for_shortest_close_dead_end(GOAL_x,GOAL_y);
	
	create_path_number = 0;
	path[create_path_number].element.distance += 1;	//�ŏ��͕K������撼�i����
	
	while(1){
	
		save_direction.all = 0;		//���ɍs������������
		
		now_x = now_x + direction_x; 		//�ʒu�C��
		now_y = now_y + direction_y; 
		
		temp_direction_count = 0;

		if( (now_x == GOAL_x) && (now_y == GOAL_y))	break;	//GOAL�ɂ��ǂ蒅������I��
		
		
		
		if( (direction_x == 1) && (direction_y == 0) ){				//���̃}�X���痈���̂ł���Ή������Ȃ�
			save_direction.element.now=3;		//���݌����Ă���������L�^
		}else{
			if( (now_x - 1) >= 0 ){		//now_x-1,now_y�̍��W�����H��(0�ȏ�)�ł���
				if( (map[now_x-1][now_y].known.right == 0) && (map[now_x][now_y].known.left == 0) ){	//�ǂ��Ȃ��Ȃ�
					if( step[now_x-1][now_y] != 255 ){					//����������������ĂȂ�
						save_direction.element.left=1;		//���ɐi�ޕ����̑I�����ɒǉ�
						temp_direction_count++;				//1���₷
						
					}
				}
			}
		}
		
		if( (direction_x == -1) && (direction_y == 0) ){			//�E�̃}�X���痈���̂ł���Ή������Ȃ�
			save_direction.element.now=1;		//���݌����Ă���������L�^
		}else{
			if( (now_x + 1) < MAX_x ){	//now_x+1,now_y�̍��W�����H��(16����)�ł���
				if( (map[now_x+1][now_y].known.left == 0) && (map[now_x][now_y].known.right == 0) ){	//�ǂ��Ȃ��Ȃ�
					if( step[now_x+1][now_y] != 255 ){				//����������������ĂȂ�
						save_direction.element.right=1;		//���ɐi�ޕ����̑I�����ɒǉ�
						temp_direction_count++;				//1���₷
						
					}
				}
			}
		}
	
		if( (direction_x == 0) && (direction_y == -1) ){				//��̃}�X���痈���̂ł���Ή������Ȃ�
			save_direction.element.now=2;		//���݌����Ă���������L�^
		}else{
			if( (now_y + 1) < MAX_y ){	//now_x,now_y+1�̍��W�����H��(16�ȉ�)�ł���
				if( (map[now_x][now_y+1].known.down == 0) && (map[now_x][now_y].known.up == 0) ){	//�ǂ��Ȃ��Ȃ�
					if( step[now_x][now_y+1] != 255 ){				//����������������ĂȂ�
						save_direction.element.up=1;		//���ɐi�ޕ����̑I�����ɒǉ�
						temp_direction_count++;				//1���₷
							
					}				
				} 
			}
		}
		
		if( (direction_x == 0) && (direction_y == 1) ){				//���̃}�X���痈���̂ł���Ή������Ȃ�
			save_direction.element.now=0;		//���݌����Ă���������L�^
		}else{
			if( (now_y - 1) >= 0 ){		//now_x,now_y-1�̍��W�����H��(0�ȏ�)�ł���
				if( (map[now_x][now_y-1].known.up == 0) && (map[now_x][now_y].known.down == 0) ){	//�ǂ��Ȃ��Ȃ�
					if( step[now_x][now_y-1] != 255 ){				//����������������ĂȂ�
						save_direction.element.down=1;		//���ɐi�ޕ����̑I�����ɒǉ�
						temp_direction_count++;				//1���₷
						
					}
				}
			}
		}
		/////////////////����_�`�F�b�N////////////////////////////////////////
	
		if( temp_direction_count >= 2 ){	//�s���������2�ȏ� �� ����H�̂Ƃ�
			
			if( save_direction.element.left == 1 ){		//���ɍs����ꍇ
				if( step[now_x][now_y] <= step[now_x-1][now_y] ){			//������ꏊ��������������Ȃ� = �����}�b�v�ɋt�炤�Ȃ� 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//�����}�b�v�ɋt�炤���Ƃ��������Ȃ�
						//�������Ȃ�
					}else{
						save_direction.element.left = 0;		//���ɐi�ޕ����̑I�����������
					}
				}
				
			}
			if( save_direction.element.right == 1 ){		//�E�ɍs����ꍇ
				if( step[now_x][now_y] <= step[now_x+1][now_y] ){			//������ꏊ��������������Ȃ� = �����}�b�v�ɋt�炤�Ȃ� 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//�����}�b�v�ɋt�炤���Ƃ��������Ȃ�
						//�������Ȃ�
					}else{
						save_direction.element.right = 0;		//���ɐi�ޕ����̑I�����������
					}
				}
				
			}
			if( save_direction.element.up == 1 ){		//��ɍs����ꍇ
				if( step[now_x][now_y] <= step[now_x][now_y+1] ){			//������ꏊ��������������Ȃ� = �����}�b�v�ɋt�炤�Ȃ� 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//�����}�b�v�ɋt�炤���Ƃ��������Ȃ�
						//�������Ȃ�
					}else{
						save_direction.element.up = 0;			//���ɐi�ޕ����̑I�����������
					}
				}
			}
			if( save_direction.element.down == 1 ){		//���ɍs����ꍇ
				if( step[now_x][now_y] <= step[now_x][now_y-1] ){			//������ꏊ��������������Ȃ� = �����}�b�v�ɋt�炤�Ȃ� 
					if( count_opposite_step <= ALLOW_OPPOSITE_STEP ){			//�����}�b�v�ɋt�炤���Ƃ��������Ȃ�
						//�������Ȃ�
					}else{
						save_direction.element.down = 0;		//���ɐi�ޕ����̑I�����������
					}
				}
			}
			
			if( junction[junction_number].all == 0 ){			//�܂����������ĂȂ����
				for(junc_count = 0; junction[junc_count].all != 0; junc_count++){		//junction���I���܂ł܂킷
					if( (junction[junc_count].element.junction_x == now_x) && (junction[junc_count].element.junction_y == now_y) ){
						return -1;	//���ɕۑ����Ă镪��H�������ꍇ -1��Ԃ��Ċ֐��I��
					}
				}
				junction[junction_number].element.junction_x = now_x;						//x���W���L�^
				junction[junction_number].element.junction_y = now_y;						//y���W���L�^
				junction[junction_number].element.max_direction = temp_direction_count;		//�����̌����L�^
				junction[junction_number].element.try_number = 1;							//���s1��ڂȂ̂�1������
			
			}else if( junction[junction_number+1].all == 0 ){	//���ɉ��������ĂȂ� = ���ꂪ����H�̍Ō�̂Ƃ�
				junction[junction_number].element.try_number++;								//���s�񐔂𑝂₷
			
			}else{												//���ɉ��������Ă�Ƃ�
				for(junc_count = (junction_number+1); junction[junc_count].all != 0; junc_count++){		//junction���I���܂ł܂킷
					//�s������������s�� = �܂��s����������c���Ă�Ȃ烋�[�v�E�o 
					if( junction[junc_count].element.max_direction > junction[junc_count].element.try_number ){
						break;
					}
				}
				junc_count++;		//1����
				if( junction[junc_count].all == 0){		//junction���I����Ă��� = �����s����������c���ĂȂ�
					junction[junction_number].element.try_number++;								//���s�񐔂𑝂₷
					//���򂪕ς�胋�[�g���ς��̂ŁA�Ȍ�̕���_�����Z�b�g
					for( junc_count = junction_number+1; junction[junc_count].all != 0; junc_count++){
						junction[junc_count].all = 0;
					}							
				}
				
				if( junction[junction_number].element.try_number > junction[junction_number].element.max_direction ){
					return OFF;
				}	
			}	
			
			//path��ǉ�����
			if( add_path(save_direction,create_path_number,junction[junction_number].element.try_number) == OFF ){
				return -1;		//�p�X�����ł��Ȃ�������G���[(-1)��Ԃ�
			}	
			
			junction_number++;	//�J�E���g��i�߂�
		
		}else{		//����_����Ȃ���
			
			temp_opposite_count = count_opposite_step;	//�����ɋt������񐔂̈ꎞ�I�ۑ�
			//path��ǉ�����
			add_path(save_direction,create_path_number,1);	
			count_opposite_step = temp_opposite_count;	//�����ɋt������񐔂�߂��@�������͕����ɋt�炤�Ƃ��l���Ȃ��B���̕���_�܂ōs��
			
		}
		
	
	}
	
	path[create_path_number].element.distance += 1;	//90mm���i��ǉ�	�S�[���ɓ��肫�邽��
	
	//improve_path();		//����^�[�������
	improve_advance_path();		//����^�[�������
	
	return ON;
	
}

void close_dead_end(char target_x, char target_y){
	union {
		unsigned char all;				//�ꊇ
		struct {
			unsigned char count	:4;		//		�s���Ȃ������̌�
			unsigned char up	:1;		//��	x=0,y=1�̕���
			unsigned char down	:1;		//��	x=0,y=-1�̕���
			unsigned char left	:1;		//��	x=-1,y=0�̕���
			unsigned char right	:1;		//��	x=1,y=0�̕���
		} direction;
	} dead_end;
	
	dead_end.all = 0;	//������
	
	//���}�X
	if( (map[target_x][target_y].known.left == 1) ){			//���ǂ�����Ȃ�
		dead_end.direction.left = 1;	//���t���O�����Ă�
		dead_end.direction.count++;		//1����	
	}else if( (target_x-1) >= 0 ){		//���W�����H��(x-1��0�ȏ�)�ɂ���
		if( (step[target_x-1][target_y] == 255) || (map[target_x-1][target_y].known.right == 1) ){		//���̃}�X�ɍs���Ȃ��i�����Ă������255 �܂��� �j
			dead_end.direction.left = 1;	//���t���O�I��
			dead_end.direction.count++;		//1����	
		}	
	}
						
	//�E�}�X
	if( (map[target_x][target_y].known.right == 1) ){			//�E�ǂ�����Ȃ�
		dead_end.direction.right = 1;		//�E�t���O�����Ă�
		dead_end.direction.count++;			//1����	
	}else if( (target_x+1) < MAX_x ){	//���W�����H��(x+1��Max_x����)�ɂ���
		if( (step[target_x+1][target_y] == 255) || (map[target_x+1][target_y].known.left == 1)){			//�E�̃}�X�ɍs���Ȃ��i�����Ă������255 �܂��� �ǂ�����j
			dead_end.direction.right = 1;	//�E�t���O�����Ă�
			dead_end.direction.count++;		//1����	
		}
	}
				
	//���}�X
	if( (map[target_x][target_y].known.down == 1) ){			//���ǂ�����Ȃ�
		dead_end.direction.down = 1;		//���t���O�����Ă�
		dead_end.direction.count++;			//1����	
	}else if( (target_y-1 >= 0) ){		//���W�����H��(y-1��0�ȏ�)�ɂ���
		if( (step[target_x][target_y-1] == 255) || (map[target_x][target_y-1].known.up == 1) ){		//���̃}�X�ɍs���Ȃ��i�����Ă������255 �܂��� �ǂ�����j
			dead_end.direction.down = 1;	//���t���O�����Ă�
			dead_end.direction.count++;		//1����	
		}
	}
				
	//��}�X
	if( (map[target_x][target_y].known.up == 1) ){			//��ǂ�����Ȃ�
		dead_end.direction.up = 1;			//��t���O�����Ă�
		dead_end.direction.count++;			//1����	
	}else if( (target_y+1 < MAX_y) ){	//x,y+1�̍��W�����H��(MAX_y����)�ł���
		if( (step[target_x][target_y+1] == 255) || (map[target_x][target_y+1].known.down == 1) ){		//��̃}�X�ɍs���Ȃ��i�����Ă������255�@�܂��́@�ǂ�����j
			dead_end.direction.up = 1;		//��t���O�����Ă�
			dead_end.direction.count++;		//1����	
		}
	}
	
	
	//�܏��H���ӂ���
	if( dead_end.direction.count >= 3 ){		//�s���Ȃ�������3�ȏ� = �܏��H�Ȃ�
		if( (target_x == 0) && (target_y == 0) ){		//���ꂪ�X�^�[�g�Ȃ牽�����Ȃ�
		}else if( (target_x == GOAL_x) && (target_y == GOAL_y) ){		//���ꂪ�S�[���ł��������Ȃ�
		}else{							//��L�ȊO�Ȃ�܏��H��ׂ�
			step[target_x][target_y] = 255;	//������������
			//�܏��H�̂����Ă�����ɂ��Ă�����񓯂����Ƃ��s��
			if( dead_end.direction.left == 0 )	close_dead_end(target_x-1,target_y);
			if( dead_end.direction.right == 0)	close_dead_end(target_x+1,target_y);
			if( dead_end.direction.down == 0)	close_dead_end(target_x,target_y-1);
			if( dead_end.direction.up == 0)		close_dead_end(target_x,target_y+1);
		}
	}
}

void create_map_for_shortest_close_dead_end(char target_x,char target_y){			//�ŒZ�p�����}�b�v�����B�P�ɖ��T����Ԃ��Ȃ�����
	char x_count,y_count;	//���ł������A�J�E���g���邾���̕ϐ�
	unsigned short head;		//
	unsigned short tail;		//
	unsigned char coordinate[MAX_x*MAX_y+2]={0};			//���W��ۊǂ���z��
	
	step_reset();	//�����}�b�v��255��
	step[target_x][target_y]=0;		//�ڕW�̍��W�̕�����0�ɂ���

	coordinate[0] = target_x*16 + target_y;		//���4bit��x���W���A����4bit��y���W
	
	//coordinate  [tail][][][] -> [][][head]
	
	head = 1;
	tail = 0;
	
	while( head != tail ){
		
		y_count = (coordinate[tail] & 0x0f);	//����4bit�̒l��y_count�ɑ��
		x_count = (coordinate[tail] >> 4);	//���4bit�̒l��x_count�ɑ��
		tail++;		
				//���}�X
				if( (x_count-1) >= 0 ){		//���W�����H��(x-1��0�ȏ�)�ɂ���
					if( map[x_count-1][y_count].check.up && map[x_count-1][y_count].check.down && map[x_count-1][y_count].check.left && map[x_count-1][y_count].check.right ){
						//�T���ς݂ł����
						if( (step[x_count-1][y_count] == 255) ){		//x-1,y�̍��W�����H��(0�ȏ�)�ł���@���@���������ĂȂ��i�����Ă������255�j
							if( (map[x_count][y_count].known.left == 0) && (map[x_count-1][y_count].known.right == 0) ){		//���̃}�X�̍��ǂ��Ȃ� ���@���̃}�X�̉E�ǂ��Ȃ�
								step[x_count-1][y_count] = step[x_count][y_count]+1;
								coordinate[head] = (x_count - 1) * 16 + y_count;
								head++;
							}
						}
					}
				}
						
				//�E�}�X
				if( (x_count+1) < MAX_x ){	//���W�����H��(x+1��Max_x����)�ɂ���
					if( map[x_count+1][y_count].check.up && map[x_count+1][y_count].check.down && map[x_count+1][y_count].check.left && map[x_count+1][y_count].check.right ){
						//�T���ς݂ł����
						if( (step[x_count+1][y_count] == 255) ){	//x+1,y�̍��W�����H��(16����)�ł���@���@���������ĂȂ��i�����Ă������255�j
							if( (map[x_count][y_count].known.right == 0) && (map[x_count+1][y_count].known.left == 0) ){		//���̃}�X�̉E�ǂ��Ȃ� ���� �E�̃}�X�̍��ǂ��Ȃ�
								step[x_count+1][y_count] = step[x_count][y_count]+1;
								coordinate[head] = (x_count + 1) * 16 + y_count;
								head++;
							}
						}
					}
				}
						
				//���}�X
				if( (y_count-1 >= 0) ){		//���W�����H��(y-1��0�ȏ�)�ɂ���
					if( map[x_count][y_count-1].check.up && map[x_count][y_count-1].check.down && map[x_count][y_count-1].check.left && map[x_count][y_count-1].check.right ){
						//�T���ς݂ł����
						if( (step[x_count][y_count-1] == 255) ){		//x,y-1�̍��W�����H��(0�ȏ�)�ł���@���@���������ĂȂ��i�����Ă������255�j
							if( (map[x_count][y_count].known.down == 0) && (map[x_count][y_count-1].known.up == 0) ){		//���̃}�X�̉��ǂ��Ȃ� ���@���̃}�X�̏�ǂ��Ȃ�
								step[x_count][y_count-1] = step[x_count][y_count]+1;
								coordinate[head] = x_count * 16 + (y_count - 1);
								head++;
							}
						}
					}
				}
						
				//��}�X
				if( (y_count+1 < MAX_y) ){	//x,y+1�̍��W�����H��(MAX_y����)�ł���
					if( map[x_count][y_count+1].check.up && map[x_count][y_count+1].check.down && map[x_count][y_count+1].check.left && map[x_count][y_count+1].check.right ){
						//�T���ς݂ł����
						if( (step[x_count][y_count+1] == 255) ){	//x,y+1�̍��W�����H��(16�ȉ�)�ł��� �@���@���������ĂȂ��i�����Ă������255�j
							if( (map[x_count][y_count].known.up == 0) && (map[x_count][y_count+1].known.down == 0) ){		//���̃}�X�̏�ǂ��Ȃ� ���� ��̃}�X�̉��ǂ��Ȃ�
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
		y_count = (coordinate[tail] & 0x0f);	//����4bit�̒l��y_count�ɑ��
		x_count = (coordinate[tail] >> 4);	//���4bit�̒l��x_count�ɑ��
	
		if( step[x_count][y_count] == 255 ){		//���ɕ���������������Ă���΃X���[
		}else{
			close_dead_end( x_count, y_count);	
		}	
		
	}
	
}

float calculate_run_time(int n_mm, int accel_value, int de_accel_value, float max_velocity, float syo_sokudo, float end_velocity){
	float temp_run_time=0.0;		//���s���Ԃ������Ƃ����߂̕ϐ�
	float temp_velocity=0.0;	//���x���v�Z����p
	int temp_count=0;			//���𐔂���
	int temp_distance=0;		//�����������Ƃ��p��
	
	//�������x����I�[���x�܂ŕω������邽�߂ɂ͂ǂꂾ���������K�v���v�Z����
	if( syo_sokudo >= end_velocity){
		temp_distance = ( syo_sokudo * syo_sokudo - end_velocity * end_velocity ) / (2 * accel_value);
	}else{
		temp_distance = ( end_velocity * end_velocity - syo_sokudo * syo_sokudo ) / (2 * de_accel_value);
	}
	
	
	//�I�[���x�ɋ߂Â������ŏI���ꍇ�i����or�����̂݁j
	if( temp_distance >= n_mm ){
		//t=��v/a
		if( syo_sokudo >= end_velocity){
			temp_run_time = ( syo_sokudo - end_velocity ) / accel_value;
		}else{
			temp_run_time = ( end_velocity - syo_sokudo ) / de_accel_value;
		}
	
	//��`�܂��͎O�p���������s���ꍇ
	}else{
		//�ō����܂ŏo�������A�ǂ̂��炢�������K�v���v�Z����i���������͂Ȃ��j
		temp_distance = ABS( ( max_velocity * max_velocity - syo_sokudo * syo_sokudo ) / (2 * accel_value));
		temp_distance += ABS( ( max_velocity * max_velocity - end_velocity * end_velocity ) / (2 * de_accel_value));
		
		//�O�p�̂Ƃ�
		if( temp_distance > n_mm ){
			
			for( temp_velocity = syo_sokudo; temp_distance < n_mm; temp_count++){
				temp_velocity = syo_sokudo + ((dt/1000) * accel_value) * temp_count;	//temp_velocity = �����x�{�����x�~����
		
				//temp_velocity�܂ŏo�������A�ǂ�قǂ̋������K�v���v�Z
				temp_distance = ABS( ( temp_velocity * temp_velocity - syo_sokudo * syo_sokudo ) / (2 * accel_value));
				temp_distance += ABS( ( temp_velocity * temp_velocity - end_velocity * end_velocity ) / (2 * de_accel_value));
			}
			
			temp_run_time += ABS((temp_velocity - syo_sokudo) / accel_value);	//�����ɂ����鎞��
			temp_run_time += ABS((temp_velocity - end_velocity) / accel_value);		//�����ɂ����鎞��
			
		//��`�̂Ƃ�
		}else{
			temp_run_time += ABS((max_velocity - syo_sokudo) / accel_value);	//�����ɂ����鎞��
			temp_run_time += ABS((max_velocity - end_velocity) / accel_value);		//�����ɂ����鎞��
			temp_run_time += (n_mm - temp_distance) / max_velocity;					//�����ɂ����鎞��
			
		}
		
	}
	
	return temp_run_time;
}

float calculate_path_time(float path_velocity, unsigned char run_mode){
	float path_time=0.0;			//path���s�ɂ����鎞��
	float temp_velocity=MIN_SPEED;	//�}�E�X�̑��x
	unsigned char path_count=0;			//�z��̔ԍ�
	char naname_flag = OFF;				//�΂ߒ����ǂ������f�@ON�Ȃ�΂ߑ��s��
	float end_velocity = 0.0;		//���Ƃ��̎��̃^�[���̑��x��ۑ�
	int accel_value=18000;


		for( path_count=0; (path_count < PATH_MAX) && (flag.bit.end == OFF); path_count++ ){
	
			if( path[path_count].all == 0){				//path�ɒl�������ĂȂ���΂����ŏI��
				break;
			}
			
			
			//�I�[���x����
			switch( path[path_count].element.turn ){
				case 0:	
					//���s�I��
					end_velocity = 0;
					break;
			
				case 1:
					//�����^�[��
					end_velocity = slalom_turn_90_right.slalom_velocity;
					break;
				
				case 2:	
					//����^�[��
					end_velocity = slalom_big_turn_90_right[run_mode].slalom_velocity;
					break;
			
				case 3:
					//180���^�[��
					end_velocity = slalom_big_turn_180_right[run_mode].slalom_velocity;
					break;
					
				case 4:
					//45���^�[��
					end_velocity = slalom_turn_45_start_right[run_mode].slalom_velocity;
					break;
				
				case 5:
					//135���^�[��
					end_velocity = slalom_turn_135_start_right[run_mode].slalom_velocity;
					break;
				
				case 6:
					//�΂�90���^�[��
					end_velocity = slalom_turn_90_oblique_right[run_mode].slalom_velocity;
					break;
				
			}
			
			
			//���i�ɂ����鎞�Ԃ����Z
					
			if( naname_flag == OFF ){		//�΂ߑ��s���ł͂Ȃ�
				//�������s�ɂ����鎞�Ԃ����Z
				path_time += calculate_run_time(( 90 * (path[path_count].element.distance) ), accel_value, accel_value, path_velocity, temp_velocity, end_velocity);
				temp_velocity = end_velocity;	//�^�[���ɂ͗��z�̑��x�œ���Ă���Ƃ���
				
			}else{							//�΂ߑ��s���ł���
				//�������s�ɂ����鎞�Ԃ����Z
				path_time += calculate_run_time(( 90 * (path[path_count].element.distance) * SQRT2 ), accel_value, accel_value, path_velocity, temp_velocity, end_velocity);
				temp_velocity = end_velocity;	//�^�[���ɂ͗��z�̑��x�œ���Ă���Ƃ���
				
			}
			
			
			
			//�^�[���ɉ����Ď��Ԃ����Z
			switch( path[path_count].element.turn ){
				case 1:	
					//�����
					if( path[path_count].element.muki == MUKI_LEFT){
						path_time += slalom_turn_90_left.time;		//������
					}else{
						path_time += slalom_turn_90_right.time;		//�E����
					}
					break;

				case 2:	
					//����
					if( path[path_count].element.muki == MUKI_LEFT){
						path_time += slalom_big_turn_90_left[run_mode].time;		//������
					}else{
						path_time += slalom_big_turn_90_right[run_mode].time;		//�E����
					}
					break;

				case 3:	
					//180���^�[��
					if( path[path_count].element.muki == MUKI_LEFT){
						path_time += slalom_big_turn_180_left[run_mode].time;		//������
					}else{
						path_time += slalom_big_turn_180_right[run_mode].time;		//�E����
					}
					break;

				case 4:	
					//45���^�[��
					if( naname_flag == OFF ){		//�΂ߒ��ł͂Ȃ�			
						flag.bit.posture_control = OFF;	
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_45_start_left[run_mode].time;		//������
						}else{
							path_time +=  slalom_turn_45_start_right[run_mode].time;		//�E����
						}
						naname_flag = ON;
						
					}else{							//�΂ߒ��ł���
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_45_end_left[run_mode].time;		//������
						}else{
							path_time +=  slalom_turn_45_end_right[run_mode].time;		//�E����
						}
						naname_flag = OFF;
					}
					break;

				case 5:	
					//135���^�[��
					if( naname_flag == OFF ){		//�΂ߒ��ł͂Ȃ�
						flag.bit.posture_control = OFF;	
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_135_start_left[run_mode].time;		//������
						}else{
							path_time +=  slalom_turn_135_start_right[run_mode].time;		//�E����
						}
						naname_flag = ON;
						
					}else{							//�΂ߒ��ł���
						if( path[path_count].element.muki == MUKI_LEFT){
							path_time +=  slalom_turn_135_end_left[run_mode].time;		//������
						}else{
							path_time +=  slalom_turn_135_end_right[run_mode].time;		//�E����
						}
						naname_flag = OFF;
					}
					break;

				case 6:	
					//�΂�90���^�[��
					if( path[path_count].element.muki == MUKI_LEFT){
						path_time +=  slalom_turn_90_oblique_left[run_mode].time;		//������
					}else{
						path_time +=  slalom_turn_90_oblique_right[run_mode].time;		//�E����
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
	JUNCTION junction[JUNCTION_MAX];	//����_�ۑ��p�z��
	unsigned long try_count=0;	//���s�񐔂��J�E���g����ϐ�
	unsigned long fast_path=0;	//�ł��������s���������s�񐔂��L�^����ϐ�
	float temp_time=0.0;			//�p�X�̑��s�ɂǂꂾ�������邩��ۑ�����ϐ�
	float fast_time=100.0;			//�p�X�̑��s�ɂ����������Ԃ̂����ŒZ�̎��Ԃ�ۑ�����ϐ�
	signed char roop_flag = ON;
	int i;	//���𐔂��邾��
	
	//������
	for( i=0; i < JUNCTION_MAX; i++){
		junction[i].all = 0;
	}
	
	//�܂�1��p�X�����
	roop_flag = create_some_path(junction);		//create_some_path�̓p�X�����ł��Ȃ���OFF��Ԃ��̂�,��������ƃ��[�v�𔲂���
	
	for( try_count = 0; roop_flag != OFF ; try_count++){			
		if( roop_flag == -1 ){		//�p�X�����ł��Ȃ������Ƃ��͌v�Z���Ȃ�
			//�������Ȃ�
		}else{
			temp_time = calculate_path_time(path_velocity,run_mode);//���������p�X�̎��Ԃ��v�Z
			if( temp_time < fast_time ){			//���܂ł̃p�X�Ɣ�ׁA�͂₢�̂��`�F�b�N
				//������΁Atry_count���L�^�����Ԃ��X�V
				fast_path = try_count;
				fast_time = temp_time;
			}
		}
		roop_flag = create_some_path(junction);		//create_some_path�̓p�X�����ł��Ȃ���OFF��Ԃ��̂�,��������ƃ��[�v�𔲂���
	}
	printf("try %d,  fast %d\n",try_count,fast_path);
		
	//junction�����Z�b�g
	for( try_count= 0; try_count < JUNCTION_MAX; try_count++){
		junction[try_count].all = 0;
	}
	
	//try_count�܂ŏ�̃��[�v��������x�܂킵�āA�ړI�̃p�X���擾
	for( try_count = 0; try_count < fast_path; try_count++){
		create_some_path(junction);		//�p�X����
	}
	
	//1�񑫂�Ȃ����A�������ďI���
	create_some_path(junction);		//�p�X����
	
}

void improve_path(){
	unsigned char count=0;
	unsigned char number=0;		//���𐔂��邾��
	unsigned char naname_flag = OFF;	//���݋@�̂��΂߂��𔻒f	ON�Ȃ�΂ߑ��s��
	
	while( path[count].all != 0 ){		//path���I���ΏI��
		
		if( naname_flag == ON ){							//�΂ߑ��s���Ȃ�	�m���ɒ��i����(distance)��0�̂͂�
			if( path[count].element.distance == 0 ){
				naname_flag = OFF;
			
			}else{
				
				if( path[count+1].element.distance >= 1 ){			//���̃^�[����90mm�ȏ㒼�i(�΂ߏI���)
					path[count+1].element.turn = 4;							//45���^�[���ɕύX
					path[count+1].element.distance -= 1;					//����������90mm���炷
					naname_flag = OFF;
				
				}else if( path[count+2].element.distance >= 1 ){	//���̎��̃^�[����90mm�ȏ㒼�i(�΂ߏI���)
					
					if( path[count].element.muki == path[count+1].element.muki ){		//����������2��^�[��
						path[count].element.turn = 5;					//135���^�[���ɕύX
						
						path[count+1].all = path[count+2].all;
						//1���炷
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
						
						path[count+1].element.distance -= 1;				//����������90mm���炷
						naname_flag = ON;
						
						
					}else{																//���݂̃^�[��(�M�U�M�U)
						path[count].element.distance += 1;				//�΂߂̒���������1���₷
						
						path[count+1].all = path[count+2].all;
						//1���炷
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
					}
					
				}else{												//�܂��܂��΂߂͑����Ȃ�
					if( path[count].element.muki == path[count+1].element.muki ){		//����������2��^�[��	�R�̎�
						path[count].element.turn = 6;					//�΂�90���^�[���ɕύX
					
						path[count+1].all = path[count+2].all;
						//1���炷
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}					
					
					}else{																//�Ⴄ������2��^�[��	�M�U�M�U
						path[count].element.distance += 1;				//�΂߂̒���������1���₷
						
						path[count+1].all = path[count+2].all;
						//1���炷
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
							
					}
				}
				
			}
		
		
		}else if( path[count].element.distance >= 1 ){		//90mm�ȏ㒼�i����Ȃ�
			
			if( path[count+1].element.distance >= 1 ){		//�^�[�����90mm�ȏ㒼�i����Ȃ�	����̃`�F�b�N���s��
				path[count].element.turn = 2;					//����^�[���ɕύX
				path[count].element.distance -= 1;				//����������90mm���炷
				path[count+1].element.distance -= 1;			//����������90mm���炷
			
			}else{											//�^�[����90mm���i�͂��Ȃ��Ȃ�
				
				if( path[count].element.muki == path[count+1].element.muki ){	//���������ɋȂ���Ȃ�(U�^�[��)
					
					if( path[count+2].element.distance >= 1 ){		//U�^�[����90mm���i����Ȃ�
						path[count].element.turn = 3;					//180���^�[���ɕύX
						path[count].element.distance -= 1;				//����������90mm���炷
						path[count+2].element.distance -= 1;			//����������90mm���炷
						
						path[count+1].all = path[count+2].all;
						//1���炷
						for( number = count+1; path[number].all != 0; number++){
							path[number].all = path[number+1].all;
						}
						
					}else{											//U�^�[���シ���Ȃ���Ȃ�
						
						if( path[count+2].all != 0 ){					//path���I����ĂȂ����`�F�b�N�@�I����ĂȂ���΋t�����Ƀ^�[���̂͂�
							/*
							path[count].element.turn = 5;					//135���^�[���ɕύX
							path[count].element.distance -= 1;				//����������90mm���炷
							
							path[count+1].all = path[count+2].all;
							//1���炷
							for( number = count+1; path[number].all != 0; number++){
								path[number].all = path[number+1].all;
							}
							naname_flag = ON;
							*/
						}
						
					}
				
				}else{		//�Ⴄ���@�ɋȂ���Ȃ�
					/*
					path[count].element.turn = 4;							//45���^�[���ɕύX
					path[count].element.distance -= 1;						//����������90mm���炷
					naname_flag = ON;
					*/
				}
								
			}
		
		}
		
		count++;
	}
	
}

void improve_advance_path(){
	unsigned char count=0;			//���𐔂��邾��
	unsigned char temp_distance=0;	//�ꎞ�I�ȋ����ۑ�		
	unsigned char naname_flag = OFF;	//���݋@�̂��΂߂��𔻒f	ON�Ȃ�΂ߑ��s��
	
	while( path[count].all != 0 ){		//path���I���ΏI��
		
		if( naname_flag == ON ){							//�΂ߑ��s���Ȃ�	�m���ɒ��i����(distance)��0�̂͂�
				
			if( path[count+1].element.distance >= 1 ){			//���̃^�[����90mm�ȏ㒼�i(�΂ߏI���)
				
				path[count].element.turn = 4;							//45���^�[���ɕύX
				path[count+1].element.distance -= 1;					//����������90mm���炷
				naname_flag = OFF;
				count++;												//�z�������
				
			}else if( path[count+2].element.distance >= 1 ){	//���̎��̃^�[����90mm�ȏ㒼�i(�΂ߏI���)
				
				if( path[count].element.muki == path[count+1].element.muki ){		//����������2��^�[��
					
					path[count].element.turn = 5;					//135���^�[���ɕύX
					displace_path(count+1);							//����炷
					path[count+1].element.distance -= 1;			//�^�[����̒���������90mm���炷
					naname_flag = OFF;
					count++;										//�z�������
					
				}else{																//���݂̃^�[��(�M�U�M�U)
					
					path[count].element.distance += 1;				//�΂߂̒���������1���₷
					temp_distance = path[count].element.distance;	//�������ꎞ�I�Ɏ����Ă���
					displace_path(count);							//����炷
					path[count].element.distance = temp_distance;	//���������Ȃ���
						
				}
				
			}else{												//�܂��܂��΂߂͑����Ȃ�
					
				if( path[count].element.muki == path[count+1].element.muki ){		//����������2��^�[��	�R�̎�
					
					path[count].element.turn = 6;					//�΂�90���^�[���ɕύX
					displace_path(count+1);							//����炷
					count++;										//�z�������
					
				}else{																//�Ⴄ������2��^�[��	�M�U�M�U
					
					path[count].element.distance += 1;				//�΂߂̒���������1���₷
					temp_distance = path[count].element.distance;	//�������ꎞ�I�Ɏ����Ă���
					displace_path(count);							//����炷
					path[count].element.distance = temp_distance;	//���������Ȃ���
				
				}
			}
		
		}else {										//�΂߂���Ȃ����
			
			if( path[count+1].element.distance >= 1 ){		//�^�[�����90mm�ȏ㒼�i����Ȃ�	����̃`�F�b�N���s��
			
				if( (count != 0) || (path[0].element.distance > 1) ){		//�����[�̃^�[������Ȃ����
			
					path[count].element.turn = 2;					//����^�[���ɕύX
					path[count].element.distance -= 1;				//����������90mm���炷
					path[count+1].element.distance -= 1;			//����������90mm���炷
			
				}
			
			}else{											//�^�[����90mm���i�͂��Ȃ��Ȃ�
				
				if( path[count].element.muki == path[count+1].element.muki ){	//���������ɋȂ���Ȃ�(U�^�[��)
					
					if( path[count+2].element.distance >= 1 ){		//U�^�[����90mm���i����Ȃ�
			
						path[count].element.turn = 3;					//180���^�[���ɕύX
						path[count].element.distance -= 1;				//����������90mm���炷
						path[count+2].element.distance -= 1;			//����������90mm���炷
						displace_path(count+1);							//����炷
						
					}else{											//U�^�[���シ���Ȃ���Ȃ�
						
						if( path[count+2].all != 0 ){					//path���I����ĂȂ����`�F�b�N�@�I����ĂȂ���΋t�����Ƀ^�[���̂͂�
			
							path[count].element.turn = 5;					//135���^�[���ɕύX
							path[count].element.distance -= 1;				//����������90mm���炷
							displace_path(count+1);							//����炷
							naname_flag = ON;
							
						}
						
					}
				
				}else{		//�Ⴄ���@�ɋȂ���Ȃ�
					
					path[count].element.turn = 4;							//45���^�[���ɕύX
					path[count].element.distance -= 1;						//����������90mm���炷
					naname_flag = ON;
					
				}
								
			}	
			count++;		//�z�������
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

