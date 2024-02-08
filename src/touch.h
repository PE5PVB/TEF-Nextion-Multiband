#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include <WiFiClient.h>
#include "TEF6686.h"
#include <WiFi.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "WiFiConnect.h"
#include "ADF4351.h"

extern EasyNex Display;
extern TEF6686 radio;
extern WiFiClient RemoteClient;
extern WiFiUDP Udp;
extern WiFiConnect wc;
extern WiFiServer Server;
extern EspSoftwareSerial::UART swSer;
extern ADF4351 Frontend;

extern bool btconnect;
extern bool btsetup;
extern bool ctshow;
extern bool displayreset;
extern bool fullsearchrds;
extern bool manfreq;
extern bool setoffset;
extern bool showrdserrors;
extern bool showrdsinfo;
extern bool spec;
extern bool UHF;
extern bool wificonnect;
extern bool wifiretry;
extern byte am;
extern byte band;
extern byte BWset;
extern byte coaxmode;
extern byte ContrastSet;
extern byte demp;
extern byte fm;
extern byte fmsi;
extern byte IF;
extern byte ip1;
extern byte ip2;
extern byte ip3;
extern byte ip4;
extern byte lf;
extern byte OStatusold;
extern byte OStatusold;
extern byte scanner_band;
extern byte scopeview;
extern byte softmuteam;
extern byte softmutefm;
extern byte stationlist;
extern byte uhf1;
extern byte uhf2;
extern byte uhf3;
extern byte uhf4;
extern byte uhf6;
extern byte usbmode;
extern byte wifienable;
extern byte wifienableold;
extern int AM_att;
extern int AM_Cochannel;
extern int AM_NBLevel;
extern int BlendLevel;
extern int BlendOffset;
extern int HighCutLevel;
extern int HighCutOffset;
extern int HighEdgeSet0;
extern int HighEdgeSet1;
extern int HighEdgeSet2;
extern int HighEdgeSet3;
extern int HighEdgeSet4;
extern int HighEdgeSet6;
extern int LevelOffset0;
extern int LevelOffset1;
extern int LevelOffset2;
extern int LevelOffset3;
extern int LevelOffset4;
extern int LevelOffset6;
extern int LowEdgeSet0;
extern int LowEdgeSet1;
extern int LowEdgeSet2;
extern int LowEdgeSet3;
extern int LowEdgeSet4;
extern int LowEdgeSet6;
extern int NBLevel;
extern int offset;
extern int StereoLevel;
extern int VolSet;
extern int VolSet;
extern IPAddress remoteip;
extern String password;
extern unsigned int converteroffset;
extern unsigned int fmsi_11;
extern unsigned int fmsi_12;
extern unsigned int fmsi_21;
extern unsigned int fmsi_22;
extern unsigned int fmsi_31;
extern unsigned int fmsi_32;
extern unsigned int fmsi_41;
extern unsigned int fmsi_42;
extern unsigned int fmsi_attack;
extern unsigned int fmsi_release;
extern unsigned int freq;
extern unsigned int freqtemp;
extern unsigned int frequency0;
extern unsigned int frequency1;
extern unsigned int frequency2;
extern unsigned int frequency3;
extern unsigned int frequency4;
extern unsigned int frequency5;
extern unsigned int frequency6;
extern unsigned int scanner_end;
extern unsigned int scanner_start;

void trigger1(void);
void trigger2(void);
void trigger3(void);
void trigger4(void);
void trigger5(void);
void trigger6(void);
void trigger7(void);
void trigger8(void);
void trigger9(void);
void trigger10(void);
void trigger11(void);
void trigger12(void);
void trigger13(void);
void trigger14(void);
void trigger15(void);
void trigger16(void);
void trigger17(void);
void trigger18(void);
void trigger19(void);
void trigger20(void);
void trigger21(void);
void trigger22(void);
void trigger23(void);
void trigger24(void);
void trigger25(void);
void trigger26(void);
void trigger27(void);
void trigger28(void);
void trigger29(void);
void trigger30(void);
void trigger31(void);
void trigger32(void);
void trigger33(void);
void trigger34(void);
void trigger35(void);
void trigger36(void);
void trigger37(void);
void trigger38(void);
void trigger39(void);
void trigger40(void);
void trigger41(void);
void trigger42(void);

extern void doStereoToggle(void);
extern void doBW(void);
extern void ShowBW(void);
extern void doFilter(void);
extern void BandSet(void);
extern void doTuneMode(void);
extern void BuildScanScreen(void);
extern void RF(byte RFset);
extern void doExit(void);
extern void EEpromReadData(void);
extern void passwordgenerator(void);
extern void ShowFreq(void);
extern void ShowStereoStatus(void);
extern void ShowOffset(void);
extern void ShowStepSize(void);
extern void ShowTuneMode(void);
extern void ShowUSBstatus(void);
extern void ShowBTstatus(void);
extern void tryWiFi(void);

#endif