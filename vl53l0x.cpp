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
    i2c.write(tof::wrAdd, (const char*)&subAddress, 1, 1); // no stop
    i2c.write(tof::wrAdd, (const char*)&data, 1);
}

uint8_t vl53l0x::readReg8(uint8_t subAddress)
{
    uint8_t res = 0;
    i2c.write(tof::wrAdd, (const char*)&subAddress, 1, 1); // no stop
    i2c.read(tof::rdAdd, (char*)&res, 1);
    return res;
}

void vl53l0x::updateReg(uint8_t subAddress, uint8_t and_data, uint8_t or_data)
{
    uint8_t val = readReg8(subAddress);
    val = (val & and_data) | or_data;
    writeReg8(subAddress,val);
}

void vl53l0x::setbits(uint8_t subAddress, uint8_t bits)
{
    uint8_t val = readReg8(subAddress);
    val |= bits;
    writeReg8(subAddress,val);
}

void vl53l0x::clearbits(uint8_t subAddress, uint8_t bits)
{
    uint8_t val = readReg8(subAddress);
    val &= ~bits;
    writeReg8(subAddress,val);
}


void vl53l0x::writeReg16(uint8_t subAddress, uint16_t data)
{
    uint8_t buf[2];
    buf[0] = (data>>8)  & 0xFF;
    buf[1] = data       & 0xFF;
    i2c.write(tof::wrAdd, (const char*)&subAddress, 1, 1); // no stop
    i2c.write(tof::wrAdd, (const char*)buf, 2);
}

uint16_t vl53l0x::readReg16(uint8_t subAddress)
{
    char buf[2] = {0, 0};
    i2c.write(tof::wrAdd, (const char*)&subAddress, 1, 1); // no stop
    i2c.read(tof::rdAdd, buf, 2);
    uint16_t res = (buf[0]<<8 ) | buf[1];
    return res;
}

void vl53l0x::writeReg32(uint8_t subAddress, uint16_t data)
{
    uint8_t buf[4];
    buf[0] = (data>>24)  & 0xFF;
    buf[1] = (data>>16)  & 0xFF;
    buf[2] = (data>> 8)  & 0xFF;
    buf[3] = data        & 0xFF;
    i2c.write(tof::wrAdd, (const char*)&subAddress, 1, 1); // no stop
    i2c.write(tof::wrAdd, (const char*)buf, 4);
}

uint32_t vl53l0x::readReg32(uint8_t subAddress)
{
    char buf[4] = {0,0,0,0};
    i2c.write(tof::wrAdd, (const char*)&subAddress, 1, 1); // no stop
    i2c.read(tof::rdAdd, buf, 4);
    uint32_t res = (buf[0]<<24 ) | (buf[1]<<16 ) | (buf[2]<<8 ) | buf[3];
    return res;
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
    uint16_t val = readReg16(tof::reg::validate_Address);
    if(val == tof::reg::validate_Value)
    {
        res = true;
    }
    return res;
}

void vl53l0x::off()
{

}

void vl53l0x::on()
{

}

void vl53l0x::init(bool is_2v8)
{
    if(is_2v8)
    {
        setbits(tof::reg::VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV,0x01);
    }
    uint8_t val = readReg8(tof::reg::VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV);
    pr->printf("VHV Val = 0x%x\n",val);

    //I2C Standard mode
    writeReg8(tof::reg::I2C_Mode,0x00);

}
