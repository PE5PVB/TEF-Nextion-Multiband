#ifndef GUI_CPP
#define GUI_CPP

#include "gui.h"
#include "constants.h"

void ShowRDS(void) {
  RDSstatus = radio.rds.hasRDS;
  if (!menu && !spec && !manfreq) {
    ShowPI();
    ShowPS();
    ShowRadiotext();
    ShowPTY();
    ShowErrors();
    ShowCT();
    ShowECC();
    ShowAF();
    ShowRDSPlus();
    ShowEON();

    if (RDSstatusold != RDSstatus || displayreset) {
      if (band == 5) {
        Display.writeNum("rdslogo.pic", NEXTION_RDSLOGO_GREYOUT);
        Display.writeNum("m.pic", NEXTION_SPEECHLOGO_GREYOUT);
        Display.writeNum("s.pic", NEXTION_SPEECHLOGO_GREYOUT);
        Display.writeNum("PTY.pco", NEXTION_COLOR_WHITE);
        Display.writeNum("RT.pco", NEXTION_COLOR_WHITE);
        Display.writeNum("PS.pco", NEXTION_COLOR_WHITE);
        Display.writeNum("PI.pco", NEXTION_COLOR_WHITE);
        Display.writeNum("CT.pco", NEXTION_COLOR_WHITE);
        Display.writeNum("rtshow", 0);
        Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
        Display.writeNum("b.pic", NEXTION_RT_B_GREYOUT_PIC);
      } else {
        if (RDSstatus && USN < 250 && WAM < 250 && !SQ && OStatus > -250 && OStatus < 250) {
          Display.writeNum("PTY.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("RT.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("PS.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("PI.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("CT.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("rtshow", 0);
        } else {
          Display.writeNum("m.pic", NEXTION_MUSICLOGO_GREYOUT);
          Display.writeNum("s.pic", NEXTION_SPEECHLOGO_GREYOUT);
          Display.writeNum("PTY.pco", NEXTION_COLOR_WHITE);
          Display.writeNum("RT.pco", NEXTION_COLOR_WHITE);
          Display.writeNum("PS.pco", NEXTION_COLOR_WHITE);
          Display.writeNum("PI.pco", NEXTION_COLOR_WHITE);
          Display.writeNum("CT.pco", NEXTION_COLOR_WHITE);
          Display.writeNum("rtshow", 0);
          Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
          Display.writeNum("b.pic", NEXTION_RT_B_GREYOUT_PIC);
          Display.writeNum("tm3.en", 0);
          Display.writeStr("vis CT,0");
          Display.writeStr("t7.txt", "PTY:");
        }
      }
      RDSstatusold = RDSstatus;
    }

    if (MSold != radio.rds.MS || displayreset) {
      switch (radio.rds.MS) {
        case 0:
          Display.writeNum("s.pic", NEXTION_SPEECHLOGO_GREYOUT);
          Display.writeNum("m.pic", NEXTION_MUSICLOGO_GREYOUT);
          break;

        case 1:
          Display.writeNum("s.pic", NEXTION_SPEECHLOGO_GREYOUT);
          Display.writeNum("m.pic", NEXTION_MUSICLOGO);
          break;

        case 2:
          Display.writeNum("s.pic", NEXTION_SPEECHLOGO);
          Display.writeNum("m.pic", NEXTION_MUSICLOGO_GREYOUT);
          break;
      }
      MSold = radio.rds.MS;
    }

    if (TAold != radio.rds.hasTA || displayreset) {
      if (RDSstatus && radio.rds.hasTA) Display.writeNum("ta.pic", NEXTION_TALOGO); else Display.writeNum("ta.pic", NEXTION_TALOGO_GREYOUT);
      TAold = radio.rds.hasTA;
    }

    if (TPold != radio.rds.hasTP || displayreset) {
      if (RDSstatus && radio.rds.hasTP) Display.writeNum("tp.pic", NEXTION_TPLOGO); else Display.writeNum("tp.pic", NEXTION_TPLOGO_GREYOUT);
      TPold = radio.rds.hasTP;
    }

    if (EONold != radio.rds.hasEON || displayreset) {
      if (RDSstatus && radio.rds.hasEON) Display.writeNum("eon.pic", NEXTION_EONLOGO); else Display.writeNum("eon.pic", NEXTION_EONLOGO_GREYOUT);
      EONold = radio.rds.hasEON;
    }

    if ((RTPlus != radio.rds.hasRDSplus || displayreset) && showrdsinfo) {
      if (RDSstatus && radio.rds.hasRDSplus) Display.writeNum("rtplus.pic", NEXTION_RTPLUSLOGO); else Display.writeNum("rtplus.pic", NEXTION_RTPLUSLOGO_GREYOUT);
      RTPlus = radio.rds.hasRDSplus;
    }
  }
}

void ShowRDSPlus(void) {
  if (showrdsinfo) {
    if (radio.rds.RTContent1 != RTContent1old || displayreset) {
      Display.writeStr("rtplus1.txt", radio.rds.RTContent1);
      RTContent1old = radio.rds.RTContent1;
    }

    if (radio.rds.RTContent2 != RTContent2old || displayreset) {
      Display.writeStr("rtplus2.txt", radio.rds.RTContent2);
      RTContent2old = radio.rds.RTContent2;
    }
  }
}

void ShowEON(void) {
  if (showrdsinfo) {
    String eonstring;
    if (radio.eon_counter > 0) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? "" : " | "); else eonstring = "";
    if (eonstring != eonstringold || displayreset) {
      Display.writeStr("eontxt.txt", eonstring);
      eonstringold = eonstring;
    }

  }
}

void ShowAF(void) {
  if (radio.af_counter != af_counterold || displayreset) {
    af = "";
    af2 = "";
    af2show = false;
    if (stationlist == 1 && wifienable == 2) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("AF=");
    }

    for (af_scan = 0; af_scan < radio.af_counter; af_scan++) {
      if (stationlist == 1 && wifienable == 2) {
        if ((radio.af[af_scan].frequency - 8750) / 10 < 0x10) {
          Udp.print("0");
        }
        Udp.print((radio.af[af_scan].frequency - 8750) / 10, HEX);
      }

      if (radio.af[af_scan].frequency != frequency0) {
        if (displaysize == 35) {
          if (af_scan < 13) {
            af += String(radio.af[af_scan].frequency / 100) + "." + (radio.af[af_scan].frequency % 100 < 10 ? "0" : "") + String(radio.af[af_scan].frequency % 100) + "\\r";
            af2show = false;
          } else {
            af2 += String(radio.af[af_scan].frequency / 100) + "." + (radio.af[af_scan].frequency % 100 < 10 ? "0" : "") + String(radio.af[af_scan].frequency % 100) + "\\r";
            af2show = true;
          }
        } else {
          if (af_scan < 10) {
            af += String(radio.af[af_scan].frequency / 100) + "." + (radio.af[af_scan].frequency % 100 < 10 ? "0" : "") + String(radio.af[af_scan].frequency % 100) + "\\r";
            af2show = false;
          } else {
            af2 += String(radio.af[af_scan].frequency / 100) + "." + (radio.af[af_scan].frequency % 100 < 10 ? "0" : "") + String(radio.af[af_scan].frequency % 100) + "\\r";
            af2show = true;
          }
        }
      }
    }
    af_counterold = radio.af_counter;

    if (showrdsinfo) {
      Display.writeStr("AFLIST.txt", af);
      if (af2show) {
        Display.writeNum("tm0.en", 1);
        Display.writeStr("AFLIST2.txt", af2);
      } else {
        Display.writeNum("tm0.en", 0);
        Display.writeStr("vis AFLIST2,0");
      }
    }
    if (stationlist == 1 && wifienable == 2) {
      for (int i = 0; i < 25 - radio.af_counter; i++) Udp.print("00");
      Udp.endPacket();
    }
  }
}

void ShowCT(void) {
  if ((radio.rds.hasCT && !dropout) || displayreset) {
    rds_clock = ((radio.rds.hour < 10 ? "0" : "") + String(radio.rds.hour) + ":" + (radio.rds.minute < 10 ? "0" : "") + String(radio.rds.minute));
  } else if (!radio.rds.hasCT || dropout) {
    rds_clock = ((rtc.getHour(true) < 10 ? "0" : "") + String(rtc.getHour(true)) + ":" + (rtc.getMinute() < 10 ? "0" : "") + String(rtc.getMinute()));
    if (dropout) {
      radio.rds.hour = rtc.getHour(true);
      radio.rds.minute = rtc.getMinute();
    }
  }
  if (rds_clock != rds_clockold || hasCTold != radio.rds.hasCT) {
    if (radio.rds.hasCT && RDSstatus) {
      rtcset = true;
      rtc.setTime(0, radio.rds.minute, radio.rds.hour, radio.rds.day, radio.rds.month, radio.rds.year);
      Display.writeNum("tm3.en", 1);
      Display.writeStr("CT.txt", String(radio.rds.day) + "-" + String(radio.rds.month) + "-" + String(radio.rds.year) + " " + rds_clock);
    }
    rds_clockold = rds_clock;

  }
  hasCTold = radio.rds.hasCT;
}

void ShowPI(void) {
  if (String(radio.rds.picode) != PIold || displayreset) {
    Display.writeStr("PI.txt", radio.rds.picode);
    PIold = radio.rds.picode;

    if (stationlist == 1 && wifienable == 2) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner " + showsoftwareversion + ";PI=" + String(radio.rds.picode, 4));
      Udp.endPacket();
    }
  }
}

