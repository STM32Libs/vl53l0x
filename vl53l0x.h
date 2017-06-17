
#ifndef __VL53L0X__
#define __VL53L0X__

namespace tof
{
    uint8_t const i2c_default_address = 0x52;
    uint8_t const wrAdd = 0x52;
    uint8_t const rdAdd = 0x53;

    namespace reg
    {
        uint8_t const validate_Address = 0xC0;
        uint16_t const validate_Value = 0xEEAA;
        uint8_t const I2C_Mode = 0x88;
        uint8_t const VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV = 0x89;
    }
}

class vl53l0x
{
public:
    vl53l0x(Serial *ps,PinName pin_sda, PinName pin_scl);

    bool isPresent();
    void off();
    void on();
    void init(bool is_2v8 = true);
    void dump();


    //Data transfer functions
    void        updateReg(uint8_t subAddress, uint8_t and_data, uint8_t or_data);
    void        setbits(uint8_t subAddress, uint8_t bits);
    void        clearbits(uint8_t subAddress, uint8_t bits);
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