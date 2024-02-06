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
byte scopeview;
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
byte CoaxSwitch;
byte BWset;
byte BWsetAM = 2;
byte ContrastSet;
byte demp;
byte displaysize;
byte ECCold;
byte EQset;
byte change;
byte IF;
byte iMSEQ;
byte iMSset;
byte ip1;
byte ip2;
byte ip3;
byte ip4;
byte lf;
byte optrot;
byte rotarymode;
byte scanner_band;
byte scanner_speed;
byte scanner_th;
byte scanner_thenable;
byte scanstatus;
byte stepsize;
byte usbmode;
byte wifienable;
byte wifienableold;
byte am;
byte fm;
byte fmsi;
byte uhf1;
byte uhf2;
byte uhf3;
byte uhf4;
byte uhf6;
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
    if (optrot == 1) {
      optrot = 0;
      Display.writeStr("version2.txt", "standard encoder");
    } else {
      optrot = 1;
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
    if (CoaxSwitch == 1) CoaxSwitch = 0; else CoaxSwitch = 1;
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
    if (rotarymode == 0) rotarymode = 1; else rotarymode = 0;
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
  if (band == 0) RF(0);
  if (band == 1) RF(1);
  if (band == 2) RF(2);
  if (band == 3) RF(3);
  if (band == 4) RF(4);
  if (band == 5) RF(5);
  if (band == 6) RF(6);

  ShowFreq();
  ShowStepSize();
  ShowiMS();
  ShowEQ();
  ShowTuneMode();
}

