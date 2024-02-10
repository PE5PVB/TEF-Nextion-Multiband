#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include "TEF6686.h"
#include <WiFi.h>
#include <SoftwareSerial.h>
#include <Hash.h>
#include <EEPROM.h>
#include "WiFiConnect.h"
#include "ADF4351.h"

extern EasyNex Display;
extern TEF6686 radio;
extern WiFiUDP Udp;
extern EspSoftwareSerial::UART swSer;
extern WiFiServer Server;
extern WiFiClient RemoteClient;
extern WiFiConnect wc;
extern ADF4351 Frontend;

extern bool btconnect;
extern bool btsetup;
extern bool direction;
extern bool fullsearchrds;
extern bool manfreq;
extern bool menu;
extern bool RDSSpy;
extern bool spec;
extern bool SQ;
extern bool Stereostatus;
extern bool StereoToggle;
extern bool store;
extern bool UHF;
extern bool USBstatus;
extern bool wificonnect;
extern bool wifiretry;
extern bool XDRGTK;
extern bool XDRGTKdata;
extern bool XDRGTKTCP;
extern bool XDRMute;
extern byte band;
extern byte BWset;
extern byte demp;
extern byte EQset;
extern byte IF;
extern byte iMSEQ;
extern byte iMSset;
extern byte stationlist;
extern byte wifienable;
extern char buff[16];
extern int HighEdgeSet0;
extern int HighEdgeSet1;
extern int HighEdgeSet2;
extern int HighEdgeSet3;
extern int HighEdgeSet4;
extern int HighEdgeSet6;
extern int LowEdgeSet0;
extern int LowEdgeSet1;
extern int LowEdgeSet2;
extern int LowEdgeSet3;
extern int LowEdgeSet4;
extern int LowEdgeSet6;
extern int offset;
extern int Squelch;
extern int VolSet;
extern int XDRBWset;
extern int XDRBWsetold;
extern int XDRscanner_filter;
extern int16_t OStatus;
extern int16_t SStatus;
extern int8_t CN;
extern IPAddress remoteip;
extern String cryptedpassword;
extern String MAC[10];
extern String NAME[10];
extern String packet;
extern String password;
extern String salt;
extern String saltkey;
extern String showsoftwareversion;
extern uint16_t BW;
extern uint16_t MStatus;
extern uint16_t USN;
extern uint16_t WAM;
extern uint8_t buff_pos;
extern unsigned int converteroffset;
extern unsigned int freq;
extern unsigned int frequency0;
extern unsigned int frequency1;
extern unsigned int frequency2;
extern unsigned int frequency3;
extern unsigned int frequency4;
extern unsigned int frequency5;
extern unsigned int frequency6;
extern unsigned int XDRfreq_scan;
extern unsigned int XDRscanner_end;
extern unsigned int XDRscanner_old;
extern unsigned int XDRscanner_start;
extern unsigned int XDRscanner_step;
extern unsigned long signalstatustimer;
extern unsigned long XDRshowmillis;

extern void RF(byte RFset);
extern void ShowBTstatus(void);
extern void ShowFreq(void);
extern void Seek(bool mode);
extern void doStereoToggle(void);
extern void doBW(void);
extern void doFilter(void);
extern void ShowiMS(void);
extern void ShowEQ(void);

void Communication(void);
void XDRGTKprint(String string);
void XDRGTKRoutine(void);
void passwordcrypt(void);
void passwordgenerator(void);
void tryWiFi(void);
void XDRGTKTune(unsigned int freqtemp);
#endif