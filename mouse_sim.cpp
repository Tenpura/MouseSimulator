#include "DxLib.h"
#include "define.h"
#include "map.h"

#include<iostream>
#include<fstream>

using namespace std;


#define toolbutton_width 40			//��ʉE���̗]�������̉���(�X�N���[���o�[�Ɖ�ʒ[�̊�)
#define toolbutton_length 40		//��ʉE���̗]�������̏c��(�X�N���[���o�[�Ɖ�ʒ[�̊�)

#define magin 5			//��ʒ[����̗]�T
#define maze_scale	(MAZE_SIZE+1)	//���~���̖��H��[�s�N�Z��]
#define kukaku_size 40	//����̑傫��[�s�N�Z��]
#define pole_size 3		//���̑傫��(�ǂ̌���)[�s�N�Z��]

//#define PI 3.14159	//�~����

static const int console_area = 400;  //�X�N���[�����E�����ɃR���\�[���p�̋�Ԃ��ǂꂭ�炢�p�ӂ��邩
int window_width = 1100;	//��ʂ̉𑜓x

int window_length = 700;	//��ʂ̉𑜓x

static int maze_area_width = (window_width-console_area);	//���H�����̉𑜓x

//  ����	�@  	���x �@�ڕW�p�x	�N���\�C�h�p	�O����mm�@	�㋗��mm	�����x�萔	����
//�T���̏����
init_slalom slalom_turn_90_right	=		{	MUKI_RIGHT,		500.0f,	90.0f,		20.0f,		5.0f,		23.0f,		0.480,		0.265f};		//90���E��]�X�����[��
init_slalom slalom_turn_90_left		=		{	MUKI_LEFT,		500.0f,	90.0f,		20.0f,		5.0f,		23.0f,		0.480,		0.265f};		//90������]�X�����[��

init_slalom slalom_turn_90_right_shortest=	{	MUKI_RIGHT,		500.0f,	90.0f,		20.0f,		5.0f,		23.0f,		0.480,		0.265f};		//90���E��]�X�����[��
init_slalom slalom_turn_90_left_shortest=	{	MUKI_LEFT,		500.0f,	90.0f,		20.0f,		5.0f,		23.0f,		0.480,		0.265f};		//90������]�X�����[��
//tekitou 

//����
init_slalom slalom_big_turn_90_left[2]	=	{	{MUKI_LEFT,		700.0f,	90.0f,		30.0f,		13.000f,	80.000f,	0.1408,		0.160f},		//90������]����X�����[��
{MUKI_LEFT,		850.0f,	88.8f,		30.0f,		22.154f,	30.154f,	0.0955,		0.000f}};		//90������]����X�����[���@���x�A�b�v


//���̂���ȂɑO���������̂��킩��Ȃ�
init_slalom slalom_big_turn_90_right[2]	=	{	{MUKI_RIGHT,	700.0f,	90.0f,		30.0f,		43.000f,	80.000f,	0.1408,		0.160f},		//90������]����X�����[��
{MUKI_RIGHT,	850.0f,	89.8f,		30.0f,		20.154f,	32.154f,	0.0955,		0.0f}};		//90������]����X�����[��	���x�A�b�v

//70

init_slalom slalom_big_turn_180_left[2]	=	{	{MUKI_LEFT,		700.0f,	180.0f,		40.0f,		20.000f,	80.000f,	0.1044,		0.290f},		//180������]����X�����[��
{MUKI_LEFT,		1000.0f,180.0f,		80.0f,		10.000f,	10.000f,	0.0738,		0.0f}};		//180������]����X�����[��	���x�A�b�v
init_slalom slalom_big_turn_180_right[2]=	{	{MUKI_RIGHT,	700.0f,	177.0f,		40.0f,		20.000f,	80.000f,	0.1044,		0.290f},		//180������]����X�����[��
{MUKI_RIGHT,	1000.0f,180.0f,		80.0f,		10.000f,	10.000f,	0.0738,		0.0f}};		//180������]����X�����[��	���x�A�b�v



//  ����	�@  	���x �@�ڕW�p�x	�N���\�C�h�p	�O����mm�@	�㋗��mm	�����x�萔	����
//�΂�
init_slalom slalom_turn_135_start_left[2]=	{	{MUKI_LEFT,		500.0f,	137.0f,		45.0f,		60.0f,		30.507f,	0.1768,		0.232f},		//135������]����X�����[��
{MUKI_LEFT,		700.0f,	135.0f,		45.0f,		30.44f,		10.000f,	0.1251,		0.0f}};
init_slalom slalom_turn_135_start_right[2]=	{	{MUKI_RIGHT,	500.0f,	135.5f,		45.0f,		60.0f,		30.000f,	0.1768,		0.232f},		//135������]����X�����[��
{MUKI_RIGHT,	700.0f,	135.0f,		45.0f,		30.44f,		10.000f,	0.1251,		0.0f}};

init_slalom slalom_turn_135_end_left[2]=	{	{MUKI_LEFT,		500.0f,	138.0f,		45.0f,		45.0f,		80.00f,		0.1768,		1.0f}};		//135������]����X�����[��
init_slalom slalom_turn_135_end_right[2]=	{	{MUKI_RIGHT,	500.0f,	137.5f,		45.0f,		45.0f,		75.00f,		0.1768,		1.0f}};		//135������]����X�����[��

init_slalom slalom_turn_45_start_left[2]=	{	{MUKI_LEFT,		700.0f,	45.0f,		15.0f,		5.000f,		40.000f,	0.1911,		0.1f}};		//45������]����X�����[��
init_slalom slalom_turn_45_start_right[2]=	{	{MUKI_RIGHT,	700.0f,	45.0f,		15.0f,		15.000f,	40.000f,	0.1910,		0.1f}};		//45������]����X�����[��

init_slalom slalom_turn_45_end_left[2]=		{	{MUKI_LEFT,		500.0f,	45.0f,		15.0f,		45.807f,	25.807f,	0.1910,		0.1f}};		//45������]����X�����[��
init_slalom slalom_turn_45_end_right[2]=	{	{MUKI_RIGHT,	500.0f,	45.0f,		15.0f,		45.807f,	25.807f,	0.1910,		0.1f}};		//45������]����X�����[��

