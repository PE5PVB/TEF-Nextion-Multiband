#include <Wire.h>                   // Included in Boardmanager
#include <WiFiClient.h>             // Included in Boardmanager
#include <EEPROM.h>                 // Included in Boardmanager
#include <SoftwareSerial.h>         // https://github.com/plerup/espsoftwareserial/
#include <EasyNextionLibrary.h>     // https://github.com/Seithan/EasyNextionLibrary
#include <Hash.h>                   // https://github.com/bbx10/Hash_tng
#include <ESP32Time.h>              // https://github.com/fbiego/ESP32Time
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

#define ROTARY_PIN_A          36
#define ROTARY_PIN_B          34
#define ROTARY_BUTTON         39
#define PIN_POT               35
#define BWBUTTON              25
#define MODEBUTTON            26
#define RFA                   32
#define RFB                   33
#define RFC                   4
#define BAND                  27
#define SMETERPIN             2
#define SOFTWAREVER           208
#define DISPLAYVER            105
#define BETA                  7


bool hasCTold;
int8_t CN;
String rds_clockold;
bool rtcset;
String PIold;
bool dropout;
String PSold;
String RTold;
byte MSold;

bool cnvis;
bool fullsearchrds;
bool wifiretry;
bool mlogo_on;
bool mlogo_off;
bool slogo_on;
bool slogo_off;
bool mutelogo_on;
bool mutelogo_off;
bool usblogo_on;
bool usblogo_off;
bool mutestatus = true;
bool memorystore;
byte SNRold;
byte SNR;
byte btselect;
byte TEF;
bool scopeview;
byte softmutefm;
byte softmuteam;
bool af2show;
bool btconnect;
bool btsetup;
bool power;
String MAC[10];
String NAME[10];
bool BWreset = true;
bool ctshow;
bool direction;
bool displayreset;
bool donesearch = false;
bool EONold;
bool manfreq;
bool menu;
bool MS;
bool RDSSpy;
bool RDSstatus;
bool RDSstatusold;
bool RTPlus;
bool scanfound = false;
bool seek;
bool setoffset;
bool showrdserrors;
bool showrdsinfo;
bool spec;
bool SQ;
bool stationlist;
bool Stereostatus;
bool Stereostatusold;
bool StereoToggle = true;
bool store;
bool TA;
bool TAold;
bool TP;
bool TPold;
byte tunemode;
bool XDRGTKdata;
bool UHF;
bool USBstatus = false;
bool wificonnect;
bool XDRGTK;
bool XDRGTKTCP;
bool XDRMute;
byte af_counterold;
byte af_scan;
byte band;
bool CoaxSwitch;
byte BWset;
byte BWsetAM = 2;
byte ContrastSet;
byte demp;
byte displaysize;
byte ECCold;
bool EQset;
byte change;
byte IF;
byte iMSEQ;
bool iMSset;
byte ip1;
byte ip2;
byte ip3;
byte ip4;
byte lf;
bool optrot;
bool rotarymode;
byte scanner_band;
byte scanner_speed;
byte scanner_th;
byte scanner_thenable;
byte scanstatus;
byte stepsize;
bool usbmode;
byte wifienable;
byte wifienableold;
bool am;
bool fm;
byte fmsi;
bool uhf1;
bool uhf2;
bool uhf3;
bool uhf4;
bool uhf6;
byte coaxmode;
char buff[16];
char musicArtistPrevious[48];
char musicTitlePrevious[48];
String programServicePrevious;
char programTypePrevious[18];
char radioIdPrevious[5];
String radioTextPrevious;
char stationEventPrevious[48];
char stationHostPrevious[48];
unsigned int BWOld;
byte BWsetOld = 254;
int HighCutLevel;
int HighCutOffset;
int BlendLevel;
int BlendOffset;
int NBLevel;
int AM_Cochannel;
int AM_NBLevel;
int AM_att;
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
int rotary;
int scanner_filter;
int Squelch;
int Squelchold;
int SStatusold;
byte OStatusold;
int StereoLevel;
int timeoffset;
int VolSet;
int XDRBWset;
int XDRBWsetold;
int displayversion;
int16_t OStatus;
int16_t SStatus;
int16_t SAvg;
int16_t SAvg2;
int16_t SAvg3;
int offset;
IPAddress remoteip;
long rssi;
long rssiold = 1;
String af;
String af2;
String clockPrevious;
String cryptedpassword;
String datePrevious;
String packet;
String password = "12345";
String PIcode;
String rds_clock = "--:--";
String rds_date = "----------";
String salt;
String saltkey = "                ";
String showsoftwareversion;
String XDRGTKRDSold;
String RDSSPYRDSold;
uint16_t BW;
uint8_t RDSerrorsold;
uint16_t minutesold;
uint16_t MStatus;
uint16_t USN;
uint16_t WAM;
uint16_t highcut;
uint16_t stereo;
uint16_t sthiblend;
uint8_t stband_1;
uint8_t stband_2;
uint8_t stband_3;
uint8_t stband_4;
uint8_t af_counter;
uint8_t buff_pos = 0;
unsigned int fmsi_attack;
unsigned int fmsi_release;
unsigned int fmsi_11;
unsigned int fmsi_12;
unsigned int fmsi_21;
unsigned int fmsi_22;
unsigned int fmsi_31;
unsigned int fmsi_32;
unsigned int fmsi_41;
unsigned int fmsi_42;
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
unsigned int scanner_end;
unsigned int scanner_found;
unsigned int scanner_start;
unsigned int scanner_vbw;
unsigned int XDRfreq_scan;
unsigned int XDRscanner_end;
unsigned int XDRscanner_filter;
unsigned int XDRscanner_old;
unsigned int XDRscanner_start;
unsigned int XDRscanner_step;
unsigned long showmillis;
unsigned long stlmillis;
unsigned long time_now;
unsigned long XDRshowmillis;
unsigned int memory[30];
unsigned int converteroffset;
byte memory_pos;

