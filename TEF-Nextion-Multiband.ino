#include <Wire.h>                   // Included in Boardmanager
#include <WiFiClient.h>             // Included in Boardmanager
#include <EEPROM.h>                 // Included in Boardmanager
#include <SoftwareSerial.h>         // https://github.com/plerup/espsoftwareserial/
#include <EasyNextionLibrary.h>     // https://github.com/Seithan/EasyNextionLibrary
#include <Hash.h>                   // https://github.com/bbx10/Hash_tng
#include <TimeLib.h>                // https://github.com/PaulStoffregen/Time
#include "src/constants.h"
#include "src/TEF6686.h"            // Included with this file
#include "src/ADF4351.h"            // Included with this file
#include "src/WiFiConnect.h"        // Included with this file
#include "src/gui.h"
#include "src/comms.h"
#include "src/scanner.h"
#include "src/touch.h"

WiFiConnect wc;
WiFiServer Server(7373);
WiFiUDP Udp;
WiFiClient RemoteClient;
EasyNex Display(Serial2);
TEF6686 radio;
ADF4351 Frontend;
EspSoftwareSerial::UART swSer;
ESP32Time rtc(0);

bool af2show;
bool btconnect;
bool btsetup;
bool BWreset = true;
bool cnvis;
bool ctshow;
bool direction;
bool displayreset;
bool donesearch;
bool dropout;
bool EONold;
bool fullsearchrds;
bool hasCTold;
bool manfreq;
bool memorystore;
bool menu;
bool mlogo_off;
bool mlogo_on;
bool MS;
bool mutelogo_off;
bool mutelogo_on;
bool mutestatus = true;
bool optrot;
bool power;
bool RDSSpy;
bool RDSstatus;
bool RDSstatusold;
bool rotarymode;
bool rtcset;
bool RTPlus;
bool scanfound;
bool seek;
bool setoffset;
bool showrdserrors;
bool showrdsinfo;
bool slogo_off;
bool slogo_on;
bool spec;
bool SQ;
bool Stereostatus;
bool Stereostatusold;
bool StereoToggle = true;
bool store;
bool TA;
bool TAold;
bool TP;
bool TPold;
bool UHF;
bool usblogo_off;
bool usblogo_on;
bool USBstatus;
bool wificonnect;
bool wifiretry;
bool XDRGTK;
bool XDRGTKdata;
bool XDRGTKTCP;
bool XDRMute;
byte af_counterold;
byte af_scan;
byte am;
byte band;
byte btselect;
byte BWset;
byte BWsetAM = 2;
byte BWsetOld = 254;
byte change;
byte coaxmode;
byte CoaxSwitch;
byte ContrastSet;
byte demp;
byte displaysize;
byte ECCold;
byte EQset;
byte fm;
byte fmsi;
byte IF;
byte iMSEQ;
byte iMSset;
byte ip1;
byte ip2;
byte ip3;
byte ip4;
byte lf;
byte memory_pos;
byte MSold;
byte OStatusold;
byte scanner_band;
byte scanner_speed;
byte scanner_th;
byte scanner_thenable;
byte scanstatus;
byte scopeview;
byte softmuteam;
byte softmutefm;
byte stationlist;
byte stepsize;
byte TEF;
byte tunemode;
byte uhf1;
byte uhf2;
byte uhf3;
byte uhf4;
byte uhf6;
byte usbmode;
byte wifienable;
byte wifienableold;
char buff[16];
char musicArtistPrevious[48];
char musicTitlePrevious[48];
char programTypePrevious[18];
char radioIdPrevious[5];
char stationEventPrevious[48];
char stationHostPrevious[48];
int AM_att;
int AM_Cochannel;
int AM_NBLevel;
int BlendLevel;
int BlendOffset;
int displayversion;
int HighCutLevel;
int HighCutOffset;
int HighEdgeSet0;
int HighEdgeSet1;
int HighEdgeSet2;
int HighEdgeSet3;
int HighEdgeSet4;
int HighEdgeSet6;
int LevelOffset0;
int LevelOffset1;
int LevelOffset2;
int LevelOffset3;
int LevelOffset4;
int LevelOffset6;
int LowEdgeSet0;
int LowEdgeSet1;
int LowEdgeSet2;
int LowEdgeSet3;
int LowEdgeSet4;
int LowEdgeSet6;
int NBLevel;
int offset;
int rotary;
int scanner_filter;
int Squelch;
int Squelchold;
int SStatusold;
int StereoLevel;
int timeoffset;
int VolSet;
int XDRBWset;
int XDRBWsetold;
int XDRscanner_filter;
int16_t OStatus;
int16_t SAvg;
int16_t SAvg2;
int16_t SAvg3;
int16_t SStatus;
int8_t CN;
int8_t CNold;
IPAddress remoteip;
long rssi;
long rssiold = 1;
String af;
String af2;
String clockPrevious;
String cryptedpassword;
String datePrevious;
String eonstringold;
String MAC[10];
String NAME[10];
String packet;
String password = "12345";
String PIcode;
String PIold;
String programServicePrevious;
String PSold;
String radioTextPrevious;
String rds_clock = "--:--";
String rds_clockold;
String rds_date = "----------";
String RDSSPYRDSold;
String RTContent1old;
String RTContent2old;
String RTold;
String salt;
String saltkey = "                ";
String showsoftwareversion;
String XDRGTKRDSold;
uint16_t BW;
uint16_t highcut;
uint16_t minutesold;
uint16_t MStatus;
uint16_t stereo;
uint16_t sthiblend;
uint16_t USN;
uint16_t WAM;
uint8_t af_counter;
uint8_t buff_pos = 0;
uint8_t RDSerrorsold;
uint8_t stband_1;
uint8_t stband_2;
uint8_t stband_3;
uint8_t stband_4;
unsigned int BWOld;
unsigned int converteroffset;
unsigned int fmsi_11;
unsigned int fmsi_12;
unsigned int fmsi_21;
unsigned int fmsi_22;
unsigned int fmsi_31;
unsigned int fmsi_32;
unsigned int fmsi_41;
unsigned int fmsi_42;
unsigned int fmsi_attack;
unsigned int fmsi_release;
unsigned int freq;
unsigned int freq_scan;
unsigned int freqtemp;
unsigned int frequency0;
unsigned int frequency0old;
unsigned int frequency1;
unsigned int frequency1old;
unsigned int frequency2;
unsigned int frequency2old;
unsigned int frequency3;
unsigned int frequency3old;
unsigned int frequency4;
unsigned int frequency4old;
unsigned int frequency5;
unsigned int frequency5old;
unsigned int frequency6;
unsigned int frequency6old;
unsigned int memory[30];
unsigned int scanner_end;
unsigned int scanner_found;
unsigned int scanner_start;
unsigned int scanner_vbw;
unsigned int XDRfreq_scan;
unsigned int XDRscanner_end;
unsigned int XDRscanner_old;
unsigned int XDRscanner_start;
unsigned int XDRscanner_step;
unsigned long showmillis;
unsigned long signalstatustimer;
unsigned long stlmillis;
unsigned long time_now;
unsigned long XDRshowmillis;