void ShowPS(void) {
  if (radio.rds.stationName != PSold || displayreset) {
    Display.writeStr("PS.txt", radio.rds.stationName);
    PSold = radio.rds.stationName;

    if (stationlist == 1 && wifienable == 2) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner " + showsoftwareversion + ";PS=");
      char PShex[9];
      radio.rds.stationName.toCharArray(PShex, 9);
      for (int i = 0; i < 8; i++) {
        if (PShex[i] < 0x10) Udp.print("0");
        if (PShex[i] == 0x20) PShex[i] =  '_';
        Udp.print(PShex[i], HEX);
      }
      Udp.endPacket();
    }
  }
}

void ShowRadiotext(void) {
  if (RTold != (radio.rds.stationText + " " + radio.rds.stationText32) || displayreset) {
	  String txt = radio.rds.stationText + " " + radio.rds.stationText32;
	  txt.replace("\"", "\\\"");
    Display.writeStr("RT.txt", txt);
    RTold = radio.rds.stationText + " " + radio.rds.stationText32;

    if (radio.rds.hasRT) {
      if (!radio.rds.rtAB) {
        Display.writeNum("a.pic", NEXTION_RT_A_PIC);
        Display.writeNum("b.pic", NEXTION_RT_B_GREYOUT_PIC);
      } else {
        Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
        Display.writeNum("b.pic", NEXTION_RT_B_PIC);
      }
    } else {
      Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
      Display.writeNum("b.pic", NEXTION_RT_B_GREYOUT_PIC);
    }

    if (stationlist == 1 && wifienable == 2) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner " + showsoftwareversion + ";RT1=");
      char RThex[65];
      radio.rds.stationText.toCharArray(RThex, 65);
      for (int i = 0; i < 64; i++)
      {
        if (RThex[i] < 0x10) Udp.print("0");
        if (RThex[i] == ' ') RThex[i] =  '_';
        Udp.print(RThex[i], HEX);
      }
      Udp.endPacket();
    }
  }
}