void setup() {
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
  EEPROM.begin(380);
  if (EEPROM.readByte(41) != SOFTWAREVER) FactoryDefaults();

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(MODEBUTTON) == HIGH && digitalRead(BWBUTTON) == HIGH) {
    optrot = EEPROM.readByte(184);
    EEPROM.commit();
    if (optrot) {
      optrot = false;
      Display.writeStr("version2.txt", "standard encoder");
    } else {
      optrot = true;
      Display.writeStr("version2.txt", "optical encoder");
    }
    EEPROM.writeByte(184, optrot);
    EEPROM.commit();
    Display.writeStr("version.txt", "Changed to: ");
    delay(2000);
    Display.writeStr("version.txt", "Please release");
    Display.writeStr("version2.txt", "the button!");
    while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }


  if (digitalRead(MODEBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == HIGH && digitalRead(BWBUTTON) == HIGH) {
    CoaxSwitch = EEPROM.readByte(157);
    EEPROM.commit();
    if (CoaxSwitch) CoaxSwitch = false; else CoaxSwitch = true;
    EEPROM.writeByte(157, CoaxSwitch);
    EEPROM.commit();
    Display.writeStr("version.txt", "Coax switch");
    Display.writeStr("version2.txt", "changed!");
    delay(2000);
    Display.writeStr("version.txt", "Please release");
    Display.writeStr("version2.txt", "the button!");
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }

  if (digitalRead(BWBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == HIGH && digitalRead(MODEBUTTON) == HIGH) {
    rotarymode = EEPROM.readByte(163);
    EEPROM.commit();
    if (!rotarymode) rotarymode = true; else rotarymode = false;
    EEPROM.writeByte(163, rotarymode);
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
  delay(100);
  Display.writeStr("version.txt", "Version " + String(showsoftwareversion));
  Display.writeStr("version2.txt", showdisplayversion);

  if (displayversion < DISPLAYVER) {
    Display.writeStr("page 0");
    delay(100);
    Display.writeStr("version.txt", "Incompatible display version");
    Display.writeStr("version2.txt", "Update display to v" + String (DISPLAYVER / 100) + ".0" + String (DISPLAYVER % 10) + "!");
    for (;;);
  }

  TEF = EEPROM.readByte(183);

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
    Display.writeNum("TEFicon.pic", 4);
    Display.writeStr("vis TEFicon,1");
    Display.writeNum("TEF.pco", 34800);
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
    Display.writeNum("TEFicon.pic", 5);
    Display.writeStr("vis TEFicon,1");
    Display.writeNum("TEF.pco", 63488);
    Display.writeStr("TEF.txt", "Tuner NOT detected!");
  }

  if (digitalRead(BAND) == LOW) {
    Display.writeNum("UHFicon.pic", 4);
    Display.writeStr("vis UHFicon,1");
    Display.writeNum("UHF.pco", 34800);
    Display.writeStr("UHF.txt", "UHF Board detected!");
    Display.writeNum("uhf", 1);
    UHF = true;
  } else {
    Display.writeNum("UHFicon.pic", 5);
    Display.writeStr("vis UHFicon,1");
    Display.writeNum("UHF.pco", 63488);
    Display.writeStr("UHF.txt", "UHF Board NOT detected!");
    UHF = false;
  }

  swSer.print("AT+STATUS");
  delay(100);

  if (swSer.available()) {
    Display.writeNum("BTicon.pic", 4);
    Display.writeStr("vis BTicon,1");
    Display.writeNum("BT.pco", 34800);
    Display.writeStr("BT.txt", "Bluetooth detected!");
    Display.writeNum("btenable", 1);
  }

  Frontend.SetFreq(100000, offset);
  delay(400);

  EEpromReadData();

  if (usbmode) Serial.begin(19200); else Serial.begin(115200);

  Display.writeNum("smeterold", 0);

  if (iMSset && EQset) iMSEQ = 2;
  if (!iMSset && EQset) iMSEQ = 3;
  if (iMSset && !EQset) iMSEQ = 4;
  if (!iMSset && !EQset) iMSEQ = 1;

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

void loop() {
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
    if ((SStatus < 100) || (OStatus < -200 || OStatus > 200) || (USN > 200) && (WAM > 230)) {
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
      if (millis() >= XDRshowmillis + 200) {
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

void BandSet() {
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
      EEPROM.writeByte(46, band);
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

  if (RFset == 0 && !fm) {
    band ++;
    RFset ++;
  }
  if (RFset == 1 && !uhf1) {
    band ++;
    RFset ++;
  }
  if (RFset == 2 && !uhf2) {
    band ++;
    RFset ++;
  }
  if (RFset == 3 && !uhf3) {
    band ++;
    RFset ++;
  }
  if (RFset == 4 && !uhf4) {
    band ++;
    RFset ++;
  }
  if (RFset == 5 && !am) {
    if (UHF) {
      band = 0;
      RFset = 0;
    } else {
      band ++;
      RFset ++;
    }
  }
  if (RFset == 6 && !uhf6) {
    band = 0;
    RFset = 0;
  }

  if (RFset == 5) {
    if (showrdsinfo && !manfreq) {
      Display.writeStr("page 1");
      showrdsinfo = false;
    }
    if (!manfreq) Display.writeStr("vis m0,0");
    if (!scopeview && !manfreq) {
      Display.writeStr("vis U_disp,0");
      Display.writeStr("vis W_disp,0");
      Display.writeNum("tm4.en", 0);
      Display.writeStr("vis m1,0");
      Display.writeStr("vis signalform,1");
      Display.writeStr("vis modpos,1");
      Display.writeNum("scopeview", 1);
    }
    if (!manfreq) {
      Display.writeNum("BW.pco", 65504);
      Display.writeNum("autobwlogo.pic", 22);
      Display.writeNum("imslogo.pic", 28);
      Display.writeNum("eqlogo.pic", 26);
      Display.writeNum("stereo.pic", 10);
      Display.writeNum("ber.pic", 206);
      Display.writeNum("t4.pco", 33840);
      Display.writeNum("t5.pco", 33840);
      Display.writeNum("t6.pco", 33840);
      Display.writeNum("t7.pco", 33840);
      Display.writeNum("t10.pco", 33840);

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
      if (!scopeview) {
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
      Display.writeNum("t4.pco", 65535);
      Display.writeNum("t5.pco", 65535);
      Display.writeNum("t6.pco", 65535);
      Display.writeNum("t7.pco", 65535);
      Display.writeNum("t10.pco", 65535);
      ShowBW();
    }
  }

  switch (RFset) {
    case 0:
      if (CoaxSwitch) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      delay(50);
      radio.SetFreq(frequency0);
      radio.setOffset(LevelOffset0);
      Frontend.Power(0);
      if (!spec && !manfreq) Display.writeNum("offsettouch", 0);
      break;

    case 1:
      if (CoaxSwitch) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, LOW);
      digitalWrite(RFB, LOW);
      radio.power(0);
      delay(50);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset1 - 7);
      Frontend.Power(1);
      Frontend.SetFreq(frequency1 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 2:
      if (CoaxSwitch) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, LOW);
      radio.power(0);
      delay(50);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset2 - 4);
      Frontend.SetFreq(frequency2 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 3:
      if (CoaxSwitch) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, LOW);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      delay(50);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset3);
      Frontend.SetFreq(frequency3 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 4:
      if (CoaxSwitch) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      delay(50);
      radio.SetFreq(IF * 100);
      radio.clearRDS(fullsearchrds);
      radio.setOffset(LevelOffset4 + 2);
      Frontend.SetFreq(frequency4 - (IF * 100), offset);
      Display.writeNum("offsettouch", 1);
      break;

    case 5:
      if (CoaxSwitch) {
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
      if (CoaxSwitch) {
        if (!coaxmode) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
      } else {
        if (!coaxmode) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
      }
      digitalWrite(RFA, HIGH);
      digitalWrite(RFB, HIGH);
      radio.power(0);
      delay(50);
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

void readRds() {
  if (band == 5) RDSstatus = false; else radio.readRDS(showrdserrors);
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
          if (XDRGTKTCP) RemoteClient.print("P"); else Serial.print("P");
          String PIcodeToSend;
          PIcodeToSend = String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX) + String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
          PIcodeToSend.toUpperCase();
          if (XDRGTKTCP) RemoteClient.print(PIcodeToSend); else Serial.print(PIcodeToSend);
          while (piState != 0) {
            if (XDRGTKTCP) RemoteClient.print("?"); else Serial.print("?");
            piState--;
          }
          if (XDRGTKTCP) RemoteClient.print("\n"); else Serial.print("\n");
        }
      }

      XDRGTKRDSold = XDRGTKRDS;
      XDRGTKRDS.toUpperCase();
      if (XDRGTKTCP) RemoteClient.print(XDRGTKRDS); else Serial.print(XDRGTKRDS);
    }
  }
}

void doStepSize() {
  stepsize++;
  if (stepsize > 4) stepsize = 0;
  ShowStepSize();
  EEPROM.writeByte(42, stepsize);
  EEPROM.commit();
  if (stepsize == 0) {
    RoundStep();
    ShowFreq();
  }
}

void doTuneMode() {
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

void doFilter() {
  if (iMSEQ == 0) iMSEQ = 1;

  switch (iMSEQ) {
    case 4:
      iMSset = false;
      EQset = false;
      ShowiMS();
      ShowEQ();
      iMSEQ = 0;
      break;

    case 3:
      iMSset = true;
      EQset = false;
      ShowiMS();
      ShowEQ();
      iMSEQ = 4;
      break;

    case 2:
      iMSset = false;
      EQset = true;
      ShowiMS();
      ShowEQ();
      iMSEQ = 3;
      break;

    case 1:
      iMSset = true;
      EQset = true;
      ShowiMS();
      ShowEQ();
      iMSEQ = 2;
      break;
  }

  EEPROM.writeByte(44, iMSset);
  EEPROM.writeByte(45, EQset);
  EEPROM.commit();
}


void ButtonPress() {
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
            Display.writeNum("memlogo.pic", 25);
            memorystore = false;
            EEPROM.writeUInt((memory_pos * 4) + 230, freq);
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

void RoundStep() {
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

  EEPROM.writeUInt(0, frequency0);
  EEPROM.writeUInt(83, frequency1);
  EEPROM.writeUInt(87, frequency2);
  EEPROM.writeUInt(91, frequency3);
  EEPROM.writeUInt(95, frequency4);
  EEPROM.writeUInt(158, frequency5);
  EEPROM.writeUInt(364, frequency6);
  EEPROM.commit();
}

void ModeButtonPress() {
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
          delay(50);
          Display.writeNum("fmsi", fmsi);
        }
      }
    }
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }
}