void setup(void) {
  swSer.begin(9600, EspSoftwareSerial::SWSERIAL_8N1, 13, 14, false, 95);
  btStop();
  Display.begin(38400);
  delay(500);
  pinMode(SMETERPIN, OUTPUT);
  pinMode(MODEBUTTON, INPUT);
  pinMode(BAND, INPUT_PULLUP);
  pinMode(BWBUTTON, INPUT);
  pinMode(ROTARY_BUTTON, INPUT);
  pinMode(ROTARY_PIN_A, INPUT);
  pinMode(ROTARY_PIN_B, INPUT);
  pinMode(RFA, OUTPUT);
  pinMode(RFB, OUTPUT);
  pinMode(RFC, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
  analogWrite(SMETERPIN, 0);

  Display.writeNum("sleep", 0);
  delay(500);
  EEPROM.begin(EE_TOTAL);
  if (EEPROM.readByte(EE_UINT8T_VERSIONCHECK) != EE_VERSIONCOUNTER) FactoryDefaults();

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(MODEBUTTON) == HIGH && digitalRead(BWBUTTON) == HIGH) {
    optrot = EEPROM.readByte(EE_UINT8T_OPTROT);
    if (optrot) {
      optrot = false;
      Display.writeStr("version2.txt", "standard encoder");
    } else {
      optrot = true;
      Display.writeStr("version2.txt", "optical encoder");
    }
    EEPROM.writeByte(184, EE_UINT8T_OPTROT);
    EEPROM.commit();
    Display.writeStr("version.txt", "Changed to: ");
    delay(2000);
    Display.writeStr("version.txt", "Please release");
    Display.writeStr("version2.txt", "the button!");
    while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }


  if (digitalRead(MODEBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == HIGH && digitalRead(BWBUTTON) == HIGH) {
    CoaxSwitch = EEPROM.readByte(EE_UINT8T_COAXSWITCH);
    if (CoaxSwitch == 1) CoaxSwitch = 0; else CoaxSwitch = 1;
    EEPROM.writeByte(EE_UINT8T_COAXSWITCH, CoaxSwitch);
    EEPROM.commit();
    Display.writeStr("version.txt", "Coax switch");
    Display.writeStr("version2.txt", "changed!");
    delay(2000);
    Display.writeStr("version.txt", "Please release");
    Display.writeStr("version2.txt", "the button!");
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }

  if (digitalRead(BWBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == HIGH && digitalRead(MODEBUTTON) == HIGH) {
    rotarymode = EEPROM.readByte(EE_UINT8T_ROTARYMODE);
    if (!rotarymode) rotarymode = true; else rotarymode = false;
    EEPROM.writeByte(EE_UINT8T_ROTARYMODE, rotarymode);
    EEPROM.commit();
    Display.writeStr("version.txt", "Rotary direc-");
    Display.writeStr("version2.txt", "tion changed");
    delay(2000);
    Display.writeStr("version.txt", "Please release");
    Display.writeStr("version2.txt", "the button!");
    while (digitalRead(BWBUTTON) == LOW) delay(50);
  }

  if (digitalRead(BWBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == LOW && digitalRead(MODEBUTTON) == HIGH) {
    FactoryDefaults();
    Display.writeStr("version.txt", "Tuner back to");
    Display.writeStr("version2.txt", "default values");
    delay(2000);
    Display.writeStr("version.txt", "Please release");
    Display.writeStr("version2.txt", "the buttons!");
    while (digitalRead(BWBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }

  if (digitalRead(BWBUTTON) == HIGH && digitalRead(ROTARY_BUTTON) == LOW && digitalRead(MODEBUTTON) == LOW) {
    Display.writeStr("version.txt", "Calibrate s-meter");
    Display.writeStr("version2.txt", "");
    delay(2000);
    Display.writeStr("version.txt", "Release buttons");
    Display.writeStr("version2.txt", "when ready!");
    while (digitalRead(MODEBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }

  String displayversionext;
  String softwareversionext;
  displayversion = Display.readNumber("versie");

  if (displayversion % 10 < 10 && displayversion % 10 > 0) {
    displayversionext = ".0" + String (displayversion % 10);
  } else if (displayversion % 10 == 0) {
    displayversionext = ".00";
  } else {
    displayversionext = "." + String (displayversion % 10);
  }

  if (SOFTWAREVER % 10 < 10 && SOFTWAREVER % 10 > 0) {
    softwareversionext = ".0" + String (SOFTWAREVER % 10);
  } else if (SOFTWAREVER % 10 == 0) {
    softwareversionext = ".00";
  } else {
    softwareversionext = "." + String (SOFTWAREVER % 10);
  }

  showsoftwareversion = String ("v" + String (SOFTWAREVER / 100) + String(softwareversionext));
  if (BETA > 0) showsoftwareversion += String(" beta ");
  if (BETA > 1) showsoftwareversion += String(BETA);
  String showdisplayversion = String ("Display v" + String (displayversion / 100) + String(displayversionext));
  Display.writeStr("page 0");
  Display.writeStr("version.txt", "Version " + String(showsoftwareversion));
  Display.writeStr("version2.txt", showdisplayversion);

  if (displayversion < DISPLAYVER) {
    Display.writeStr("page 0");
    Display.writeStr("version.txt", "Incompatible display version");
    Display.writeStr("version2.txt", "Update display to v" + String (DISPLAYVER / 100) + ".0" + String (DISPLAYVER % 10) + "!");
    for (;;);
  }

  TEF = EEPROM.readByte(EE_UINT8T_TEF);

  if (TEF != 101 && TEF != 102 && TEF != 205) SetTunerPatch();

  Frontend.Init(5, 25000000);
  radio.init(TEF);
  uint16_t device;
  uint16_t hw;
  uint16_t sw;
  radio.getIdentification(device, hw, sw);
  if (TEF != (highByte(hw) * 100 + highByte(sw))) SetTunerPatch();

  radio.power(0);
  radio.setMute();
  radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);

  if (lowByte(device) != 0) {
    Display.writeNum("TEFicon.pic", NEXTION_RTPLUSLOGO);
    Display.writeStr("vis TEFicon,1");
    Display.writeNum("TEF.pco", NEXTION_COLOR_GREEN);
    if (lowByte(device) == 14) {
      Display.writeStr("TEF.txt", "TEF6686 detected!");
    } else if (lowByte(device) == 1) {
      Display.writeStr("TEF.txt", "TEF6687 detected!");
      Display.writeNum("fmsienable", 1);
      fullsearchrds = true;
    } else if (lowByte(device) == 9) {
      Display.writeStr("TEF.txt", "TEF6688 detected!");
    } else if (lowByte(device) == 3) {
      Display.writeStr("TEF.txt", "TEF6689 detected!");
      Display.writeNum("fmsienable", 1);
      fullsearchrds = true;
    }
  } else {
    Display.writeNum("TEFicon.pic", NEXTION_RTPLUSLOGO_GREYOUT);
    Display.writeStr("vis TEFicon,1");
    Display.writeNum("TEF.pco", NEXTION_COLOR_RED);
    Display.writeStr("TEF.txt", "Tuner NOT detected!");
  }

  if (digitalRead(BAND) == LOW) {
    Display.writeNum("UHFicon.pic", NEXTION_RTPLUSLOGO);
    Display.writeStr("vis UHFicon,1");
    Display.writeNum("UHF.pco", NEXTION_COLOR_GREEN);
    Display.writeStr("UHF.txt", "UHF Board detected!");
    Display.writeNum("uhf", 1);
    UHF = true;
  } else {
    Display.writeNum("UHFicon.pic", NEXTION_RTPLUSLOGO_GREYOUT);
    Display.writeStr("vis UHFicon,1");
    Display.writeNum("UHF.pco", NEXTION_COLOR_RED);
    Display.writeStr("UHF.txt", "UHF Board NOT detected!");
    UHF = false;
  }

  swSer.print("AT+STATUS");
  delay(100);

  if (swSer.available()) {
    Display.writeNum("BTicon.pic", NEXTION_RTPLUSLOGO);
    Display.writeStr("vis BTicon,1");
    Display.writeNum("BT.pco", NEXTION_COLOR_GREEN);
    Display.writeStr("BT.txt", "Bluetooth detected!");
    Display.writeNum("btenable", 1);
  }

  Frontend.SetFreq(100000, offset);
  delay(400);

  EEpromReadData();

  if (usbmode == 1) Serial.begin(19200); else Serial.begin(115200);

  Display.writeNum("smeterold", 0);

  if (iMSset == 1 && EQset == 1) iMSEQ = 2;
  if (iMSset == 0 && EQset == 1) iMSEQ = 3;
  if (iMSset == 1 && EQset == 0) iMSEQ = 4;
  if (iMSset == 0 && EQset == 0) iMSEQ = 1;

  if (wifienable == 2) tryWiFi(); else WiFi.mode(WIFI_OFF);

  radio.setVolume(VolSet);
  radio.setMute();
  radio.setStereoLevel(StereoLevel);
  radio.setHighCutLevel(HighCutLevel);
  radio.setHighCutOffset(HighCutOffset);
  radio.setStHiBlendLevel(BlendLevel);
  radio.setStHiBlendOffset(BlendOffset);
  radio.setDeemphasis(demp);
  radio.setAudio(lf);
  radio.setFMNoiseBlanker(NBLevel);
  radio.setAMCoChannel(AM_Cochannel);
  radio.setAMNoiseBlanker(AM_NBLevel);
  radio.setAMAttenuation(AM_att);
  radio.setFMSI(fmsi);
  radio.setFMSI_Time(fmsi_attack, fmsi_release);
  radio.setFMSI_Gain(fmsi_11, fmsi_21, fmsi_31, fmsi_41);
  radio.setFMSI_Bias(fmsi_12, fmsi_22, fmsi_32, fmsi_42);
  radio.rds.rtbuffer = true;
  radio.rds.underscore = false;
  radio.rds.filter = false;
  radio.rds.pierrors = true;
  radio.rds.sortaf = true;
  radio.rds.fastps = true;

  Display.writeStr("page 1");

  switch (band) {
    case 0: RF(0); break;
    case 1: RF(1); break;
    case 2: RF(2); break;
    case 3: RF(3); break;
    case 4: RF(4); break;
    case 5: RF(5); break;
    case 6: RF(6); break;
  }

  ShowFreq();
  ShowStepSize();
  ShowiMS();
  ShowEQ();
  ShowTuneMode();
}

void loop(void) {
  Display.NextionListen();
  Communication();

  if (seek) Seek(direction);
  if (spec) scan_loop();

  if (menu) {
    radio.getProcessing(highcut, stereo, sthiblend, stband_1, stband_2, stband_3, stband_4);
    Display.writeNum("highcut", highcut);
    Display.writeNum("stereol", stereo);
    Display.writeNum("sthiblend", sthiblend);
    Display.writeNum("stband_1", stband_1);
    Display.writeNum("stband_2", stband_2);
    Display.writeNum("stband_3", stband_3);
    Display.writeNum("stband_4", stband_4);
  }

  if (!menu && !manfreq && !spec && !setoffset) {
    if ((SStatus < 0) || ((OStatus < -200 || OStatus > 200) || (USN > 200 && WAM > 230))) {
      if (millis() >= showmillis + 250) {
        if (band == 5) radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN); else radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
        readRds();
        ShowStereoStatus();
        showmillis = millis();
      }
    } else {
      if (band == 5) radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN); else radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
      readRds();
      ShowStereoStatus();
    }

    if (XDRGTKTCP || XDRGTK) {
      if (millis() >= XDRshowmillis + 25) {
        ShowBW();
        ShowSignalLevel();
        ShowOffset();
        ShowUSBstatus();
        ShowRSSI();
        doSquelch();
        XDRshowmillis = millis();
      }
    } else {
      ShowBW();
      ShowSignalLevel();
      ShowOffset();
      ShowUSBstatus();
      ShowRSSI();
      doSquelch();
    }

    doEEpromWrite();
    displayreset = false;

    if (rotary == -1) KeyUp();
    if (rotary == 1) KeyDown();

    if (digitalRead(ROTARY_BUTTON) == LOW) ButtonPress();
    if (digitalRead(MODEBUTTON) == LOW) ModeButtonPress();
    if (digitalRead(BWBUTTON) == LOW) BWButtonPress();
    if (digitalRead(BAND) == LOW) BandSet();
  }

  if (setoffset) {
    radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
    Display.writeNum("offsetvalue.val", OStatus);
    ShowOffset();
  }
}

void BandSet(void) {
  if (!XDRGTK && !XDRGTKTCP) {
    unsigned long counterold = millis();
    unsigned long counter = millis();

    while (digitalRead(BAND) == LOW && counter - counterold <= 1000) counter = millis();

    if (counter - counterold < 1000 || power) {
      if (power) {
        Display.writeNum("sleep", 0);
        Display.writeStr("page 0");
        ESP.restart();
      }

      seek = false;
      tunemode = 0;
      ShowTuneMode();

      if (UHF) {
        band ++;
        if (band > 5) band = 0;
        switch (band) {
          case 0: RF(0); break;
          case 1: RF(1); break;
          case 2: RF(2); break;
          case 3: RF(3); break;
          case 4: RF(4); break;
          case 5: RF(5); break;
        }
      } else {
        band ++;
        if (band > 6) band = 0;
        if (band == 1) band = 5;
        if (band == 0) RF(0);
        if (band == 5) RF(5);
        if (band == 6) RF(6);
      }
      EEPROM.writeByte(EE_UINT8T_BAND, band);
      EEPROM.commit();
      ShowFreq();
      radio.clearRDS(fullsearchrds);
    } else {
      power = true;
      Display.writeNum("sleep", 1);
      Frontend.Power(0);
      radio.power(1);
      analogWrite(SMETERPIN, 0);
      if (wifienable == 1) {
        Server.end();
        Udp.stop();
        WiFi.mode(WIFI_OFF);
      }
    }
    while (digitalRead(BAND) == LOW) delay(50);
  }
}

void RF(byte RFset) {
  if (!spec && !manfreq) {
    Display.writeNum("outlimit.en", 0);
    Display.writeStr("vis outoflimit,0");
  }

  if (RFset == 0 && fm == 0) {
    band ++;
    RFset ++;
  }
  if (RFset == 1 && uhf1 == 0) {
    band ++;
    RFset ++;
  }
  if (RFset == 2 && uhf2 == 0) {
    band ++;
    RFset ++;
  }
  if (RFset == 3 && uhf3 == 0) {
    band ++;
    RFset ++;
  }
  if (RFset == 4 && uhf4 == 0) {
    band ++;
    RFset ++;
  }
  if (RFset == 5 && am == 0) {
    if (UHF) {
      band = 0;
      RFset = 0;
    } else {
      band ++;
      RFset ++;
    }
  }
  if (RFset == 6 && uhf6 == 0) {
    band = 0;
    RFset = 0;
  }

  if (RFset == 5) {
    if (showrdsinfo && !manfreq) {
      Display.writeStr("page 1");
      showrdsinfo = false;
    }
    if (!manfreq) {
      Display.writeStr("vis m0,0");
    }

    if (scopeview == false && !manfreq) {
      Display.writeStr("vis U_disp,0");
      Display.writeStr("vis W_disp,0");
      Display.writeNum("tm4.en", 0);
      Display.writeStr("vis m1,0");
      Display.writeStr("vis signalform,1");
      Display.writeStr("vis modpos,1");
      Display.writeNum("scopeview", 1);
    }
    if (!manfreq) {
      Display.writeNum("BW.pco", NEXTION_COLOR_YELLOW);
      Display.writeNum("autobwlogo.pic", NEXTION_AUTOBWLOGO_GREYOUT);
      Display.writeNum("imslogo.pic", NEXTION_IMSLOGO_GREYOUT);
      Display.writeNum("eqlogo.pic", NEXTION_EQLOGO_GREYOUT);
      Display.writeNum("stereo.pic", NEXTION_STEREOLOGO_GREYOUT);
      Display.writeNum("ber.pic", NEXTION_RDSBAR_0);
      Display.writeNum("t4.pco", NEXTION_COLOR_GREY);
      Display.writeNum("t5.pco", NEXTION_COLOR_GREY);
      Display.writeNum("t6.pco", NEXTION_COLOR_GREY);
      Display.writeNum("t7.pco", NEXTION_COLOR_GREY);
      Display.writeNum("t10.pco", NEXTION_COLOR_GREY);

      String count = String(frequency5, DEC);
      if (count.length() > 3) {
        Display.writeNum("freq.vvs1", 3);
        Display.writeStr("t2.txt", "MHz");
      } else {
        Display.writeNum("freq.vvs1", 0);
        Display.writeStr("t2.txt", "kHz");
      }
    }
  } else {
    if (!spec && !manfreq) {
      ShowiMS();
      ShowEQ();
      Display.writeStr("vis m0,1");
      if (scopeview == false) {
        Display.writeStr("vis U_disp,1");
        Display.writeStr("vis W_disp,1");
        Display.writeNum("tm4.en", 1);
        Display.writeStr("vis m1,1");
        Display.writeStr("vis signalform,0");
        Display.writeStr("vis modpos,0");
        Display.writeNum("scopeview", 0);
      }
      Display.writeNum("freq.vvs1", 2);
      Display.writeStr("t2.txt", "MHz");
      Display.writeNum("t4.pco", NEXTION_COLOR_WHITE);
      Display.writeNum("t5.pco", NEXTION_COLOR_WHITE);
      Display.writeNum("t6.pco", NEXTION_COLOR_WHITE);
      Display.writeNum("t7.pco", NEXTION_COLOR_WHITE);
      Display.writeNum("t10.pco", NEXTION_COLOR_WHITE);
      ShowBW();
    }
  }

  switch (RFset) {
    case 0:
      if (CoaxSwitch == 1) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      delay(50);
      radio.SetFreq(frequency0);
      radio.setOffset(LevelOffset0);
      Frontend.Power(0);
      if (!spec && !manfreq) {
        Display.writeNum("offsettouch", 0);
      }
      break;

    case 1:
      if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, LOW);
      digitalWrite(RFB, LOW);
      radio.power(0);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset1 - 7);
      Frontend.Power(1);
      Frontend.SetFreq(frequency1 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 2:
      if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, LOW);
      radio.power(0);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset2 - 4);
      Frontend.SetFreq(frequency2 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 3:
      if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, LOW);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset3);
      Frontend.SetFreq(frequency3 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 4:
      if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset4 + 2);
      Frontend.SetFreq(frequency4 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 5:
      if (CoaxSwitch == 1) {
        if (coaxmode && !UHF) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      } else {
        if (coaxmode && !UHF) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
      }
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, HIGH);
      radio.clearRDS(fullsearchrds);
      radio.SetFreqAM(frequency5);
      Frontend.Power(0);
      Display.writeNum("offsettouch", 0);
      break;

    case 6:
      if (CoaxSwitch == 1) {
        if (!coaxmode) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      } else {
        if (!coaxmode) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
      }
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      radio.setOffset(LevelOffset6);
      radio.SetFreq(frequency6 - converteroffset * 100);
      Display.writeNum("offsettouch", 0);
      Wire.beginTransmission(0x12);
      Wire.write(converteroffset >> 8);
      Wire.write(converteroffset & (0xFF));
      Wire.endTransmission();
      radio.clearRDS(fullsearchrds);
      break;
  }

  OStatusold = 0;
  BWreset = true;

  if (band == 5) radio.setSoftmuteAM(softmuteam); else radio.setSoftmuteFM(softmutefm);
}