init_slalom slalom_turn_90_oblique_right[2]={	{MUKI_RIGHT,	500.0f,	92.5f,		20.0f,		15.0f,		10.0f,		0.2344,		0.146f}};		//90���E��]�X�����[��
init_slalom slalom_turn_90_oblique_left[2]=	{	{MUKI_LEFT,		500.0f,	92.5f,		20.0f,		15.0f,		10.0f,		0.2344,		0.146f}};		//90������]�X�����[��




char key[256];
int look_xy[2]={0};	//�����Ă鎋�_�̍��W,xy�̏�
int scroll_scale_x=1;	//x�����ɃX�N���[���o�[�̉��{��ʂ�������
int scroll_scale_y=1;	//y�����ɃX�N���[���o�[�̉��{��ʂ�������
int bar_x,bar_y;	//�X�N���[���o�[���N���b�N�����Ƃ��̍��W�ۑ�
bool bar_flag_x,bar_flag_y;		//�X�N���[���o�[���N���b�N���Ă��TRUE
bool button_flag =false;		//���{�^���������Ă�Ƃ�TRUE
bool edit_mode = false;			//�ǂ�������郂�[�h�ƃe�X�g���[�h�̐؂�ւ�

//�F
int red,white,gray,blue,black,green;

//�摜�ۑ��p�ϐ�
int blue_arror[2]={0};
int red_arror[2]={0};
int icon;
int tool_button[4]={0};


int color_bit;

//�`��֌W
void draw_all(adachi sim_map);
void draw_mouse(unsigned char mouse_x,unsigned char mouse_y,unsigned char muki);
void draw_step(adachi &sim_map);
void draw_path(path sim_path);


//���H��̍��W���w�肷��ƁA���̍��W�̍���̃s�N�Z��(�H)��Ԃ�
int convert_draw_x(signed char maze_x);
int convert_draw_y(signed char maze_y);


//���̍��W�̍���̃s�N�Z��(�H)���w�肷��ƁA���H��̍��W��Ԃ�
int convert_maze_x(signed int draw_x);
int convert_maze_y(signed int draw_y);

//45����]������֐�
void direction_turn_half(signed char *direction_x,signed char *direction_y, unsigned char direction_turn_muki);		


