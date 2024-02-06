#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include <WiFiClient.h>
#include "TEF6686.h"
#include <TimeLib.h>
#include <WiFi.h>
#include <ESP32Time.h>

extern EasyNex Display;
extern TEF6686 radio;
extern WiFiUDP Udp;
extern ESP32Time rtc;

extern bool displayreset;
extern bool dropout;
extern bool EONold;
extern bool hasCTold;
extern bool manfreq;
extern bool menu;
extern bool RDSstatus;
extern bool RDSstatusold;
extern bool rtcset;
extern bool RTPlus;
extern bool showrdsinfo;
extern bool spec;
extern bool SQ;
extern bool stationlist;
extern bool TAold;
extern bool TPold;
extern byte band;
extern byte ECCold;
extern byte MSold;
extern byte wifienable;
extern char programTypePrevious[18];
extern int16_t OStatus;
extern IPAddress remoteip;
extern String PIold;
extern String PSold;
extern String rds_clock;
extern String rds_clockold;
extern String RTold;
extern String showsoftwareversion;
extern uint16_t USN;
extern uint16_t WAM;
extern uint8_t RDSerrorsold;

void ShowRDS(void);
void ShowCT(void);
void ShowPI(void);
void ShowPS(void);
void ShowRadiotext(void);
void ShowPTY(void);
void ShowErrors(void);
void ShowECC(void);

#endif