void readRds(void) {
  if (band == 5) RDSstatus = false; else radio.readRDS(showrdserrors ? 3 : 1);
  RDSstatus = radio.rds.hasRDS;
  ShowRDS();

  if (RDSSpy && RDSstatus && band != 5) {
    String RDSSPYRDS;
    RDSSPYRDS = "G:\r\n";
    if (radio.rds.rdsAerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX) + String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
    if (radio.rds.rdsBerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX) + String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
    if (radio.rds.rdsCerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX) + String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
    if (radio.rds.rdsDerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX) + String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);
    RDSSPYRDS += "\r\n\r\n";

    if (RDSSPYRDS != RDSSPYRDSold) {
      RDSSPYRDSold = RDSSPYRDS;
      if (wificonnect) RemoteClient.print(RDSSPYRDS); else Serial.print(RDSSPYRDS);
    }
  }

  if ((XDRGTKTCP || XDRGTK) && RDSstatus && band != 5) {
    String XDRGTKRDS;
    XDRGTKRDS = "R";
    XDRGTKRDS += String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX);
    XDRGTKRDS += String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
    XDRGTKRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX);
    XDRGTKRDS += String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
    XDRGTKRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX);
    XDRGTKRDS += String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
    XDRGTKRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX);
    XDRGTKRDS += String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);

    uint8_t erroutput = 0;
    erroutput |= ((radio.rds.rdsErr >> 8) & B00110000) >> 4;
    erroutput |= ((radio.rds.rdsErr >> 8) & B00001100);
    erroutput |= ((radio.rds.rdsErr >> 8) & B00000011) << 4;

    XDRGTKRDS += String((erroutput >> 4) & 0xF, HEX);
    XDRGTKRDS += String(erroutput & 0xF, HEX);
    XDRGTKRDS += "\n";

    if (XDRGTKRDS != XDRGTKRDSold) {
      uint8_t piError = radio.rds.rdsErr >> 14;
      if (piError < 3) {
        uint8_t piState = radio.rds.piBuffer.add(radio.rds.rdsA, piError);

        if (piState != RdsPiBuffer::STATE_INVALID) {
          if (XDRGTKTCP) RemoteClient.print("P");
          if (XDRGTK) Serial.print("P");
          String PIcodeToSend;
          PIcodeToSend = String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX) + String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
          PIcodeToSend.toUpperCase();
          if (XDRGTKTCP) RemoteClient.print(PIcodeToSend);
          if (XDRGTK) Serial.print(PIcodeToSend);
          while (piState != 0) {
            if (XDRGTKTCP) RemoteClient.print("?");
            if (XDRGTK) Serial.print("?");
            piState--;
          }
          if (XDRGTKTCP) RemoteClient.print("\n");
          if (XDRGTK) Serial.print("\n");
        }
      }

      XDRGTKRDSold = XDRGTKRDS;
      XDRGTKRDS.toUpperCase();
      if (XDRGTKTCP) RemoteClient.print(XDRGTKRDS);
      if (XDRGTK) Serial.print(XDRGTKRDS);
    }
  }
}

