#ifndef GUI_H
#define GUI_H

#define ROTARY_PIN_A          36
#define ROTARY_PIN_B          34
#define SMETERPIN             2

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
extern WiFiClient RemoteClient;

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
extern byte stationlist;
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
extern long rssi;
extern long rssiold;
extern unsigned int freq;
extern unsigned int frequency0;
extern unsigned int frequency1;
extern unsigned int frequency2;
extern unsigned int frequency3;
extern unsigned int frequency4;
extern unsigned int frequency5;
extern unsigned int frequency6;
extern bool RDSSpy;
extern unsigned long stlmillis;
extern bool wificonnect;
extern int SStatusold;
extern bool seek;
extern uint16_t MStatus;
extern uint16_t BW;
extern unsigned int BWOld;
extern byte BWsetOld;
extern byte BWset;
extern int16_t SStatus;
extern int16_t SAvg;
extern int16_t SAvg2;
extern int16_t SAvg3;
extern int8_t CNold;
extern int8_t CN;
extern bool cnvis;
extern bool BWreset;
extern bool StereoToggle;
extern bool Stereostatus;
extern bool Stereostatusold;
extern byte OStatusold;
extern bool setoffset;
extern byte stepsize;
extern byte tunemode;
extern bool btconnect;
extern bool USBstatus;
extern bool usblogo_on;
extern bool usblogo_off;
extern byte iMSset;
extern byte EQset;
extern bool mutelogo_on;
extern bool mutelogo_off;
extern String af;
extern String af2;
extern bool af2show;
extern byte displaysize;
extern byte af_scan;
extern byte af_counterold;
extern bool fullsearchrds;
extern String RTContent1old;
extern String RTContent2old;
extern String eonstringold;

extern void read_encoder(void);

void ShowRDS(void);
void ShowCT(void);
void ShowPI(void);
void ShowPS(void);
void ShowRadiotext(void);
void ShowPTY(void);
void ShowErrors(void);
void ShowECC(void);
void ShowRSSI(void);
void ShowFreq(void);
void ShowModLevel(void);
void ShowBW(void);
void ShowSignalLevel(void);
void ShowStereoStatus(void);
void ShowOffset(void);
void ShowStepSize(void);
void ShowTuneMode(void);
void ShowBTstatus(void);
void ShowUSBstatus(void);
void ShowiMS(void);
void ShowEQ(void);
void ShowSquelch(void);
void ShowAF(void);
void ShowRDSPlus(void);
void ShowEON(void);

#endif