//����N���X����Ǐ����p������֐�
void get_square(adachi& orig, adachi& tar, unsigned char x, unsigned char y);

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{

	ChangeWindowMode(TRUE);		//�E�C���h�E���[�h�ύX

	if( DxLib_Init() == -1 )		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}

	SetWindowSizeChangeEnableFlag(TRUE);	//�E�C���h�E�T�C�Y�ς�
	SetGraphMode( window_width , window_length , 32 ) ;		//�𑜓x�A�J���[�r�b�g�ύX

	SetDrawScreen(DX_SCREEN_BACK);
	GetScreenState(&window_width,&window_length,&color_bit);		//�摜�̉𑜓x����уJ���[�r�b�g�擾


    
	//������
	bar_flag_x = false;	
	bar_flag_y = false;	
	button_flag = false;


	//�F
	red = GetColor(255, 0, 0);
	white = GetColor(255, 255, 255);
	gray = GetColor(169, 169, 169);
	blue = GetColor(0, 0, 255);
	black = GetColor(0, 0, 0);
	green = GetColor(0,255,0);

	icon = LoadGraph("�摜/icon.png");
	LoadDivGraph("�摜/blue_arror.png",2,1,2,40,20,blue_arror) ;
	LoadDivGraph("�摜/red_arror.png",2,1,2,40,20,red_arror) ;
	tool_button[0] = LoadGraph("�摜/�c�[���{�^��.png");
	tool_button[1] = LoadGraph("�摜/�c�[���{�^��END.png");
	tool_button[2] = LoadGraph("�摜/�c�[���{�^����.png");
	tool_button[3] = LoadGraph("�摜/�c�[���{�^����.png");



	adachi sim_map, now_map;	
	path sim_path;
	MAP_DATA input_data, now_map_data;

	status sim_status;		//status�N���X

	unsigned char h_data[16][16]={{14,4,6,5,13,12,4,5,13,12,4,5,12,4,6,5},{12,0,5,8,2,1,9,8,2,1,9,8,1,8,5,9},{9,9,8,1,13,9,8,2,4,1,8,3,11,11,8,1},{9,8,1,8,1,8,1,12,1,8,1,14,4,5,11,9},{8,1,9,9,8,1,8,1,8,3,11,12,1,8,5,9},{9,10,1,8,1,10,1,8,3,14,4,1,9,9,9,9},{8,4,3,9,10,5,10,3,14,4,3,11,11,9,9,9},{9,8,4,2,6,2,5,12,4,0,6,6,7,11,9,9},{8,1,8,4,6,6,3,8,3,10,6,6,6,5,9,9},{9,10,1,9,12,6,4,2,7,12,6,6,6,3,9,9},{9,13,8,1,9,12,1,12,6,2,4,4,4,6,0,3},{9,9,11,9,8,1,11,9,13,13,9,9,9,13,9,13},{9,9,12,3,9,10,5,8,0,0,0,0,0,0,1,9},{9,8,2,5,10,6,2,3,11,11,11,11,11,11,10,1},{8,2,7,10,6,4,6,4,6,6,4,6,4,6,5,9},{10,6,6,6,6,2,6,2,6,6,2,6,2,6,2,3}};

	//�����ŒZ{{14, 4, 6, 5,13,12, 4, 4, 7,12, 4, 5,12, 4, 6, 7},{12, 2, 5, 8, 2, 1, 9, 8, 6, 1, 9, 8, 1, 8, 5,13},{ 8, 5,10, 1,12, 1, 8, 2, 4, 1, 8, 3,11,11, 8, 1},{ 9,10, 5, 8, 1,10, 2, 5, 9, 8, 3,14, 4, 5,11, 9},{ 9,12, 2, 1, 8, 4, 6, 1, 8, 3,14, 4, 1, 8, 5, 9},{ 8, 2, 4, 2, 1, 8, 5, 8, 3,14, 4, 1, 9, 9, 9, 9},{ 8, 4, 2, 6, 0, 3,10, 3,14, 4, 3,11,11,11, 9, 9},{ 9, 8, 4, 6, 2, 6, 5,12, 4, 0, 6, 6, 6, 7, 9, 9},{ 8, 1, 9,12, 6, 6, 3, 8, 3,10, 6, 6, 6, 5, 9, 9},{ 9, 8, 1, 9,12, 6, 4, 2, 7,12, 6, 6, 6, 3, 9, 9},{ 8, 3,11, 9, 9,12, 3,14, 4, 2, 6, 6, 6, 6, 0, 1},{ 9,12, 7, 9, 9,10, 5,12, 3,13,13,13,13,12, 3,11},{ 9, 8, 6, 3,10, 5, 8, 0, 4, 0, 0, 0, 0, 0, 6, 5},{ 9, 8, 6, 4, 5,10, 3,11,11,11,11,11,11,11,12, 1},{ 8, 2, 6, 3,10, 4, 6, 4, 6, 6, 4, 6, 4, 6, 1, 9},{10, 6, 6, 6, 6, 2, 6, 2, 6, 6, 2, 6, 2, 6, 2, 3}};
	//�����ŒZ{{14,4,6,5,13,12,4,4,7,12,4,5,12,4,6,5},{12,2,5,8,2,1,9,8,6,1,9,8,1,8,5,9},{8,5,10,1,12,1,8,2,4,1,8,3,11,11,8,1},{9,10,5,8,1,10,2,5,9,8,1,14,4,5,11,9},{9,12,2,1,8,4,6,1,8,3,11,12,1,8,5,9},{8,2,4,2,1,8,5,8,3,14,4,1,9,9,9,9},{8,4,2,6,0,1,10,3,14,4,3,11,11,11,9,9},{9,8,4,6,2,2,5,12,4,0,6,6,6,7,9,9},{8,1,11,12,6,6,3,8,3,10,6,6,6,5,9,9},{9,8,5,9,13,14,4,2,7,12,6,6,6,3,9,9},{9,11,11,9,9,12,3,14,4,2,4,4,4,6,0,1},{9,12,7,9,8,3,12,4,3,13,9,9,9,12,3,9},{9,8,6,3,10,5,9,8,4,0,0,0,0,0,4,3},{9,8,6,4,5,10,2,3,11,11,11,11,11,11,10,5},{8,2,6,3,10,4,6,4,6,6,4,6,4,6,5,9},{10,6,6,6,6,2,6,2,6,6,2,6,2,6,2,3}};	

	sim_map.convert_mapdata(h_data);

	for(int i=0;i<MAZE_SIZE;i++){
		for(int j=0;j<MAZE_SIZE;j++){
			for(int k=0; k<4 ; k++){
				sim_map.remember_exist(i,j,k);
			}
		}
	}

	sim_map.output_map_data(&input_data);	//map_data�ɖ��H��f���o��

	sim_path.input_map_data(&input_data);
	sim_path.create_path_naname();
	//sim_path.selection_root(4000,18000,1);
	float path_time=0.0;
	path_time = sim_path.calculate_path_time(4000,18000,0);

	//�}�E�X����������W
	unsigned char now_x = 0;
	unsigned char now_y = 0;
	//�S�[�����W
	unsigned char goal_x = GOAL_x;
	unsigned char goal_y = GOAL_y;


	get_square(sim_map,now_map,now_x,now_y);	


	bool key_flag=false;
	bool edit_click_flag = false;		//�G�f�B�b�g���[�h���ɃN���b�N���Ă��邩���ʗp�B�A���N���b�N�΍�

	while(ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && GetHitKeyStateAll(key)==0){	
		GetScreenState(&window_width,&window_length,&color_bit);
		DrawBox(0, 0, maze_area_width, window_length, white, TRUE);		//�w�i(��)

		//DrawFormatString(50,50,black,"x-%d \n y-%d",icon_x,icon_y);

		if(edit_mode){
			draw_all(sim_map);	//�������Ƃ̖��H��\��

		}else{
			//sim_map.set_step_all_search(GOAL_x,GOAL_y);
			//sim_map.set_step(GOAL_x,GOAL_y);
			//sim_map.close_dead_end();
			//draw_step(sim_map);
			//draw_path(sim_path);

			if(key[KEY_INPUT_X]==1){
				now_map.set_step_by_known(goal_x,goal_y);
				draw_path(sim_path);
			}else now_map.set_step(goal_x,goal_y);

			//		now_map.set_step(goal_x,goal_y);
			draw_step(now_map);

			draw_mouse(sim_status.get_x_position(),sim_status.get_y_position(),sim_status.get_direction());
			draw_all(now_map);	//���}�E�X���m���Ă�����H������\��
		}
		


		if(!edit_mode)	DrawFormatString(maze_area_width+10,10,white,"path time  %f",path_time);

		//�g�p����
		if(edit_mode){
			DrawFormatString(maze_area_width+10,window_length-130,white,"T�F�e�X�g���[�h�Ɉڍs");
			DrawFormatString(maze_area_width+10,window_length-110,white,"F�F�V�~�����[�^�[���I������");

		}else{
			DrawFormatString(maze_area_width+10,window_length-170,white,"W�F���H������������");
			DrawFormatString(maze_area_width+10,window_length-150,white,"I�F�S�Ă̕ǂ�Y���");
			DrawFormatString(maze_area_width+10,window_length-130,white,"A�F�S�Ă̕ǂ�c������");
			DrawFormatString(maze_area_width+10,window_length-110,white,"E�F�G�f�B�b�g���[�h�Ɉڍs");
			DrawFormatString(maze_area_width+10,window_length-90,white, "F�F�V�~�����[�^�[���I������");
			DrawFormatString(maze_area_width+10,window_length-70,white, "X�F�������̃p�X�\��&���m�ǂ����̕���");
			DrawFormatString(maze_area_width+10,window_length-50,white, "�X�y�[�X�F�S�[���؂�ւ� (0,0)<->(7,7)");
			DrawFormatString(maze_area_width+10,window_length-30,white, "���������F�}�E�X�𓮂���");
		}

		if(key[KEY_INPUT_F]==1)	//�V�~�����[�V�����I��
			break;
		if(key[KEY_INPUT_E]==1)	//edit_mode��
			edit_mode = true;		
		if(key[KEY_INPUT_T]==1){	//test_mode��
			edit_mode = false;	
			now_map.init_map(MAZE_SIZE);
			sim_map.output_map_data(&input_data);	//map_data�ɖ��H��f���o��
			sim_path.input_map_data(&input_data);
			sim_path.create_path_naname();
			path_time = sim_path.calculate_path_time(4000,18000,0);
		}
		if(key[KEY_INPUT_A]==1){		
			sim_map.output_map_data(&input_data);	//map_data�ɖ��H��f���o��
			now_map.input_map_data(&input_data);//�S�m		
		}
		if(key[KEY_INPUT_I]==1)		
			now_map.init_map(MAZE_SIZE);		//���m		

		if( key_flag == true ){	
			if(CheckHitKeyAll() == 0){		//����������ĂȂ��Ȃ�
				key_flag = false;
			}

		}else{
			if(edit_mode){
				int icon_x,icon_y;
				GetMousePoint( &icon_x, &icon_y);		//�}�E�X�̈ʒu���擾

				//���݂̃}�E�X�|�C���^�̈ʒu���ǂ̕ǂɋ߂��̂����肵�Ă���
				//���ǂ����ǂ��l����΂悢�悤�ɍ��W�𒲐�
				int edit_x = convert_maze_x(icon_x);
				int edit_y = convert_maze_y(icon_y);
				if(icon_x >= (convert_draw_x(edit_x)+convert_draw_x(edit_x+1))/2)	//�}�E�X�̈ʒu���E�̕ǂɂ���Ă����
					edit_x++;						
				if(icon_y >= (convert_draw_y(edit_y)+convert_draw_y(edit_y-1))/2)	//�}�E�X�̈ʒu�����̕ǂɂ���Ă����
					edit_y--;						
						
				bool change_flag = false;	//�ǂ�ω������邩�ǂ���
				bool is_side_wall;	//�ω�������͉̂���(---)�ł����H
				//�ǂ̒Z�ӕ����̒��S������A���T�C�Y�~2�ȉ��͈̔͂ɂ���ΕǕύX�̌��ɓ����
				//�c�ǁi|�j
				if(icon_x <= convert_draw_x(edit_x)+3*pole_size){
					if(icon_x >= convert_draw_x(edit_x)-3*pole_size){
						change_flag = ~change_flag;
						is_side_wall = false;
					}
				}
				//���ǁi---�j
				if(icon_y <= convert_draw_y(edit_y)+3*pole_size){
					if(icon_y >= convert_draw_y(edit_y)-3*pole_size){
						change_flag = ~change_flag;
						is_side_wall = true;
					}
				}

				//��������͐؂�
				if((edit_x < 0) || (edit_x>MAZE_SIZE))
					change_flag = false;
				if((edit_y < 0) || (edit_y>MAZE_SIZE))
					change_flag = false;


				if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) == 0 ){	// �}�E�X�̍��N���b�N��������Ă��Ȃ�
					//�t���O��܂�
					edit_click_flag = false;
					
					//���ݑΏۂƂ��Ă���ǂ��n�C���C�g�\��
					//�ǂ��炩�������ω������Ƃ������A�ǕύX���ɂ����
					if(change_flag){
						if(is_side_wall){
							edit_x = convert_maze_x(icon_x);
							DrawBox( convert_draw_x(edit_x)+pole_size, convert_draw_y(edit_y)-pole_size,convert_draw_x(edit_x+1)-pole_size, convert_draw_y(edit_y)+pole_size, blue, TRUE) ;
						}else{
							edit_y = convert_maze_y(icon_y);
							DrawBox( convert_draw_x(edit_x)-pole_size, convert_draw_y(edit_y-1)-pole_size,convert_draw_x(edit_x)+pole_size, convert_draw_y(edit_y)+pole_size, blue, TRUE) ;
						}
					}
					

				}else{      // �}�E�X�̍��N���b�N��������Ă���
					if(!edit_click_flag){
						//�N���b�N������Ǐ���ύX
						if(change_flag){
							if(is_side_wall){
								edit_x = convert_maze_x(icon_x);
								//(edit_x,edit_y)�̏�ǂ��A�ʑ��𔽓]������
								if(sim_map.get_wall(edit_x, edit_y, MUKI_UP) == TRUE)
									sim_map.destroy_wall(edit_x, edit_y, MUKI_UP);									
								else
									sim_map.create_wall(edit_x, edit_y, MUKI_UP);									
							}else{
								edit_y = convert_maze_y(icon_y);
								//(edit_x,edit_y)�̍��ǂ��A�ʑ��𔽓]������
								if(sim_map.get_wall(edit_x, edit_y, MUKI_LEFT) == TRUE)
									sim_map.destroy_wall(edit_x, edit_y, MUKI_LEFT);									
								else
									sim_map.create_wall(edit_x, edit_y, MUKI_LEFT);;
							}
						}
						
						edit_click_flag = true;
					}

					

				}
			}else{
				if(key[KEY_INPUT_W]==1){			//W�������Ə�������
					ofstream outputfile("map.txt");
					outputfile<<"{";
					for(int x = 0; x< MAZE_SIZE; x++){
						if(x!=0)	
							outputfile<<",";
						outputfile<<"{";
						outputfile<<static_cast<int>(sim_map.output_Hiramatu(x,0));
						for(int y = 1; y< MAZE_SIZE; y++){
							outputfile<<","<<static_cast<int>(sim_map.output_Hiramatu(x,y));
						}
						outputfile<<"}";
					}
					outputfile<<"};";
					outputfile.close();
				}
				
				if(key[KEY_INPUT_UP]==1){
					if(sim_status.get_direction()==MUKI_UP){
						sim_status.set_position( sim_status.get_x_position(), sim_status.get_y_position()+1 );
					}else{
						sim_status.set_direction(MUKI_UP);
					}
					key_flag = true;
				}
				if(key[KEY_INPUT_DOWN]==1){
					if(sim_status.get_direction()==MUKI_DOWN){
						sim_status.set_position( sim_status.get_x_position(), sim_status.get_y_position()-1 );
					}else{
						sim_status.set_direction(MUKI_DOWN);
					}
					key_flag = true;
				}
				if(key[KEY_INPUT_RIGHT]==1){
					if(sim_status.get_direction()==MUKI_RIGHT){
						sim_status.set_position( sim_status.get_x_position()+1, sim_status.get_y_position() );
					}else{
						sim_status.set_direction(MUKI_RIGHT);
					}
					key_flag = true;
				}
				if(key[KEY_INPUT_LEFT]==1){
					if(sim_status.get_direction()==MUKI_LEFT){
						sim_status.set_position( sim_status.get_x_position()-1, sim_status.get_y_position() );
					}else{
						sim_status.set_direction(MUKI_LEFT);
					}
					key_flag = true;
				}

				if(key[KEY_INPUT_SPACE]==1){		//�X�y�[�X�L�[�ŃS�[����(0,0)��
					if(goal_x==GOAL_x&&goal_y==GOAL_y){
						goal_x=0;
						goal_y=0;
					}else{
						goal_x=GOAL_x;
						goal_y=GOAL_y;
					}
					key_flag = true;
				}
				
				now_x = sim_status.get_x_position();
				now_y = sim_status.get_y_position();
				get_square(sim_map,now_map,now_x,now_y);
			}

		}
	}



	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������


	return 0 ;				// �\�t�g�̏I�� 
}


