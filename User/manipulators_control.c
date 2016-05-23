#include "manipulators_control.h"

unsigned int init_angle[6] = {720, 984, 360, 1472, 1800, 1800};
unsigned int current_angle[6] = {0};                 //舵机当前位置
unsigned int new_angle[6] = {0};                     //舵机新位置

unsigned int palt_pos[2] = {1424, 1176};
unsigned int cur_plat[2] = {0};           
unsigned int new_plat[2] = {0};                 



void delay(unsigned long time)
{
		while(time--);
}

void PWM_init(void)
{
	TIM3_PWM_Init(14399,99);
	TIM4_PWM_Init(14399,99);
	TIM5_PWM_Init(23,99);
}


void crawl(char a)
{
			if(a==0)
			{
						angle_paw(50);
			}
			else
			{
						angle_paw(74);
			}
}

void angle_wrist_x(unsigned int angle)
{
		new_angle[1] = angle * 8 + 360;
		while(current_angle[1] != new_angle[1])
		{
				if(current_angle[1] < new_angle[1])
				{
						current_angle[1]++;
				}
				else	
				{
						current_angle[1]--;
				}
				TIM_SetCompare2(TIM3,current_angle[1]);
				delay(8000);
		}				
}

void angle_wrist_y(unsigned int angle)
{
		new_angle[2] = angle * 8 + 360;
		while(current_angle[2] != new_angle[2])
		{
				if(current_angle[2] < new_angle[2])
				{
						current_angle[2]++;
				}
				else	
				{
						current_angle[2]--;
				}
				TIM_SetCompare3(TIM3,current_angle[2]);
				delay(8000);
		}
}

void angle_wrist_y_time(unsigned int angle, unsigned long time)
{
		new_angle[2] = angle * 8 + 360;
		while(current_angle[2] != new_angle[2])
		{
				if(current_angle[2] < new_angle[2])
				{
						current_angle[2]++;
				}
				else	
				{
						current_angle[2]--;
				}
				TIM_SetCompare3(TIM3,current_angle[2]);
				delay(time);
		}
}

void angle_paw(unsigned int angle)
{
		new_angle[0] = angle * 8 + 360;
		while(current_angle[0] != new_angle[0])
		{
				if(current_angle[0] < new_angle[0])
				{
						current_angle[0]++;
				}
				else	
				{
						current_angle[0]--;
				}
				TIM_SetCompare1(TIM3,current_angle[0]);
				delay(6000);
		}
}

void angle_base(unsigned int angle)
{
		new_angle[3] = angle * 8 + 360;
		while(current_angle[3] != new_angle[3])
		{
				if(current_angle[3] < new_angle[3])
				{
						current_angle[3]++;
				}
				else	
				{
						current_angle[3]--;
				}
				TIM_SetCompare4(TIM3,current_angle[3]);
				delay(8000);
		}		
}

void angle_button(unsigned int angle)
{
		new_angle[4] = angle * 8 + 360;
		while(current_angle[4] != new_angle[4])
		{
				if(current_angle[4] < new_angle[4])
				{
						current_angle[4]++;
				}
				else	
				{
						current_angle[4]--;
				}
				TIM_SetCompare1(TIM4,current_angle[4]);
				delay(8000);
		}		
}

void angle_arm(unsigned int angle)
{
		new_angle[5] = angle * 8 + 360;
		while(current_angle[5] != new_angle[5])
		{
				if(current_angle[5] < new_angle[5])
				{
						current_angle[5]++;
				}
				else	
				{
						current_angle[5]--;
				}
				TIM_SetCompare2(TIM4,current_angle[5]);
				delay(8000);
		}		
}

void angle_init(void)
{
		char  i;
		for(i=0; i<6; i++)
		{
				current_angle[i] = init_angle[i];
		}
		TIM_SetCompare1(TIM3,current_angle[0]);
		TIM_SetCompare2(TIM3,current_angle[1]);
		TIM_SetCompare3(TIM3,current_angle[2]);
		TIM_SetCompare4(TIM3,current_angle[3]);
		TIM_SetCompare1(TIM4,current_angle[4]);
		TIM_SetCompare2(TIM4,current_angle[5]);
}

void set_angle(int x1, int x2, int x3, int x4, int x5)
{		
		angle_wrist_y(x2);
		angle_base(x3);				
		angle_button(x4);
		angle_arm(x5);
		angle_wrist_x(x1);
}

void plat_init(void)
{
		char  i;
		for(i=0; i<2; i++)
		{
				cur_plat[i] = palt_pos[i];
		}
		TIM_SetCompare3(TIM4,cur_plat[0]);
		TIM_SetCompare4(TIM4,cur_plat[1]);		
}

void platform_angle(unsigned int angle)
{
		new_plat[0] = angle * 8 + 360;
		while(cur_plat[0] != new_plat[0])
		{
				if(cur_plat[0] < new_plat[0])
				{
						cur_plat[0]++;
				}
				else	
				{
						cur_plat[0]--;
				}
				TIM_SetCompare3(TIM4,cur_plat[0]);
				delay(6000);
		}		
}

void platform_base_angle(unsigned int angle)
{
		new_plat[1] = angle * 8 + 360;
		while(cur_plat[1] != new_plat[1])
		{
				if(cur_plat[1] < new_plat[1])
				{
						cur_plat[1]++;
				}
				else	
				{
						cur_plat[1]--;
				}
				TIM_SetCompare4(TIM4,cur_plat[1]);
				delay(6000);
		}		
}

void set_platform(unsigned int con)
{
		if(con == 0)
		{
				platform_angle(134);
		}
		else
		{
				platform_angle(59);
		}
}

void set_platform_base(unsigned int con)
{
		if(con == 1)
		{
				platform_base_angle(27);
		}
		else
		{
				platform_base_angle(102);
		}
}

