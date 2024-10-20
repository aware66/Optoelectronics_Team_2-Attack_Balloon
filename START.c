#include "Header.h"

void START_00(void)
{
	if(shop < START_00_number)
	{
		car.L_out = 2000;
		car.R_out = 2000;
	}
}

void START_01(void)
{
	if(shop < START_01_number)
	{
		car.L_out = 1700;
		car.R_out = -1700;
	}
}

void START_02(void)
{
	
		car.L_out = Incremental_PI_Left (MotorA.Current_Encoder,car.speed + car.Wheel_Differential);			//增量式--左
		car.R_out = Incremental_PI_Right (MotorB.Current_Encoder,car.speed - car.Wheel_Differential);
	
}

void START_Turn_01(void)
{ 
	if(shop < START_03_number)
	{
		car.L_out = -2000;
		car.R_out = 2000;
	}
}

void START_Turn_02(void)
{ 
	if(shop < START_05_number)
	{
		car.L_out = -2000;
		car.R_out = 2000;
	}
}

void START_Turn_03(void)
{ 
	if(shop < START_07_number)
	{
		car.L_out = -2000;
		car.R_out = 2000;
	}
}

void START_IN(void)
{
	if(shop < START_08_number)
	{
		car.L_out = 2000;
		car.R_out = 2000;
	}
}

void START_Turn_04(void)
{ 
	if(shop < START_09_number)
	{
		car.L_out = 2000;
		car.R_out = -2000;
	}
}


void START_shop(void)
{
	
//		car.L_out = 0;
//		car.R_out = 0;
	BLack_to_ball_Flag = 'H';
	
	
}

void START(void)
{
	
			switch(start_flag)
			{
				case 0:
					START_00();
					break;
				
				case 1:
					START_01();
					break;
				
				case 2:
					START_02();
					break;
				
				case 3:
					START_Turn_01();
					break;
				
				case 4:
					START_02();
					break;
				
				case 5:
					START_Turn_02();
					break;
				
				case 6:
					START_02();
					break;
				
				case 7:
					START_Turn_02();
					break;
				
				case 8:
					START_02();
					break;
				
				case 9:
					START_Turn_02();
					break;
				
				case 10:
					START_02();
					break;
				
				case 11:
					START_Turn_03();
					break;
				
				case 12:
					START_IN();
					break;
				
				case 13:
					START_Turn_04();
					break;
				
				case 14:
					START_shop();
					break;
			}
	
			if(shop >= START_00_number && 0 == start_flag) 	start_flag = 1; //发车前进START_Turn_04(void)
			else if(shop >= START_01_number && 1 == start_flag)	 //发车转向
			{				
				start_flag = 2;
				shop = 0;
			}
			
			else if(shop >= START_02_number && 2 == start_flag)		start_flag = 3; //前进01
			else if(shop >= START_03_number && 3 == start_flag)		//转向01
			{
				start_flag = 4; 
				shop = 0;
			}
			
			else if(shop >= START_04_number && 4 == start_flag)		start_flag = 5; //前进02
			else if(shop >= START_05_number && 5 == start_flag)		//转向02
			{	
				start_flag = 6;
				shop = 0;
			}
			
			else if(shop >= START_04_number && 6 == start_flag)		start_flag = 7; //前进03
			else if(shop >= START_05_number && 7 == start_flag)		//转向03
			{	
				start_flag = 8;
				shop = 0;
			}
			
			else if(shop >= START_04_number && 8 == start_flag)		start_flag = 9; //前进04
			else if(shop >= START_05_number && 9 == start_flag)		//转向04
			{	
				start_flag = 10;
				shop = 0;
			}
			
			else if(shop >= START_06_number && 10 == start_flag)	start_flag = 11; //前进05
			
			else if(shop >= START_07_number && 11 == start_flag)		//转向05
			{	
				start_flag = 12;
				shop = 0;
			}
			
			else if(shop >= START_08_number && 12 == start_flag)		//转向05
			{	
				start_flag = 13;
				shop = 0;
			}
			
			else if(shop >= START_09_number && 13 == start_flag)		//转向05
			{	
				start_flag = 14;
				shop = 0;
			}
			

}