void ShowPTY(void) {
  if (strcmp(radio.rds.stationType, programTypePrevious) || displayreset) {
    Display.writeStr("PTY.txt", radio.rds.stationType);
    strcpy(programTypePrevious, radio.rds.stationType);
    if (stationlist == 1 && wifienable == 2) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner " + showsoftwareversion + ";PTY=");
      Udp.print(radio.rds.stationTypeCode, HEX);
      Udp.endPacket();
    }
  }
}

void ShowErrors(void) {
  uint8_t calc = 4;
  if (!radio.rds.rdsAerror) calc--;
  if (!radio.rds.rdsBerror) calc--;
  if (!radio.rds.rdsCerror) calc--;
  if (!radio.rds.rdsDerror) calc--;

  SAvg3 = (((SAvg3 * 9) + 5) / 10) + calc;
  calc = SAvg3 / 10;

  if (calc != RDSerrorsold || displayreset) {
    if (RDSstatus) {
      switch (calc) {
        case 0: Display.writeNum("ber.pic", NEXTION_RDSBAR_4); break;
        case 1: Display.writeNum("ber.pic", NEXTION_RDSBAR_3); break;
        case 2: Display.writeNum("ber.pic", NEXTION_RDSBAR_2); break;
        case 3: Display.writeNum("ber.pic", NEXTION_RDSBAR_1); break;
        case 4: Display.writeNum("ber.pic", NEXTION_RDSBAR_0); break;
      }
    } else {
      Display.writeNum("ber.pic", NEXTION_RDSBAR_0);
    }
    RDSerrorsold = calc;
  }
}

