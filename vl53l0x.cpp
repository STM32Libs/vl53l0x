#include "mbed.h"

 
#include "vl53l0x.h"


vl53l0x::vl53l0x(Serial *ps,PinName pin_sda, PinName pin_scl):i2c(pin_sda,pin_scl),pr(ps)
{
    i2c.frequency(400000);  // use fast (400 kHz) I2C  
    //The STM32 Bluepill reset pin creates a start condition without a stop which blocks any further i2c communication
    //This start and stop resets the PMU i2c state machine and allos further communication to continue
    i2c.start();
    i2c.stop();
    
}

void vl53l0x::writeReg8(uint8_t subAddress, uint8_t data)
{

}

uint8_t vl53l0x::readReg8(uint8_t subAddress)
{

}

void vl53l0x::writeReg16(uint8_t subAddress, uint16_t data)
{

}

uint16_t vl53l0x::readReg16(uint8_t subAddress)
{
    uint16_t res;
    char data = 0xFF;
    i2c.write(0x52|0x00, (const char*)&subAddress, 1, 1); // no stop
    i2c.read(0x52|0x01, (char*)&res, 2, false);
    return res;
}

void vl53l0x::writeReg32(uint8_t subAddress, uint16_t data)
{

}

uint32_t vl53l0x::readReg32(uint8_t subAddress)
{

}

void vl53l0x::readBuffer(uint8_t subAddress, uint8_t count, uint8_t * dest)
{

}

void vl53l0x::writeBuffer(uint8_t subAddress, uint8_t count, uint8_t * dest)
{

}

bool vl53l0x::isPresent()
{
    bool res = false;
    uint16_t val = readReg16(tof::reg::validate_0xC0);
    pr->printf("validation val : 0x%04X\n",val);
    if(val == 0xEEAA)
    {
        res = true;
    }
    return res;
}