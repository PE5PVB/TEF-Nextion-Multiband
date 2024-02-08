#ifndef TOUCH_CPP
#define TOUCH_CPP

#include "touch.h"
#include "constants.h"

void trigger1(void) { // Stereotoggle
  doStereoToggle();
}

void trigger2(void) { // Change Bandwidth
  BWset++;
  doBW();
  ShowBW();
}

void trigger3(void) { // Change iMS/EQ
  doFilter();
}

void trigger4(void) { // Set band
  BandSet();
}

void trigger5(void) { // User manual tuning input
  Display.writeStr("page 2");
  manfreq = true;
}

void trigger6(void) { // Change tuningmode
  doTuneMode();
}

void trigger7(void) { // Start spectrumanalyser
  spec = true;
  Display.writeStr("page 3");
  BuildScanScreen();
}

void trigger8(void) { // Check User manual tuning input
  bool failed = false;
  freqtemp = Display.readNumber("freqresult.val");
  delay(50);

  if (freqtemp >= LowEdgeSet0 * 100 && freqtemp <= HighEdgeSet0 * 100) {
    frequency0 = freqtemp;
    RF(0);
    band = 0;
  } else if (UHF && freqtemp >= LowEdgeSet1 * 100 && freqtemp <= HighEdgeSet1 * 100) {
    frequency1 = freqtemp;
    RF(1);
    band = 1;
  } else if (UHF && freqtemp >= LowEdgeSet2 * 100 && freqtemp <= HighEdgeSet2 * 100) {
    frequency2 = freqtemp;
    RF(2);
    band = 2;
  } else if (UHF && freqtemp >= LowEdgeSet3 * 100 && freqtemp <= HighEdgeSet3 * 100) {
    frequency3 = freqtemp;
    RF(3);
    band = 3;
  } else if (UHF && freqtemp >= LowEdgeSet4 * 100 && freqtemp <= HighEdgeSet4 * 100) {
    frequency4 = freqtemp;
    RF(4);
    band = 4;
  } else if (!UHF && freqtemp >= LowEdgeSet6 * 100 && freqtemp <= HighEdgeSet6 * 100) {
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
  if (!failed) {
    EEPROM.writeByte(EE_UINT8T_BAND, band);
    EEPROM.commit();
    doExit();
  }
}

void trigger9(void) { // Cancel User manual tuning input
  Display.writeNum("freqresult.val", 0);
  Display.writeNum("fcount", 0);
  doExit();
}

void trigger10(void) { // Close and save menu
  Display.writeNum("b0.pic", NEXTION_BUT_AUDIO15065_GREYOUT);
  Display.writeNum("b1.pic", NEXTION_BUT_DSP15065_GREYOUT);
  Display.writeNum("b2.pic", NEXTION_BUT_SYSTEM15065_GREYOUT);
  Display.writeNum("b3.pic", NEXTION_BUT_RF15065_GREYOUT);
  Display.writeNum("b4.pic", NEXTION_BUT_OK15065_GREYOUT);
  Display.writeNum("b5.pic", NEXTION_BUT_CANCEL15065_GREYOUT);
  Display.writeStr("tsw b0,0");
  Display.writeStr("tsw b1,0");
  Display.writeStr("tsw b2,0");
  Display.writeStr("tsw b3,0");
  Display.writeStr("tsw b4,0");
  Display.writeStr("tsw b5,0");
  delay(50);

  LowEdgeSet0 = Display.readNumber("l0");
  delay(50);
  LowEdgeSet1 = Display.readNumber("l1");
  delay(50);
  LowEdgeSet2 = Display.readNumber("l2");
  delay(50);
  LowEdgeSet3 = Display.readNumber("l3");
  delay(50);
  LowEdgeSet4 = Display.readNumber("l4");
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

  EEPROM.writeByte(EE_UINT8T_SCANNERBAND, scanner_band);
  EEPROM.writeInt(EE_INT16T_CONTRAST, ContrastSet);
  EEPROM.writeInt(EE_INT16T_VOLSET, VolSet);
  EEPROM.writeInt(EE_INT16T_STEREOLEVEL, StereoLevel);
  EEPROM.writeInt(EE_INT16T_HIGHCUTLEVEL, HighCutLevel);
  EEPROM.writeInt(EE_INT16T_HIGHCUTOFFSET, HighCutOffset);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET0, LowEdgeSet0);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET1, LowEdgeSet1);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET2, LowEdgeSet2);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET3, LowEdgeSet3);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET4, LowEdgeSet4);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET0, HighEdgeSet0);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET1, HighEdgeSet1);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET2, HighEdgeSet2);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET3, HighEdgeSet3);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET4, HighEdgeSet4);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET0, LevelOffset0);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET1, LevelOffset1);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET2, LevelOffset2);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET3, LevelOffset3);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET4, LevelOffset4);
  EEPROM.writeByte(EE_UINT8T_IF, IF);
  EEPROM.writeByte(EE_UINT8T_LF, lf);
  EEPROM.writeByte(EE_UINT8T_DEMP, demp);
  EEPROM.writeByte(EE_UINT8T_USBMODE, usbmode);
  EEPROM.writeByte(EE_UINT8T_WIFIENABLE, wifienable);
  EEPROM.writeString(EE_STRING_PASSWORD, password);
  EEPROM.writeByte(EE_UINT8T_IP1, ip1);
  EEPROM.writeByte(EE_UINT8T_IP2, ip2);
  EEPROM.writeByte(EE_UINT8T_IP3, ip3);
  EEPROM.writeByte(EE_UINT8T_IP4, ip4);
  EEPROM.writeByte(EE_UINT8T_STATIONLIST, stationlist);
  EEPROM.writeInt(EE_INT16T_BLENDLEVEL, BlendLevel);
  EEPROM.writeInt(EE_INT16T_BLENDOFFSET, BlendOffset);
  EEPROM.writeInt(EE_INT16T_NBLEVEL, NBLevel);
  EEPROM.writeInt(EE_INT16T_AMCOCHANNEL, AM_Cochannel);
  EEPROM.writeInt(EE_INT16T_AMNBLEVEL, AM_NBLevel);
  EEPROM.writeInt(EE_INT16T_AMATT, AM_att);
  EEPROM.writeByte(EE_UINT8T_AM, am);
  EEPROM.writeByte(EE_UINT8T_FM, fm);
  EEPROM.writeByte(EE_UINT8T_UHF1, uhf1);
  EEPROM.writeByte(EE_UINT8T_UHF2, uhf2);
  EEPROM.writeByte(EE_UINT8T_UHF3, uhf3);
  EEPROM.writeByte(EE_UINT8T_UHF4, uhf4);
  EEPROM.writeByte(EE_UINT8T_COAXMODE, coaxmode);
  EEPROM.writeByte(EE_UINT8T_FMSI, fmsi);
  EEPROM.writeUInt(EE_UINT16T_FMSIATTACK, fmsi_attack);
  EEPROM.writeUInt(EE_UINT16T_FMSIRELEASE, fmsi_release);
  EEPROM.writeUInt(EE_UINT16T_FMSI11, fmsi_11);
  EEPROM.writeUInt(EE_UINT16T_FMSI12, fmsi_12);
  EEPROM.writeUInt(EE_UINT16T_FMSI21, fmsi_21);
  EEPROM.writeUInt(EE_UINT16T_FMSI22, fmsi_22);
  EEPROM.writeUInt(EE_UINT16T_FMSI31, fmsi_31);
  EEPROM.writeUInt(EE_UINT16T_FMSI32, fmsi_32);
  EEPROM.writeUInt(EE_UINT16T_FMSI41, fmsi_41);
  EEPROM.writeUInt(EE_UINT16T_FMSI42, fmsi_42);
  EEPROM.writeByte(EE_UINT8T_UHF6, uhf6);
  EEPROM.writeInt(EE_INT16T_LEVELOFFSET6, LevelOffset6);
  EEPROM.writeInt(EE_INT16T_LOWEDGESET6, LowEdgeSet6);
  EEPROM.writeInt(EE_INT16T_HIGHEDGESET6, HighEdgeSet6);
  EEPROM.writeUInt(EE_UINT16T_CONVERTEROFFSET, converteroffset);
  EEPROM.writeUInt(EE_UINT16T_SCANNERSTART, scanner_start);
  EEPROM.writeUInt(EE_UINT16T_SCANNEREND, scanner_end);
  EEPROM.writeByte(EE_UINT8T_SOFTMUTEFM, softmutefm);
  EEPROM.writeByte(EE_UINT8T_SOFTMUTEAM, softmuteam);
  EEPROM.writeByte(EE_UINT8T_SHOWRDSERRORS, showrdserrors);
  EEPROM.commit();

  remoteip = IPAddress (ip1, ip2, ip3, ip4);

  if (wifienable == 2) {
    Udp.stop();
    if (stationlist == 1) Udp.begin(9031);
  }

  Serial.end();
  if (usbmode == 1) Serial.begin(19200); else Serial.begin(115200);

  switch (band) {
    case 0: radio.setOffset(LevelOffset0); break;
    case 1: radio.setOffset(LevelOffset1); radio.SetFreq(IF * 100); break;
    case 2: radio.setOffset(LevelOffset2); radio.SetFreq(IF * 100); break;
    case 3: radio.setOffset(LevelOffset3); radio.SetFreq(IF * 100); break;
    case 4: radio.setOffset(LevelOffset4); radio.SetFreq(IF * 100); break;
    case 6: radio.setOffset(LevelOffset6); break;
  }

  doExit();
}