void loop() {
  Display.NextionListen();
  Communication();

  if (seek == true) Seek(direction);

  if (spec == true) scan_loop();

  if (menu == true) {
    radio.getProcessing(highcut, stereo, sthiblend, stband_1, stband_2, stband_3, stband_4);
    Display.writeNum("highcut", highcut);
    delay(10);
    Display.writeNum("stereol", stereo);
    delay(10);
    Display.writeNum("sthiblend", sthiblend);
    delay(10);
    Display.writeNum("stband_1", stband_1);
    delay(10);
    Display.writeNum("stband_2", stband_2);
    delay(10);
    Display.writeNum("stband_3", stband_3);
    delay(10);
    Display.writeNum("stband_4", stband_4);
  }

  if (menu == false && manfreq == false && spec == false && setoffset == false) {
    if ((SStatus < 100) || (OStatus < -200 || OStatus > 200) || (USN > 200) && (WAM > 230)) {
      if (millis() >= showmillis + 250) {
        if (band == 5) radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN); else radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
        readRds();
        ShowStereoStatus();
        showmillis += 250;
      }
    } else {
      if (band == 5) radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN); else radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
      readRds();
      ShowStereoStatus();
    }

    if (XDRGTKTCP == true || XDRGTK == true) {
      if (millis() >= XDRshowmillis + 200) {
        ShowBW();
        ShowSignalLevel();
        ShowOffset();
        ShowUSBstatus();
        ShowRSSI();
        doSquelch();
        XDRshowmillis += 200;
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

  if (setoffset == true) {
    radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
    Display.writeNum("offsetvalue.val", OStatus);
    ShowOffset();
  }
}

void BandSet() {
  if (XDRGTK == false && XDRGTKTCP == false) {
    unsigned long counterold = millis();
    unsigned long counter = millis();

    while (digitalRead(BAND) == LOW && counter - counterold <= 1000) counter = millis();
    if (counter - counterold < 1000 || power == true) {
      if (power == true) {
        Display.writeNum("sleep", 0);
        Display.writeStr("page 0");
        ESP.restart();
      }
      seek = false;
      tunemode = 0;
      ShowTuneMode();
      if (UHF == true) {
        band ++;
        if (band > 5) band = 0;
        if (band == 0) RF(0);
        if (band == 1) RF(1);
        if (band == 2) RF(2);
        if (band == 3) RF(3);
        if (band == 4) RF(4);
        if (band == 5) RF(5);
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
  if (spec == false && manfreq == false) Display.writeNum("outlimit.en", 0);
  if (spec == false && manfreq == false) Display.writeStr("vis outoflimit,0");
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
    if (UHF == true) {
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
    if (showrdsinfo == true && manfreq == false) {
      Display.writeStr("page 1");
      showrdsinfo = false;
    }
    if (manfreq == false) Display.writeStr("vis m0,0");
    if (scopeview == 0 && manfreq == false) {
      Display.writeStr("vis U_disp,0");
      Display.writeStr("vis W_disp,0");
      Display.writeNum("tm4.en", 0);
      Display.writeStr("vis m1,0");
      Display.writeStr("vis signalform,1");
      Display.writeStr("vis modpos,1");
      Display.writeNum("scopeview", 1);
    }
    if (manfreq == false) {
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
    if (spec == false && manfreq == false) {
      ShowiMS();
      ShowEQ();
      Display.writeStr("vis m0,1");
      if (scopeview == 0) {
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
  if (RFset == 0) {
    if (CoaxSwitch == 1) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
    digitalWrite(RFA, HIGH);
    digitalWrite(RFB, HIGH);
    radio.power(0);
    delay(50);
    radio.SetFreq(frequency0);
    radio.setOffset(LevelOffset0);
    Frontend.Power(0);
    if (spec == false && manfreq == false) Display.writeNum("offsettouch", 0);
  } else if (RFset == 1) {
    if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
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
  } else if (RFset == 2) {
    if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
    digitalWrite(RFA, HIGH);
    digitalWrite(RFB, LOW);
    radio.power(0);
    delay(50);
    radio.SetFreq(IF * 100);
    radio.clearRDS(fullsearchrds);
    radio.setOffset(LevelOffset2 - 4);
    Frontend.SetFreq(frequency2 - (IF * 100), offset);
    Display.writeNum("offsettouch", 1);
  } else if (RFset == 3) {
    if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
    digitalWrite(RFA, LOW);
    digitalWrite(RFB, HIGH);
    radio.power(0);
    delay(50);
    radio.SetFreq(IF * 100);
    radio.clearRDS(fullsearchrds);
    radio.setOffset(LevelOffset3);
    Frontend.SetFreq(frequency3 - (IF * 100), offset);
    Display.writeNum("offsettouch", 1);
  } else if (RFset == 4) {
    if (CoaxSwitch == 1) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
    digitalWrite(RFA, HIGH);
    digitalWrite(RFB, HIGH);
    radio.power(0);
    delay(50);
    radio.SetFreq(IF * 100);
    radio.clearRDS(fullsearchrds);
    radio.setOffset(LevelOffset4 + 2);
    Frontend.SetFreq(frequency4 - (IF * 100), offset);
    Display.writeNum("offsettouch", 1);
  } else if (RFset == 5) {
    if (CoaxSwitch == 1) {
      if (coaxmode == 1 && UHF == false) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
    } else {
      if (coaxmode == 1 && UHF == false) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
    }
    digitalWrite(RFA, HIGH);
    digitalWrite(RFB, HIGH);
    radio.clearRDS(fullsearchrds);
    radio.SetFreqAM(frequency5);
    Frontend.Power(0);
    Display.writeNum("offsettouch", 0);
  } else if (RFset == 6) {
    if (CoaxSwitch == 1) {
      if (coaxmode == 0) digitalWrite(RFC, HIGH); else digitalWrite(RFC, LOW);
    } else {
      if (coaxmode == 0) digitalWrite(RFC, LOW); else digitalWrite(RFC, HIGH);
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
  }
  OStatusold = 0;
  BWreset = true;

  if (band == 5) radio.setSoftmuteAM(softmuteam); else radio.setSoftmuteFM(softmutefm);
}

void readRds() {
  if (band == 5) RDSstatus = false; else radio.readRDS(showrdserrors);
  RDSstatus = radio.rds.hasRDS;
  ShowRDS();
  /*
    if (RDSSpy == true && RDSstatus == true && band != 5) {
      String RDSSPYRDS;
      RDSSPYRDS = "G:\r\n";
      RDSSPYRDS += String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX);
      RDSSPYRDS += String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
      RDSSPYRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX);
      RDSSPYRDS += String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
      RDSSPYRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX);
      RDSSPYRDS += String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
      RDSSPYRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX);
      RDSSPYRDS += String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);
      RDSSPYRDS += "\r\n\r\n";

      if (RDSSPYRDS != RDSSPYRDSold) {
        RDSSPYRDSold = RDSSPYRDS;
        if (wificonnect == true) RemoteClient.print(RDSSPYRDS); else Serial.print(RDSSPYRDS);
      }
    }

    if ((XDRGTKTCP == true || XDRGTK == true) && RDSstatus == true && band != 5) {
      String XDRGTKPI;
      XDRGTKPI = "P";
      XDRGTKPI += String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX);
      XDRGTKPI += String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
      if (radio.rds.correct == false) XDRGTKPI += "?";
      XDRGTKPI += "\n";

      String XDRGTKRDS;
      XDRGTKRDS = "R";
      XDRGTKRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.errors >> 8) >> 4) & 0xF, HEX) + String((radio.rds.errors >> 8) & 0xF, HEX);
      XDRGTKRDS += "\n";

      if (XDRGTKTCP == true) RemoteClient.print(XDRGTKPI); else Serial.print(XDRGTKPI);

      if (XDRGTKRDS != XDRGTKRDSold) {
        XDRGTKRDSold = XDRGTKRDS;
        if (XDRGTKTCP == true) RemoteClient.print(XDRGTKRDS); else Serial.print(XDRGTKRDS);
      }
    }
  */
}

void ShowRSSI()
{
  if (wifienable == 2) rssi = WiFi.RSSI(); else rssi = 0;

  if (rssiold != rssi) {
    rssiold = rssi;
    if (rssi == 0) {
      Display.writeNum("wifilogo.pic", 46);
    } else if (rssi > -50 && rssi < 0) {
      Display.writeNum("wifilogo.pic", 50);
    } else if (rssi > -60) {
      Display.writeNum("wifilogo.pic", 49);
    } else if (rssi > -70) {
      Display.writeNum("wifilogo.pic", 48);
    } else if (rssi < -70) {
      Display.writeNum("wifilogo.pic", 47);
    }
  }
}

void ShowFreq() {
  detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
  detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));
  if (band == 0) freq = frequency0;
  if (band == 1) freq = frequency1;
  if (band == 2) freq = frequency2;
  if (band == 3) freq = frequency3;
  if (band == 4) freq = frequency4;
  if (band == 5) freq = frequency5;
  if (band == 6) freq = frequency6;

  if (stationlist == 1 && wifienable == 2) {
    Udp.beginPacket(remoteip, 9030);
    Udp.print("from=TEF tuner " + showsoftwareversion + ";freq=");
    if (band == 5) Udp.print(String(frequency5) + "000;ClearRDS=1"); else Udp.print(String(frequency0) + "0000;ClearRDS=1");
    Udp.endPacket();
    stlmillis += 500;
  }
  if (band == 5) {
    String count = String(frequency5, DEC);
    if (count.length() > 3) {
      Display.writeNum("freq.vvs1", 3);
      Display.writeStr("t2.txt", "MHz");
    } else {
      Display.writeNum("freq.vvs1", 0);
      Display.writeStr("t2.txt", "kHz");
    }
  }
  Display.writeNum("freq.val", freq);
  if (RDSSpy) {
    if (wificonnect == true) RemoteClient.print("G:\r\nRESET-------\r\n\r\n"); else Serial.print("G:\r\nRESET-------\r\n\r\n");
  }
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
}

void ShowModLevel()
{
  if (showrdsinfo == false) {
    if (seek == false) {
      if (SQ == false) Display.writeNum("vu.val", MStatus / 2); else Display.writeNum("vu.val", 0);
    } else {
      Display.writeNum("vu.val", 0);
    }
  }
}

void ShowBW()
{
  if ((BW != BWOld || BWreset == true) || displayreset == true)
  {
    if (BWreset == true) {
      if (band != 5) {
        if (BWsetOld != BWset) {
          if (BWset == 0) {
            Display.writeNum("BW.pco", 2047);
            if (showrdsinfo == false) {
              delay(10);
              Display.writeNum("autobwlogo.pic", 23);
            }
            radio.setFMABandw();
          } else {
            Display.writeNum("BW.pco", 65504);
            if (showrdsinfo == false) {
              delay(10);
              Display.writeNum("autobwlogo.pic", 22);
            }
            BWsetOld = BWset;
          }
        }
      }
    }
    delay(10);
    Display.writeNum("BW.val", BW);
    BWOld = BW;
    BWreset = false;
    if (stationlist == 1 && wifienable == 2) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner " + showsoftwareversion + ";Bandwidth=");
      Udp.print(BW * 1000);
      Udp.endPacket();
    }
  }
}

void ShowSignalLevel()
{
  if (band != 5) SNR = int(0.46222375 * (float)(SStatus / 10) - 0.082495118 * (float)(USN)) + 10; else SNR = -((int8_t)(USN));
  SAvg = (((SAvg * 9) + 5) / 10) + SStatus;
  SAvg2 = (((SAvg2 * 9) + 5) / 10) + SNR;

  float sval = 0;
  int16_t smeter = 0;

  if (SStatus > 0)
  {
    if (SStatus < 1000)
    {
      sval = 51 * ((pow(10, (((float)SStatus) / 1000))) - 1);
      smeter = int16_t(sval);
    } else {
      smeter = 511;
    }
  }

  smeter = int16_t(sval);
  SStatus = SAvg / 10;
  SNR = SAvg2 / 10;

  if (showrdsinfo == false) {
    if (USN < 250 && WAM < 250 && OStatus > -250 && OStatus < 250) {
      if (SNR > (SNRold + 1) || SNR < (SNRold - 1)) {
        if (SNR < SStatus / 10) Display.writeNum("SNR.val", SNR);
        if (cnvis == false) {
          Display.writeStr("vis SNR,1");
          Display.writeStr("vis t12,1");
          Display.writeStr("vis t13,1");
        }
        SNRold = SNR;
        cnvis = true;
      }
    } else {
      if (cnvis == true) {
        Display.writeNum("SNR.val", 0);
        Display.writeStr("vis SNR,0");
        Display.writeStr("vis t12,0");
        Display.writeStr("vis t13,0");
        SNRold = 0;
      }
      cnvis = false;
    }
    Display.writeNum("WAM.val", WAM / 5);
    Display.writeNum("USN.val", USN / 5);

    if ((SStatus > (SStatusold + 3) || SStatus < (SStatusold - 3)) || displayreset == true)
    {
      Display.writeNum("signal.val", SStatus / 10);
      analogWrite(SMETERPIN, smeter);
      if (SStatus < 0) {
        analogWrite(SMETERPIN, 0);
        String negative = String (SStatus % 10, DEC);
        Display.writeNum("signaldec.val", negative[1]);
      } else {
        Display.writeNum("signaldec.val", SStatus % 10);
      }
      SStatusold = SStatus;
      if (stationlist == 1 && wifienable == 2) {
        Udp.beginPacket(remoteip, 9030);
        Udp.print("from=TEF tuner " + showsoftwareversion + ";RcvLevel=");
        Udp.print(SStatus / 10);
        Udp.endPacket();
      }
    }
  }
}

void ShowStereoStatus()
{
  if (StereoToggle == true && band != 5)
  {
    Stereostatus = radio.getStereoStatus();
    if ((Stereostatus != Stereostatusold) || displayreset == true)
    {
      if (Stereostatus == true) Display.writeNum("stereo.pic", 9); else Display.writeNum("stereo.pic", 10);
      Stereostatusold = Stereostatus;
    }
  }
}

void ShowOffset()
{
  if (band == 5) {
    if (OStatus < -2)
    {
      if (OStatusold != 1)
      {
        Display.writeNum("tune_neg.pic", 14);
        delay(10);
        Display.writeNum("tuned.pic", 12);
        delay(10);
        Display.writeNum("tune_pos.pic", 6);
        delay(10);
        MStatus = 0;
        OStatusold = 1;
      }
    } else if (SQ == false && OStatus > -2 && OStatus < 2) {
      if (OStatusold != 2)
      {
        Display.writeNum("tune_neg.pic", 14);
        delay(10);
        Display.writeNum("tuned.pic", 7);
        delay(10);
        Display.writeNum("tune_pos.pic", 13);
        delay(10);
        OStatusold = 2;
      }
    } else if (OStatus > 2) {
      if (OStatusold != 3) {
        Display.writeNum("tune_neg.pic", 8);
        delay(10);
        Display.writeNum("tuned.pic", 12);
        delay(10);
        Display.writeNum("tune_pos.pic", 13);
        delay(10);
        MStatus = 0;
        OStatusold = 3;
      }
    } else {
      if (OStatusold != 4) {
        Display.writeNum("tune_neg.pic", 14);
        delay(10);
        Display.writeNum("tuned.pic", 12);
        delay(10);
        Display.writeNum("tune_pos.pic", 13);
        delay(10);
        MStatus = 0;
        OStatusold = 4;
      }
    }
  } else {
    if (OStatus < -250) {
      if (OStatusold != 1) {
        Display.writeNum("tune_neg.pic", 14);
        delay(10);
        Display.writeNum("tuned.pic", 12);
        delay(10);
        Display.writeNum("tune_pos.pic", 6);
        delay(10);
        MStatus = 0;
        OStatusold = 1;
      }
    } else if (USN < 250 && WAM < 250 && SQ == false && OStatus > -250 && OStatus < 250) {
      if (OStatusold != 2) {
        Display.writeNum("tune_neg.pic", 14);
        delay(10);
        Display.writeNum("tuned.pic", 7);
        delay(10);
        Display.writeNum("tune_pos.pic", 13);
        delay(10);
        OStatusold = 2;
      }
    } else if (OStatus > 250) {
      if (OStatusold != 3) {
        Display.writeNum("tune_neg.pic", 8);
        delay(10);
        Display.writeNum("tuned.pic", 12);
        delay(10);
        Display.writeNum("tune_pos.pic", 13);
        MStatus = 0;
        OStatusold = 3;
      }
    } else {
      if (OStatusold != 4) {
        Display.writeNum("tune_neg.pic", 14);
        delay(10);
        Display.writeNum("tuned.pic", 12);
        delay(10);
        Display.writeNum("tune_pos.pic", 13);
        delay(10);
        MStatus = 0;
        OStatusold = 4;
      }
    }
  }
  if (setoffset == false) ShowModLevel();
}

void ShowStepSize() {
  Display.writeNum("step001.pic", 37);
  Display.writeNum("step010.pic", 37);
  Display.writeNum("step100.pic", 37);
  Display.writeNum("step1000.pic", 37);

  if (stepsize == 1) Display.writeNum("step001.pic", 36);
  if (stepsize == 2) Display.writeNum("step010.pic", 36);
  if (stepsize == 3) Display.writeNum("step100.pic", 36);
  if (stepsize == 4) Display.writeNum("step1000.pic", 36);
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

void ShowTuneMode() {
  ShowStepSize();
  if (tunemode == 0) {
    Display.writeNum("autologo.pic", 20);
    Display.writeNum("manlogo.pic", 31);
    Display.writeNum("memlogo.pic", 24);
  }

  if (tunemode == 1) {
    Display.writeNum("autologo.pic", 21);
    Display.writeNum("manlogo.pic", 30);
    Display.writeNum("memlogo.pic", 24);
  }

  if (tunemode == 2) {
    Display.writeNum("autologo.pic", 20);
    Display.writeNum("manlogo.pic", 30);
    Display.writeNum("memlogo.pic", 25);
  }
}

void ShowBTstatus() {
  if (btconnect == true) Display.writeNum("BT.pic", 117); else Display.writeNum("BT.pic", 116);
}

void ShowUSBstatus() {
  if (USBstatus == true)
  {
    if (usblogo_on == false) {
      Display.writeNum("usblogo.pic", 34);
      usblogo_on = true;
      usblogo_off = false;
    }
  } else {
    if (usblogo_off == false) {
      Display.writeNum("usblogo.pic", 35);
      usblogo_on = false;
      usblogo_off = true;
    }
  }
}

void doFilter() {
  if (iMSEQ == 0) iMSEQ = 1;

  if (iMSEQ == 4) {
    iMSset = 0;
    EQset = 0;
    ShowiMS();
    ShowEQ();
    iMSEQ = 0;
  }
  if (iMSEQ == 3) {
    iMSset = 1;
    EQset = 0;
    ShowiMS();
    ShowEQ();
    iMSEQ = 4;
  }
  if (iMSEQ == 2) {
    iMSset = 0;
    EQset = 1;
    ShowiMS();
    ShowEQ();
    iMSEQ = 3;
  }
  if (iMSEQ == 1) {
    iMSset = 1;
    EQset = 1;
    ShowiMS();
    ShowEQ();
    iMSEQ = 2;
  }
  EEPROM.writeByte(44, iMSset);
  EEPROM.writeByte(45, EQset);
  EEPROM.commit();
}


void ButtonPress() {
  if (power == false) {
    if (seek == true) seek = false;

    if (menu == false) {
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(ROTARY_BUTTON) == LOW && counter - counterold <= 1000) counter = millis();

      if (counter - counterold < 1000) {
        if (tunemode == 0) doStepSize();

        if (tunemode == 2) {
          if (memorystore == false) {
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

void ShowiMS() {
  if (showrdsinfo == false) {
    if (iMSset == 0) {
      Display.writeNum("imslogo.pic", 29);
      radio.setiMS(1);
    } else {
      Display.writeNum("imslogo.pic", 28);
      radio.setiMS(0);
    }
  }
}

void ShowEQ() {
  if (showrdsinfo == false) {
    if (EQset == 0) {
      Display.writeNum("eqlogo.pic", 27);
      radio.setEQ(1);
    } else {
      Display.writeNum("eqlogo.pic", 26);
      radio.setEQ(0);
    }
  }
}

void RoundStep() {
  if (band == 0) {
    unsigned int freq = frequency0;
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
  }
  if (band == 1) {
    unsigned int freq = frequency1;
    if (freq % 10 < 3) {
      frequency1 = (freq - freq % 10);
    }
    else if (freq % 10 > 2 && freq % 10 < 8) {
      frequency1 = (freq - (freq % 10 - 5));
    }
    else if (freq % 10 > 7) {
      frequency1 = (freq - (freq % 10) + 10);
    }
    Frontend.SetFreq(frequency1 - IF * 100, offset);
  }
  if (band == 2) {
    unsigned int freq = frequency2;
    if (freq % 10 < 3) {
      frequency2 = (freq - freq % 10);
    }
    else if (freq % 10 > 2 && freq % 10 < 8) {
      frequency2 = (freq - (freq % 10 - 5));
    }
    else if (freq % 10 > 7) {
      frequency2 = (freq - (freq % 10) + 10);
    }
    Frontend.SetFreq(frequency2 - IF * 100, offset);
  }
  if (band == 3) {
    unsigned int freq = frequency3;
    if (freq % 10 < 3) {
      frequency3 = (freq - freq % 10);
    }
    else if (freq % 10 > 2 && freq % 10 < 8) {
      frequency3 = (freq - (freq % 10 - 5));
    }
    else if (freq % 10 > 7) {
      frequency3 = (freq - (freq % 10) + 10);
    }
    Frontend.SetFreq(frequency3 - IF * 100, offset);
  }
  if (band == 4) {
    unsigned int freq = frequency4;
    if (freq % 10 < 3) {
      frequency4 = (freq - freq % 10);
    }
    else if (freq % 10 > 2 && freq % 10 < 8) {
      frequency4 = (freq - (freq % 10 - 5));
    }
    else if (freq % 10 > 7) {
      frequency4 = (freq - (freq % 10) + 10);
    }
    Frontend.SetFreq(frequency4 - IF * 100, offset);
  }
  if (band == 5) {
    unsigned int freq = frequency5 / 9;
    frequency5 = freq * 9;
    radio.SetFreqAM(frequency5);
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
  if (power == false) {
    if (menu == false) {
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(MODEBUTTON) == LOW && counter - counterold <= 1000) {
        counter = millis();
      }
      if (counter - counterold <= 1000) {
        if (seek == true) seek = false;
        if (band == 5 && tunemode == 0) tunemode = 1;
        doTuneMode();
      } else {
        if (XDRGTKTCP == false && XDRGTK == false && wificonnect == false && manfreq == false && spec == false) {
          if (RDSSpy == true)
          {
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
  if (power == false) {
    if (seek == true) seek = false;

    if (menu == false) {
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
  if (power == false) {
    if (menu == false) {
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
      if (XDRGTK == true) {
        if (band == 5) Serial.print("T" + String(frequency5) + "\n"); else Serial.print("T" + String(frequency0 * 10) + "\n");
      }

      if (XDRGTKTCP == true) {
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
  if (power == false) {
    if (menu == false) {
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
      if (XDRGTK == true) {
        if (band == 5) Serial.print("T" + String(frequency5) + "\n"); else Serial.print("T" + String(frequency0 * 10) + "\n");
      }

      if (XDRGTKTCP == true) {
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
  if (memorystore == false) {
    if (memory[memory_pos] >= LowEdgeSet0 * 100 && memory[memory_pos] <= HighEdgeSet0 * 100) {
      frequency0 = memory[memory_pos];
      RF(0);
      band = 0;
    } else if (UHF == true && memory[memory_pos] >= LowEdgeSet1 * 100 && memory[memory_pos] <= HighEdgeSet1 * 100) {
      frequency1 = memory[memory_pos];
      RF(1);
      band = 1;
    } else if (UHF == true && memory[memory_pos] >= LowEdgeSet2 * 100 && memory[memory_pos] <= HighEdgeSet2 * 100) {
      frequency2 = memory[memory_pos];
      RF(2);
      band = 2;
    } else if (UHF == true && memory[memory_pos] >= LowEdgeSet3 * 100 && memory[memory_pos] <= HighEdgeSet3 * 100) {
      frequency3 = memory[memory_pos];
      RF(3);
      band = 3;
    } else if (UHF == true && memory[memory_pos] >= LowEdgeSet4 * 100 && memory[memory_pos] <= HighEdgeSet4 * 100) {
      frequency4 = memory[memory_pos];
      RF(4);
      band = 4;
    } else if (UHF == false && memory[memory_pos] >= LowEdgeSet6 * 100 && memory[memory_pos] <= HighEdgeSet6 * 100) {
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
      if (spec == false) Display.writeNum("outlimit.en", 1);
    }
  }
  store = true;
  radio.clearRDS(fullsearchrds);
}

void trigger1() {
  doStereoToggle();
}

void trigger2() {
  BWset++;
  doBW();
  ShowBW();
}

void trigger3() {
  doFilter();
}

void trigger4() {
  BandSet();
}

void trigger5() {
  Display.writeStr("page 2");
  manfreq = true;
}

void trigger6() {
  doTuneMode();
}

void trigger7() {
  spec = true;
  Display.writeStr("page 3");
  BuildScanScreen();
}

void trigger8() {
  bool failed = false;
  freqtemp = Display.readNumber("freqresult.val");

  if (freqtemp >= LowEdgeSet0 * 100 && freqtemp <= HighEdgeSet0 * 100) {
    frequency0 = freqtemp;
    RF(0);
    band = 0;
  } else if (UHF == true && freqtemp >= LowEdgeSet1 * 100 && freqtemp <= HighEdgeSet1 * 100) {
    frequency1 = freqtemp;
    RF(1);
    band = 1;
  } else if (UHF == true && freqtemp >= LowEdgeSet2 * 100 && freqtemp <= HighEdgeSet2 * 100) {
    frequency2 = freqtemp;
    RF(2);
    band = 2;
  } else if (UHF == true && freqtemp >= LowEdgeSet3 * 100 && freqtemp <= HighEdgeSet3 * 100) {
    frequency3 = freqtemp;
    RF(3);
    band = 3;
  } else if (UHF == true && freqtemp >= LowEdgeSet4 * 100 && freqtemp <= HighEdgeSet4 * 100) {
    frequency4 = freqtemp;
    RF(4);
    band = 4;
  } else if (UHF == false && freqtemp >= LowEdgeSet6 * 100 && freqtemp <= HighEdgeSet6 * 100) {
    frequency6 = freqtemp;
    RF(6);
    band = 6;
  } else if (freqtemp >= 14 && freqtemp <= 2700) {
    frequency5 = freqtemp * 10;
    if (frequency5 < 144) frequency5 = 144;
    RF(5);
    band = 5;
  } else {
    Display.writeStr("vis outofrange,1");
    delay(1000);
    Display.writeStr("page 2");
    failed = true;
  }
  if (failed == false) {
    EEPROM.writeByte(46, band);
    EEPROM.commit();
    doExit();
  }
}

void trigger9() {
  Display.writeNum("freqresult.val", 0);
  Display.writeNum("fcount", 0);
  doExit();
}

void trigger10() { // Menu afsluiten met opslaan
  Display.writeNum("b0.pic", 123);
  Display.writeNum("b1.pic", 127);
  Display.writeNum("b2.pic", 129);
  Display.writeNum("b3.pic", 125);
  Display.writeNum("b4.pic", 131);
  Display.writeNum("b5.pic", 133);
  Display.writeStr("tsw b0,0");
  Display.writeStr("tsw b1,0");
  Display.writeStr("tsw b2,0");
  Display.writeStr("tsw b3,0");
  Display.writeStr("tsw b4,0");
  Display.writeStr("tsw b5,0");
  delay(200);

  LowEdgeSet0 = Display.readNumber("l0");
  delay(50);

  LowEdgeSet1 = Display.readNumber("l1");
  delay(50);

  LowEdgeSet2 = Display.readNumber("l2");
  delay(50);

  LowEdgeSet3 = Display.readNumber("l3");
  delay(50);

  LowEdgeSet4 = Display.readNumber("l4"); delay(350);
  delay(50);

  LowEdgeSet6 = Display.readNumber("l6");
  delay(50);

  HighEdgeSet0 = Display.readNumber("h0");
  delay(50);

  HighEdgeSet1 = Display.readNumber("h1");
  delay(50);

  HighEdgeSet2 = Display.readNumber("h2");
  delay(50);

  HighEdgeSet3 = Display.readNumber("h3");
  delay(50);

  HighEdgeSet4 = Display.readNumber("h4");
  delay(50);

  HighEdgeSet6 = Display.readNumber("h6");
  delay(50);

  LevelOffset0 = Display.readNumber("o0") - 25;
  delay(50);

  LevelOffset1 = Display.readNumber("o1") - 25;
  delay(50);

  LevelOffset2 = Display.readNumber("o2") - 25;
  delay(50);

  LevelOffset3 = Display.readNumber("o3") - 25;
  delay(50);

  LevelOffset4 = Display.readNumber("o4") - 25;
  delay(50);

  LevelOffset6 = Display.readNumber("o6") - 25;
  delay(50);

  IF = Display.readNumber("iffreq");
  delay(50);

  converteroffset = Display.readNumber("converterlo");
  delay(50);

  lf = Display.readNumber("lf");
  delay(50);

  demp = Display.readNumber("demp");
  delay(50);

  usbmode = Display.readNumber("usbmode");
  delay(50);

  wifienable = Display.readNumber("wifienable");
  delay(50);

  ip1 = Display.readNumber("pcip1");
  delay(50);

  ip2 = Display.readNumber("pcip2");
  delay(50);

  ip3 = Display.readNumber("pcip3");
  delay(50);

  ip4 = Display.readNumber("pcip4");
  delay(50);

  stationlist = Display.readNumber("stationlog");
  delay(50);

  VolSet = Display.readNumber("Volset") - 15;
  delay(50);

  ContrastSet = Display.readNumber("dim");
  delay(50);

  StereoLevel = Display.readNumber("StereoLevel");
  delay(50);

  HighCutLevel = Display.readNumber("HighCutLevel") / 100;
  delay(50);

  HighCutOffset = Display.readNumber("HighCutOffset");
  delay(50);

  BlendLevel = Display.readNumber("BlendLevel") / 100;
  delay(50);

  BlendOffset = Display.readNumber("BlendOffset");
  delay(50);

  NBLevel = Display.readNumber("NBLevel");
  delay(50);

  AM_Cochannel = Display.readNumber("AMcochannel");
  delay(50);

  AM_NBLevel = Display.readNumber("AMnb");
  delay(50);

  AM_att = Display.readNumber("AMatt");
  delay(50);

  fm = Display.readNumber("fm");
  delay(50);

  am = Display.readNumber("am");
  delay(50);

  uhf1 = Display.readNumber("uhf1");
  delay(50);

  uhf2 = Display.readNumber("uhf2");
  delay(50);

  uhf3 = Display.readNumber("uhf3");
  delay(50);

  uhf4 = Display.readNumber("uhf4");
  delay(50);

  uhf6 = Display.readNumber("uhf6");
  delay(50);

  coaxmode = Display.readNumber("coaxmode");
  delay(50);

  fmsi = Display.readNumber("fmsi");
  delay(50);

  fmsi_attack = Display.readNumber("fmsiattack");
  delay(50);

  fmsi_release = Display.readNumber("fmsirelease");
  delay(50);

  fmsi_11 = Display.readNumber("b1sens");
  delay(50);

  fmsi_12 = Display.readNumber("b1bias");
  delay(50);

  fmsi_21 = Display.readNumber("b2sens");
  delay(50);

  fmsi_22 = Display.readNumber("b2bias");
  delay(50);

  fmsi_31 = Display.readNumber("b3sens");
  delay(50);

  fmsi_32 = Display.readNumber("b3bias");
  delay(50);

  fmsi_41 = Display.readNumber("b4sens");
  delay(50);

  fmsi_42 = Display.readNumber("b4bias");
  delay(50);

  scanner_start = Display.readNumber("sstart") * 100;
  delay(50);

  scanner_end = Display.readNumber("sstop") * 100;
  delay(50);

  scanner_band = Display.readNumber("sband");
  delay(50);

  softmutefm = Display.readNumber("softmutefm");
  delay(50);

  softmuteam = Display.readNumber("softmuteam");
  delay(50);

  showrdserrors = Display.readNumber("showrdserrors");
  delay(50);

  EEPROM.writeByte(11, scanner_band);
  EEPROM.writeInt(20, ContrastSet);
  EEPROM.writeInt(4, VolSet);
  EEPROM.writeInt(28, StereoLevel);
  EEPROM.writeInt(32, HighCutLevel);
  EEPROM.writeInt(36, HighCutOffset);
  EEPROM.writeInt(12, LowEdgeSet0);
  EEPROM.writeInt(51, LowEdgeSet1);
  EEPROM.writeInt(59, LowEdgeSet2);
  EEPROM.writeInt(67, LowEdgeSet3);
  EEPROM.writeInt(75, LowEdgeSet4);
  EEPROM.writeInt(16, HighEdgeSet0);
  EEPROM.writeInt(55, HighEdgeSet1);
  EEPROM.writeInt(63, HighEdgeSet2);
  EEPROM.writeInt(71, HighEdgeSet3);
  EEPROM.writeInt(79, HighEdgeSet4);
  EEPROM.writeInt(24, LevelOffset0);
  EEPROM.writeInt(117, LevelOffset1);
  EEPROM.writeInt(121, LevelOffset2);
  EEPROM.writeInt(125, LevelOffset3);
  EEPROM.writeInt(129, LevelOffset4);
  EEPROM.writeByte(47, IF);
  EEPROM.writeByte(8, lf);
  EEPROM.writeByte(9, demp);
  EEPROM.writeByte(48, usbmode);
  EEPROM.writeByte(49, wifienable);
  EEPROM.writeString(134, password);
  EEPROM.writeByte(140, ip1);
  EEPROM.writeByte(141, ip2);
  EEPROM.writeByte(142, ip3);
  EEPROM.writeByte(143, ip4);
  EEPROM.writeByte(43, stationlist);
  EEPROM.writeInt(144, BlendLevel);
  EEPROM.writeInt(148, BlendOffset);
  EEPROM.writeInt(152, NBLevel);
  EEPROM.writeInt(164, AM_Cochannel);
  EEPROM.writeInt(168, AM_NBLevel);
  EEPROM.writeInt(172, AM_att);
  EEPROM.writeByte(176, am);
  EEPROM.writeByte(177, fm);
  EEPROM.writeByte(178, uhf1);
  EEPROM.writeByte(179, uhf2);
  EEPROM.writeByte(180, uhf3);
  EEPROM.writeByte(181, uhf4);
  EEPROM.writeByte(182, coaxmode);
  EEPROM.writeByte(185, fmsi);
  EEPROM.writeUInt(187, fmsi_attack);
  EEPROM.writeUInt(191, fmsi_release);
  EEPROM.writeUInt(195, fmsi_11);
  EEPROM.writeUInt(199, fmsi_12);
  EEPROM.writeUInt(203, fmsi_21);
  EEPROM.writeUInt(207, fmsi_22);
  EEPROM.writeUInt(211, fmsi_31);
  EEPROM.writeUInt(215, fmsi_32);
  EEPROM.writeUInt(219, fmsi_41);
  EEPROM.writeUInt(223, fmsi_42);
  EEPROM.writeByte(351, uhf6);
  EEPROM.writeInt(352, LevelOffset6);
  EEPROM.writeInt(356, LowEdgeSet6);
  EEPROM.writeInt(360, HighEdgeSet6);
  EEPROM.writeUInt(368, converteroffset);
  EEPROM.writeUInt(99, scanner_start);
  EEPROM.writeUInt(103, scanner_end);
  EEPROM.writeByte(377, softmutefm);
  EEPROM.writeByte(378, softmuteam);
  EEPROM.writeByte(378, showrdserrors);
  EEPROM.commit();

  remoteip = IPAddress (ip1, ip2, ip3, ip4);

  if (wifienable == 2) {
    Udp.stop();
    if (stationlist == 1) Udp.begin(9031);
  }

  Serial.end();
  if (usbmode == 1) Serial.begin(19200); else Serial.begin(115200);

  if (band == 0) {
    radio.setOffset(LevelOffset0);
  } else if (band == 1) {
    radio.setOffset(LevelOffset1);
    radio.SetFreq(IF * 100);
  } else if (band == 2) {
    radio.setOffset(LevelOffset2);
    radio.SetFreq(IF * 100);
  } else if (band == 3) {
    radio.setOffset(LevelOffset3);
    radio.SetFreq(IF * 100);
  } else if (band == 4) {
    radio.setOffset(LevelOffset4);
    radio.SetFreq(IF * 100);
  } else if (band == 6) {
    radio.setOffset(LevelOffset6);
  }

  doExit();
}

void trigger11() { // Menu afsluiten zonder opslaan
  Display.writeNum("b0.pic", 123);
  Display.writeNum("b1.pic", 127);
  Display.writeNum("b2.pic", 129);
  Display.writeNum("b3.pic", 125);
  Display.writeNum("b4.pic", 131);
  Display.writeNum("b5.pic", 133);
  Display.writeStr("tsw b0, 0");
  Display.writeStr("tsw b1, 0");
  Display.writeStr("tsw b2, 0");
  Display.writeStr("tsw b3, 0");
  Display.writeStr("tsw b4, 0");
  Display.writeStr("tsw b5, 0");

  EEpromReadData();
  radio.setVolume(VolSet);
  radio.setDeemphasis(demp);
  radio.setAudio(lf);
  trigger17();
  doExit();
}

void trigger12() { // Menu oude volume terugzetten
  radio.setVolume(VolSet);
  radio.setDeemphasis(demp);
  radio.setAudio(lf);
  Display.writeNum("demp", demp);
  Display.writeNum("lf", lf);
  Display.writeNum("Volset", VolSet + 15);
}

void trigger13() { // Nieuwe volume waarde toepassen
  radio.setVolume(Display.readNumber("slider.val") - 15);
}

void trigger14() { // Nieuwe waarde high cut offset waarde (Hz) toepassen
  radio.setHighCutLevel(Display.readNumber("slider2.val") / 100);
}

void trigger15() { // Nieuwe waarde high cut threshold toepassen
  radio.setHighCutOffset(Display.readNumber("slider3.val"));
}

void trigger16() { // Nieuwe waarde stereo sep. threshold toepassen
  radio.setStereoLevel(Display.readNumber("slider.val"));
}

void trigger17() { // oude waarde DSP terugzetten
  radio.setHighCutLevel(HighCutLevel);
  radio.setHighCutOffset(HighCutOffset);
  radio.setStereoLevel(StereoLevel);
  radio.setStHiBlendLevel(BlendLevel);
  radio.setStHiBlendOffset(BlendOffset);
  radio.setFMNoiseBlanker(NBLevel);
  radio.setAMNoiseBlanker(AM_NBLevel);
  radio.setAMAttenuation(AM_att);
  radio.setAMCoChannel(AM_Cochannel);
  radio.setFMSI(fmsi);
  radio.setFMSI_Time(fmsi_attack, fmsi_release);
  radio.setFMSI_Gain(fmsi_11, fmsi_21, fmsi_31, fmsi_41);
  radio.setFMSI_Bias(fmsi_12, fmsi_22, fmsi_32, fmsi_42);
  radio.setSoftmuteFM(softmutefm);
  radio.setSoftmuteAM(softmuteam);
}

void trigger18() { // de-emphasis instellen
  radio.setDeemphasis(Display.readNumber("demp"));
}

void trigger19() { // Audio mode instellen
  radio.setAudio(Display.readNumber("lf"));
}

void trigger20() { // Open Wifi config pagina geopend, vul wifi status in...
  wifienableold = wifienable;
  if (wifienable == 2) {
    String ssid = String(WiFi.SSID());
    Display.writeStr("IP.txt", WiFi.localIP().toString());
    Display.writeStr("SSID.txt", ssid);
    Display.writeNum("p1.pic", 183);
    Display.writeStr("password.txt", password);
  } else {
    Display.writeStr("SSID.txt", "DISCONNECTED");
    Display.writeNum("p1.pic", 175);
  }
}

void trigger21() { // Wifi connect pagina geopend, vul SSID AP in....
  String ssid = "ESP_" + String(ESP_getChipId());
  String WifiAP = String ("WIFI:T:nopass;S:" + ssid + ";P:;H:;");
  Display.writeStr("qr.txt", WifiAP);
  String SSID_AP = String ("SSID: " + ssid);
  Display.writeStr("SSID_AP.txt", SSID_AP);
  wc.startConfigurationPortal(AP_WAIT);
  ESP.restart();
}

void trigger22() { // Enable/disable WiFi
  wifienable++;
  if (wifienable == 3) wifienable = 1;
  if (wifienable == 1) {
    Display.writeNum("p1.pic", 175);
    Server.end();
    Udp.stop();
    WiFi.mode(WIFI_OFF);
    Display.writeNum("wifienable", wifienable);
    Display.writeStr("IP.txt", "");
    Display.writeStr("SSID.txt", "DISCONNECTED");
    Display.writeStr("password.txt", "");
  } else if (wifienable == 2) {
    Display.writeNum("p1.pic", 184);
    Display.writeNum("wifienable", wifienable);
    Display.writeStr("SSID.txt", "Connecting.....");
    WiFi.begin();
    if (wc.autoConnect()) {
      Server.begin();
      Udp.begin(9031);
      String ssid = String(WiFi.SSID());
      Display.writeStr("IP.txt", WiFi.localIP().toString());
      Display.writeStr("SSID.txt", ssid);
      Display.writeStr("password.txt", password);
      Display.writeNum("p1.pic", 183);
    } else {
      Display.writeStr("page 10");
      trigger21();
    }
  }
}

void trigger23() {
  passwordgenerator();
  Display.writeStr("password.txt", password);
}

void trigger24() {
  // Open RDS info
  Display.writeStr("page 12");
  displayreset = true;
  showrdsinfo = true;
  OStatusold = 0;
  delay(200);
  ShowFreq();
  delay(300);
  ShowBW();
  ShowStereoStatus();
  ShowOffset();
  ShowStepSize();
  ShowTuneMode();
  ShowUSBstatus();
  ShowBTstatus();
  ctshow = false;
  radio.clearRDS(fullsearchrds);
  if (wificonnect == true) Display.writeNum("tm2.en", 1);
}

void trigger25() {
  // Sluit RDS info
  showrdsinfo = false;
  doExit();
  if (wificonnect == true) Display.writeNum("tm2.en", 1);
}

void trigger26() {
  btsetup = true;
  btconnect = false;
  swSer.print("AT+DISCON");
  delay(250);
  swSer.print("AT+REST");
}

void trigger27() {
  btsetup = false;
}

void trigger28() {
  radio.setStHiBlendLevel(Display.readNumber("slider2.val") / 100);
}

void trigger29() {
  radio.setStHiBlendOffset(Display.readNumber("slider3.val"));
}

void trigger30() {
  radio.setFMNoiseBlanker(Display.readNumber("slider.val"));
}

void trigger31() { // Set AM noise blanker
  radio.setAMNoiseBlanker(Display.readNumber("slider2.val"));
}

void trigger32() { // AM att
  radio.setAMAttenuation(Display.readNumber("slider3.val"));
}

void trigger33() { // Set cochannel
  radio.setAMCoChannel(Display.readNumber("slider.val"));
}

void trigger34() { // Set fmsi
  radio.setFMSI(Display.readNumber("fmsi"));
}

void trigger35() { // Set FMSI attack/release
  radio.setFMSI_Time(Display.readNumber("slider.val"), Display.readNumber("slider2.val"));
}

void trigger36() { // Set FMSI bands
  radio.setFMSI_Gain(Display.readNumber("b1sens"), Display.readNumber("b2sens"), Display.readNumber("b3sens"), Display.readNumber("b4sens"));
  radio.setFMSI_Bias(Display.readNumber("b1bias"), Display.readNumber("b2bias"), Display.readNumber("b3bias"), Display.readNumber("b4bias"));
}

void trigger37() {
  scopeview = Display.readNumber("scopeview");
  EEPROM.writeByte(186, scopeview);
  EEPROM.commit();
}

void trigger38() {
  OStatusold = 0;
  setoffset = true;
  Display.writeStr("tm1.en=0");
  offset = Display.readNumber("offsetkhz.val");
  Frontend.SetFreq(freq - (IF * 100), offset);
}

void trigger39() {
  setoffset = false;
  int x;
  offset = Display.readNumber("looffset");
  EEPROM.writeInt(372, offset);
  EEPROM.commit();
  doExit();
}

void trigger40() {
  wifiretry = false;
  tryWiFi();
}

void trigger41() {
  WiFi.mode(WIFI_OFF);
  wifienable = 1;
  EEPROM.writeByte(49, 1);
  EEPROM.commit();
  wifiretry = false;
}

void trigger42() {
  radio.setSoftmuteFM(Display.readNumber("softmutefm"));
  radio.setSoftmuteAM(Display.readNumber("softmuteam"));
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
  if (showrdsinfo == false) Display.writeStr("page 1"); else Display.writeStr("page 12");
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
    if (BWsetAM == 1) radio.setAMBandw(3);
    if (BWsetAM == 2) radio.setAMBandw(4);
    if (BWsetAM == 3) radio.setAMBandw(6);
    if (BWsetAM == 4) radio.setAMBandw(8);
  } else {
    if (BWset > 16) BWset = 0;
    ShowBW();
    BWreset = true;

    if (BWset == 1) radio.setFMBandw(56);
    if (BWset == 2) radio.setFMBandw(64);
    if (BWset == 3) radio.setFMBandw(72);
    if (BWset == 4) radio.setFMBandw(84);
    if (BWset == 5) radio.setFMBandw(97);
    if (BWset == 6) radio.setFMBandw(114);
    if (BWset == 7) radio.setFMBandw(133);
    if (BWset == 8) radio.setFMBandw(151);
    if (BWset == 9) radio.setFMBandw(168);
    if (BWset == 10) radio.setFMBandw(184);
    if (BWset == 11) radio.setFMBandw(200);
    if (BWset == 12) radio.setFMBandw(217);
    if (BWset == 13) radio.setFMBandw(236);
    if (BWset == 14) radio.setFMBandw(254);
    if (BWset == 15) radio.setFMBandw(287);
    if (BWset == 16) radio.setFMBandw(311);
  }
}

void doSquelch() {
  if (power == false) {
    if (XDRGTK == false && XDRGTKTCP == false) {
      Squelch = analogRead(PIN_POT) / 4 - 100;
      if (Squelch > 920) Squelch = 920;
      if (showrdsinfo == false && menu == false && Squelch != Squelchold) {
        if (Squelch == -100) {
          if (spec == false) Display.writeStr("SQ.txt", "OFF");
        } else if (Squelch == 920) {
          if (spec == false) Display.writeStr("SQ.txt", "ST");
        } else {
          String SQVAL = String(Squelch / 10);
          Display.writeStr("SQ.txt", SQVAL);
        }
        Squelchold = Squelch;
      }

    }
    if (XDRGTK == true || XDRGTKTCP == true) {
      if (XDRMute == false) {
        if (Squelch != -1) {
          if (seek == false && (Squelch == 0)) {
            if (mutestatus == true) {
              radio.setUnMute();
              mutestatus = false;
            }
            if (showrdsinfo == false) if (spec == false) Display.writeStr("SQ.txt", "OFF");
            SQ = false;
          } else if (seek == false && (Squelch < SStatus || Squelch == -100)) {
            if (mutestatus == true) {
              radio.setUnMute();
              mutestatus = false;
            }
            SQ = false;
          } else {
            if (mutestatus == false) {
              radio.setMute();
              mutestatus = true;
            }
            SQ = true;
          }
        } else {
          if (seek == false && Stereostatus == true) {
            if (mutestatus == true) {
              radio.setUnMute();
              mutestatus = false;
            }
            SQ = false;
          } else {
            if (mutestatus == false) {
              radio.setMute();
              mutestatus = true;
            }
            SQ = true;
          }
        }
        if (showrdsinfo == false) {
          if (Squelch != Squelchold) {
            if (Squelch == -1) {
              if (spec == false) Display.writeStr("SQ.txt", "ST");
            } else {
              String SQVAL = String(Squelch / 10);
              if (spec == false) Display.writeStr("SQ.txt", SQVAL);
            }
            Squelchold = Squelch;
          }
        }
      }
    } else {
      if (Squelch != 920) {
        if (seek == false && (Squelch < SStatus || Squelch == -100)) {
          if (mutestatus == true) {
            radio.setUnMute();
            mutestatus = false;
          }
          SQ = false;
        } else {
          if (mutestatus == false) {
            radio.setMute();
            mutestatus = true;
          }
          SQ = true;
        }
      } else {
        if (Stereostatus == true) {
          if (mutestatus == true) {
            radio.setUnMute();
            mutestatus = false;
          }
          SQ = false;
        } else {
          if (mutestatus == false) {
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

void ShowSquelch() {
  if (menu == false && spec == false) {
    if (SQ == false) {
      if (mutelogo_off == false) {
        Display.writeNum("mutelogo.pic", 32);
        mutelogo_off = true;
        mutelogo_on = false;
      }
    } else {
      if (mutelogo_on == false) {
        Display.writeNum("mutelogo.pic", 33);
        mutelogo_on = true;
        mutelogo_off = false;
      }
    }
  }
}

void doStereoToggle() {
  if (StereoToggle == true) {
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

void SpectrumAnalyser() {
  radio.setFMBandw(scanner_vbw);
  radio.setMute();
  RF(scanner_band);
  int scancounter = 20;
  if (displaysize == 35) {
    scancounter = 35;
    Display.writeStr("fill 35,286,222,3,BLACK");
  } else {
    Display.writeStr("fill 20,222,222,3,BLACK");
  }

  for (freq_scan = scanner_start; freq_scan <= scanner_end; freq_scan += (((scanner_end - scanner_start) / 100) / 2) * scanner_speed)
  {
    if (scanner_band == 0) {
      radio.SetFreq(freq_scan);
    } else if (scanner_band == 6) {
      radio.SetFreq(freq_scan - converteroffset * 100);
    } else {
      Frontend.SetFreq(freq_scan - (IF * 100), offset);
    }
    delay(20);

    radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);

    if (displaysize == 35) {
      for (int i = 1; i <= scanner_speed && scancounter < 236; i++) {
        scancounter++;
        if (SStatus < 0) SStatus = 5;
        String LevelString = "line " + String(scancounter, DEC) + ",284," + String(scancounter, DEC) + "," + String(284 - SStatus / 5, DEC) + ",65535";
        String LevelBlankString = "line " + String(scancounter, DEC) + ",84," + String(scancounter, DEC) + "," + String(284 - SStatus / 5, DEC) + ",BLACK";
        String LevelDot = "line " + String(scancounter, DEC) + ",286," + String(scancounter, DEC) + ",288,65504";
        Display.writeStr(LevelString);
        Display.writeStr(LevelBlankString);
        Display.writeStr(LevelDot);

        for (int dot = 284; dot >= 84; dot -= 20) {
          String DotString = "fill " + String(scancounter, DEC) + "," + String(dot, DEC) + ",2,2,33840";
          Display.writeStr(DotString);
        }

        for (int dot = 235; dot >= 20; dot -= 20) {
          String DotString = "fill " + String(dot, DEC) + ",84,2,201,33840";
          Display.writeStr(DotString);
        }
      }
    } else {
      for (int i = 1; i <= scanner_speed && scancounter < 221; i++) {
        scancounter++;
        if (SStatus < 0) SStatus = 5;
        String LevelString = "line " + String(scancounter, DEC) + ",220," + String(scancounter, DEC) + "," + String(220 - SStatus / 5, DEC) + ",65535";
        String LevelBlankString = "line " + String(scancounter, DEC) + ",1," + String(scancounter, DEC) + "," + String(219 - SStatus / 5, DEC) + ",BLACK";
        String LevelDot = "line " + String(scancounter, DEC) + "," + String(222, DEC) + "," + String(scancounter, DEC) + "," + String(224, DEC) + ",65504";
        Display.writeStr(LevelString);
        Display.writeStr(LevelBlankString);
        Display.writeStr(LevelDot);

        for (int dot = 220; dot >= 20; dot -= 20) {
          String DotString = "fill " + String(scancounter, DEC) + "," + String(dot, DEC) + ",2,2,33840";
          Display.writeStr(DotString);
        }

        for (int dot = 220; dot >= 20; dot -= 20) {
          String DotString = "fill " + String(dot, DEC) + ",20,2,201,33840";
          Display.writeStr(DotString);
        }
      }
    }
    if (scanner_thenable == 2 && scanfound == false && SStatus / 10 > scanner_th) {
      scanner_found = freq_scan - ((scanner_end - scanner_start) / 100) / 2;
      scanfound = true;
      Display.writeNum("scanstatus", 5);
    } else {
      donesearch = true;
    }
  }
}

void BuildScanScreen() {
  delay(200);
  Display.writeStr("tsw bstart,1");
  Display.writeStr("tsw bconfig,1");
  Display.writeStr("tsw bexit,1");
  Display.writeStr("tsw bstop,0");
  Display.writeNum("bstart.pic", 147);
  Display.writeNum("bconfig.pic", 151);
  Display.writeNum("bexit.pic", 153);
  Display.writeNum("bstop.pic", 150);
  String rbw = String(((((scanner_end - scanner_start) / 100) / 2) * 10) * scanner_speed, DEC) + " kHz";
  String vbw = String(scanner_vbw, DEC) + " kHz";
  String span = String((scanner_end - scanner_start) / 100, DEC) + " MHz";
  Display.writeStr("RBW.txt", rbw);
  Display.writeStr("VBW.txt", vbw);
  Display.writeStr("SPAN.txt", span);

  if (displaysize == 35) {
    for (int dot = 284; dot >= 84; dot -= 20)
    {
      String DotString = "fill 35," + String(dot, DEC) + ",201,2,33840";
      Display.writeStr(DotString);
    }
    for (int dot = 235; dot >= 20; dot -= 20)
    {
      String DotString = "fill " + String(dot, DEC) + ",84,2,201,33840";
      Display.writeStr(DotString);
    }
  } else {
    for (int dot = 220; dot >= 20; dot -= 20)
    {
      String DotString = "fill 20," + String(dot, DEC) + ",201,2,33840";
      Display.writeStr(DotString);
    }
    for (int dot = 220; dot >= 20; dot -= 20)
    {
      String DotString = "fill " + String(dot, DEC) + ",20,2,201,33840";
      Display.writeStr(DotString);
    }
  }
}

void scan_loop() {
  // Loop voor Spectrum Analyser
  if (millis() >= time_now + 2000) {
    time_now += 2000;
    scanstatus = Display.readNumber("scanstatus");
  }

  // // Afsluiten van configuratie, knoppen grijs, gegevens wel opgeslagen
  if (scanstatus == 2) {
    Display.writeStr("tsw b0,0");
    Display.writeStr("tsw b1,0");
    Display.writeStr("tsw b2,0");
    Display.writeStr("tsw b3,0");
    Display.writeNum("b0.pic", 159);
    delay(350);
    scanner_start = Display.readNumber("sstart") * 100;
    delay (50);
    scanner_end = Display.readNumber("sstop") * 100;
    delay (50);
    scanner_vbw = Display.readNumber("sbw");
    delay (50);
    scanner_th = Display.readNumber("scanthreshold.val");
    delay (50);
    scanner_band = Display.readNumber("sband");
    delay (50);
    scanner_speed = Display.readNumber("speed");
    delay (50);
    scanner_thenable = Display.readNumber("thenable");
    EEPROM.writeUInt(99, scanner_start);
    EEPROM.writeUInt(103, scanner_end);
    EEPROM.writeUInt(107, scanner_vbw);
    EEPROM.writeByte(10, scanner_th);
    EEPROM.writeByte(11, scanner_band);
    EEPROM.writeByte(40, scanner_speed);
    EEPROM.writeByte(113, scanner_thenable);
    EEPROM.commit();
    Display.writeStr("page 3");
    delay(25);
    scanstatus = Display.readNumber("scanstatus");
    BuildScanScreen();

    // Afsluiten van configuratie, knoppen grijs, gegevens niet opgeslagen
  } else if (scanstatus == 3 ) {
    Display.writeStr("tsw b0,0");
    Display.writeStr("tsw b1,0");
    Display.writeStr("tsw b2,0");
    Display.writeStr("tsw b3,0");
    Display.writeNum("b0.pic", 159);
    Display.writeStr("page 3");
    BuildScanScreen();

    // Indien op start wordt gedrukt de analyser starten totdat er op stop wordt gedrukt.
  } else if (scanstatus == 4) {
    Display.writeStr("vis scanner_found,0");
    if (displaysize == 35) {
      for (int dot = 284; dot >= 80; dot -= 20)
      {
        String DotString = "fill 35," + String(dot, DEC) + ",201,2,33840";
        Display.writeStr(DotString);
      }

      for (int dot = 235; dot >= 20; dot -= 20)
      {
        String DotString = "fill " + String(dot, DEC) + ",84,2,201,33840";
        Display.writeStr(DotString);
      }
    } else {
      for (int dot = 220; dot >= 20; dot -= 20)
      {
        String DotString = "fill 20," + String(dot, DEC) + ",201,2,33840";
        Display.writeStr(DotString);
      }

      for (int dot = 220; dot >= 20; dot -= 20)
      {
        String DotString = "fill " + String(dot, DEC) + ",20,2,201,33840";
        Display.writeStr(DotString);
      }
    }

    Display.writeStr("tsw bstop,1");
    Display.writeStr("tsw bconfig,0");
    Display.writeStr("tsw bexit,0");
    Display.writeStr("tsw bstart,0");
    Display.writeNum("bstop.pic", 149);
    Display.writeNum("bconfig.pic", 152);
    Display.writeNum("bexit.pic", 154);
    Display.writeNum("bstart.pic", 148);
    donesearch = false;
    SpectrumAnalyser();

  } else if (scanstatus == 5) {
    Display.writeStr("tsw bstart,1");
    Display.writeStr("tsw bconfig,1");
    Display.writeStr("tsw bexit,1");
    Display.writeStr("tsw bstop,0");
    Display.writeNum("bstart.pic", 147);
    Display.writeNum("bconfig.pic", 151);
    Display.writeNum("bexit.pic", 153);
    Display.writeNum("bstop.pic", 150);
    Display.writeStr("vis scanner_found,1");
    Display.writeNum("scanstatus", 0);
    if (scanfound == true) {
      if (scanner_band == 0)
      {
        radio.SetFreq(scanner_found);
      } else if (scanner_band == 6)
      {
        radio.SetFreq(scanner_found - converteroffset * 100);
      } else {
        radio.SetFreq(IF * 100);
        Frontend.SetFreq(scanner_found - (IF * 100), offset);
      }
      radio.setUnMute();
      radio.setFMABandw();
      donesearch = false;
      scanfound = false;
      Display.writeNum("scanner_found.val", scanner_found);
      String DotString;
      if (displaysize == 35) {
        Display.writeStr("fill 35,286,237,3,BLACK");
        DotString = "fill 35,286," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
      } else {
        Display.writeStr("fill 20,222,222,3,BLACK");
        DotString = "fill 20,222," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
      }
      Display.writeStr(DotString);
    }

    if (donesearch == true) {
      scanner_found = ((scanner_end - scanner_start) / 2) + scanner_start;
      if (scanner_band == 0) radio.SetFreq(scanner_found);
      if (scanner_band == 6) {
        radio.SetFreq(scanner_found - converteroffset * 100);
      } else {
        radio.SetFreq(IF * 100);
        Frontend.SetFreq(scanner_found - (IF * 100), offset);
      }

      radio.setUnMute();
      radio.setFMABandw();
      donesearch = false;
      Display.writeNum("scanner_found.val", scanner_found);
      String DotString;
      if (displaysize == 35) {
        Display.writeStr("fill 35,286,222,3,BLACK");
        DotString = "fill 35,286," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
      } else {
        Display.writeStr("fill 20,222,222,3,BLACK");
        DotString = "fill 20,222," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
      }
      Display.writeStr(DotString);
    } else {
      if (rotary == -1) scanup(); else scandown();

      if (digitalRead(ROTARY_BUTTON) == LOW) {
        freq = scanner_found;
        band = scanner_band;
        if (band == 0) frequency0 = freq;
        if (band == 1) frequency1 = freq;
        if (band == 2) frequency2 = freq;
        if (band == 3) frequency3 = freq;
        if (band == 4) frequency4 = freq;
        doExit();
        RoundStep();
      }
    }
    // Indien op exit wordt gedrukt de analyser afsluiten zonder af te stemmen
  } else if (scanstatus == 6) {
    spec = false;
    doExit();
  }
}

void scanup() {
  rotary = 0;
  scanner_found += (((scanner_end - scanner_start) / 100) / 2);
  if (scanner_found > scanner_end) scanner_found = scanner_start;

  if (scanner_band == 0)
  {
    radio.SetFreq(scanner_found);
  } else if (scanner_band == 6) {
    radio.SetFreq(scanner_found - converteroffset * 100);
  } else {
    Frontend.SetFreq(scanner_found - (IF * 100), offset);
  }
  String DotString;
  if (displaysize == 35) {
    Display.writeStr("fill 35,286,237,3,BLACK");
    DotString = "fill 35,286," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
  } else {
    Display.writeStr("fill 20,222,222,3,BLACK");
    DotString = "fill 20,222," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
  }
  Display.writeNum("scanner_found.val", scanner_found);
  Display.writeStr(DotString);
  time_now = millis();
}

void scandown() {
  rotary = 0;
  scanner_found -= (((scanner_end - scanner_start) / 100) / 2);
  if (scanner_found < scanner_start) scanner_found = scanner_end;

  if (scanner_band == 0) radio.SetFreq(scanner_found); else Frontend.SetFreq(scanner_found - (IF * 100), offset);
  String DotString;
  if (displaysize == 35) {
    Display.writeStr("fill 35,286,237,3,BLACK");
    DotString = "fill 35,286," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
  } else {
    Display.writeStr("fill 20,222,222,3,BLACK");
    DotString = "fill 20,222," + String((scanner_found - scanner_start) / (((scanner_end - scanner_start) / 100) / 2)) + ",2,65504";
  }
  Display.writeNum("scanner_found.val", scanner_found);
  Display.writeStr(DotString);
  time_now = millis();
  // Einde Spectrum analyser loop
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

  if (UHF == false && band != 0 && band != 5 && band != 6) {
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

void doEEpromWrite() {
  if (store == true) change++;

  if (change > 200 && store == true) {
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
  if (mode == false) TuneDown(); else TuneUp();
  delay(50);
  ShowFreq();
  if (XDRGTK == true) {
    if (band == 0) Serial.print("T" + String(frequency0 * 10) + "\n"); else Serial.print("T" + String(frequency5) + "\n");
  }

  if (XDRGTKTCP == true) {
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
  if (stepsize == 1) temp = 1;
  if (stepsize == 2) temp = 10;
  if (stepsize == 3) temp = 100;
  if (stepsize == 4) temp = 1000;

  if (band == 0) {
    frequency0 += temp;
    if (frequency0 >= (HighEdgeSet0 * 100) + 1) {
      frequency0 = LowEdgeSet0 * 100;
    }
    radio.SetFreq(frequency0);
  }
  if (band == 1) {
    frequency1 += temp;
    if (frequency1 >= (HighEdgeSet1 * 100) + 1) {
      frequency1 = LowEdgeSet1 * 100;
    }
    Frontend.SetFreq(frequency1 - (IF * 100), offset);
  }
  if (band == 2) {
    frequency2 += temp;
    if (frequency2 >= (HighEdgeSet2 * 100) + 1) {
      frequency2 = LowEdgeSet2 * 100;
    }
    Frontend.SetFreq(frequency2 - (IF * 100), offset);
  }
  if (band == 3) {
    frequency3 += temp;
    if (frequency3 >= (HighEdgeSet3 * 100) + 1) {
      frequency3 = LowEdgeSet3 * 100;
    }
    Frontend.SetFreq(frequency3 - (IF * 100), offset);
  }
  if (band == 4) {
    frequency4 += temp;
    if (frequency4 >= (HighEdgeSet4 * 100) + 1) {
      frequency4 = LowEdgeSet4 * 100;
    }
    Frontend.SetFreq(frequency4 - (IF * 100), offset);
  }
  if (band == 5) {
    frequency5 += temp;
    if (frequency5 > 27000) {
      frequency5 = 144;
    }
    radio.SetFreqAM(frequency5);
  }
  if (band == 6) {
    frequency6 += temp;
    if (frequency6 >= (HighEdgeSet6 * 100) + 1) {
      frequency6 = LowEdgeSet6 * 100;
    }
    radio.SetFreq(frequency6 - converteroffset * 100);
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
  if (stepsize == 1) temp = 1;
  if (stepsize == 2) temp = 10;
  if (stepsize == 3) temp = 100;
  if (stepsize == 4) temp = 1000;

  if (band == 0) {
    frequency0 -= temp;
    if (frequency0 < LowEdgeSet0 * 100) frequency0 = HighEdgeSet0 * 100;
    radio.SetFreq(frequency0);
  }

  if (band == 1) {
    frequency1 -= temp;
    if (frequency1 < LowEdgeSet1 * 100) frequency1 = HighEdgeSet1 * 100;
    Frontend.SetFreq(frequency1 - (IF * 100), offset);
  }

  if (band == 2) {
    frequency2 -= temp;
    if (frequency2 < LowEdgeSet2 * 100) frequency2 = HighEdgeSet2 * 100;
    Frontend.SetFreq(frequency2 - (IF * 100), offset);
  }

  if (band == 3) {
    frequency3 -= temp;
    if (frequency3 < LowEdgeSet3 * 100) frequency3 = HighEdgeSet3 * 100;
    Frontend.SetFreq(frequency3 - (IF * 100), offset);
  }

  if (band == 4) {
    frequency4 -= temp;
    if (frequency4 < LowEdgeSet4 * 100) frequency4 = HighEdgeSet4 * 100;
    Frontend.SetFreq(frequency4 - (IF * 100), offset);
  }

  if (band == 5) {
    if (temp == 1000 && frequency5 <= 1440)
    {
      frequency5 = 27000;
    } else {
      frequency5 -= temp;
      if (frequency5 < 144) frequency5 = 27000;
    }
    radio.SetFreqAM(frequency5);
  }

  if (band == 6) {
    frequency6 -= temp;
    if (frequency6 < LowEdgeSet6 * 100) frequency6 = HighEdgeSet6 * 100;
    radio.SetFreq(frequency6 - converteroffset * 100);
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
  while (true);
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
    if (stationlist == 1) Udp.begin(9031);
  } else {
    wifiretry = true;
    Display.writeStr("page 26");
    while (wifiretry == true) Display.NextionListen();
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

  if (optrot == 1) {
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