void draw_all(adachi sim_map){
	static int icon_x,icon_y;		//�}�E�X�A�C�R���̍��W

	static int bar_scale_x = maze_area_width-40*2-toolbutton_width;	//���X�N���[���o�[�̒���[�s�N�Z��]	�����l��max�T�C�Y(�X�N���[���ł��Ȃ�)
	static int closed_width = maze_scale*kukaku_size+magin*2-maze_area_width;		//��ʂ���؂�Ă镔���̒���[�s�N�Z��]

	static int bar_scale_y = window_length-40*2-toolbutton_length;	//�c�X�N���[���o�[�̒���[�s�N�Z��]	�����l��max�T�C�Y(�X�N���[���ł��Ȃ�)
	static int closed_length = maze_scale*kukaku_size+magin*2-window_length;		//��ʂ���؂�Ă镔���̒���[�s�N�Z��]

	static int draw_flag=FALSE;	//���̊֐������s���ꂽ��

	if(draw_flag==FALSE){
		//�X�N���[���o�[�̒�������
		//��
		if(closed_width < 0){	//�S�������Ă�Ȃ�
			closed_width = 0;
		}
		while(closed_width >= bar_scale_x){	//�����Ȃ��͈͂��X�N���[���G���A�𒴂���ꍇ
			closed_width /= 5;
			scroll_scale_x *= 5;
		}
		bar_scale_x -= closed_width; 

		//�c
		if(closed_length < 0){	//�S�������Ă�Ȃ�
			closed_length = 0;
		}
		while(closed_length >= bar_scale_y){	//�����Ȃ��͈͂��X�N���[���G���A�𒴂���ꍇ
			closed_length /= 5;
			scroll_scale_y *= 5;
		}
		bar_scale_y -= closed_length; 

		draw_flag=TRUE;	//flag�𗧂Ă�

	}

	GetMousePoint( &icon_x, &icon_y);		//�}�E�X�̈ʒu���擾

	//�X�N���[������
	//��
	if(bar_flag_x == true){		//�X�N���[���o�[���h���b�O���Ȃ�	
		look_xy[0] += icon_x - bar_x;
	}
	if(look_xy[0] < 0)	look_xy[0]=0;	//���
	if(look_xy[0] > maze_area_width-toolbutton_width-40*2-bar_scale_x){
		look_xy[0]=maze_area_width-bar_scale_x-toolbutton_width-40*2;	//����
	}
	//�c
	if(bar_flag_y == true){		//�X�N���[���o�[���h���b�O���Ȃ�	
		look_xy[1] += icon_y - bar_y;
	}
	if(look_xy[1] < 0)	look_xy[1]=0;	//���
	if(look_xy[1] > window_length-toolbutton_length-40*2-bar_scale_y){
		look_xy[1]=window_length-bar_scale_y-toolbutton_length-40*2;	//����
	}



	//����`��
	for(int i = 0; i < maze_scale; i++){
		for(int j = 0; j < maze_scale; j++){
			DrawBox( convert_draw_x(i)-pole_size, convert_draw_y(j-1)-pole_size, convert_draw_x(i)+pole_size, convert_draw_y(j-1)+pole_size, red, TRUE) ;
		}
	}

	

	//�������̕�(---)��`��
	for(int i = 0; i < MAZE_SIZE; i++){
		for(int j = 0; j < MAZE_SIZE; j++){
			if( sim_map.get_wall(i,j,MUKI_UP) == TRUE){
				DrawBox( convert_draw_x(i)+pole_size, convert_draw_y(j)-pole_size,convert_draw_x(i+1)-pole_size, convert_draw_y(j)+pole_size, red, TRUE) ;
			}
		}
		if( sim_map.get_wall(i,0,MUKI_DOWN) == TRUE){
			DrawBox( convert_draw_x(i)+pole_size, convert_draw_y(0-1)-pole_size,convert_draw_x(i+1)-pole_size, convert_draw_y(0-1)+pole_size, red, TRUE) ;
		}

	}
	//�c�����̕�( | )��`��
	for(int j = 0; j < MAZE_SIZE; j++){
		for(int i = 0; i < MAZE_SIZE; i++){
			if( sim_map.get_wall(i,j,MUKI_LEFT) == TRUE){
				DrawBox( convert_draw_x(i)-pole_size, convert_draw_y(j-1)+pole_size,convert_draw_x(i)+pole_size, convert_draw_y(j)-pole_size, red, TRUE) ;
			}
		}
		if( sim_map.get_wall(MAZE_SIZE-1,j,MUKI_RIGHT) == TRUE){
			DrawBox( convert_draw_x(MAZE_SIZE)-pole_size, convert_draw_y(j-1)+pole_size,convert_draw_x(MAZE_SIZE)+pole_size, convert_draw_y(j)-pole_size, red, TRUE) ;
		}
	}

	//�c����
	DrawBox(maze_area_width-40,0,maze_area_width,window_length,gray,TRUE);		
	DrawBox(maze_area_width-35,40+look_xy[1],maze_area_width-5,40+bar_scale_y+look_xy[1],blue,TRUE);	//�X�N���[���o�[
	DrawGraph(maze_area_width-40,5,blue_arror[0],TRUE);			//����
	DrawGraph(maze_area_width-40,window_length-25-toolbutton_length,blue_arror[1],TRUE);		//�����
	DrawBox(maze_area_width-40,0,maze_area_width,window_length-toolbutton_length,black,FALSE);			//�g
	DrawBox(maze_area_width-40,40-5,maze_area_width,window_length-40+5-toolbutton_length,black,FALSE);			//�g	

	//������
	DrawBox(0,window_length-40,maze_area_width,window_length,gray,TRUE);		
	DrawBox(40+look_xy[0],window_length-35,40+bar_scale_x+look_xy[0],window_length-5,blue,TRUE);	//�X�N���[���o�[
	DrawRotaGraph(10+5,window_length-40+20,1.0,-PI/2,blue_arror[0],TRUE);				//�����@�������]�`��
	DrawRotaGraph(maze_area_width-25-toolbutton_width+10,window_length-40+20,1.0,-PI/2,blue_arror[1],TRUE);				//�E���@��������]�`��
	DrawBox(0,window_length-40,maze_area_width-toolbutton_width,window_length,black,FALSE);			//�g
	DrawBox(40-5,window_length-40,maze_area_width-40-toolbutton_width+5,window_length,black,FALSE);			//�g	





	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) == 0 ){	// �}�E�X�̍��N���b�N��������Ă��Ȃ�
		//�t���O��܂�
		bar_flag_x = false;	
		bar_flag_y = false;	
		button_flag = false;

	}else{      // �}�E�X�̍��N���b�N��������Ă���
		if( (bar_flag_x == false) && (bar_flag_y == false) ){		//�X�N���[���o�[���쒆�͉����Ȃ�
			//���̍����
			if( (icon_x <= 40) && (icon_y >= (window_length-40)) ){
				look_xy[0] -= 1;			
				//�摜��ύX
				DrawBox(0,window_length-40,40-5,window_length,red,TRUE);
				DrawRotaGraph(10+5,window_length-40+20,1.0,-PI/2,red_arror[0],TRUE);				//�����@�������]�`��
				button_flag = true;
			}

			//���̉E���
			if( (icon_x >= maze_area_width-40-toolbutton_width) && (icon_y >= (window_length-40)) ){
				look_xy[0] += 1;			
				//�摜��ύX
				DrawBox(maze_area_width-40+5-toolbutton_width,window_length-40,maze_area_width-toolbutton_width,window_length,red,TRUE);
				DrawRotaGraph(maze_area_width-25-toolbutton_width+10,window_length-40+20,1.0,-PI/2,red_arror[1],TRUE);				//�E���@��������]�`��
				button_flag = true;
			}


			//�c�̏���
			if( (icon_y <= 40) && (icon_x >= (maze_area_width-40)) ){
				look_xy[1] -= 1;			
				//�摜��ύX
				DrawBox(maze_area_width-40,0,maze_area_width,40-5,red,TRUE);
				DrawGraph(maze_area_width-40,5,red_arror[0],TRUE);			//����	
				button_flag = true;
			}

			//�c�̉����
			if( (icon_y >= window_length-40-toolbutton_length) && (icon_x >= (maze_area_width-40)) ){
				look_xy[1] += 1;			
				//�摜��ύX
				DrawBox(maze_area_width-40,window_length-40+5-toolbutton_length,maze_area_width,window_length-toolbutton_length,red,TRUE);
				DrawGraph(maze_area_width-40,window_length-25-40,red_arror[1],TRUE);			//�����	
				button_flag = true;
			}
		}

		if( button_flag == false ){		//�{�^�����쒆�͉����Ȃ�
			//���̃X�N���[���o�[
			if( (icon_x <= (40+bar_scale_x+look_xy[0])) && (icon_x >= (40+look_xy[0]))){
				if( (icon_y >= (window_length-40-5)) && (icon_y <= (window_length-5))){ 
					//�}�E�X���X�N���[���o�[�̒��ɂ����
					DrawBox(40+look_xy[0],window_length-40+5,40+bar_scale_x+look_xy[0],window_length-5,red,TRUE);	//�X�N���[���o�[��Ԃ�����
					bar_flag_x=true;	//�t���O�����Ă�
					bar_x = icon_x;	//�N���b�N�����ʒu��ۑ�

				}else if(bar_flag_y == true){
					//�}�E�X���X�N���[���o�[�̒��ɂȂ��Ƃ��A�h���b�O���Ă�Ȃ�
					DrawBox(40+look_xy[0],window_length-40-5,40+bar_scale_x+look_xy[0],window_length-5,red,TRUE);	//�X�N���[���o�[��Ԃ�����
					bar_x = icon_x;	//�N���b�N�����ʒu��ۑ�

				}	
			}


			//�c�̃X�N���[���o�[
			if( (icon_y <= (40+bar_scale_y+look_xy[1])) && (icon_y >= (40+look_xy[1]))){
				if( (icon_x >= (maze_area_width-40-5)) && (icon_x <= (maze_area_width-5))){ 
					//�}�E�X���X�N���[���o�[�̒��ɂ����
					DrawBox(maze_area_width-35,40+look_xy[1],maze_area_width-5,40+bar_scale_y+look_xy[1],red,TRUE);	//�X�N���[���o�[��Ԃ�����
					bar_flag_y=true;	//�t���O�����Ă�
					bar_y = icon_y;	//�N���b�N�����ʒu��ۑ�

				}else if(bar_flag_y == true){
					//�}�E�X���X�N���[���o�[�̒��ɂȂ��Ƃ��A�h���b�O���Ă�Ȃ�
					DrawBox(maze_area_width-35,40+look_xy[1],maze_area_width-5,40+bar_scale_y+look_xy[1],red,TRUE);	//�X�N���[���o�[��Ԃ�����
					bar_y = icon_y;	//�N���b�N�����ʒu��ۑ�

				}

			}
		}


	}


	//		DrawGraph(window_width-40,window_length-40,tool_button[0],TRUE);			//�c�[���{�^��

	//		DrawGraph(icon_x-13,icon_y-17,icon,TRUE);			//�}�E�X�̃A�C�R��

	//		DrawFormatString(50,50,black,"x-%d \n y-%d \n ",convert_maze_x(icon_x),convert_maze_y(icon_y));

	DrawBox(maze_area_width, 0, window_width, window_length, black, TRUE);		//�w�i(��)

}

