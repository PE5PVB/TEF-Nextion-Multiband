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
extern WiFiClient RemoteClient;

extern bool af2show;
extern bool btconnect;
extern bool BWreset;
extern bool cnvis;
extern bool displayreset;
extern bool dropout;
extern bool EONold;
extern bool fullsearchrds;
extern bool hasCTold;
extern bool manfreq;
extern bool menu;
extern bool mutelogo_off;
extern bool mutelogo_on;
extern bool RDSSpy;
extern bool RDSstatus;
extern bool RDSstatusold;
extern bool rtcset;
extern bool RTPlus;
extern bool seek;
extern bool setoffset;
extern bool showrdsinfo;
extern bool spec;
extern bool SQ;
extern bool Stereostatus;
extern bool Stereostatusold;
extern bool StereoToggle;
extern bool TAold;
extern bool TPold;
extern bool tunereset;
extern bool usblogo_off;
extern bool usblogo_on;
extern bool USBstatus;
extern bool wificonnect;
extern bool XDRGTK;
extern bool XDRGTKTCP;
extern byte af_counterold;
extern byte af_scan;
extern byte band;
extern byte BWset;
extern byte BWsetOld;
extern byte displaysize;
extern byte ECCold;
extern byte EQset;
extern byte iMSset;
extern byte MSold;
extern byte OStatusold;
extern byte stationlist;
extern byte stepsize;
extern byte tunemode;
extern byte wifienable;
extern char programTypePrevious[18];
extern int SStatusold;
extern int16_t OStatus;
extern int16_t SAvg;
extern int16_t SAvg2;
extern int16_t SAvg3;
extern int16_t SStatus;
extern int8_t CN;
extern int8_t CNold;
extern IPAddress remoteip;
extern long rssi;
extern long rssiold;
extern String af;
extern String af2;
extern String eonstringold;
extern String PIold;
extern String PSold;
extern String rds_clock;
extern String rds_clockold;
extern String RTContent1old;
extern String RTContent2old;
extern String RTold;
extern String showsoftwareversion;
extern uint16_t BW;
extern uint16_t MStatus;
extern uint16_t USN;
extern uint16_t WAM;
extern uint8_t RDSerrorsold;
extern unsigned int BWOld;
extern unsigned int freq;
extern unsigned int frequency0;
extern unsigned int frequency1;
extern unsigned int frequency2;
extern unsigned int frequency3;
extern unsigned int frequency4;
extern unsigned int frequency5;
extern unsigned int frequency6;
extern unsigned long BWTimer;
extern unsigned long CNTimer;
extern unsigned long stlmillis;
extern unsigned long tuneresetcounter;

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