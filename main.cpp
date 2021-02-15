#include "mbed.h"
#include "HR2046.h"

int main()
{
  SPI spiPort(A6, A5, A4);
  HR2046 touch(&spiPort, D6);
  touch.initialize();
  touch.setRotation(0);

  while(true)
  {
    if(touch.wasTouched())
    {
      uint16_t x = 0, y = 0, z = 0;
      touch.readData(&x, &y, &z);
      printf("X: %d; Y: %d; Z: %d\n", x, y, z);
      printf("Touched!\n");
      ThisThread::sleep_for(100);
    }
  }
}

