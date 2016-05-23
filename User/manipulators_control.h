#ifndef _MANIPULATORS_CONTROL
#define _MANIPULATORS_CONTROL

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "pwm.h"

void angle_paw(unsigned int angle);
void angle_wrist_y_time(unsigned int angle, unsigned long time);
void angle_wrist_x(unsigned int angle);
void angle_wrist_y(unsigned int angle);
void angle_base(unsigned int angle);
void angle_button(unsigned int angle);
void angle_arm(unsigned int angle);
void angle_init(void);
void set_angle(int x1, int x2, int x3, int x4, int x5);
void crawl(char a);
void delay(unsigned long time);
void PWM_init(void);
void set_platform(unsigned int con);
void set_platform_base(unsigned int con);
void plat_init(void);
void platform_angle(unsigned int angle);
void platform_base_angle(unsigned int angle);


#endif

