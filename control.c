
#include "control.h"

#include "MPU6050.h"

float Move_X = 0,Move_Z = 0;						//Ŀ���ٶȺ�Ŀ��ת���ٶ�
float PWM_Left,PWM_Right;					//���ҵ��PWMֵ


Motor_parameter MotorA,MotorB;				//���ҵ����ر���
int Servo_PWM = SERVO_INIT;					//�����������ر���

int Servo_PWM_2 = 0;

int ADC_Flag = 0;

Encoder OriginalEncoder; //Encoder raw data //������ԭʼ����   
short Accel_Y,Accel_Z,Accel_X,Accel_Angle_x,Accel_Angle_y,Gyro_X,Gyro_Z,Gyro_Y;
/**************************************************************************
Function: Control Function
Input   : none
Output  : none
�������ܣ�5ms��ʱ�жϿ��ƺ���
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
int TIMING_TIM_IRQHandler(void)
{
	if(TIM_GetITStatus( TIMING_TIM, TIM_IT_Update) != RESET) 
	{			
		TIM_ClearITPendingBit(TIMING_TIM , TIM_IT_Update);
		Get_Velocity_From_Encoder();								//��ȡ���ұ�������ֵ��ת�����ٶ�

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
�������ܣ���ȡ��������ת�����ٶ�
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
void Get_Velocity_From_Encoder(void)
{
	
	MotorA.Current_Encoder = -Read_Encoder(Encoder1)*10;			//��ȡ�������ٶ�
  MotorB.Current_Encoder = Read_Encoder(Encoder2)*10; 
//	MotorA.Velocity = -MotorA.Current_Encoder*Frequency/Gear_Ratio/Encoder_resolution*Perimeter/4;//4��Ƶ����AB����ض������������4
//	MotorB.Velocity =  MotorB.Current_Encoder*Frequency/Gear_Ratio/Encoder_resolution*Perimeter/4;
}

/**************************************************************************
Function: Get angle
Input   : way��The algorithm of getting angle 1��DMP  2��kalman  3��Complementary filtering
Output  : none
�������ܣ���ȡ�Ƕ�	
��ڲ�����way����ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
����  ֵ����
**************************************************************************/	
//void Get_Angle(u8 way)
//{ 
//	if(way==1)                           //DMP�Ķ�ȡ�����ݲɼ��ж϶�ȡ���ϸ���ѭʱ��Ҫ��
//	{	
//		Read_DMP();                      //��ȡ���ٶȡ����ٶȡ����
//	}			
//	else
//	{
//		Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //��ȡX��������
//		Gyro_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //��ȡY��������
//		Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
//		Accel_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //��ȡX����ٶȼ�
//		Accel_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //��ȡX����ٶȼ�
//		Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
//		if(Gyro_X>32768)  Gyro_X-=65536;                 //��������ת��  Ҳ��ͨ��shortǿ������ת��
//		if(Gyro_Y>32768)  Gyro_Y-=65536;                 //��������ת��  Ҳ��ͨ��shortǿ������ת��
//		if(Gyro_Z>32768)  Gyro_Z-=65536;                 //��������ת��
//		if(Accel_X>32768) Accel_X-=65536;                //��������ת��
//		if(Accel_Y>32768) Accel_Y-=65536;                //��������ת��
//		if(Accel_Z>32768) Accel_Z-=65536;                //��������ת��
//		Accel_Angle_x=atan2(Accel_Y,Accel_Z)*180/Pi;     //������ǣ�ת����λΪ��	
//		Accel_Angle_y=atan2(Accel_X,Accel_Z)*180/Pi;     //������ǣ�ת����λΪ��
//		Gyro_X=Gyro_X/65.5;                              //����������ת�������̡�2000��/s��Ӧ������16.4���ɲ��ֲ�
//		Gyro_Y=Gyro_Y/65.5;                              //����������ת��	
//		
//	}
// 
//}
