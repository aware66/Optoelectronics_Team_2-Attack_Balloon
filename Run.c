
#include "stm32f10x.h"                  // Device header
#include "Header.h"									//调用函数的头文件

float shop = 0;

int start_flag = 0;

int Find_black = 0;

int adcValue = 0;

int back_flag = 0;

CAR car;

void Error_out(void)
{
	
	 car.Error = Cx - img_Center;
	
	 if (car.Error >= img_Center) 	car.Error = img_Center;
   else if (car.Error <= -img_Center) 	car.Error = -img_Center;
	
//	 if(abs(abs(car.Error) - abs(car.Error_last)) > 45) car.Error = car.Error_last;
//	 car.Error_last = car.Error;

}


void Run()
{

			if('F' == BLack_to_ball_Flag)		car.speed = target_speed_Black;
			else car.speed = target_speed_Red;
	
			
	
			Find_balloon();
	
			car.Wheel_Differential=Position_PID (car.Error,0);	
		
			car.L_out = Incremental_PI_Left (MotorA.Current_Encoder,car.speed + car.Wheel_Differential);			//增量式--左
			car.R_out = Incremental_PI_Right (MotorB.Current_Encoder,car.speed - car.Wheel_Differential);		//增量式--右

			START();
			
			SERVO_Change();
	
			if(Find_black < 3000  && 'H' == BLack_to_ball_Flag) 
			{
					car.L_out = 0;
					car.R_out = 0;
			}
			
//			if('H' == BLack_to_ball_Flag && 114 == Color)
//			{
//					if(MotorA.Current_Encoder <= 100 && back_flag < 5) 
//					{
//						car.L_out = -2000;
//						car.R_out = -2000;
//						
//						back_flag += (abs(MotorA.Current_Encoder) + abs(MotorB.Current_Encoder)) / 4000.0;
//						
//					}
//					else if(back_flag > 10) back_flag = 0;
//					
//			}
			
			Set_Pwm(car.L_out,-car.R_out);		//控制转向 

			SERVO_TIM_SetCompareX_FUN(SERVO_TIM,Servo_PWM); //舵机1 put:1700 down:400 右
			SERVO_TIM_SetCompareX_FUN_2(SERVO_TIM,Servo_PWM_2); //舵机2 put:1300  down: 2600 左
			
			shop += (abs(MotorA.Current_Encoder) + abs(MotorB.Current_Encoder)) / 4000.0;
			
			if(shop > 200) shop = 200;
			
			if('H' == BLack_to_ball_Flag)
			{
				Find_black += 5;
				if(Find_black > 5000) Find_black = 5000;
			}

}