void ShowECC(void) {
  if (stationlist == 1 && wifienable == 2) {
    Udp.beginPacket(remoteip, 9030);
    Udp.print("ECC=");
    if (radio.rds.ECC < 0x10) Udp.print("0");
    Udp.print(radio.rds.ECC, HEX);
    Udp.endPacket();
  }
  if (radio.rds.ECC != ECCold || displayreset) {
    if (radio.rds.picode[0] == '1') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 55);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 56);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 57);
      if (radio.rds.ECC == 228) Display.writeNum("ECC.pic", 58);
    } else if (radio.rds.picode[0] == '2') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 59);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 60);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 61);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 62);
      if (radio.rds.ECC == 228) Display.writeNum("ECC.pic", 63);
    } else if (radio.rds.picode[0] == '3') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 64);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 65);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 66);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 67);
    } else if (radio.rds.picode[0] == '4') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 68);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 69);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 70);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 71);
    } else if (radio.rds.picode[0] == '5') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 72);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 73);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 74);
    } else if (radio.rds.picode[0] == '6') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 75);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 76);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 77);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 78);
      if (radio.rds.ECC == 228) Display.writeNum("ECC.pic", 79);
    } else if (radio.rds.picode[0] == '7') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 80);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 81);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 82);
    } else if (radio.rds.picode[0] == '8') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 83);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 84);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 85);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 86);
      if (radio.rds.ECC == 228) Display.writeNum("ECC.pic", 87);
    } else if (radio.rds.picode[0] == '9') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 88);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 89);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 90);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 91);
      if (radio.rds.ECC == 228) Display.writeNum("ECC.pic", 92);
    } else if (radio.rds.picode[0] == 'A') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 93);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 94);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 95);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 96);
    } else if (radio.rds.picode[0] == 'B') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 97);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 98);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 99);
    } else if (radio.rds.picode[0] == 'C') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 100);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 101);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 102);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 103);
    } else if (radio.rds.picode[0] == 'D') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 104);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 105);
    } else if (radio.rds.picode[0] == 'E') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 106);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 107);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 108);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 109);
    } else if (radio.rds.picode[0] == 'F') {
      if (radio.rds.ECC == 224) Display.writeNum("ECC.pic", 110);
      if (radio.rds.ECC == 225) Display.writeNum("ECC.pic", 111);
      if (radio.rds.ECC == 226) Display.writeNum("ECC.pic", 112);
      if (radio.rds.ECC == 227) Display.writeNum("ECC.pic", 113);
      if (radio.rds.ECC == 228) Display.writeNum("ECC.pic", 114);
    } else {
      Display.writeNum("ECC.pic", 115);
    }
    ECCold = radio.rds.ECC;
  }
}

void ShowRSSI(void) {
  if (wifienable == 2) rssi = WiFi.RSSI(); else rssi = 0;

  if (rssiold != rssi || displayreset) {
    rssiold = rssi;
    if (rssi == 0) {
      Display.writeNum("wifilogo.pic", NEXTION_WIFIBAR0);
    } else if (rssi > -50 && rssi < 0) {
      Display.writeNum("wifilogo.pic", NEXTION_WIFIBAR4);
    } else if (rssi > -60) {
      Display.writeNum("wifilogo.pic", NEXTION_WIFIBAR3);
    } else if (rssi > -70) {
      Display.writeNum("wifilogo.pic", NEXTION_WIFIBAR2);
    } else if (rssi < -70) {
      Display.writeNum("wifilogo.pic", NEXTION_WIFIBAR1);
    }
  }
}

void ShowFreq(void) {
  detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
  detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));

  switch (band) {
    case 0: freq = frequency0; break;
    case 1: freq = frequency1; break;
    case 2: freq = frequency2; break;
    case 3: freq = frequency3; break;
    case 4: freq = frequency4; break;
    case 5: freq = frequency5; break;
    case 6: freq = frequency6; break;
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
    if (wificonnect) RemoteClient.print("G:\r\nRESET-------\r\n\r\n"); else Serial.print("G:\r\nRESET-------\r\n\r\n");
  }

  if (stationlist == 1 && wifienable == 2) {
    Udp.beginPacket(remoteip, 9030);
    Udp.print("from=TEF tuner " + showsoftwareversion + ";freq=");
    if (band == 5) Udp.print(String(frequency5) + "000;ClearRDS=1"); else Udp.print(String(frequency0) + "0000;ClearRDS=1");
    Udp.endPacket();
    stlmillis += 500;
  }

  if (!displayreset) radio.clearRDS(fullsearchrds);

  if (showrdsinfo) {
    af2show = false;
    af = "";
    af2 = "";
    Display.writeStr("AFLIST.txt", af);
    Display.writeStr("AFLIST2.txt", af2);
    Display.writeNum("tm0.en", 0);
    Display.writeStr("vis AFLIST2,0");
  }

  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
}

