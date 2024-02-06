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

    if (RDSstatusold != RDSstatus || displayreset == true) {
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
        Display.writeStr("vis BER,0");
        Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
        Display.writeNum("b.pic", NEXTION_RT_B_GREYOUT_PIC);
      } else {
        if (RDSstatus && USN < 250 && WAM < 250 && !SQ && OStatus > -250 && OStatus < 250) {
          Display.writeNum("rdslogo.pic", NEXTION_RDSLOGO);
          Display.writeNum("PTY.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("RT.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("PS.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("PI.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("CT.pco", NEXTION_COLOR_YELLOW);
          Display.writeNum("rtshow", 0);
          Display.writeStr("vis BER,1");
        } else {
          Display.writeNum("rdslogo.pic", NEXTION_RDSLOGO_GREYOUT);
          delay(10);
          Display.writeNum("m.pic", NEXTION_MUSICLOGO_GREYOUT);
          delay(10);
          Display.writeNum("s.pic", NEXTION_SPEECHLOGO_GREYOUT);
          delay(10);
          Display.writeNum("PTY.pco", NEXTION_COLOR_WHITE);
          delay(10);
          Display.writeNum("RT.pco", NEXTION_COLOR_WHITE);
          delay(10);
          Display.writeNum("PS.pco", NEXTION_COLOR_WHITE);
          delay(10);
          Display.writeNum("PI.pco", NEXTION_COLOR_WHITE);
          delay(10);
          Display.writeNum("CT.pco", NEXTION_COLOR_WHITE);
          delay(10);
          Display.writeNum("rtshow", 0);
          delay(10);
          Display.writeStr("vis BER,0");
          delay(10);
          Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
          delay(10);
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

    if (RTPlus != radio.rds.hasRDSplus && showrdsinfo) {
      if (RDSstatus && radio.rds.hasRDSplus) Display.writeNum("rtplus.pic", NEXTION_RTPLUSLOGO); else Display.writeNum("rtplus.pic", NEXTION_RTPLUSLOGO_GREYOUT);
      RTPlus = radio.rds.hasRDSplus;
    }
  }
}

void ShowCT(void) {
  if ((radio.rds.hasCT && !dropout) || displayreset == true) {
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
      Display.writeStr("CT.txt", rds_clock);
    }
    rds_clockold = rds_clock;

  }
  hasCTold = radio.rds.hasCT;
}

void ShowPI(void) {
  if (String(radio.rds.picode) != PIold || displayreset == true) {
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
  if (radio.rds.stationName != PSold || displayreset == true) {
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
  if (RTold != (radio.rds.stationText + " " + radio.rds.stationText32) || displayreset == true) {
    Display.writeStr("RT.txt", radio.rds.stationText + " " + radio.rds.stationText32);
    RTold = radio.rds.stationText + " " + radio.rds.stationText32;

    if (radio.rds.hasRT == true) {
      if (!radio.rds.rtAB) {
        Display.writeNum("a.pic", NEXTION_RT_A_PIC);
        delay(10);
        Display.writeNum("b.pic", NEXTION_RT_B_GREYOUT_PIC);
      } else {
        Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
        delay(10);
        Display.writeNum("b.pic", NEXTION_RT_B_PIC);
      }
    } else {
      Display.writeNum("a.pic", NEXTION_RT_A_GREYOUT_PIC);
      delay(10);
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
  if (strcmp(radio.rds.stationType, programTypePrevious) || displayreset == true) {
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
  if (calc != RDSerrorsold || displayreset) {
    switch (calc) {
      case 0: Display.writeNum("ber.pic", NEXTION_RDSBAR_4); break;
      case 1: Display.writeNum("ber.pic", NEXTION_RDSBAR_3); break;
      case 2: Display.writeNum("ber.pic", NEXTION_RDSBAR_2); break;
      case 3: Display.writeNum("ber.pic", NEXTION_RDSBAR_1); break;
      case 4: Display.writeNum("ber.pic", NEXTION_RDSBAR_0); break;
    }
    RDSerrorsold = calc;
  }
}

void ShowECC(void) {
  if ((ECCold != radio.rds.ECC) || displayreset) {
    if (stationlist == 1 && wifienable == 2 && radio.rds.hasECC) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("ECC=");
      if (radio.rds.ECC < 0x10) Udp.print("0");
      Udp.print(radio.rds.ECC, HEX);
      Udp.endPacket();

      ECCold = radio.rds.ECC;
    }
  }
}

#endif