void doStepSize(void) {
  stepsize++;
  if (stepsize > 4) stepsize = 0;
  ShowStepSize();
  EEPROM.writeByte(EE_UINT8T_STEPSIZE, stepsize);
  EEPROM.commit();
  if (stepsize == 0) {
    RoundStep();
    ShowFreq();
  }
}

void doTuneMode(void) {
  tunemode++;
  if (tunemode > 2) tunemode = 0;
  ShowTuneMode();
  if (stepsize != 0) {
    stepsize = 0;
    RoundStep();
    ShowStepSize();
    ShowFreq();
  }
}

void doFilter(void) {
  switch (iMSEQ) {
    case 0:
      iMSset = 1;
      EQset = 0;
      ShowiMS();
      ShowEQ();
      iMSEQ = 1;
      break;

    case 1:
      iMSset = 0;
      EQset = 1;
      ShowiMS();
      ShowEQ();
      iMSEQ = 2;
      break;

    case 2:
      iMSset = 1;
      EQset = 1;
      ShowiMS();
      ShowEQ();
      iMSEQ = 3;
      break;

    case 3:
      iMSset = 0;
      EQset = 0;
      ShowiMS();
      ShowEQ();
      iMSEQ = 0;
      break;
  }

  EEPROM.writeByte(EE_UINT8T_IMSSET, iMSset);
  EEPROM.writeByte(EE_UINT8T_EQSET, EQset);
  EEPROM.commit();
}


void ButtonPress(void) {
  if (!power) {
    if (seek) seek = false;

    if (!menu) {
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(ROTARY_BUTTON) == LOW && counter - counterold <= 1000) counter = millis();

      if (counter - counterold < 1000) {
        if (tunemode == 0) doStepSize();

        if (tunemode == 2) {
          if (!memorystore) {
            memorystore = true;
            Display.writeNum("store.en", 1);
          } else {
            Display.writeNum("store.en", 0);
            Display.writeNum("memlogo.pic", NEXTION_MEMLOGO);
            memorystore = false;
            EEPROM.writeUInt((memory_pos * 4) + EE_UINT16T_MEMFREQ, freq);
            EEPROM.commit();
            memory[memory_pos] = freq;
          }
        }
      } else {
        doFilter();
      }
    }
    while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }
}

void RoundStep(void) {
  switch (band) {
    case 0:
      freq = frequency0;
      if (freq % 10 < 3) {
        frequency0 = (freq - freq % 10);
      }
      else if (freq % 10 > 2 && freq % 10 < 8) {
        frequency0 = (freq - (freq % 10 - 5));
      }
      else if (freq % 10 > 7) {
        frequency0 = (freq - (freq % 10) + 10);
      }
      radio.SetFreq(frequency0);
      break;

    case 1:
      freq = frequency1;
      if (freq % 10 < 3) {
        frequency1 = (freq - freq % 10);
      } else if (freq % 10 > 2 && freq % 10 < 8) {
        frequency1 = (freq - (freq % 10 - 5));
      } else if (freq % 10 > 7) {
        frequency1 = (freq - (freq % 10) + 10);
      }

      Frontend.SetFreq(frequency1 - IF * 100, offset);
      break;

    case 2:
      freq = frequency2;
      if (freq % 10 < 3) {
        frequency2 = (freq - freq % 10);
      } else if (freq % 10 > 2 && freq % 10 < 8) {
        frequency2 = (freq - (freq % 10 - 5));
      } else if (freq % 10 > 7) {
        frequency2 = (freq - (freq % 10) + 10);
      }

      Frontend.SetFreq(frequency2 - IF * 100, offset);
      break;

    case 3:
      freq = frequency3;
      if (freq % 10 < 3) {
        frequency3 = (freq - freq % 10);
      } else if (freq % 10 > 2 && freq % 10 < 8) {
        frequency3 = (freq - (freq % 10 - 5));
      } else if (freq % 10 > 7) {
        frequency3 = (freq - (freq % 10) + 10);
      }

      Frontend.SetFreq(frequency3 - IF * 100, offset);
      break;
    case 4:
      freq = frequency4;
      if (freq % 10 < 3) {
        frequency4 = (freq - freq % 10);
      } else if (freq % 10 > 2 && freq % 10 < 8) {
        frequency4 = (freq - (freq % 10 - 5));
      } else if (freq % 10 > 7) {
        frequency4 = (freq - (freq % 10) + 10);
      }

      Frontend.SetFreq(frequency4 - IF * 100, offset);
      break;

    case 5:
      freq = frequency5 / 9;
      frequency5 = freq * 9;
      radio.SetFreqAM(frequency5);
      break;
  }

  while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);

  EEPROM.writeUInt(EE_UINT16T_FREQUENCY0, frequency0);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY1, frequency1);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY2, frequency2);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY3, frequency3);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY4, frequency4);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY5, frequency5);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY6, frequency6);
  EEPROM.commit();
}

void ModeButtonPress(void) {
  if (!power) {
    if (!menu) {
      unsigned long counterold = millis();
      unsigned long counter = millis();

      while (digitalRead(MODEBUTTON) == LOW && counter - counterold <= 1000) {
        counter = millis();
      }

      if (counter - counterold <= 1000) {
        if (seek) seek = false;
        if (band == 5 && tunemode == 0) tunemode = 1;
        doTuneMode();
      } else {
        if (!XDRGTKTCP && !XDRGTK && !wificonnect && !manfreq && !spec) {
          if (RDSSpy) {
            RDSSpy = false;
            USBstatus = false;
          }

          menu = true;
          wifienableold = wifienable;
          Display.writeStr("page 5");
          Display.writeNum("fmsi", fmsi);
        }
      }
    }
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }
}

void BWButtonPress(void) {
  if (!power) {
    if (seek) seek = false;

    if (!menu) {
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(BWBUTTON) == LOW && counter - counterold <= 1000) {
        counter = millis();
      }
      if (counter - counterold < 1000) {
        if (band == 5) BWsetAM++; else BWset++;
        doBW();
      } else {
        if (band != 5) doStereoToggle();
      }
    }
    while (digitalRead(BWBUTTON) == LOW) delay(50);
  }
}

void KeyUp(void) {
  rotary = 0;
  if (!power) {
    if (!menu) {
      if (tunemode == 0) TuneUp();
      if (tunemode == 1) {
        freqtemp = freq;
        direction = true;
        seek = true;
        Seek(direction);
      }
      if (tunemode == 2) {
        memory_pos++;
        if (memory_pos > 29) memory_pos = 0;
        MemoryTune();
      }
      if (XDRGTK) {
        if (band == 5) Serial.print("T" + String(frequency5) + "\n"); else Serial.print("T" + String(frequency0 * 10) + "\n");
      }

      if (XDRGTKTCP) {
        if (band == 5) RemoteClient.print("T" + String(frequency5) + "\n"); else RemoteClient.print("T" + String(frequency0 * 10) + "\n");
      }
      change = 0;
      ShowFreq();
      store = true;
    }
  }
}

