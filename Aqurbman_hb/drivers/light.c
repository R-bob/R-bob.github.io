#include "light.h"
#include "pwm_out.h"

u8 light;

void LIGHT(unsigned char pwm)
{
	TIM1->CCR1 = 4 * pwm + 4000;				
};
