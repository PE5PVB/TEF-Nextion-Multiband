#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include "TEF6686.h"
#include <WiFi.h>
#include <SoftwareSerial.h>
#include <Hash.h>

extern EasyNex Display;
extern TEF6686 radio;
extern WiFiUDP Udp;
extern EspSoftwareSerial::UART swSer;
extern WiFiServer Server;
extern WiFiClient RemoteClient;

extern bool btconnect;
extern bool btsetup;
extern bool direction;
extern bool fullsearchrds;
extern bool manfreq;
extern bool menu;
extern bool RDSSpy;
extern bool spec;
extern bool SQ;
extern bool stationlist;
extern bool Stereostatus;
extern bool StereoToggle;
extern bool store;
extern bool USBstatus;
extern bool wificonnect;
extern bool XDRGTK;
extern bool XDRGTKdata;
extern bool XDRGTKTCP;
extern bool XDRMute;
extern byte band;
extern byte BWset;
extern byte demp;
extern bool EQset;
extern byte iMSEQ;
extern bool iMSset;
extern byte SNR;
extern byte wifienable;
extern char buff[16];
extern int Squelch;
extern int VolSet;
extern int XDRBWset;
extern int XDRBWsetold;
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
extern unsigned int frequency0;
extern unsigned int frequency5;
extern unsigned int XDRfreq_scan;
extern unsigned int XDRscanner_end;
extern unsigned int XDRscanner_filter;
extern unsigned int XDRscanner_old;
extern unsigned int XDRscanner_start;
extern unsigned int XDRscanner_step;

extern void RF(byte RFset);
extern void ShowBTstatus();
extern void ShowFreq();
extern void Seek(bool mode);
extern void doStereoToggle();
extern void doBW();
extern void doFilter();

void Communication(void);
void XDRGTKprint(String string);
void XDRGTKRoutine(void);
void passwordcrypt(void);
void passwordgenerator(void);
#endif