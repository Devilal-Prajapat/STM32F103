/*
  @   Date               :        09.05.2020 / Saturday
  @   Contact            :        Editing by Devilal Prajapat & Sakshi Baliyan & Rahul Sharma
  @   Description        :        This Library for LC709203F Gauge Sensor
*/


#include "main.h"
#include <stdint.h>
//#include "stm32l0xx_hal_i2c.h"

extern I2C_HandleTypeDef hi2c1;

#ifndef      _LC709203F_H_ 
#define      _LC709_H_ 

#define cmd_beforeRSOC            0x04
#define cmd_thermistorB           0x06
#define cmd_initialRSOC           0x07
#define cmd_cellTemperature       0x08
#define cmd_cellVoltage           0x09
#define cmd_currentDirection      0x0A
#define cmd_APA                   0x0B
#define cmd_APT                   0x0C
#define cmd_RSOC                  0x0D
#define cmd_ITE                   0x0F
#define cmd_ICversion             0x11
#define cmd_changeOftheParameter  0x12
#define cmd_alarmLowRSOC          0x13
#define cmd_alarmLowCellVoltage   0x14
#define cmd_ICpowerMode           0x15
#define cmd_statusBit             0x16
#define cmd_numberOfTheParameter  0x1A

#define cmd_CRCpolynomial         0x07
#define LC709203_DeviceID         0x0B

/* 
	 @Brief         CRC Checker
	 @Description   Needed byte for Cyclic Redundancy Check.
									LC709203_DeviceID, Control Reg, LSB Byte, MSB Byte, CRC Byte 
	 @Parameter     uint8_t *rec_values -> array name for check
									uint8_t len         -> lengt of array
	 @Return value  uint8_t
*/
uint8_t check_crc(uint8_t *rec_values, uint8_t len);
uint32_t write_rsoc(void);

/* 
	 @Brief         Calibration before the startup
	 @Description   Obtain OCV(Open Circuit Voltage) in 10ms.
									Figure 8 on datasheet
	 @Parameter     I2C_HandleTypeDef   -> i2c 
	 @Return value  None
*/
void LC709203_RSOC_before(I2C_HandleTypeDef i2c) ;


/* @
	 @Brief           Thermistor set
	 @Description     Sets B-constant of the thermistor to be measured. Refer to
										the specification sheet of the thermistor for the set value to use
	 @Parameter       I2C_HandleTypeDef   -> i2c 
	 @Return value    uint16_t
 */
uint16_t LC709203_thermistorB(I2C_HandleTypeDef i2c);

/*  
	 @Brief           Automatic Initialization RSOC
	 @Description     Calibration when start-up.More efficiency than RSOC_before @Figure 7 on datasheet
	 @Parameter       I2C_HandleTypeDef -> i2c 
	 @Return value    None
 */
void LC709203_RSOC_initial(I2C_HandleTypeDef i2c);

/*  
	 @Brief           Displays Cell Temperature
	 @Description     This register contains the cell temperature from -20C (0×09E4) to
										+60 C (0×0D04) measured in 0.1C units
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    float
 */
float LC709203_cellTemperature(I2C_HandleTypeDef i2c);

/*  
	 @Brief           Displays Cell Voltage
	 @Description     This register contains the voltage on VDD 1 mV units
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_cellVoltage(I2C_HandleTypeDef i2c); 

/*  
	 @Brief           This register is used to control the reporting of RSOC
	 @Description     In Auto mode the RSOC is reported as it increases or decreases.
										In Charge mode the RSOC is not permitted to decrease. In
										Discharge mode the RSOC is not permitted to increase
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_currentDirection(I2C_HandleTypeDef i2c);

/*  
	 @Brief           This register contains the adjustment value for a battery
										type to improve the RSOC precision
	 @Description     The deeper adjustment of APA may
										improve the accuracy  
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_adjusmentPackApplicaiton(I2C_HandleTypeDef i2c);

/*  
	 @Brief           This is used to compensate for the delay of the thermistor
										measurement caused by a capacitor across the thermistor
	 @Description     The default value has been found to meet most of circuits
										where a capacitor like showing in Figure 13 is not put
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_adjusmentPackThermistor(I2C_HandleTypeDef i2c);

/*  
	 @Brief           RSOC is reported in 1% units over the range 0% to 100%
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_RSOC(I2C_HandleTypeDef i2c);

/*  
	 @Brief           This is the same as RSOC with a resolution of 0.1% over
										the range 0.0% to 100.0%
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_indicatorToEmpty(I2C_HandleTypeDef i2c);

/*  
	 @Brief           This is an ID number of an LSI
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_IC_Version(I2C_HandleTypeDef i2c) ;

/*  
	 @Brief           This register is used to select the battery profile to
										be used
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_changeOfTheParameter(I2C_HandleTypeDef i2c);

/*  
	 @Brief           The ALARMB pin will be set low when the RSOC value
										falls below this value, will be released from low when RSOC
										value rises than this value
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_RSOC_alarmLow(I2C_HandleTypeDef i2c);

/*  
	 @Brief           The ALARMB pin will be set low if VDD falls below this
										value, will be released from low if VDD rises than this value
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_alarmLowCellVoltage(I2C_HandleTypeDef i2c) ;

/*  
	 @Brief           The LSI has two power modes. Sleep (0x15 = 02) or
										Operational mode (0x15 = 01)                  
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_IC_powerMode(I2C_HandleTypeDef i2c);

/*  
	 @Brief           This selects the Thermistor mode
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_statusBit(I2C_HandleTypeDef i2c);

/*  
	 @Brief           The LSI contains a data file comprised of two battery
										profiles. This register contains identity of the data file.
	 @Description   
	 @Parameter       I2C_HandleTypeDef -> i2c
	 @Return value    uint16_t
 */
uint16_t LC709203_numberOfTheParameter(I2C_HandleTypeDef i2c);
    
#endif