void draw_mouse(unsigned char mouse_x,unsigned char mouse_y,unsigned char muki){
	static int mouse[4],temp_gh[4];
	static int func_flag=FALSE;	//�֐���ǂݍ��񂾉񐔂��J�E���g

	if(func_flag == FALSE){
		LoadDivGraph("�摜/mouse.png",4,4,1,374,374,temp_gh) ;
		mouse[MUKI_RIGHT]	= temp_gh[0];
		mouse[MUKI_UP]		= temp_gh[1];
		mouse[MUKI_LEFT]	= temp_gh[2];
		mouse[MUKI_DOWN]	= temp_gh[3];
		func_flag = TRUE;
	}
	DrawExtendGraph(convert_draw_x(mouse_x),convert_draw_y(mouse_y),convert_draw_x(mouse_x)+kukaku_size,convert_draw_y(mouse_y)+kukaku_size,mouse[muki],TRUE);
	//�}�E�X��`��

}

void draw_step(adachi &sim_map){

	for(int i=0;i<MAZE_SIZE;i++){
		for(int j=0;j<MAZE_SIZE;j++){
			//�����������l�̏ꏊ�͕`�悵�Ȃ�			
			if(sim_map.get_step(i,j)<965){		
				DrawFormatString(convert_draw_x(i)+magin,convert_draw_y(j)+magin,black,"%d",sim_map.get_step(i,j));	
			}

		}	
	}

}

