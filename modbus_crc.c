#include <stdint.h>
#include <stdio.h>

#define CRC_POLY  0xA001

uint16_t cal_crc16(uint8_t *pbuff, uint16_t len)
{
	uint16_t crc_reg = 0xFFFF;
	
	for(uint16_t i = 0; i< len; i++)
	{
		crc_reg = crc_reg^pbuff[i];
		for(uint8_t j = 8; j>0;j--)
		{
			if(crc_reg & 0x001 == 0x001)
			{
				crc_reg >>= 1;
				crc_reg ^= CRC_POLY;
			}
			else
			{
				crc_reg >>= 1;
			}		
		}
	}
	return crc_reg;
}

//01 03 0C 25 00 02 D6 90
//0x90d6
uint8_t data[] = {0x01, 0x03, 0x0C, 0x25, 0x00, 0x02};

int main()
{
	printf("0x%02x",cal_crc16(data,sizeof(data)));
}
