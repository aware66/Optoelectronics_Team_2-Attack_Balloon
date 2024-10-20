/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��V1.0
�޸�ʱ�䣺2023-03-02

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update��2023-03-02

All rights reserved
***********************************************/


#ifndef __CONTROL_H
#define __CONTROL_H


#include "Header.h"

//PWM���������Сֵ
#define PWM_MAX  6900
#define PWM_MIN  -6900


#define forward_velocity 0.25  //Move_X�ٶ�
#define Along_Angle      77    //������ķ���

#define FILTERING_TIMES 					10			//�����˲�

//С����ģʽ����


#define Measure_Distance_Mode				7			//Ĭ��û��ʹ��


#define Pi									3.14159265358979f	//Բ����
#define Angle_To_Rad						57.295779513f	//�Ƕ���ת�����ƣ������������
#define Frequency							200.0f			//ÿ5ms��ȡһ�α�������ֵ
#define SERVO_INIT 							1500  			//������PWMֵ


#define Encoder_resolution_Photoelectric	500.0f			//��������500��
#define Encoder_resolution_Hall 			13.0f			//����������13��
#define Encoder_resolution 					Encoder_resolution_Hall		//ʹ��13�߻���������

#define Angle_TO_PWM						640.62f			//���ڼ���pwm�ͽǶȵĹ�ϵ

#define Normal								0				//����쳣״̬��0Ϊ����
#define Abnormal							1


//#define forward_velocity 250 //С����ʼ�ٶ�

//���������ݶ�ȡƵ��
#define   CONTROL_FREQUENCY 100
#define   Encoder_precision 4*Encoder_resolution_Hall*Gear_Ratio
//����ٶȿ�����ز����ṹ��
typedef struct  
{
	float Current_Encoder;     	//��������ֵ����ȡ���ʵʱ�ٶ�
	float Motor_Pwm;     		//���PWM��ֵ�����Ƶ��ʵʱ�ٶ�
	float Target_Encoder;  		//���Ŀ��������ٶ�ֵ�����Ƶ��Ŀ���ٶ�
	float Velocity; 	 		//����ٶ�ֵ
}Motor_parameter;

//�������ṹ��
typedef struct  
{
  int A;      
  int B;  
}Encoder;

extern u16 mini_distance1;
extern float angle1;
extern short Accel_Y,Accel_Z,Accel_X,Accel_Angle_x,Accel_Angle_y,Gyro_X,Gyro_Z,Gyro_Y;
extern float Move_X,Move_Z;
extern float PWM_Left,PWM_Right;
extern float RC_Velocity,RC_Turn_Velocity;

extern Motor_parameter MotorA,MotorB;	
extern int Servo_PWM;

extern int Servo_PWM_2;

extern Encoder OriginalEncoder;




void Get_Target_Encoder(float Vx,float Vz);
void Get_Motor_PWM(void);
void Get_Velocity_From_Encoder(void);
float target_limit_float(float insert,float low,float high);
int target_limit_int(int insert,int low,int high);

float PWM_Limit(float IN,float max,float min);
u8 Turn_Off(void);
float Mean_Filter_Left(float data);
float Mean_Filter_Right(float data);

float Merge_Angle(float angle1,float angle2);
//float Get_Merge_Angle(float angle,PointDataProcessDef Data,u8 Current_Count);
void Ultrasonic_Follow(void);
void Car_Perimeter_Init(void);

void Get_Angle(u8 way);

extern int ADC_Flag;



#endif
