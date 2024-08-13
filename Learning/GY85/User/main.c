#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "MPU6050.h"
#include "Serial.h"

uint8_t i;
// uint8_t rt = 1;
int16_t Acc[3];
int16_t Gyo[3];

int main()
{
  GY85_Init();
  Serial_Init();

  while (1)
  {
    GY85_GetData(Acc, Gyo);
    for(i = 0; i < 3; i++)
    {
      u1_printf("Acc[%d] = %+06d, ", i, Acc[i]);
    }
    // u1_printf("\r\n");
    for(i = 0; i < 3; i++)
    {
      u1_printf("Gyo[%d] = %+06d, ", i, Gyo[i]);
    }
    u1_printf("\r\n");
  }
  return 0;
}