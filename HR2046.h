#include "mbed.h"
#include <cstdint>

#define HR2046_Z_THRESHOLD 400

class TouchPoint
{
  public:
    TouchPoint(void) : x(0), y(0), z(0) {}
    TouchPoint(uint16_t x, uint16_t y, uint16_t z) : x(x), y(y), z(z) {}

    bool operator==(TouchPoint point)
    {
      return (point.x == x && point.y == y && point.z == z);
    }

    bool operator!=(TouchPoint point)
    {
      return (point.x != x || point.y != y || point.z != z);
    }

    uint16_t x, y, z;
};

class HR2046
{
  public:
    HR2046(SPI* spiPort, PinName cs);
    void initialize(void);
    void setRotation(uint8_t rot);
    void readData(uint16_t* x, uint16_t* y, uint16_t* z);
    bool wasTouched(void);

  private:
    SPI* spiPort;
    DigitalOut chipSelect;
    uint8_t rotation = 1;
    uint16_t xraw = 0;
    uint16_t yraw = 0;
    uint16_t zraw = 0;

    void update(void);
    uint16_t transfer16(uint8_t cmd);
    int16_t bestTwoAvg(int16_t x, int16_t y, int16_t z);
};