void ShowModLevel(void) {
  if (!showrdsinfo) {
    if (!seek) {
      if (!SQ) Display.writeNum("vu.val", MStatus / 2); else Display.writeNum("vu.val", 0);
    } else {
      Display.writeNum("vu.val", 0);
    }
  }
}

void ShowBW(void) {
  if ((BW != BWOld || BWreset) || displayreset) {
    if (BWreset) {
      if (band != 5) {
        if (BWsetOld != BWset) {
          if (BWset == 0) {
            Display.writeNum("BW.pco", NEXTION_COLOR_SKYBLUE);
            if (!showrdsinfo) Display.writeNum("autobwlogo.pic", NEXTION_AUTOBWLOGO);
            radio.setFMABandw();
          } else {
            Display.writeNum("BW.pco", NEXTION_COLOR_YELLOW);
            if (!showrdsinfo) Display.writeNum("autobwlogo.pic", NEXTION_AUTOBWLOGO_GREYOUT);
            BWsetOld = BWset;
          }
        }
      }
    }

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

void ShowSignalLevel(void) {
  SAvg = (((SAvg * 9) + 5) / 10) + SStatus;
  SAvg2 = (((SAvg2 * 9) + 5) / 10) + CN;

  float sval = 0;
  int16_t smeter = 0;

  if (SStatus > 0) {
    if (SStatus < 1000) {
      sval = 51 * ((pow(10, (((float)SStatus) / 1000))) - 1);
      smeter = int16_t(sval);
    } else {
      smeter = 511;
    }
  }

  smeter = int16_t(sval);
  SStatus = SAvg / 10;
  CN = SAvg2 / 10;

  if (!showrdsinfo) {
    if (USN < 250 && WAM < 250 && OStatus > -250 && OStatus < 250) {
      if (CN > (CNold + 1) || CN < (CNold - 1)) {
        if (CN < SStatus / 10) Display.writeNum("SNR.val", CN);
        if (!cnvis) {
          Display.writeStr("vis SNR,1");
          Display.writeStr("vis t12,1");
          Display.writeStr("vis t13,1");
        }
        CNold = CN;
        cnvis = true;
      }
    } else {
      if (cnvis) {
        Display.writeNum("SNR.val", 0);
        Display.writeStr("vis SNR,0");
        Display.writeStr("vis t12,0");
        Display.writeStr("vis t13,0");
        CNold = 0;
      }
      cnvis = false;
    }
    Display.writeNum("WAM.val", WAM / 5);
    Display.writeNum("USN.val", USN / 5);

    if ((SStatus > (SStatusold + 3) || SStatus < (SStatusold - 3)) || displayreset) {
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

void ShowStereoStatus(void) {
  if (StereoToggle && band != 5) {
    Stereostatus = radio.getStereoStatus();
    if ((Stereostatus != Stereostatusold) || displayreset) {
      if (Stereostatus) Display.writeNum("stereo.pic", NEXTION_STEREOLOGO); else Display.writeNum("stereo.pic", NEXTION_STEREOLOGO_GREYOUT);
      Stereostatusold = Stereostatus;
    }
  }
}

void ShowOffset(void) {
  if (band == 5) {
    if (OStatus < -2) {
      if (OStatusold != 1) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N_GREYOUT);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T_GREYOUT);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P);
        MStatus = 0;
        OStatusold = 1;
      }
    } else if (!SQ && OStatus > -2 && OStatus < 2) {
      if (OStatusold != 2) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N_GREYOUT);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P_GREYOUT);
        OStatusold = 2;
      }
    } else if (OStatus > 2) {
      if (OStatusold != 3) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T_GREYOUT);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P_GREYOUT);
        MStatus = 0;
        OStatusold = 3;
      }
    } else {
      if (OStatusold != 4) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N_GREYOUT);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T_GREYOUT);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P_GREYOUT);
        MStatus = 0;
        OStatusold = 4;
      }
    }
  } else {
    if (OStatus < -250) {
      if (OStatusold != 1) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N_GREYOUT);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T_GREYOUT);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P);
        MStatus = 0;
        OStatusold = 1;
      }
    } else if (USN < 250 && WAM < 250 && !SQ && OStatus > -250 && OStatus < 250) {
      if (OStatusold != 2) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N_GREYOUT);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P_GREYOUT);
        OStatusold = 2;
      }
    } else if (OStatus > 250) {
      if (OStatusold != 3) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T_GREYOUT);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P_GREYOUT);
        MStatus = 0;
        OStatusold = 3;
      }
    } else {
      if (OStatusold != 4) {
        Display.writeNum("tune_neg.pic", NEXTION_TUNELOGO_N_GREYOUT);
        Display.writeNum("tuned.pic", NEXTION_TUNELOGO_T_GREYOUT);
        Display.writeNum("tune_pos.pic", NEXTION_TUNELOGO_P_GREYOUT);
        MStatus = 0;
        OStatusold = 4;
      }
    }
  }
}