void trigger11(void) {  // Cancel menu
  Display.writeNum("b0.pic", NEXTION_BUT_AUDIO15065_GREYOUT);
  Display.writeNum("b1.pic", NEXTION_BUT_DSP15065_GREYOUT);
  Display.writeNum("b2.pic", NEXTION_BUT_SYSTEM15065_GREYOUT);
  Display.writeNum("b3.pic", NEXTION_BUT_RF15065_GREYOUT);
  Display.writeNum("b4.pic", NEXTION_BUT_OK15065_GREYOUT);
  Display.writeNum("b5.pic", NEXTION_BUT_CANCEL15065_GREYOUT);
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

void trigger12(void) {  // reset audio settings
  radio.setVolume(VolSet);
  radio.setDeemphasis(demp);
  radio.setAudio(lf);
  Display.writeNum("demp", demp);
  Display.writeNum("lf", lf);
  Display.writeNum("Volset", VolSet + 15);
}

void trigger13(void) {  // Apply volume
  radio.setVolume(Display.readNumber("slider.val") - 15);
  delay(50);
}

void trigger14(void) {  // Apply Highcut threshold
  radio.setHighCutLevel(Display.readNumber("slider2.val") / 100);
  delay(50);
}

void trigger15(void) {  // Apply highcut offset
  radio.setHighCutOffset(Display.readNumber("slider3.val"));
  delay(50);
}

void trigger16(void) {  // Apply stereo threshold
  radio.setStereoLevel(Display.readNumber("slider.val"));
  delay(50);
}

void trigger17(void) {  // Undo DSP settings
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

void trigger18(void) {  // Apply deemphasis
  radio.setDeemphasis(Display.readNumber("demp"));
  delay(50);
}

void trigger19(void) {  // Apply audio output mode
  radio.setAudio(Display.readNumber("lf"));
  delay(50);
}

void trigger20(void) {  // Show Wifi information
  wifienableold = wifienable;
  if (wifienable == 2) {
    String ssid = String(WiFi.SSID());
    Display.writeStr("IP.txt", WiFi.localIP().toString());
    Display.writeStr("SSID.txt", ssid);
    Display.writeNum("p1.pic", NEXTION_BUT_ACTIVE15065_YELLOW);
    Display.writeStr("password.txt", password);
  } else {
    Display.writeStr("SSID.txt", "DISCONNECTED");
    Display.writeNum("p1.pic", NEXTION_BUT_OFF15065_YELLOW);
  }
}

void trigger21(void) {  // Show Wifi configurator
  String ssid = "ESP_" + String(ESP_getChipId());
  String WifiAP = String ("WIFI:T:nopass;S:" + ssid + ";P:;H:;");
  Display.writeStr("qr.txt", WifiAP);
  String SSID_AP = String ("SSID: " + ssid);
  Display.writeStr("SSID_AP.txt", SSID_AP);
  wc.startConfigurationPortal(AP_WAIT);
  ESP.restart();
}

void trigger22(void) {  // Enable/disable WiFi
  wifienable++;
  if (wifienable == 3) wifienable = 1;
  if (wifienable == 1) {
    Display.writeNum("p1.pic", NEXTION_BUT_OFF15065_YELLOW);
    Server.end();
    Udp.stop();
    WiFi.mode(WIFI_OFF);
    Display.writeNum("wifienable", wifienable);
    Display.writeStr("IP.txt", "");
    Display.writeStr("SSID.txt", "DISCONNECTED");
    Display.writeStr("password.txt", "");
  } else if (wifienable == 2) {
    Display.writeNum("p1.pic", NEXTION_BUT_WAIT15065_YELLOW);
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
      Display.writeNum("p1.pic", NEXTION_BUT_ACTIVE15065_YELLOW);
    } else {
      Display.writeStr("page 10");
      trigger21();
    }
  }
}

void trigger23(void) {  // Generate new password
  passwordgenerator();
  Display.writeStr("password.txt", password);
}

void trigger24(void) {  // Show advanced RDS
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
  if (wificonnect) Display.writeNum("tm2.en", 1);
}

void trigger25(void) {  // Close advanced RDS
  showrdsinfo = false;
  doExit();
  if (wificonnect) Display.writeNum("tm2.en", 1);
}

void trigger26(void) {  // Start BT configurator
  btsetup = true;
  btconnect = false;
  swSer.print("AT+DISCON");
  delay(250);
  swSer.print("AT+REST");
}

void trigger27(void) {  // Close BT configurator
  btsetup = false;
}

void trigger28(void) {  // Set highblend level
  radio.setStHiBlendLevel(Display.readNumber("slider2.val") / 100);
  delay(50);
}

void trigger29(void) {  // Set highblend threshold
  radio.setStHiBlendOffset(Display.readNumber("slider3.val"));
  delay(50);
}

void trigger30(void) {  // Set FM noiseblanker
  radio.setFMNoiseBlanker(Display.readNumber("slider.val"));
  delay(50);
}

void trigger31(void) {  // Set AM noise blanker
  radio.setAMNoiseBlanker(Display.readNumber("slider2.val"));
  delay(50);
}

void trigger32(void) {  // AM attenuator
  radio.setAMAttenuation(Display.readNumber("slider3.val"));
  delay(50);
}

void trigger33(void) {  // Set cochannel
  radio.setAMCoChannel(Display.readNumber("slider.val"));
  delay(50);
}

void trigger34(void) {  // Enable/disable FMSI
  radio.setFMSI(Display.readNumber("fmsi"));
  delay(50);
}

void trigger35(void) {  // Set FMSI attack/release
  radio.setFMSI_Time(Display.readNumber("slider.val"), Display.readNumber("slider2.val"));
  delay(50);
}

void trigger36(void) {  // Set FMSI bands
  radio.setFMSI_Gain(Display.readNumber("b1sens"), Display.readNumber("b2sens"), Display.readNumber("b3sens"), Display.readNumber("b4sens"));
  delay(50);
  radio.setFMSI_Bias(Display.readNumber("b1bias"), Display.readNumber("b2bias"), Display.readNumber("b3bias"), Display.readNumber("b4bias"));
  delay(50);
}

void trigger37(void) {  // Switch scopeview
  scopeview = Display.readNumber("scopeview");
  EEPROM.writeByte(EE_UINT8T_SCOPEMODE, scopeview);
  EEPROM.commit();
}

void trigger38(void) {  // Set offset's offset
  OStatusold = 0;
  setoffset = true;
  Display.writeStr("tm1.en=0");
  offset = Display.readNumber("offsetkhz.val");
  delay(50);
  Frontend.SetFreq(freq - (IF * 100), offset);
}

void trigger39(void) {  // Apply offset's offset
  setoffset = false;
  int x;
  offset = Display.readNumber("looffset");
  delay(50);
  EEPROM.writeInt(EE_INT16T_OFFSET, offset);
  EEPROM.commit();
  doExit();
}

void trigger40(void) {  // Retry WiFi
  wifiretry = false;
  tryWiFi();
}

void trigger41(void) {  // Disable WiFi
  WiFi.mode(WIFI_OFF);
  wifienable = 1;
  EEPROM.writeByte(EE_UINT8T_WIFIENABLE, 1);
  EEPROM.commit();
  wifiretry = false;
}

void trigger42(void) {  // Set softmute
  radio.setSoftmuteFM(Display.readNumber("softmutefm"));
  delay(50);
  radio.setSoftmuteAM(Display.readNumber("softmuteam"));
  delay(50);
}

#endif