#ifndef SCANNER_CPP
#define SCANNER_CPP

#include "scanner.h"
#include "constants.h"

void SpectrumAnalyser(void) {
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

  for (freq_scan = scanner_start; freq_scan <= scanner_end; freq_scan += (((scanner_end - scanner_start) / 100) / 2) * scanner_speed) {
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
    if (scanner_thenable == 2 && !scanfound && SStatus / 10 > scanner_th) {
      scanner_found = freq_scan - ((scanner_end - scanner_start) / 100) / 2;
      scanfound = true;
      Display.writeNum("scanstatus", 5);
    } else {
      donesearch = true;
    }
  }
}

void BuildScanScreen(void) {
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
    for (int dot = 284; dot >= 84; dot -= 20) {
      String DotString = "fill 35," + String(dot, DEC) + ",201,2,33840";
      Display.writeStr(DotString);
    }

    for (int dot = 235; dot >= 20; dot -= 20) {
      String DotString = "fill " + String(dot, DEC) + ",84,2,201,33840";
      Display.writeStr(DotString);
    }

  } else {
    for (int dot = 220; dot >= 20; dot -= 20) {
      String DotString = "fill 20," + String(dot, DEC) + ",201,2,33840";
      Display.writeStr(DotString);
    }

    for (int dot = 220; dot >= 20; dot -= 20) {
      String DotString = "fill " + String(dot, DEC) + ",20,2,201,33840";
      Display.writeStr(DotString);
    }
  }
}

void scan_loop(void) {
  if (millis() >= time_now + 2000) {
    time_now += 2000;
    scanstatus = Display.readNumber("scanstatus");
  }

  if (scanstatus == 2) {
    Display.writeStr("tsw b0,0");
    Display.writeStr("tsw b1,0");
    Display.writeStr("tsw b2,0");
    Display.writeStr("tsw b3,0");
    Display.writeNum("b0.pic", 159);
    delay(350);
    scanner_start = Display.readNumber("sstart") * 100;
    scanner_end = Display.readNumber("sstop") * 100;
    scanner_vbw = Display.readNumber("sbw");
    scanner_th = Display.readNumber("scanthreshold.val");
    scanner_band = Display.readNumber("sband");
    scanner_speed = Display.readNumber("speed");
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

  } else if (scanstatus == 3 ) {
    Display.writeStr("tsw b0,0");
    Display.writeStr("tsw b1,0");
    Display.writeStr("tsw b2,0");
    Display.writeStr("tsw b3,0");
    Display.writeNum("b0.pic", 159);
    Display.writeStr("page 3");
    BuildScanScreen();

  } else if (scanstatus == 4) {
    Display.writeStr("vis scanner_found,0");
    if (displaysize == 35) {
      for (int dot = 284; dot >= 80; dot -= 20) {
        String DotString = "fill 35," + String(dot, DEC) + ",201,2,33840";
        Display.writeStr(DotString);
      }

      for (int dot = 235; dot >= 20; dot -= 20) {
        String DotString = "fill " + String(dot, DEC) + ",84,2,201,33840";
        Display.writeStr(DotString);
      }

    } else {
      for (int dot = 220; dot >= 20; dot -= 20) {
        String DotString = "fill 20," + String(dot, DEC) + ",201,2,33840";
        Display.writeStr(DotString);
      }

      for (int dot = 220; dot >= 20; dot -= 20) {
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
    if (scanfound) {
      if (scanner_band == 0) {
        radio.SetFreq(scanner_found);
      } else if (scanner_band == 6) {
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

    if (donesearch) {
      scanner_found = ((scanner_end - scanner_start) / 2) + scanner_start;

      if (scanner_band == 0) {
        radio.SetFreq(scanner_found);
      } else if (scanner_band == 6) {
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

        switch (band) {
          case 0: frequency0 = freq; break;
          case 1: frequency1 = freq; break;
          case 2: frequency2 = freq; break;
          case 3: frequency3 = freq; break;
          case 4: frequency4 = freq; break;
        }

        doExit();
        RoundStep();
      }
    }

  } else if (scanstatus == 6) {
    spec = false;
    doExit();
  }
}

void scanup(void) {
  rotary = 0;
  scanner_found += (((scanner_end - scanner_start) / 100) / 2);
  if (scanner_found > scanner_end) scanner_found = scanner_start;

  if (scanner_band == 0) {
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

void scandown(void) {
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
}

#endif