# vl53l0x
The Time Of Flight sensor through i2c interface

# Origin
Started on the basis of https://developer.mbed.org/teams/ST/code/X_NUCLEO_53L0A1/docs/8d27ebb4e1eb/classVL53L0X.html
But then realised it's way toom uch effort and the registers are undocumented as they invite developpers to use the API 
which is fair because the exchange is way too complex.
# Stopped
The work was to mbed-ify the ST driver, luckily, here is exactly that : https://github.com/dbaba/vl53l0x-mbedos
forked just in case it disappears
