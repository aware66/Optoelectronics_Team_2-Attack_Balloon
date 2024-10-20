
#include "control.h"

#include "MPU6050.h"

float Move_X = 0,Move_Z = 0;						//目标速度和目标转向速度
float PWM_Left,PWM_Right;					//左右电机PWM值


Motor_parameter MotorA,MotorB;				//左右电机相关变量
int Servo_PWM = SERVO_INIT;					//阿克曼舵机相关变量

int Servo_PWM_2 = 0;

int ADC_Flag = 0;

Encoder OriginalEncoder; //Encoder raw data //编码器原始数据   
short Accel_Y,Accel_Z,Accel_X,Accel_Angle_x,Accel_Angle_y,Gyro_X,Gyro_Z,Gyro_Y;
/**************************************************************************
Function: Control Function
Input   : none
Output  : none
函数功能：5ms定时中断控制函数
入口参数: 无 
返回  值：无
**************************************************************************/	 	
int TIMING_TIM_IRQHandler(void)
{
	if(TIM_GetITStatus( TIMING_TIM, TIM_IT_Update) != RESET) 
	{			
		TIM_ClearITPendingBit(TIMING_TIM , TIM_IT_Update);
		Get_Velocity_From_Encoder();								//读取左右编码器的值且转换成速度

		Flag_Stop = KEY2_STATE;
		
		adcValue = ADC_Read();
		
		Error_out();
		
//		Get_Angle(2);
		
//		Read_DMP();
		
		if(adcValue > 550) ADC_Flag = 1;
		
//		if(1 == ADC_Flag)  Buzzer_Alarm(10);
		
		if(!Flag_Stop && ADC_Flag)	Run();

		return 0;
 }
}


/**************************************************************************
Function: Get_Velocity_From_Encoder
Input   : none
Output  : none
函数功能：读取编码器和转换成速度
入口参数: 无 
返回  值：无
**************************************************************************/	 	
void Get_Velocity_From_Encoder(void)
{
	
	MotorA.Current_Encoder = -Read_Encoder(Encoder1)*10;			//读取编码器速度
  MotorB.Current_Encoder = Read_Encoder(Encoder2)*10; 
//	MotorA.Velocity = -MotorA.Current_Encoder*Frequency/Gear_Ratio/Encoder_resolution*Perimeter/4;//4倍频，即AB相边沿都计数，需除以4
//	MotorB.Velocity =  MotorB.Current_Encoder*Frequency/Gear_Ratio/Encoder_resolution*Perimeter/4;
}

/**************************************************************************
Function: Get angle
Input   : way：The algorithm of getting angle 1：DMP  2：kalman  3：Complementary filtering
Output  : none
函数功能：获取角度	
入口参数：way：获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
返回  值：无
**************************************************************************/	
//void Get_Angle(u8 way)
//{ 
//	if(way==1)                           //DMP的读取在数据采集中断读取，严格遵循时序要求
//	{	
//		Read_DMP();                      //读取加速度、角速度、倾角
//	}			
//	else
//	{
//		Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //读取X轴陀螺仪
//		Gyro_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //读取Y轴陀螺仪
//		Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //读取Z轴陀螺仪
//		Accel_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //读取X轴加速度计
//		Accel_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //读取X轴加速度计
//		Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //读取Z轴加速度计
//		if(Gyro_X>32768)  Gyro_X-=65536;                 //数据类型转换  也可通过short强制类型转换
//		if(Gyro_Y>32768)  Gyro_Y-=65536;                 //数据类型转换  也可通过short强制类型转换
//		if(Gyro_Z>32768)  Gyro_Z-=65536;                 //数据类型转换
//		if(Accel_X>32768) Accel_X-=65536;                //数据类型转换
//		if(Accel_Y>32768) Accel_Y-=65536;                //数据类型转换
//		if(Accel_Z>32768) Accel_Z-=65536;                //数据类型转换
//		Accel_Angle_x=atan2(Accel_Y,Accel_Z)*180/Pi;     //计算倾角，转换单位为度	
//		Accel_Angle_y=atan2(Accel_X,Accel_Z)*180/Pi;     //计算倾角，转换单位为度
//		Gyro_X=Gyro_X/65.5;                              //陀螺仪量程转换，量程±2000°/s对应灵敏度16.4，可查手册
//		Gyro_Y=Gyro_Y/65.5;                              //陀螺仪量程转换	
//		
//	}
// 
//}