void ShowStepSize(void) {
  Display.writeNum("step001.pic", NEXTION_STEPSIZEBAR_GREYOUT);
  Display.writeNum("step010.pic", NEXTION_STEPSIZEBAR_GREYOUT);
  Display.writeNum("step100.pic", NEXTION_STEPSIZEBAR_GREYOUT);
  Display.writeNum("step1000.pic", NEXTION_STEPSIZEBAR_GREYOUT);

  switch (stepsize) {
    case 1: Display.writeNum("step001.pic", NEXTION_STEPSIZEBAR); break;
    case 2: Display.writeNum("step010.pic", NEXTION_STEPSIZEBAR); break;
    case 3: Display.writeNum("step100.pic", NEXTION_STEPSIZEBAR); break;
    case 4: Display.writeNum("step1000.pic", NEXTION_STEPSIZEBAR); break;
  }
}

void ShowTuneMode(void) {
  ShowStepSize();
  if (tunemode == 0) {
    Display.writeNum("autologo.pic", NEXTION_AUTOLOGO_GREYOUT);
    Display.writeNum("manlogo.pic", NEXTION_MANLOGO);
    Display.writeNum("memlogo.pic", NEXTION_MEMLOGO_GREYOUT);
  }

  if (tunemode == 1) {
    Display.writeNum("autologo.pic", NEXTION_AUTOLOGO);
    Display.writeNum("manlogo.pic", NEXTION_MANLOGO_GREYOUT);
    Display.writeNum("memlogo.pic", NEXTION_MEMLOGO_GREYOUT);
  }

  if (tunemode == 2) {
    Display.writeNum("autologo.pic", NEXTION_AUTOLOGO_GREYOUT);
    Display.writeNum("manlogo.pic", NEXTION_MANLOGO_GREYOUT);
    Display.writeNum("memlogo.pic", NEXTION_MEMLOGO);
  }
}

void ShowBTstatus(void) {
  if (btconnect) Display.writeNum("BT.pic", NEXTION_BTLOGO); else Display.writeNum("BT.pic", NEXTION_BTLOGO_GREYOUT);
}

void ShowUSBstatus(void) {
  if (USBstatus) {
    if (!usblogo_on || displayreset) {
      Display.writeNum("usblogo.pic", NEXTION_USBLOGO);
      usblogo_on = true;
      usblogo_off = false;
    }
  } else {
    if (!usblogo_off || displayreset) {
      Display.writeNum("usblogo.pic", NEXTION_USBLOGO_GREYOUT);
      usblogo_on = false;
      usblogo_off = true;
    }
  }
}

void ShowiMS(void) {
  if (!showrdsinfo) {
    if (iMSset == 0) {
      Display.writeNum("imslogo.pic", NEXTION_IMSLOGO);
      radio.setiMS(1);
    } else {
      Display.writeNum("imslogo.pic", NEXTION_IMSLOGO_GREYOUT);
      radio.setiMS(0);
    }
  }
}

void ShowEQ(void) {
  if (!showrdsinfo) {
    if (EQset == 0) {
      Display.writeNum("eqlogo.pic", NEXTION_EQLOGO);
      radio.setEQ(1);
    } else {
      Display.writeNum("eqlogo.pic", NEXTION_EQLOGO_GREYOUT);
      radio.setEQ(0);
    }
  }
}

void ShowSquelch(void) {
  if (!menu && !spec) {
    if (!SQ) {
      if (!mutelogo_off) {
        Display.writeNum("mutelogo.pic", NEXTION_MUTELOGO_GREYOUT);
        mutelogo_off = true;
        mutelogo_on = false;
      }
    } else {
      if (!mutelogo_on) {
        Display.writeNum("mutelogo.pic", NEXTION_MUTELOGO);
        mutelogo_on = true;
        mutelogo_off = false;
      }
    }
  }
}

#endif