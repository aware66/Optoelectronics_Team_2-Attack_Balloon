#include <Header.h>

void Find_balloon(void)
{
	if(114 == Color && 'H' == BLack_to_ball_Flag)
	{
		car.Error = -60;
	}
}

void SERVO_Change(void)
{
	
	if(114 != Color && 'H' == BLack_to_ball_Flag)
	{
		Servo_PWM = 1700;
		Servo_PWM_2 = 1300;
	}
	else
	{
		Servo_PWM = 400;
		Servo_PWM_2 = 2600;
	}

}