void draw_path(path sim_path){
	unsigned char draw_distance=0;
	unsigned char path_x=0,path_y=0;				//���W�Ǘ��p
	unsigned int draw_x=0,draw_y=0;				//�`��Ǘ��p
	signed char draw_direction_x,draw_direction_y;	//�����Ǘ��p
	signed char temp_direction_x,temp_direction_y;	//�����Ǘ��p
	signed char naname_flag = FALSE;		//�i�i���X�C�b�`

	//���W��������
	path_x=0;
	path_y=0;

	//������������
	draw_direction_x=0;
	draw_direction_y=1;

	draw_x = convert_draw_x(path_x) + kukaku_size/2;//+ kukaku_size/2*draw_direction_x;
	draw_y = convert_draw_y(path_y) + kukaku_size/2;//+ kukaku_size/2*draw_direction_y;




	for(int i=0;;i++){
		draw_distance = sim_path.get_path_straight(i);
		DrawLine( draw_x, draw_y, draw_x+draw_distance*kukaku_size/2*draw_direction_x, draw_y+draw_distance*kukaku_size/2*(-draw_direction_y), blue, TRUE) ;

		//�X�V
		draw_x += draw_direction_x * draw_distance * kukaku_size/2;
		draw_y += (-draw_direction_y) * draw_distance * kukaku_size/2;

		if(sim_path.get_path_flag(i) == TRUE)	break;

		switch(sim_path.get_path_turn_type(i)){
		case 0:
			return;
			break;

		case 1:			//�����
			temp_direction_x = draw_direction_x;
			temp_direction_y = draw_direction_y;
			direction_turn(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
			DrawLine( draw_x, draw_y, draw_x + (temp_direction_x+draw_direction_x)*kukaku_size/2, draw_y - (temp_direction_y+draw_direction_y)*kukaku_size/2, blue, TRUE);
			draw_x += (temp_direction_x+draw_direction_x)*kukaku_size/2;
			draw_y -= (temp_direction_y+draw_direction_y)*kukaku_size/2;
			break;

		case 2:			//����
			//����撼�i
			DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), red, TRUE) ;
			draw_x += draw_direction_x * kukaku_size/2;
			draw_y += (-draw_direction_y) * kukaku_size/2;
			//�^�[��
			temp_direction_x = draw_direction_x;
			temp_direction_y = draw_direction_y;
			direction_turn(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
			DrawLine( draw_x, draw_y, draw_x + (temp_direction_x+draw_direction_x)*kukaku_size/2, draw_y - (temp_direction_y+draw_direction_y)*kukaku_size/2, red, TRUE);
			draw_x += (temp_direction_x+draw_direction_x)*kukaku_size/2;
			draw_y -= (temp_direction_y+draw_direction_y)*kukaku_size/2;
			//����撼�i
			DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), red, TRUE) ;
			draw_x += draw_direction_x * kukaku_size/2;
			draw_y += (-draw_direction_y) * kukaku_size/2;
			break;

		case 3:			//U�^�[��
			//����撼�i
			DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), red, TRUE) ;
			draw_x += draw_direction_x * kukaku_size/2;
			draw_y += (-draw_direction_y) * kukaku_size/2;
			//�^�[��
			temp_direction_x = draw_direction_x;
			temp_direction_y = draw_direction_y;
			direction_turn(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
			DrawLine( draw_x, draw_y, draw_x + (temp_direction_x+draw_direction_x)*kukaku_size/2, draw_y - (temp_direction_y+draw_direction_y)*kukaku_size/2, red, TRUE);
			draw_x += (temp_direction_x+draw_direction_x)*kukaku_size/2;
			draw_y -= (temp_direction_y+draw_direction_y)*kukaku_size/2;
			//�^�[��
			temp_direction_x = draw_direction_x;
			temp_direction_y = draw_direction_y;
			direction_turn(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
			DrawLine( draw_x, draw_y, draw_x + (temp_direction_x+draw_direction_x)*kukaku_size/2, draw_y - (temp_direction_y+draw_direction_y)*kukaku_size/2, red, TRUE);
			draw_x += (temp_direction_x+draw_direction_x)*kukaku_size/2;
			draw_y -= (temp_direction_y+draw_direction_y)*kukaku_size/2;
			//����撼�i
			DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), red, TRUE) ;
			draw_x += draw_direction_x * kukaku_size/2;
			draw_y += (-draw_direction_y) * kukaku_size/2;
			break;

		case 4:			//45���^�[��
			if( naname_flag == TRUE){
				naname_flag = FALSE;
				//45���^�[��
				DrawLine( draw_x, draw_y, draw_x + (draw_direction_x)*kukaku_size/2, draw_y - (draw_direction_y)*kukaku_size/2, green, TRUE);
				draw_x += (draw_direction_x)*kukaku_size/2;
				draw_y -= (draw_direction_y)*kukaku_size/2;
				direction_turn_half(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
				//����撼�i
				DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), green, TRUE) ;
				draw_x += draw_direction_x * kukaku_size/2;
				draw_y += (-draw_direction_y) * kukaku_size/2;
			}else{
				naname_flag = TRUE;
				//����撼�i
				DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), green, TRUE) ;
				draw_x += draw_direction_x * kukaku_size/2;
				draw_y += (-draw_direction_y) * kukaku_size/2;
				//45���^�[��
				direction_turn_half(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
				DrawLine( draw_x, draw_y, draw_x + (draw_direction_x)*kukaku_size/2, draw_y - (draw_direction_y)*kukaku_size/2, green, TRUE);
				draw_x += (draw_direction_x)*kukaku_size/2;
				draw_y -= (draw_direction_y)*kukaku_size/2;
			}
			break;

		case 5:			//135���^�[��
			if( naname_flag == TRUE){
				naname_flag = FALSE;
				//45���^�[��
				DrawLine( draw_x, draw_y, draw_x + (draw_direction_x)*kukaku_size/2, draw_y - (draw_direction_y)*kukaku_size/2, green, TRUE);
				draw_x += (draw_direction_x)*kukaku_size/2;
				draw_y -= (draw_direction_y)*kukaku_size/2;
				direction_turn_half(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
				//90���^�[��
				temp_direction_x = draw_direction_x;
				temp_direction_y = draw_direction_y;
				direction_turn(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
				DrawLine( draw_x, draw_y, draw_x + (temp_direction_x+draw_direction_x)*kukaku_size/2, draw_y - (temp_direction_y+draw_direction_y)*kukaku_size/2, green, TRUE);
				draw_x += (temp_direction_x+draw_direction_x)*kukaku_size/2;
				draw_y -= (temp_direction_y+draw_direction_y)*kukaku_size/2;
				//����撼�i
				DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), green, TRUE) ;
				draw_x += draw_direction_x * kukaku_size/2;
				draw_y += (-draw_direction_y) * kukaku_size/2;
			}else{
				naname_flag = TRUE;
				//����撼�i
				DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), green, TRUE) ;
				draw_x += draw_direction_x * kukaku_size/2;
				draw_y += (-draw_direction_y) * kukaku_size/2;
				//90���^�[��
				temp_direction_x = draw_direction_x;
				temp_direction_y = draw_direction_y;
				direction_turn(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
				DrawLine( draw_x, draw_y, draw_x + (temp_direction_x+draw_direction_x)*kukaku_size/2, draw_y - (temp_direction_y+draw_direction_y)*kukaku_size/2, green, TRUE);
				draw_x += (temp_direction_x+draw_direction_x)*kukaku_size/2;
				draw_y -= (temp_direction_y+draw_direction_y)*kukaku_size/2;
				//45���^�[��
				direction_turn_half(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
				DrawLine( draw_x, draw_y, draw_x + (draw_direction_x)*kukaku_size/2, draw_y - (draw_direction_y)*kukaku_size/2, green, TRUE);
				draw_x += (draw_direction_x)*kukaku_size/2;
				draw_y -= (draw_direction_y)*kukaku_size/2;
			}
			break;

		case 6:			//�i�i��90���^�[��
			//����撼�i
			DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), green, TRUE) ;
			draw_x += draw_direction_x * kukaku_size/2;
			draw_y += (-draw_direction_y) * kukaku_size/2;
			//�����]��
			direction_turn(&draw_direction_x,&draw_direction_y,sim_path.get_path_turn_muki(i));
			//����撼�i
			DrawLine( draw_x, draw_y, draw_x+kukaku_size/2*draw_direction_x, draw_y+kukaku_size/2*(-draw_direction_y), green, TRUE) ;
			draw_x += draw_direction_x * kukaku_size/2;
			draw_y += (-draw_direction_y) * kukaku_size/2;
			break;

		}

	}

}

