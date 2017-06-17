
#ifndef __VL53L0X__
#define __VL53L0X__

namespace tof
{
    uint8_t const i2c_default_address = 0x52;
    namespace reg
    {
        uint8_t const validate_0xC0 = 0xC0;
    }
}

class vl53l0x
{
public:
    vl53l0x(Serial *ps,PinName pin_sda, PinName pin_scl);

    bool isPresent();


    //Data transfer functions
    void        writeReg8(uint8_t subAddress, uint8_t data);
    uint8_t     readReg8(uint8_t subAddress);
    void        writeReg16(uint8_t subAddress, uint16_t data);
    uint16_t    readReg16(uint8_t subAddress);
    void        writeReg32(uint8_t subAddress, uint16_t data);
    uint32_t    readReg32(uint8_t subAddress);
    void        readBuffer(uint8_t subAddress, uint8_t count, uint8_t * dest);
    void        writeBuffer(uint8_t subAddress, uint8_t count, uint8_t * dest);

public:
    I2C     i2c;
    Serial *pr;
};


#endif /*__VL53L0X__*/