void BWButtonPress() {
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

void KeyUp() {
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

void KeyDown() {
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

void MemoryTune() {
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


void doExit() {
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
    Display.writeNum("ber.pic", 206);
  } else {
    Display.writeStr("vis m0,1");
    Display.writeNum("freq.vvs1", 2);
  }
  delay(200);
  ShowFreq();
  delay(200);
  RF(band);
  ShowiMS();
  ShowEQ();
  Squelchold = 200;
  mutestatus = false;
  cnvis = false;
  SNRold = 0;
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

void doBW() {
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

void doSquelch() {
  if (!power) {
    if (!XDRGTK && !XDRGTKTCP) {
      Squelch = analogRead(PIN_POT) / 4 - 100;
      if (Squelch > 920) Squelch = 920;
      if (!showrdsinfo && !menu && Squelch != Squelchold) {
        if (Squelch == -100) {
          if (!spec) Display.writeStr("SQ.txt", "OFF");
        } else if (Squelch == 920) {
          if (!spec) Display.writeStr("SQ.txt", "ST");
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
            if (!showrdsinfo) if (!spec) Display.writeStr("SQ.txt", "OFF");
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

void doStereoToggle() {
  if (StereoToggle) {
    Display.writeNum("stereo.pic", 11);
    radio.setMono(2);
    StereoToggle = false;
  } else {
    Display.writeNum("stereo.pic", 10);
    radio.setMono(0);
    Stereostatusold = false;
    StereoToggle = true;
  }
}

void EEpromReadData() {
  frequency0 = EEPROM.readUInt(0);
  VolSet = EEPROM.readInt(4);
  ContrastSet = EEPROM.readInt(20);
  StereoLevel = EEPROM.readInt(28);
  HighCutLevel = EEPROM.readInt(32);
  HighCutOffset = EEPROM.readInt(36);
  scanner_speed = EEPROM.readByte(40);
  stepsize = EEPROM.readByte(42);
  stationlist = EEPROM.readByte(43);
  iMSset = EEPROM.readByte(44);
  EQset = EEPROM.readByte(45);
  band = EEPROM.readByte(46);
  IF = EEPROM.readByte(47);
  LowEdgeSet0 = EEPROM.readInt(12);
  HighEdgeSet0 = EEPROM.readInt(16);
  LowEdgeSet1 = EEPROM.readInt(51);
  HighEdgeSet1 = EEPROM.readInt(55);
  LowEdgeSet2 = EEPROM.readInt(59);
  HighEdgeSet2 = EEPROM.readInt(63);
  LowEdgeSet3 = EEPROM.readInt(67);
  HighEdgeSet3 = EEPROM.readInt(71);
  LowEdgeSet4 = EEPROM.readInt(75);
  HighEdgeSet4 = EEPROM.readInt(79);
  frequency1 = EEPROM.readUInt(83);
  frequency2 = EEPROM.readUInt(87);
  frequency3 = EEPROM.readUInt(91);
  frequency4 = EEPROM.readUInt(95);
  scanner_start = EEPROM.readUInt(99);
  scanner_end = EEPROM.readUInt(103);
  scanner_vbw = EEPROM.readUInt(107);
  scanner_th = EEPROM.readByte(10);
  scanner_band = EEPROM.readByte(11);
  scanner_thenable = EEPROM.readByte(113);
  LevelOffset0 = EEPROM.readInt(24);
  LevelOffset1 = EEPROM.readInt(117);
  LevelOffset2 = EEPROM.readInt(121);
  LevelOffset3 = EEPROM.readInt(125);
  LevelOffset4 = EEPROM.readInt(129);
  lf = EEPROM.readByte(8);
  demp = EEPROM.readByte(9);
  usbmode = EEPROM.readByte(48);
  wifienable = EEPROM.readByte(49);
  password = EEPROM.readString(134);
  ip1 = EEPROM.readByte(140);
  ip2 = EEPROM.readByte(141);
  ip3 = EEPROM.readByte(142);
  ip4 = EEPROM.readByte(143);
  BlendLevel = EEPROM.readInt(144);
  BlendOffset = EEPROM.readInt(148);
  NBLevel = EEPROM.readInt(152);
  CoaxSwitch = EEPROM.readByte(157);
  frequency5 = EEPROM.readUInt(158);
  rotarymode = EEPROM.readByte(163);
  AM_Cochannel = EEPROM.readInt(164);
  AM_NBLevel = EEPROM.readInt(168);
  AM_att = EEPROM.readInt(172);
  am = EEPROM.readByte(176);
  fm = EEPROM.readByte(177);
  uhf1 = EEPROM.readByte(178);
  uhf2 = EEPROM.readByte(179);
  uhf3 = EEPROM.readByte(180);
  uhf4 = EEPROM.readByte(181);
  coaxmode = EEPROM.readByte(182);
  optrot = EEPROM.readByte(184);
  fmsi = EEPROM.readByte(185);
  scopeview = EEPROM.readByte(186);
  fmsi_attack = EEPROM.readUInt(187);
  fmsi_release = EEPROM.readUInt(191);
  fmsi_11 = EEPROM.readUInt(195);
  fmsi_12 = EEPROM.readUInt(199);
  fmsi_21 = EEPROM.readUInt(203);
  fmsi_22 = EEPROM.readUInt(207);
  fmsi_31 = EEPROM.readUInt(211);
  fmsi_32 = EEPROM.readUInt(215);
  fmsi_41 = EEPROM.readUInt(219);
  fmsi_42 = EEPROM.readUInt(223);
  memory_pos = EEPROM.readByte(227);
  tunemode = EEPROM.readByte(228);
  uhf6 = EEPROM.readByte(351);
  LevelOffset6 = EEPROM.readInt(352);
  LowEdgeSet6 = EEPROM.readInt(356);
  HighEdgeSet6 = EEPROM.readInt(360);
  frequency6 = EEPROM.readUInt(364);
  converteroffset = EEPROM.readUInt(368);
  offset = EEPROM.readInt(372);
  softmutefm = EEPROM.readByte(377);
  softmuteam = EEPROM.readByte(378);
  showrdserrors = EEPROM.readByte(379);

  uint8_t i;
  for (i = 0; i < 30; i++) memory[i] = EEPROM.readUInt((i * 4) + 230);
  EEPROM.commit();

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
  Display.writeNum("sstop", scanner_end / 100);
  Display.writeNum("sbw", scanner_vbw);
  Display.writeNum("sth", scanner_th);
  Display.writeNum("sband", scanner_band);
  Display.writeNum("sspeed", scanner_speed);
  Display.writeNum("thenable", scanner_thenable);
  Display.writeNum("l0", LowEdgeSet0 / 2 * 2);
  Display.writeNum("l1", LowEdgeSet1 / 2 * 2);
  Display.writeNum("l2", LowEdgeSet2 / 2 * 2);
  Display.writeNum("l3", LowEdgeSet3 / 2 * 2);
  Display.writeNum("l4", LowEdgeSet4 / 2 * 2);
  Display.writeNum("l6", LowEdgeSet6 / 2 * 2);
  Display.writeNum("h0", HighEdgeSet0 / 2 * 2);
  Display.writeNum("h1", HighEdgeSet1 / 2 * 2);
  Display.writeNum("h2", HighEdgeSet2 / 2 * 2);
  Display.writeNum("h3", HighEdgeSet3 / 2 * 2);
  Display.writeNum("h4", HighEdgeSet4 / 2 * 2);
  Display.writeNum("h6", HighEdgeSet6 / 2 * 2);
  Display.writeNum("Volset", VolSet + 15);
  Display.writeNum("dim", ContrastSet);
  Display.writeNum("HighCutOffset", HighCutOffset);
  Display.writeNum("HighCutLevel", HighCutLevel * 100);
  Display.writeNum("StereoLevel", StereoLevel);
  Display.writeNum("o0", LevelOffset0 + 25);
  Display.writeNum("o1", LevelOffset1 + 25);
  Display.writeNum("o2", LevelOffset2 + 25);
  Display.writeNum("o3", LevelOffset3 + 25);
  Display.writeNum("o4", LevelOffset4 + 25);
  Display.writeNum("o6", LevelOffset6 + 25);
  Display.writeNum("iffreq", IF);
  Display.writeNum("demp", demp);
  Display.writeNum("lf", lf);
  Display.writeNum("usbmode", usbmode);
  Display.writeNum("wifienable", wifienable);
  Display.writeNum("pcip1", ip1);
  Display.writeNum("pcip2", ip2);
  Display.writeNum("pcip3", ip3);
  Display.writeNum("pcip4", ip4);
  Display.writeNum("stationlog", stationlist);
  Display.writeNum("BlendLevel", BlendLevel * 100);
  Display.writeNum("BlendOffset", BlendOffset);
  Display.writeNum("NBLevel", NBLevel);
  Display.writeNum("AMcochannel", AM_Cochannel);
  Display.writeNum("AMnb", AM_NBLevel);
  Display.writeNum("AMatt", AM_att);
  Display.writeNum("am", am);
  Display.writeNum("fm", fm);
  Display.writeNum("uhf1", uhf1);
  Display.writeNum("uhf2", uhf2);
  Display.writeNum("uhf3", uhf3);
  Display.writeNum("uhf4", uhf4);
  Display.writeNum("uhf6", uhf6);
  Display.writeNum("converterlo", converteroffset);
  Display.writeNum("coaxmode", coaxmode);
  Display.writeNum("fmsi", fmsi);
  Display.writeNum("scopeview", scopeview);
  Display.writeNum("fmsiattack", fmsi_attack);
  Display.writeNum("fmsirelease", fmsi_release);
  Display.writeNum("b1sens", fmsi_11);
  Display.writeNum("b1bias", fmsi_12);
  Display.writeNum("b2sens", fmsi_21);
  Display.writeNum("b2bias", fmsi_22);
  Display.writeNum("b3sens", fmsi_31);
  Display.writeNum("b3bias", fmsi_32);
  Display.writeNum("b4sens", fmsi_41);
  Display.writeNum("b4bias", fmsi_42);
  Display.writeNum("looffset", offset);
  Display.writeNum("softmutefm", softmutefm);
  Display.writeNum("softmuteam", softmuteam);
  Display.writeNum("showrdserrors", showrdserrors);
}

void doEEpromWrite() {
  if (store) change++;

  if (change > 200 && store) {
    detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
    detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));
    EEPROM.writeUInt(0, frequency0);
    EEPROM.writeUInt(83, frequency1);
    EEPROM.writeUInt(87, frequency2);
    EEPROM.writeUInt(91, frequency3);
    EEPROM.writeUInt(95, frequency4);
    EEPROM.writeUInt(158, frequency5);
    EEPROM.writeUInt(364, frequency6);
    EEPROM.writeByte(227, memory_pos);
    EEPROM.writeByte(228, tunemode);
    EEPROM.commit();
    store = false;
    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
  }
}

void Seek(bool mode) {
  radio.setMute();
  if (!mode) TuneDown(); else TuneUp();
  delay(50);
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

void TuneUp() {
  unsigned int temp;
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

  radio.clearRDS(fullsearchrds);
}

void TuneDown() {
  unsigned int temp;
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
  radio.clearRDS(fullsearchrds);
}

void SetTunerPatch() {
  radio.init(102);
  uint16_t device;
  uint16_t hw;
  uint16_t sw;
  radio.getIdentification(device, hw, sw);
  TEF = highByte(hw) * 100 + highByte(sw);
  if (TEF == 0) Display.writeStr("version.txt", "Tuner not detected"); else Display.writeStr("version.txt", String("Tuner version set: v") + String(TEF));
  Display.writeStr("version2.txt", "Please restart tuner");
  EEPROM.writeByte(183, TEF);
  EEPROM.commit();
  for (;;);
}

void FactoryDefaults() {
  swSer.print("AT+DELVMLINK");
  delay(250);
  swSer.print("AT+ADDLINKADD=0xffffffffffff");
  passwordgenerator();
  EEPROM.writeUInt(0, 9630);
  EEPROM.writeInt(4, 0);
  EEPROM.writeByte(8, 1);
  EEPROM.writeByte(9, 1);
  EEPROM.writeByte(10, 50);
  EEPROM.writeByte(11, 0);
  EEPROM.writeInt(12, 84);
  EEPROM.writeInt(16, 108);
  EEPROM.writeInt(20, 50);
  EEPROM.writeInt(24, 0);
  EEPROM.writeInt(28, 0);
  EEPROM.writeInt(32, 70);
  EEPROM.writeInt(36, 0);
  EEPROM.writeByte(40, 1);
  EEPROM.writeByte(41, SOFTWAREVER);
  EEPROM.writeByte(42, 0);
  EEPROM.writeByte(43, 1);
  EEPROM.writeByte(44, 1);
  EEPROM.writeByte(45, 1);
  EEPROM.writeByte(46, 0);
  EEPROM.writeByte(47, 70);
  EEPROM.writeByte(48, 1);
  EEPROM.writeByte(49, 1);
  EEPROM.writeInt(51, 430);
  EEPROM.writeInt(55, 440);
  EEPROM.writeInt(59, 870);
  EEPROM.writeInt(63, 880);
  EEPROM.writeInt(67, 1290);
  EEPROM.writeInt(71, 1310);
  EEPROM.writeInt(75, 2320);
  EEPROM.writeInt(79, 2400);
  EEPROM.writeUInt(83, 43500);
  EEPROM.writeUInt(87, 87400);
  EEPROM.writeUInt(91, 129900);
  EEPROM.writeUInt(95, 232500);
  EEPROM.writeUInt(99, 8800);
  EEPROM.writeUInt(103, 10800);
  EEPROM.writeUInt(107, 56);
  EEPROM.writeByte(113, 0);
  EEPROM.writeInt(117, 0);
  EEPROM.writeInt(121, 0);
  EEPROM.writeInt(125, 0);
  EEPROM.writeInt(129, 0);
  EEPROM.writeString(134, password);
  EEPROM.writeByte(140, 192);
  EEPROM.writeByte(141, 168);
  EEPROM.writeByte(142, 178);
  EEPROM.writeByte(143, 150);
  EEPROM.writeInt(144, 70);
  EEPROM.writeInt(148, 0);
  EEPROM.writeInt(152, 0);
  EEPROM.writeByte(157, 1);
  EEPROM.writeUInt(158, 828);
  EEPROM.writeByte(163, 0);
  EEPROM.writeInt(164, 100);
  EEPROM.writeInt(168, 0);
  EEPROM.writeInt(172, 0);
  EEPROM.writeByte(176, 1);
  EEPROM.writeByte(177, 1);
  EEPROM.writeByte(178, 1);
  EEPROM.writeByte(179, 1);
  EEPROM.writeByte(180, 1);
  EEPROM.writeByte(181, 1);
  EEPROM.writeByte(182, 1);
  EEPROM.writeByte(183, 0);
  EEPROM.writeByte(184, 0);
  EEPROM.writeByte(185, 2);
  EEPROM.writeByte(186, 0);
  EEPROM.writeUInt(187, 50);
  EEPROM.writeUInt(191, 50);
  EEPROM.writeUInt(195, 100);
  EEPROM.writeUInt(199, 175);
  EEPROM.writeUInt(203, 100);
  EEPROM.writeUInt(207, 215);
  EEPROM.writeUInt(211, 100);
  EEPROM.writeUInt(215, 225);
  EEPROM.writeUInt(219, 100);
  EEPROM.writeUInt(223, 225);
  EEPROM.writeByte(227, 0);
  EEPROM.writeByte(228, 0);
  EEPROM.writeByte(351, 0);
  EEPROM.writeInt(352, 0);
  EEPROM.writeInt(356, 430);
  EEPROM.writeInt(360, 440);
  EEPROM.writeUInt(364, 43500);
  EEPROM.writeUInt(368, 340);
  EEPROM.writeInt(372, 0);
  EEPROM.writeByte(377, 0);
  EEPROM.writeByte(378, 0);
  EEPROM.writeByte(379, 0);

  uint8_t i;
  for (i = 0; i < 30; i++) EEPROM.writeUInt((i * 4) + 230, 8750);
  EEPROM.commit();
}

void tryWiFi() {
  if (wc.autoConnect()) {
    Server.begin();
    if (stationlist) Udp.begin(9031);
  } else {
    wifiretry = true;
    Display.writeStr("page 26");
    while (wifiretry) Display.NextionListen();
  }
}

void read_encoder() {
  static uint8_t old_AB = 3;
  static int8_t encval = 0;
  static const int8_t enc_states[]  = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

  old_AB <<= 2;

  if (digitalRead(ROTARY_PIN_A)) old_AB |= 0x02;
  if (digitalRead(ROTARY_PIN_B)) old_AB |= 0x01;
  encval += enc_states[( old_AB & 0x0f )];

  if (optrot) {
    if (encval > 2) {
      rotary = 1;
      encval = 0;
    } else if (encval < -2) {
      rotary = -1;
      encval = 0;
    }
  } else {
    if (encval > 3) {
      rotary = 1;
      encval = 0;
    } else if (encval < -3) {
      rotary = -1;
      encval = 0;
    }
  }
}
