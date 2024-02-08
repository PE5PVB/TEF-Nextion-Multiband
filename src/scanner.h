#ifndef SCANNER_H
#define SCANNER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <EasyNextionLibrary.h>
#include "TEF6686.h"
#include "ADF4351.h"

#define ROTARY_BUTTON         39

extern EasyNex Display;
extern TEF6686 radio;
extern ADF4351 Frontend;

extern unsigned int scanner_vbw;
extern byte scanner_band;
extern byte displaysize;
extern unsigned int freq_scan;
extern unsigned int scanner_start;
extern unsigned int scanner_end;
extern unsigned int converteroffset;
extern byte scanner_speed;
extern byte IF;
extern int offset;
extern int16_t SStatus;
extern uint16_t USN;
extern uint16_t WAM;
extern int16_t OStatus;
extern uint16_t BW;
extern uint16_t MStatus;
extern int8_t CN;
extern byte scanner_thenable;
extern bool scanfound;
extern byte scanner_th;
extern unsigned int scanner_found;
extern bool donesearch;
extern byte scanner_speed;
extern unsigned int scanner_vbw;
extern unsigned long time_now;
extern byte scanstatus;
extern int rotary;
extern unsigned int freq;
extern byte band;
extern unsigned int frequency0;
extern unsigned int frequency1;
extern unsigned int frequency2;
extern unsigned int frequency3;
extern unsigned int frequency4;
extern bool spec;

extern void RF(byte RFset);
extern void doExit(void);
extern void RoundStep(void);

void SpectrumAnalyser(void);
void BuildScanScreen(void);
void scan_loop(void);
void scanup(void);
void scandown(void);

#endif