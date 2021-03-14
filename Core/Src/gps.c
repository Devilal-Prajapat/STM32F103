/*
 * gps.c
 *
 *  Created on: Jul 19, 2020
 *      Author: 0h2
 */

#include "main.h"
#include "gps.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char Header[]={'$','D','P',',','s','L','I','C','S',','};
char Version[]={'v','1','.','0','N','R','L'};
char Vch_No[]={'R','J','1','1','S','F','0','1','7','2'};
char IMEI_NUM[15] = "12345678912345";

extern uint8_t GPSRecvComplt_F;
extern uint8_t Rx_BuffCount;
extern uint8_t RxData;
extern uint8_t Gps_RxBuff[512];
extern uint8_t gps_string_f;

char GPS_Buff[512];
// parse data
char  gps_string[256];
int gps_string_len = 0;
char gps_sentence[7];
char gps_time[11];
char gps_date[7];
char gps_valid[2];
char lat[11];
char lat_d[2];
char lng[12];
char lng_d[2];
char gps_speed[10];
char gps_angle[10];
int  num_of_sat;
float altitude;

void  get_gps(void)
{
	while(1)
	{
		HAL_UART_Receive(&huart3, &RxData, 1, 1);
		if(Rx_BuffCount>180)
		{
			GPSRecvComplt_F = 1;
			break;
		}
		else if((RxData == '$' || RxData == 'G' || RxData == 'P' || RxData == 'R' || RxData == 'M' || RxData == 'C') && (gps_string_f == 0))
		{
			if(Rx_BuffCount == 0 && RxData == '$')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			if(Rx_BuffCount == 1 && RxData == 'G')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 2 && RxData == 'P')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 3 && RxData == 'R')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 4 && RxData == 'M')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 5 && RxData == 'C')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
				gps_string_f = 1;
			}
		}
		else
		{
			if(gps_string_f == 1)
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}else
			{
				Rx_BuffCount = 0;
			}
		}
	}
}

static float NMEA_to_DD(char * Buf)
{
	float nmea = atof(Buf);
	int  dd = (int)(nmea/100);
	float minutes = (nmea - dd*100)/60;
	return  (float)(dd + minutes);
}

static void create_gps_buff(void)
{
//	if(gps_valid == "A" || gps_valid == "V")
//	{
//
//	}
	memset(gps_string,0x00,sizeof(gps_string));
	gps_string_len = sprintf(gps_string,"$DP,SILICS,v1.0,NR,L,%s,%s,%s,%s,%s,%f,%s,%f,%s,%s,%s,%d,%f\n\r",IMEI_NUM,Vch_No,gps_valid, gps_date, gps_time, NMEA_to_DD(lat), lat_d,NMEA_to_DD(lng),lng_d,gps_speed, gps_angle,num_of_sat,altitude);
//	HAL_UART_Transmit(&huart2,(uint8_t *)gps_string, len, 100);

}

static void parse_gprmc(char *nmea)
{

	char *ptr;

	ptr = strtok(nmea,",");
	strcpy(gps_sentence,ptr);
	ptr = strtok(NULL ,",");
	strcpy(gps_time,ptr);
	ptr = strtok(NULL ,",");
	strcpy(gps_valid,ptr);
	ptr = strtok(NULL ,",");
	strcpy(lat,ptr);
	ptr = strtok(NULL ,",");
	strcpy(lat_d,ptr);
	ptr = strtok(NULL ,",");
	strcpy(lng,ptr);
	ptr = strtok(NULL ,",");
	strcpy(lng_d,ptr);
	ptr = strtok(NULL ,",");
	strcpy(gps_speed,ptr);
	ptr = strtok(NULL ,",");
	strcpy(gps_angle,ptr);
	ptr = strtok(NULL ,",");
	strcpy(gps_date,ptr);
}

static void parse_gpgga(char * Buf)
{
	char *ret = strstr(Buf, "E");
	if(ret[0] == 'E' || ret[0] == 'W')
	{
		char nmea[21];
		strncpy(nmea,ret,21);

		char *ptr;
		ptr = strtok(nmea,",");
		ptr = strtok(NULL,",");
		ptr = strtok(NULL,",");
		num_of_sat = atoi(ptr);
		ptr = strtok(NULL,",");
		ptr = strtok(NULL,",");
		altitude = atof(ptr);
	}
}

void  Parse_GPS(char *Buf)
{
	if((strncmp(Buf,"$GPRMC",6) == 0))
	{
		if((Buf[18] == 'A' || Buf[18] == 'V') && (Buf[31] == 'N' || Buf[31] == 'S') && (Buf[45] == 'E' || Buf[45] == 'W'))
		{
			char gprmc[86];
			char gpgga[86];
			strncpy(gprmc,Buf,86);
			parse_gprmc(gprmc);
			char *ret = strstr(Buf, "$GPGGA");
			if(strncmp(ret,"$GPGGA",6) == 0)
			{

				strncpy(gpgga,ret,86);
				parse_gpgga(gpgga);
			}
			create_gps_buff();
		}
	}


}

