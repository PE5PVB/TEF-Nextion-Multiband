#ifndef CONSTANTS_CPP
#define CONSTANTS_CPP

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
    EEPROM.writeByte(46, band);
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

  LowEdgeSet0 = Display.readNumber("l0");
  LowEdgeSet1 = Display.readNumber("l1");
  LowEdgeSet2 = Display.readNumber("l2");
  LowEdgeSet3 = Display.readNumber("l3");
  LowEdgeSet4 = Display.readNumber("l4");
  LowEdgeSet6 = Display.readNumber("l6");
  HighEdgeSet0 = Display.readNumber("h0");
  HighEdgeSet1 = Display.readNumber("h1");
  HighEdgeSet2 = Display.readNumber("h2");
  HighEdgeSet3 = Display.readNumber("h3");
  HighEdgeSet4 = Display.readNumber("h4");
  HighEdgeSet6 = Display.readNumber("h6");
  LevelOffset0 = Display.readNumber("o0") - 25;
  LevelOffset1 = Display.readNumber("o1") - 25;
  LevelOffset2 = Display.readNumber("o2") - 25;
  LevelOffset3 = Display.readNumber("o3") - 25;
  LevelOffset4 = Display.readNumber("o4") - 25;
  LevelOffset6 = Display.readNumber("o6") - 25;
  IF = Display.readNumber("iffreq");
  converteroffset = Display.readNumber("converterlo");
  lf = Display.readNumber("lf");
  demp = Display.readNumber("demp");
  usbmode = Display.readNumber("usbmode");
  wifienable = Display.readNumber("wifienable");
  ip1 = Display.readNumber("pcip1");
  ip2 = Display.readNumber("pcip2");
  ip3 = Display.readNumber("pcip3");
  ip4 = Display.readNumber("pcip4");
  stationlist = Display.readNumber("stationlog");
  VolSet = Display.readNumber("Volset") - 15;
  ContrastSet = Display.readNumber("dim");
  StereoLevel = Display.readNumber("StereoLevel");
  HighCutLevel = Display.readNumber("HighCutLevel") / 100;
  HighCutOffset = Display.readNumber("HighCutOffset");
  BlendLevel = Display.readNumber("BlendLevel") / 100;
  BlendOffset = Display.readNumber("BlendOffset");
  NBLevel = Display.readNumber("NBLevel");
  AM_Cochannel = Display.readNumber("AMcochannel");
  AM_NBLevel = Display.readNumber("AMnb");
  AM_att = Display.readNumber("AMatt");
  fm = Display.readNumber("fm");
  am = Display.readNumber("am");
  uhf1 = Display.readNumber("uhf1");
  uhf2 = Display.readNumber("uhf2");
  uhf3 = Display.readNumber("uhf3");
  uhf4 = Display.readNumber("uhf4");
  uhf6 = Display.readNumber("uhf6");
  coaxmode = Display.readNumber("coaxmode");
  fmsi = Display.readNumber("fmsi");
  fmsi_attack = Display.readNumber("fmsiattack");
  fmsi_release = Display.readNumber("fmsirelease");
  fmsi_11 = Display.readNumber("b1sens");
  fmsi_12 = Display.readNumber("b1bias");
  fmsi_21 = Display.readNumber("b2sens");
  fmsi_22 = Display.readNumber("b2bias");
  fmsi_31 = Display.readNumber("b3sens");
  fmsi_32 = Display.readNumber("b3bias");
  fmsi_41 = Display.readNumber("b4sens");
  fmsi_42 = Display.readNumber("b4bias");
  scanner_start = Display.readNumber("sstart") * 100;
  scanner_end = Display.readNumber("sstop") * 100;
  scanner_band = Display.readNumber("sband");
  softmutefm = Display.readNumber("softmutefm");
  softmuteam = Display.readNumber("softmuteam");
  showrdserrors = Display.readNumber("showrdserrors");

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
    if (stationlist) Udp.begin(9031);
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
}

void trigger14(void) {  // Apply Highcut threshold
  radio.setHighCutLevel(Display.readNumber("slider2.val") / 100);
}

void trigger15(void) {  // Apply highcut offset
  radio.setHighCutOffset(Display.readNumber("slider3.val"));
}

void trigger16(void) {  // Apply stereo threshold
  radio.setStereoLevel(Display.readNumber("slider.val"));
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
}

void trigger19(void) {  // Apply audio output mode
  radio.setAudio(Display.readNumber("lf"));
}

void trigger20(void) {  // Show Wifi information
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
}

void trigger29(void) {  // Set highblend threshold
  radio.setStHiBlendOffset(Display.readNumber("slider3.val"));
}

void trigger30(void) {  // Set FM noiseblanker
  radio.setFMNoiseBlanker(Display.readNumber("slider.val"));
}

void trigger31(void) {  // Set AM noise blanker
  radio.setAMNoiseBlanker(Display.readNumber("slider2.val"));
}

void trigger32(void) {  // AM attenuator
  radio.setAMAttenuation(Display.readNumber("slider3.val"));
}

void trigger33(void) {  // Set cochannel
  radio.setAMCoChannel(Display.readNumber("slider.val"));
}

void trigger34(void) {  // Enable/disable FMSI
  radio.setFMSI(Display.readNumber("fmsi"));
}

void trigger35(void) {  // Set FMSI attack/release
  radio.setFMSI_Time(Display.readNumber("slider.val"), Display.readNumber("slider2.val"));
}

void trigger36(void) {  // Set FMSI bands
  radio.setFMSI_Gain(Display.readNumber("b1sens"), Display.readNumber("b2sens"), Display.readNumber("b3sens"), Display.readNumber("b4sens"));
  radio.setFMSI_Bias(Display.readNumber("b1bias"), Display.readNumber("b2bias"), Display.readNumber("b3bias"), Display.readNumber("b4bias"));
}

void trigger37(void) {  // Switch scopeview
  scopeview = Display.readNumber("scopeview");
  EEPROM.writeByte(186, scopeview);
  EEPROM.commit();
}

void trigger38(void) {  // Set offset's offset
  OStatusold = 0;
  setoffset = true;
  Display.writeStr("tm1.en=0");
  offset = Display.readNumber("offsetkhz.val");
  Frontend.SetFreq(freq - (IF * 100), offset);
}

void trigger39(void) {  // Apply offset's offset
  setoffset = false;
  int x;
  offset = Display.readNumber("looffset");
  EEPROM.writeInt(372, offset);
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
  EEPROM.writeByte(49, 1);
  EEPROM.commit();
  wifiretry = false;
}

void trigger42(void) {  // Set softmute
  radio.setSoftmuteFM(Display.readNumber("softmutefm"));
  radio.setSoftmuteAM(Display.readNumber("softmuteam"));
}

#endif