int convert_draw_x(signed char maze_x){
	int draw_x = magin+kukaku_size*maze_x -look_xy[0]*scroll_scale_x;
	return draw_x;
}

int convert_draw_y(signed char maze_y){
	int draw_y = magin+kukaku_size*(MAZE_SIZE-maze_y-1) -look_xy[1]*scroll_scale_y;
	return draw_y;
}

int convert_maze_x(signed int draw_x){
	int maze_x = (draw_x + look_xy[0]*scroll_scale_x -magin) / kukaku_size;
	return maze_x;
}

int convert_maze_y(signed int draw_y){
	int maze_y = (MAZE_SIZE - 1 - (draw_y + look_xy[1]*scroll_scale_y - magin) / kukaku_size);
	return maze_y;
}

void direction_turn_half(signed char *direction_x,signed char *direction_y, unsigned char direction_turn_muki){
	signed char temp_direction_x = (*direction_x);		//���̏ꏊ�ɕۑ����Ȃ��ƕϊ��r���ŎQ�Ƃ���H�ڂɂȂ� 
	signed char temp_direction_y = (*direction_y);
	if(direction_turn_muki == MUKI_LEFT){
		*direction_x = (temp_direction_x)*1 + (temp_direction_y)*(-1);	//��]�s��̃�=45�̌v�Z�̃��[�g2�{
		*direction_y = (temp_direction_x)*1 + (temp_direction_y)*1;		//��]�s��̃�=45�̌v�Z�̃��[�g2�{
	}else{
		*direction_x = (temp_direction_x)*1 + (temp_direction_y)*1;		//��]�s��̃�=45�̌v�Z�̃��[�g2�{
		*direction_y = (temp_direction_x)*(-1) + (temp_direction_y)*1;	//��]�s��̃�=45�̌v�Z�̃��[�g2�{		
	}

	if( (*direction_x) * (*direction_x) == 4)	*direction_x = *direction_x/2;	//��Βl��2�Ȃ甼����
	if( (*direction_y) * (*direction_y) == 4)	*direction_y = *direction_y/2;	//��Βl��2�Ȃ甼����

}	


void get_square(adachi& orig, adachi& tar, unsigned char x, unsigned char y){
	for(int i=0;i<4;i++){	//MUKI��Define���O�`�R�܂łȂ̂ł������Ă�
		if(orig.get_wall(x,y,i)==TRUE){
			tar.create_wall(x,y,i);
		}else{
			tar.destroy_wall(x,y,i);
		}
		if(orig.check_exist(x,y,i)==TRUE){
			tar.remember_exist(x,y,i);
		}else{
			tar.forget_exist(x,y,i);
		}
	}
}