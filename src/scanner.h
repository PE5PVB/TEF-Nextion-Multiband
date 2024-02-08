#ifndef SCANNER_H
#define SCANNER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <EasyNextionLibrary.h>
#include "TEF6686.h"
#include "ADF4351.h"

extern EasyNex Display;
extern TEF6686 radio;
extern ADF4351 Frontend;

extern bool donesearch;
extern bool scanfound;
extern bool spec;
extern byte band;
extern byte displaysize;
extern byte IF;
extern byte scanner_band;
extern byte scanner_speed;
extern byte scanner_speed;
extern byte scanner_th;
extern byte scanner_thenable;
extern byte scanstatus;
extern int offset;
extern int rotary;
extern int16_t OStatus;
extern int16_t SStatus;
extern int8_t CN;
extern uint16_t BW;
extern uint16_t MStatus;
extern uint16_t USN;
extern uint16_t WAM;
extern unsigned int converteroffset;
extern unsigned int freq;
extern unsigned int freq_scan;
extern unsigned int frequency0;
extern unsigned int frequency1;
extern unsigned int frequency2;
extern unsigned int frequency3;
extern unsigned int frequency4;
extern unsigned int scanner_end;
extern unsigned int scanner_found;
extern unsigned int scanner_start;
extern unsigned int scanner_vbw;
extern unsigned int scanner_vbw;
extern unsigned long time_now;

extern void RF(byte RFset);
extern void doExit(void);
extern void RoundStep(void);

void SpectrumAnalyser(void);
void BuildScanScreen(void);
void scan_loop(void);
void scanup(void);
void scandown(void);

#endif