void KeyDown(void) {
  rotary = 0;
  if (!power) {
    if (!menu) {
      if (tunemode == 0) TuneDown();
      if (tunemode == 1) {
        freqtemp = freq;
        direction = false;
        seek = true;
        Seek(direction);
      }
      if (tunemode == 2) {
        memory_pos--;
        if (memory_pos > 29) memory_pos = 29;
        MemoryTune();
      }
      if (XDRGTK) {
        if (band == 5) Serial.print("T" + String(frequency5) + "\n"); else Serial.print("T" + String(frequency0 * 10) + "\n");
      }

      if (XDRGTKTCP) {
        if (band == 5) RemoteClient.print("T" + String(frequency5) + "\n"); else RemoteClient.print("T" + String(frequency0 * 10) + "\n");
      }
      change = 0;
      ShowFreq();
      store = true;
    }
  }
}

void MemoryTune(void) {
  Display.writeStr("vis t14,1");
  Display.writeStr("vis channel,1");
  Display.writeNum("memvis", 0);
  Display.writeNum("showmem.en", 1);
  Display.writeNum("channel.val", memory_pos + 1);

  if (!memorystore) {
    if (memory[memory_pos] >= LowEdgeSet0 * 100 && memory[memory_pos] <= HighEdgeSet0 * 100) {
      frequency0 = memory[memory_pos];
      RF(0);
      band = 0;
    } else if (UHF && memory[memory_pos] >= LowEdgeSet1 * 100 && memory[memory_pos] <= HighEdgeSet1 * 100) {
      frequency1 = memory[memory_pos];
      RF(1);
      band = 1;
    } else if (UHF && memory[memory_pos] >= LowEdgeSet2 * 100 && memory[memory_pos] <= HighEdgeSet2 * 100) {
      frequency2 = memory[memory_pos];
      RF(2);
      band = 2;
    } else if (UHF && memory[memory_pos] >= LowEdgeSet3 * 100 && memory[memory_pos] <= HighEdgeSet3 * 100) {
      frequency3 = memory[memory_pos];
      RF(3);
      band = 3;
    } else if (UHF && memory[memory_pos] >= LowEdgeSet4 * 100 && memory[memory_pos] <= HighEdgeSet4 * 100) {
      frequency4 = memory[memory_pos];
      RF(4);
      band = 4;
    } else if (!UHF && memory[memory_pos] >= LowEdgeSet6 * 100 && memory[memory_pos] <= HighEdgeSet6 * 100) {
      frequency6 = memory[memory_pos];
      RF(6);
      band = 6;
    } else if (memory[memory_pos] >= 14 && memory[memory_pos] <= 2700) {
      frequency5 = memory[memory_pos];
      if (frequency5 < 144) {
        frequency5 = 144;
      }
      RF(5);
      band = 5;
    } else {
      if (!spec) Display.writeNum("outlimit.en", 1);
    }
  }
  store = true;
  radio.clearRDS(fullsearchrds);
}


void doExit(void) {
  if (band == 5) showrdsinfo = false;
  BWsetOld = 254;
  displayreset = true;
  manfreq = false;
  menu = false;
  spec = false;
  BWreset = true;
  Display.writeNum("smeterold", 0);
  radio.clearRDS(fullsearchrds);
  if (!showrdsinfo) Display.writeStr("page 1"); else Display.writeStr("page 12");
  if (band == 5) {
    Display.writeStr("vis m0,0");
    Display.writeNum("freq.vvs1", 3);
    Display.writeNum("ber.pic", NEXTION_RDSBAR_0);
  } else {
    Display.writeStr("vis m0,1");
    Display.writeNum("freq.vvs1", 2);
  }
  ShowFreq();
  delay(200);
  RF(band);
  ShowiMS();
  ShowEQ();
  Squelchold = 200;
  mutestatus = false;
  cnvis = false;
  CNold = 0;
  doSquelch();
  ShowBW();
  ShowSignalLevel();
  ShowStereoStatus();
  ShowOffset();
  ShowStepSize();
  ShowTuneMode();
  ShowUSBstatus();
  ShowBTstatus();
  Display.writeNum("tm3.en", 0);
  Display.writeStr("vis CT,0");
  Display.writeStr("t7.txt", "PTY:");
  ctshow = false;
  store = true;
}

void doBW(void) {
  if (band == 5) {
    if (BWsetAM > 4) BWsetAM = 1;
    ShowBW();
    BWreset = true;

    switch (BWsetAM) {
      case 1: radio.setAMBandw(3); break;
      case 2: radio.setAMBandw(4); break;
      case 3: radio.setAMBandw(6); break;
      case 4: radio.setAMBandw(8); break;
    }
  } else {
    if (BWset > 16) BWset = 0;
    ShowBW();
    BWreset = true;

    switch (BWset) {
      case 1: radio.setFMBandw(56); break;
      case 2: radio.setFMBandw(64); break;
      case 3: radio.setFMBandw(72); break;
      case 4: radio.setFMBandw(84); break;
      case 5: radio.setFMBandw(97); break;
      case 6: radio.setFMBandw(114); break;
      case 7: radio.setFMBandw(133); break;
      case 8: radio.setFMBandw(151); break;
      case 9: radio.setFMBandw(168); break;
      case 10: radio.setFMBandw(184); break;
      case 11: radio.setFMBandw(200); break;
      case 12: radio.setFMBandw(217); break;
      case 13: radio.setFMBandw(236); break;
      case 14: radio.setFMBandw(254); break;
      case 15: radio.setFMBandw(287); break;
      case 16: radio.setFMBandw(311); break;
    }
  }
}

void doSquelch(void) {
  if (!power) {
    if (!XDRGTK && !XDRGTKTCP && !spec) {
      Squelch = analogRead(PIN_POT) / 4 - 100;
      if (Squelch > 920) Squelch = 920;
      if (!showrdsinfo && !menu && Squelch != Squelchold) {
        if (Squelch == -100) {
          Display.writeStr("SQ.txt", "OFF");
        } else if (Squelch == 920) {
          Display.writeStr("SQ.txt", "ST");
        } else {
          String SQVAL = String(Squelch / 10);
          Display.writeStr("SQ.txt", SQVAL);
        }
        Squelchold = Squelch;
      }

    }
    if (XDRGTK || XDRGTKTCP) {
      if (!XDRMute) {
        if (Squelch != -1) {
          if (!seek && (Squelch == 0)) {
            if (mutestatus) {
              radio.setUnMute();
              mutestatus = false;
            }
            if (!showrdsinfo && !spec) Display.writeStr("SQ.txt", "OFF");
            SQ = false;
          } else if (!seek && (Squelch < SStatus || Squelch == -100)) {
            if (mutestatus) {
              radio.setUnMute();
              mutestatus = false;
            }
            SQ = false;
          } else {
            if (!mutestatus) {
              radio.setMute();
              mutestatus = true;
            }
            SQ = true;
          }
        } else {
          if (!seek && Stereostatus) {
            if (mutestatus) {
              radio.setUnMute();
              mutestatus = false;
            }
            SQ = false;
          } else {
            if (!mutestatus) {
              radio.setMute();
              mutestatus = true;
            }
            SQ = true;
          }
        }
        if (!showrdsinfo) {
          if (Squelch != Squelchold) {
            if (Squelch == -1) {
              if (!spec) Display.writeStr("SQ.txt", "ST");
            } else {
              String SQVAL = String(Squelch / 10);
              if (!spec) Display.writeStr("SQ.txt", SQVAL);
            }
            Squelchold = Squelch;
          }
        }
      }
    } else {
      if (Squelch != 920) {
        if (!seek && (Squelch < SStatus || Squelch == -100)) {
          if (mutestatus) {
            radio.setUnMute();
            mutestatus = false;
          }
          SQ = false;
        } else {
          if (!mutestatus) {
            radio.setMute();
            mutestatus = true;
          }
          SQ = true;
        }
      } else {
        if (Stereostatus) {
          if (mutestatus) {
            radio.setUnMute();
            mutestatus = false;
          }
          SQ = false;
        } else {
          if (!mutestatus) {
            radio.setMute();
            mutestatus = true;
          }
          SQ = true;
        }
      }
    }
    ShowSquelch();
  }
}

void doStereoToggle(void) {
  if (StereoToggle) {
    Display.writeNum("stereo.pic", NEXTION_MONOLOGO);
    radio.setMono(2);
    StereoToggle = false;
  } else {
    Display.writeNum("stereo.pic", NEXTION_STEREOLOGO_GREYOUT);
    radio.setMono(0);
    Stereostatusold = false;
    StereoToggle = true;
  }
}

