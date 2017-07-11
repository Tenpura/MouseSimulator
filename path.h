#ifndef DEF_PATH_H
#define DEF_PATH_H

typedef union {
		unsigned char all;				//�ꊇ
		struct {
			unsigned char up	:1;		//��	x=1,y=0�̕���
			unsigned char right	:1;		//��	x=-1,y=0�̕���
			unsigned char down	:1;		//��	x=0,y=-1�̕���
			unsigned char left	:1;		//��	x=0,y=1�̕���
			unsigned char now	:4;		//���݂̕������Ǘ��A���̐��Asave_direction���r�b�g�V�t�g����ƌ��݂̌����ɑΉ�	
		} element;
}SAVE_DIRECTION;				//���ɍs���}�X�̕�����ۑ�

void add_path_turn(SAVE_DIRECTION next_direction, unsigned char path_number);		//���̐i�s�}�X�̕����Ƃ����ڂ�path����^�����path�̃^�[������(�����Ə����)����������

signed char add_path(SAVE_DIRECTION next_direction, unsigned char path_number, unsigned char priority);	//�����ڂ�path���ƗD��x(�I�����̉��Ԗڂ�I������̂��j��^�����path��ǉ�����
//�D��x��left->down->right->up�̏��Ƃ���
//�p�X�����ł����ON�A�ł��Ȃ���OFF��Ԃ�

void create_path();				//path�����A�����������Ȃ璼�i�D��B�����^�[���̂�

signed char create_some_path(JUNCTION *junction);
//�o�H�I���悤��path�����B����_�̔z���^����Ƃ���ɉ�����path����,����_�̔z��͌J��Ԃ��g�p���������߈����Ƃ��ēn���i�O���[�o���̑���j�B�@
//path�������ł����ꍇON���A���ׂĖԗ������ꍇOFF��Ԃ��B�p�X�𐶐��ł��Ȃ������ꍇ(�~��)-1��Ԃ��B

void close_dead_end(char target_x, char target_y);			//�ڕW��(x,y)���܏��H���m���߂āA�܏��H�Ȃ����֐��@�����ꍇ�ċN�����ɓ���

void create_map_for_shortest_close_dead_end(char target_x,char target_y);	//�ŒZ�p�����}�b�v�����B���T����Ԃ��Ȃ��܏��H���ӂ���

float calculate_run_time(int n_mm, int accel_value, int de_accel_value, float max_velocity, float syo_sokudo, float end_velocity);	//��`�������ő��s�����Ƃ��́A���s���Ԃ����߂�֐�
//�����@n_mm:�ڕW����[mm]	accel_value:�����x[mm/s/s]	de_accel_value:�����x[mm/s/s]	
//		max_velcoty:�ō����x[mm/s]	start_velocity:�����x[mm/s]	end_velocity:�I�[���x[mm/s]

float calculate_path_time(float path_velocity, unsigned char run_mode);		//������path�̑��s���Ԃ��v�Z����B�����Ƃ��čō����ƃ^�[���̃��[�h��^����ƁA���Ԃ�Ԃ��B

void selection_root(float path_velocity, unsigned char run_mode);			//�ŒZ�o�H�I���@���񂩕����}�b�v�ɋt�炤

void improve_path();			//path�ɑ���^�[���Ƃ��ǉ�

void improve_advance_path();	//path�ɑ���^�[���Ǝ΂߂�ǉ�

void run_by_path(float path_velocity, unsigned char run_mode);	//�ǂ̂��炢�̑��x�ő���̂����w�肷��ƁApath�ǂ���ɑ��� mode���オ��قǃ^�[�����xUP

void displace_path(unsigned int path_number);	//path_number�ڂ̗v�f���������āA����l�߂�
	
void path_reset();				//path�����Z�b�g

void auto_start();				//�I�[�g�X�^�[�g�p

#endif