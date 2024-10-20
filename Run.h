#ifndef _RUN_H
#define _RUN_H


#define img_Center 80

#define target_speed_Black 300

#define target_speed_Red 150

#define Black_add_0 3600

#define START_00_number 17.5

#define START_01_number 25.0

#define START_02_number 37.5

#define START_03_number 43.0

#define START_04_number 85.0

#define START_05_number 94.5


#define START_06_number 32.0

#define START_07_number 40.0

#define START_08_number 4

#define START_09_number 6

typedef struct{

	int Wheel_Differential;

	int Error;
	
	int Error_last;
	
	int16_t speed;
	
	int L_out;
	
	int R_out;
	
	int ADD_flag;
	
	int Time_Find_ball;
	
	int distance_openmv;
	
	int distance_openmv_last;

} CAR;

extern CAR car;

extern float shop;

extern int start_flag;

extern int adcValue;



void Run(void);

void Error_out(void);

void SERVO_Change(void);

void Find_balloon(void);

#endif