void EEpromReadData(void) {
  frequency0 = EEPROM.readUInt(EE_UINT16T_FREQUENCY0);
  VolSet = EEPROM.readInt(EE_INT16T_VOLSET);
  ContrastSet = EEPROM.readInt(EE_INT16T_CONTRAST);
  StereoLevel = EEPROM.readInt(EE_INT16T_STEREOLEVEL);
  HighCutLevel = EEPROM.readInt(EE_INT16T_HIGHCUTLEVEL);
  HighCutOffset = EEPROM.readInt(EE_INT16T_HIGHCUTOFFSET);
  scanner_speed = EEPROM.readByte(EE_UINT8T_SCANNERSPEED);
  stepsize = EEPROM.readByte(EE_UINT8T_STEPSIZE);
  stationlist = EEPROM.readByte(EE_UINT8T_STATIONLIST);
  iMSset = EEPROM.readByte(EE_UINT8T_IMSSET);
  EQset = EEPROM.readByte(EE_UINT8T_EQSET);
  band = EEPROM.readByte(EE_UINT8T_BAND);
  IF = EEPROM.readByte(EE_UINT8T_IF);
  LowEdgeSet0 = EEPROM.readInt(EE_INT16T_LOWEDGESET0);
  HighEdgeSet0 = EEPROM.readInt(EE_INT16T_HIGHEDGESET0);
  LowEdgeSet1 = EEPROM.readInt(EE_INT16T_LOWEDGESET1);
  HighEdgeSet1 = EEPROM.readInt(EE_INT16T_HIGHEDGESET1);
  LowEdgeSet2 = EEPROM.readInt(EE_INT16T_LOWEDGESET2);
  HighEdgeSet2 = EEPROM.readInt(EE_INT16T_HIGHEDGESET2);
  LowEdgeSet3 = EEPROM.readInt(EE_INT16T_LOWEDGESET3);
  HighEdgeSet3 = EEPROM.readInt(EE_INT16T_HIGHEDGESET3);
  LowEdgeSet4 = EEPROM.readInt(EE_INT16T_LOWEDGESET4);
  HighEdgeSet4 = EEPROM.readInt(EE_INT16T_HIGHEDGESET4);
  frequency1 = EEPROM.readUInt(EE_UINT16T_FREQUENCY1);
  frequency2 = EEPROM.readUInt(EE_UINT16T_FREQUENCY2);
  frequency3 = EEPROM.readUInt(EE_UINT16T_FREQUENCY3);
  frequency4 = EEPROM.readUInt(EE_UINT16T_FREQUENCY4);
  scanner_start = EEPROM.readUInt(EE_UINT16T_SCANNERSTART);
  scanner_end = EEPROM.readUInt(EE_UINT16T_SCANNEREND);
  scanner_vbw = EEPROM.readUInt(EE_UINT16T_SCANNERVBW);
  scanner_th = EEPROM.readByte(EE_UINT8T_SCANNERTH);
  scanner_band = EEPROM.readByte(EE_UINT8T_SCANNERBAND);
  scanner_thenable = EEPROM.readByte(EE_UINT8T_SCANNERTHENABLE);
  LevelOffset0 = EEPROM.readInt(EE_INT16T_LEVELOFFSET0);
  LevelOffset1 = EEPROM.readInt(EE_INT16T_LEVELOFFSET1);
  LevelOffset2 = EEPROM.readInt(EE_INT16T_LEVELOFFSET2);
  LevelOffset3 = EEPROM.readInt(EE_INT16T_LEVELOFFSET3);
  LevelOffset4 = EEPROM.readInt(EE_INT16T_LEVELOFFSET4);
  lf = EEPROM.readByte(EE_UINT8T_LF);
  demp = EEPROM.readByte(EE_UINT8T_DEMP);
  usbmode = EEPROM.readByte(EE_UINT8T_USBMODE);
  wifienable = EEPROM.readByte(EE_UINT8T_WIFIENABLE);
  password = EEPROM.readString(EE_STRING_PASSWORD);
  ip1 = EEPROM.readByte(EE_UINT8T_IP1);
  ip2 = EEPROM.readByte(EE_UINT8T_IP2);
  ip3 = EEPROM.readByte(EE_UINT8T_IP3);
  ip4 = EEPROM.readByte(EE_UINT8T_IP4);
  BlendLevel = EEPROM.readInt(EE_INT16T_BLENDLEVEL);
  BlendOffset = EEPROM.readInt(EE_INT16T_BLENDOFFSET);
  NBLevel = EEPROM.readInt(EE_INT16T_NBLEVEL);
  CoaxSwitch = EEPROM.readByte(EE_UINT8T_COAXSWITCH);
  frequency5 = EEPROM.readUInt(EE_UINT16T_FREQUENCY5);
  rotarymode = EEPROM.readByte(EE_UINT8T_ROTARYMODE);
  AM_Cochannel = EEPROM.readInt(EE_INT16T_AMCOCHANNEL);
  AM_NBLevel = EEPROM.readInt(EE_INT16T_AMNBLEVEL);
  AM_att = EEPROM.readInt(EE_INT16T_AMATT);
  am = EEPROM.readByte(EE_UINT8T_AM);
  fm = EEPROM.readByte(EE_UINT8T_FM);
  uhf1 = EEPROM.readByte(EE_UINT8T_UHF1);
  uhf2 = EEPROM.readByte(EE_UINT8T_UHF2);
  uhf3 = EEPROM.readByte(EE_UINT8T_UHF3);
  uhf4 = EEPROM.readByte(EE_UINT8T_UHF4);
  coaxmode = EEPROM.readByte(EE_UINT8T_COAXMODE);
  optrot = EEPROM.readByte(EE_UINT8T_OPTROT);
  fmsi = EEPROM.readByte(EE_UINT8T_FMSI);
  scopeview = EEPROM.readByte(EE_UINT8T_SCOPEMODE);
  fmsi_attack = EEPROM.readUInt(EE_UINT16T_FMSIATTACK);
  fmsi_release = EEPROM.readUInt(EE_UINT16T_FMSIRELEASE);
  fmsi_11 = EEPROM.readUInt(EE_UINT16T_FMSI11);
  fmsi_12 = EEPROM.readUInt(EE_UINT16T_FMSI12);
  fmsi_21 = EEPROM.readUInt(EE_UINT16T_FMSI21);
  fmsi_22 = EEPROM.readUInt(EE_UINT16T_FMSI22);
  fmsi_31 = EEPROM.readUInt(EE_UINT16T_FMSI31);
  fmsi_32 = EEPROM.readUInt(EE_UINT16T_FMSI32);
  fmsi_41 = EEPROM.readUInt(EE_UINT16T_FMSI41);
  fmsi_42 = EEPROM.readUInt(EE_UINT16T_FMSI42);
  memory_pos = EEPROM.readByte(EE_UINT8T_MEMORYPOS);
  tunemode = EEPROM.readByte(EE_UINT8T_TUNEMODE);
  uhf6 = EEPROM.readByte(EE_UINT8T_UHF6);
  LevelOffset6 = EEPROM.readInt(EE_INT16T_LEVELOFFSET6);
  LowEdgeSet6 = EEPROM.readInt(EE_INT16T_LOWEDGESET6);
  HighEdgeSet6 = EEPROM.readInt(EE_INT16T_HIGHEDGESET6);
  frequency6 = EEPROM.readUInt(EE_UINT16T_FREQUENCY6);
  converteroffset = EEPROM.readUInt(EE_UINT16T_CONVERTEROFFSET);
  offset = EEPROM.readInt(EE_INT16T_OFFSET);
  softmutefm = EEPROM.readByte(EE_UINT8T_SOFTMUTEFM);
  softmuteam = EEPROM.readByte(EE_UINT8T_SOFTMUTEAM);
  showrdserrors = EEPROM.readByte(EE_UINT8T_SHOWRDSERRORS);

  uint8_t i;
  for (i = 0; i < 30; i++) memory[i] = EEPROM.readUInt((i * 4) + EE_UINT16T_MEMFREQ);

  if (!UHF && band != 0 && band != 5 && band != 6) {
    band = 0;
    if (scanner_start > 10800) {
      scanner_band = 0;
      scanner_start = LowEdgeSet0 * 100;
      scanner_end = HighEdgeSet0 * 100;
    }
  }

  if (frequency0 < 6500) {
    FactoryDefaults();
    EEpromReadData();
  }

  remoteip = IPAddress (ip1, ip2, ip3, ip4);
  delay(100);

  displaysize = Display.readNumber("displaysize");
  delay(200);

  Display.writeNum("sstart", scanner_start / 100);
  delay(50);
  Display.writeNum("sstop", scanner_end / 100);
  delay(50);
  Display.writeNum("sbw", scanner_vbw);
  delay(50);
  Display.writeNum("sth", scanner_th);
  delay(50);
  Display.writeNum("sband", scanner_band);
  delay(50);
  Display.writeNum("sspeed", scanner_speed);
  delay(50);
  Display.writeNum("thenable", scanner_thenable);
  delay(50);
  Display.writeNum("l0", LowEdgeSet0 / 2 * 2);
  delay(50);
  Display.writeNum("l1", LowEdgeSet1 / 2 * 2);
  delay(50);
  Display.writeNum("l2", LowEdgeSet2 / 2 * 2);
  delay(50);
  Display.writeNum("l3", LowEdgeSet3 / 2 * 2);
  delay(50);
  Display.writeNum("l4", LowEdgeSet4 / 2 * 2);
  delay(50);
  Display.writeNum("l6", LowEdgeSet6 / 2 * 2);
  delay(50);
  Display.writeNum("h0", HighEdgeSet0 / 2 * 2);
  delay(50);
  Display.writeNum("h1", HighEdgeSet1 / 2 * 2);
  delay(50);
  Display.writeNum("h2", HighEdgeSet2 / 2 * 2);
  delay(50);
  Display.writeNum("h3", HighEdgeSet3 / 2 * 2);
  delay(50);
  Display.writeNum("h4", HighEdgeSet4 / 2 * 2);
  delay(50);
  Display.writeNum("h6", HighEdgeSet6 / 2 * 2);
  delay(50);
  Display.writeNum("Volset", VolSet + 15);
  delay(50);
  Display.writeNum("dim", ContrastSet);
  delay(50);
  Display.writeNum("HighCutOffset", HighCutOffset);
  delay(50);
  Display.writeNum("HighCutLevel", HighCutLevel * 100);
  delay(50);
  Display.writeNum("StereoLevel", StereoLevel);
  delay(50);
  Display.writeNum("o0", LevelOffset0 + 25);
  delay(50);
  Display.writeNum("o1", LevelOffset1 + 25);
  delay(50);
  Display.writeNum("o2", LevelOffset2 + 25);
  delay(50);
  Display.writeNum("o3", LevelOffset3 + 25);
  delay(50);
  Display.writeNum("o4", LevelOffset4 + 25);
  delay(50);
  Display.writeNum("o6", LevelOffset6 + 25);
  delay(50);
  Display.writeNum("iffreq", IF);
  delay(50);
  Display.writeNum("demp", demp);
  delay(50);
  Display.writeNum("lf", lf);
  delay(50);
  Display.writeNum("usbmode", usbmode);
  delay(50);
  Display.writeNum("wifienable", wifienable);
  delay(50);
  Display.writeNum("pcip1", ip1);
  delay(50);
  Display.writeNum("pcip2", ip2);
  delay(50);
  Display.writeNum("pcip3", ip3);
  delay(50);
  Display.writeNum("pcip4", ip4);
  delay(50);
  Display.writeNum("stationlog", stationlist);
  delay(50);
  Display.writeNum("BlendLevel", BlendLevel * 100);
  delay(50);
  Display.writeNum("BlendOffset", BlendOffset);
  delay(50);
  Display.writeNum("NBLevel", NBLevel);
  delay(50);
  Display.writeNum("AMcochannel", AM_Cochannel);
  delay(50);
  Display.writeNum("AMnb", AM_NBLevel);
  delay(50);
  Display.writeNum("AMatt", AM_att);
  delay(50);
  Display.writeNum("am", am);
  delay(50);
  Display.writeNum("fm", fm);
  delay(50);
  Display.writeNum("uhf1", uhf1);
  delay(50);
  Display.writeNum("uhf2", uhf2);
  delay(50);
  Display.writeNum("uhf3", uhf3);
  delay(50);
  Display.writeNum("uhf4", uhf4);
  delay(50);
  Display.writeNum("uhf6", uhf6);
  delay(50);
  Display.writeNum("converterlo", converteroffset);
  delay(50);
  Display.writeNum("coaxmode", coaxmode);
  delay(50);
  Display.writeNum("fmsi", fmsi);
  delay(50);
  Display.writeNum("scopeview", scopeview);
  delay(50);
  Display.writeNum("fmsiattack", fmsi_attack);
  delay(50);
  Display.writeNum("fmsirelease", fmsi_release);
  delay(50);
  Display.writeNum("b1sens", fmsi_11);
  delay(50);
  Display.writeNum("b1bias", fmsi_12);
  delay(50);
  Display.writeNum("b2sens", fmsi_21);
  delay(50);
  Display.writeNum("b2bias", fmsi_22);
  delay(50);
  Display.writeNum("b3sens", fmsi_31);
  delay(50);
  Display.writeNum("b3bias", fmsi_32);
  delay(50);
  Display.writeNum("b4sens", fmsi_41);
  delay(50);
  Display.writeNum("b4bias", fmsi_42);
  delay(50);
  Display.writeNum("looffset", offset);
  delay(50);
  Display.writeNum("softmutefm", softmutefm);
  delay(50);
  Display.writeNum("softmuteam", softmuteam);
  delay(50);
  Display.writeNum("showrdserrors", showrdserrors);
  delay(50);
}

void doEEpromWrite(void) {
  if (store) change++;

  if (change > 200 && store) {
    detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
    detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));
    EEPROM.writeUInt(EE_UINT16T_FREQUENCY0, frequency0);
    EEPROM.writeUInt(EE_UINT16T_FREQUENCY1, frequency1);
    EEPROM.writeUInt(EE_UINT16T_FREQUENCY2, frequency2);
    EEPROM.writeUInt(EE_UINT16T_FREQUENCY3, frequency3);
    EEPROM.writeUInt(EE_UINT16T_FREQUENCY4, frequency4);
    EEPROM.writeUInt(EE_UINT16T_FREQUENCY5, frequency5);
    EEPROM.writeUInt(EE_UINT16T_FREQUENCY6, frequency6);
    EEPROM.writeByte(EE_UINT8T_MEMORYPOS, memory_pos);
    EEPROM.writeByte(EE_UINT8T_TUNEMODE, tunemode);
    EEPROM.commit();
    store = false;
    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
  }
}

void Seek(bool mode) {
  radio.setMute();
  if (!mode) TuneDown(); else TuneUp();
  ShowFreq();
  if (XDRGTK) {
    if (band == 0) Serial.print("T" + String(frequency0 * 10) + "\n"); else Serial.print("T" + String(frequency5) + "\n");
  }

  if (XDRGTKTCP) {
    if (band == 0) RemoteClient.print("T" + String(frequency0 * 10) + "\n"); else RemoteClient.print("T" + String(frequency5) + "\n");
  }

  radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);

  if ((USN < 200) && (WAM < 230) && (OStatus < 80 && OStatus > -80) && (Squelch < SStatus || Squelch == 920)) {
    seek = false;
    radio.setUnMute();
    store = true;
  } else {
    seek = true;
  }
}

void TuneUp(void) {
  unsigned int temp = 0;
  if (stepsize == 0) {
    if (band == 5) {
      if (frequency5 < 1998) {
        temp = 9;
        frequency5 = (frequency5 / 9) * 9;
      } else {
        temp = 5;
        frequency5 = (frequency5 / 5) * 5;
      }
    } else {
      temp = 5;
    }
  }

  switch (stepsize) {
    case 1: temp = 1; break;
    case 2: temp = 10; break;
    case 3: temp = 100; break;
    case 4: temp = 1000; break;
  }

  switch (band) {
    case 0:
      frequency0 += temp;
      if (frequency0 >= (HighEdgeSet0 * 100) + 1) {
        frequency0 = LowEdgeSet0 * 100;
      }
      radio.SetFreq(frequency0);
      break;

    case 1:
      frequency1 += temp;
      if (frequency1 >= (HighEdgeSet1 * 100) + 1) {
        frequency1 = LowEdgeSet1 * 100;
      }
      Frontend.SetFreq(frequency1 - (IF * 100), offset);
      break;

    case 2:
      frequency2 += temp;
      if (frequency2 >= (HighEdgeSet2 * 100) + 1) {
        frequency2 = LowEdgeSet2 * 100;
      }
      Frontend.SetFreq(frequency2 - (IF * 100), offset);
      break;

    case 3:
      frequency3 += temp;
      if (frequency3 >= (HighEdgeSet3 * 100) + 1) {
        frequency3 = LowEdgeSet3 * 100;
      }
      Frontend.SetFreq(frequency3 - (IF * 100), offset);
      break;

    case 4:
      frequency4 += temp;
      if (frequency4 >= (HighEdgeSet4 * 100) + 1) {
        frequency4 = LowEdgeSet4 * 100;
      }
      Frontend.SetFreq(frequency4 - (IF * 100), offset);
      break;

    case 5:
      frequency5 += temp;
      if (frequency5 > 27000) {
        frequency5 = 144;
      }
      radio.SetFreqAM(frequency5);
      break;

    case 6:
      frequency6 += temp;
      if (frequency6 >= (HighEdgeSet6 * 100) + 1) {
        frequency6 = LowEdgeSet6 * 100;
      }
      radio.SetFreq(frequency6 - converteroffset * 100);
      break;
  }
}

void TuneDown(void) {
  unsigned int temp = 0;
  if (stepsize == 0) {
    if (band == 5) {
      if (frequency5 <= 2000) {
        if (frequency5 == 2000) {
          frequency5 = 1998;
          temp = 0;
        } else {
          temp = 9;
          frequency5 = (frequency5 / 9) * 9;
        }
      } else {
        temp = 5;
        frequency5 = (frequency5 / 5) * 5;
      }
    } else {
      temp = 5;
    }
  }

  switch (stepsize) {
    case 1: temp = 1; break;
    case 2: temp = 10; break;
    case 3: temp = 100; break;
    case 4: temp = 1000; break;
  }

  switch (band) {
    case 0:
      frequency0 -= temp;
      if (frequency0 < LowEdgeSet0 * 100) frequency0 = HighEdgeSet0 * 100;
      radio.SetFreq(frequency0);
      break;

    case 1:
      frequency1 -= temp;
      if (frequency1 < LowEdgeSet1 * 100) frequency1 = HighEdgeSet1 * 100;
      Frontend.SetFreq(frequency1 - (IF * 100), offset);
      break;

    case 2:
      frequency2 -= temp;
      if (frequency2 < LowEdgeSet2 * 100) frequency2 = HighEdgeSet2 * 100;
      Frontend.SetFreq(frequency2 - (IF * 100), offset);
      break;

    case 3:
      frequency3 -= temp;
      if (frequency3 < LowEdgeSet3 * 100) frequency3 = HighEdgeSet3 * 100;
      Frontend.SetFreq(frequency3 - (IF * 100), offset);
      break;

    case 4:
      frequency4 -= temp;
      if (frequency4 < LowEdgeSet4 * 100) frequency4 = HighEdgeSet4 * 100;
      Frontend.SetFreq(frequency4 - (IF * 100), offset);
      break;

    case 5:
      if (temp == 1000 && frequency5 <= 1440) {
        frequency5 = 27000;
      } else {
        frequency5 -= temp;
        if (frequency5 < 144) frequency5 = 27000;
      }
      radio.SetFreqAM(frequency5);
      break;

    case 6:
      frequency6 -= temp;
      if (frequency6 < LowEdgeSet6 * 100) frequency6 = HighEdgeSet6 * 100;
      radio.SetFreq(frequency6 - converteroffset * 100);
      break;
  }
}

void SetTunerPatch(void) {
  radio.init(102);
  uint16_t device;
  uint16_t hw;
  uint16_t sw;
  radio.getIdentification(device, hw, sw);
  TEF = highByte(hw) * 100 + highByte(sw);
  if (TEF == 0) Display.writeStr("version.txt", "Tuner not detected"); else Display.writeStr("version.txt", String("Tuner version set: v") + String(TEF));
  Display.writeStr("version2.txt", "Please restart tuner");
  EEPROM.writeByte(EE_UINT8T_TEF, TEF);
  EEPROM.commit();
  for (;;);
}

void FactoryDefaults(void) {
  swSer.print("AT+DELVMLINK");
  delay(250);
  swSer.print("AT+ADDLINKADD=0xffffffffffff");
  passwordgenerator();
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY0, 9630);
  EEPROM.writeInt(EE_INT16T_VOLSET, 0);
  EEPROM.writeByte(EE_UINT8T_LF, 0);
  EEPROM.writeByte(EE_UINT8T_DEMP, 1);
  EEPROM.writeByte(EE_UINT8T_SCANNERTH, 50);
  EEPROM.writeByte(EE_UINT8T_SCANNERBAND, 0);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET0, 84);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET0, 108);
  EEPROM.writeInt(EE_INT16T_CONTRAST, 50);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET0, 0);
  EEPROM.writeInt(EE_INT16T_STEREOLEVEL, 0);
  EEPROM.writeInt(EE_INT16T_HIGHCUTLEVEL, 70);
  EEPROM.writeInt(EE_INT16T_HIGHCUTOFFSET, 0);
  EEPROM.writeByte(EE_UINT8T_SCANNERSPEED, 1);
  EEPROM.writeByte(EE_UINT8T_VERSIONCHECK, EE_VERSIONCOUNTER);
  EEPROM.writeByte(EE_UINT8T_STEPSIZE, 0);
  EEPROM.writeByte(EE_UINT8T_STATIONLIST, 1);
  EEPROM.writeByte(EE_UINT8T_IMSSET, 1);
  EEPROM.writeByte(EE_UINT8T_EQSET, 1);
  EEPROM.writeByte(EE_UINT8T_BAND, 0);
  EEPROM.writeByte(EE_UINT8T_IF, 70);
  EEPROM.writeByte(EE_UINT8T_USBMODE, 0);
  EEPROM.writeByte(EE_UINT8T_WIFIENABLE, 1);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET1, 430);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET1, 440);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET2, 870);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET2, 880);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET3, 1290);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET3, 1310);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET4, 2320);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET4, 2400);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY1, 43500);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY2, 87400);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY3, 129900);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY4, 232500);
  EEPROM.writeUInt(EE_UINT16T_SCANNERSTART, 8800);
  EEPROM.writeUInt(EE_UINT16T_SCANNEREND, 10800);
  EEPROM.writeUInt(EE_UINT16T_SCANNERVBW, 56);
  EEPROM.writeByte(EE_UINT8T_SCANNERTHENABLE, 0);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET1, 0);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET2, 0);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET3, 0);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET4, 0);
  EEPROM.writeString(EE_STRING_PASSWORD, password);
  EEPROM.writeByte(EE_UINT8T_IP1, 192);
  EEPROM.writeByte(EE_UINT8T_IP2, 168);
  EEPROM.writeByte(EE_UINT8T_IP3, 178);
  EEPROM.writeByte(EE_UINT8T_IP4, 150);
  EEPROM.writeInt(EE_INT16T_BLENDLEVEL, 70);
  EEPROM.writeInt(EE_INT16T_BLENDOFFSET, 0);
  EEPROM.writeInt(EE_INT16T_NBLEVEL, 0);
  EEPROM.writeByte(EE_UINT8T_COAXSWITCH, 1);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY5, 828);
  EEPROM.writeByte(EE_UINT8T_ROTARYMODE, 0);
  EEPROM.writeInt(EE_INT16T_AMCOCHANNEL, 100);
  EEPROM.writeInt(EE_INT16T_AMNBLEVEL, 0);
  EEPROM.writeInt(EE_INT16T_AMATT, 0);
  EEPROM.writeByte(EE_UINT8T_AM, 1);
  EEPROM.writeByte(EE_UINT8T_FM, 1);
  EEPROM.writeByte(EE_UINT8T_UHF1, 1);
  EEPROM.writeByte(EE_UINT8T_UHF2, 1);
  EEPROM.writeByte(EE_UINT8T_UHF3, 1);
  EEPROM.writeByte(EE_UINT8T_UHF4, 1);
  EEPROM.writeByte(EE_UINT8T_COAXMODE, 1);
  EEPROM.writeByte(EE_UINT8T_TEF, 0);
  EEPROM.writeByte(EE_UINT8T_OPTROT, 0);
  EEPROM.writeByte(EE_UINT8T_FMSI, 2);
  EEPROM.writeByte(EE_UINT8T_SCOPEMODE, 0);
  EEPROM.writeUInt(EE_UINT16T_FMSIATTACK, 50);
  EEPROM.writeUInt(EE_UINT16T_FMSIRELEASE, 50);
  EEPROM.writeUInt(EE_UINT16T_FMSI11, 100);
  EEPROM.writeUInt(EE_UINT16T_FMSI12, 175);
  EEPROM.writeUInt(EE_UINT16T_FMSI21, 100);
  EEPROM.writeUInt(EE_UINT16T_FMSI22, 215);
  EEPROM.writeUInt(EE_UINT16T_FMSI31, 100);
  EEPROM.writeUInt(EE_UINT16T_FMSI32, 225);
  EEPROM.writeUInt(EE_UINT16T_FMSI41, 100);
  EEPROM.writeUInt(EE_UINT16T_FMSI42, 225);
  EEPROM.writeByte(EE_UINT8T_MEMORYPOS, 0);
  EEPROM.writeByte(EE_UINT8T_TUNEMODE, 0);
  EEPROM.writeByte(EE_UINT8T_UHF6, 0);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET6, 0);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET6, 430);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET6, 440);
  EEPROM.writeUInt(EE_UINT16T_FREQUENCY6, 43500);
  EEPROM.writeUInt(EE_UINT16T_CONVERTEROFFSET, 340);
  EEPROM.writeInt(EE_INT16T_OFFSET, 0);
  EEPROM.writeByte(EE_UINT8T_SOFTMUTEFM, 0);
  EEPROM.writeByte(EE_UINT8T_SOFTMUTEAM, 0);
  EEPROM.writeByte(EE_UINT8T_SHOWRDSERRORS, 0);

  uint8_t i;
  for (i = 0; i < 30; i++) EEPROM.writeUInt((i * 4) + EE_UINT16T_MEMFREQ, 8750);
  EEPROM.commit();
}

void read_encoder(void) {
  static uint8_t old_AB = 3;
  static int8_t encval = 0;
  static const int8_t enc_states[]  = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

  old_AB <<= 2;

  if (digitalRead(ROTARY_PIN_A)) old_AB |= 0x02;
  if (digitalRead(ROTARY_PIN_B)) old_AB |= 0x01;
  encval += enc_states[( old_AB & 0x0f )];

  if (optrot) {
    if (encval > 2) {
      if (rotarymode) rotary = -1; else rotary = 1;
      encval = 0;
    } else if (encval < -2) {
      if (rotarymode) rotary = 1; else rotary = -1;
      encval = 0;
    }
  } else {
    if (encval > 3) {
      if (rotarymode) rotary = -1; else rotary = 1;
      encval = 0;
    } else if (encval < -3) {
      if (rotarymode) rotary = 1; else rotary = -1;
      encval = 0;
    }
  }
}
