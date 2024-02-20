#ifndef COMMS_CPP
#define COMMS_CPP

#include "comms.h"
#include "constants.h"

void Communication(void) {
  if (swSer.available()) {
    String data_str = swSer.readStringUntil('\n');
    if (data_str.substring(0, 3) == "CON") {
      btconnect = true;
      if (!menu) ShowBTstatus();
    } else if (data_str.substring(0, 3) == "DIS") {
      btconnect = false;
      if (!menu) ShowBTstatus();
    }

    if (data_str.charAt(11) == ':') {
      int number = data_str.substring(12, 13).toInt();
      MAC[number] = data_str.substring(data_str.indexOf(",MacAdd:0x") + 10, data_str.indexOf(",MacAdd:0x") + 22);
      NAME[number] = data_str.substring(data_str.indexOf(",Name:") + 6);
    }

    if (btsetup) {
      Display.writeStr("bt1.txt", NAME[1]);
      Display.writeStr("bt2.txt", NAME[2]);
      Display.writeStr("bt3.txt", NAME[3]);
      Display.writeStr("bt4.txt", NAME[4]);
      Display.writeStr("bt5.txt", NAME[5]);
      Display.writeStr("bt6.txt", NAME[6]);
      int number = Display.readNumber("bt");
      if (number > 0) {
        if (number == 7) {
          swSer.print("AT+DELVMLINK");
          delay(250);
          swSer.print("AT+ADDLINKADD=0xffffffffffff");
          delay(250);
          swSer.print("AT+REST");
          Display.writeStr("page 15");
        } else if (number < 7) {
          swSer.print("AT+ADDLINKADD=0x" + MAC[number]);
          delay(50);
          Display.writeNum("bt", 0);
          delay(50);
          Display.writeStr("page 14");
          delay(50);
        }
      }
    }
  }

  if (!menu) {
    if (!manfreq && !spec) {
      if (stationlist == 1 && wifienable == 2) {
        int packetSize = Udp.parsePacket();
        if (packetSize) {
          char packetBuffer[packetSize];
          Udp.read(packetBuffer, packetSize);
          Udp.endPacket();
          packet = String(packetBuffer);
          if (strcmp(packetBuffer, "from=StationList;freq=?;bandwidth=?") == 0) {
            ShowFreq();
            Udp.beginPacket(remoteip, 9030);
            Udp.print("from=TEF tuner " + showsoftwareversion + ";Bandwidth=");
            Udp.print(BW * 1000);
            Udp.endPacket();
          } else {
            int symPos = packet.indexOf("freq=");
            String stlfreq = packet.substring(symPos + 5, packetSize);
            if ((stlfreq.toInt()) / 10000 > 6500 && (stlfreq.toInt()) / 10000 < 10800) {
              if (band != 0) {
                band = 0;
                RF(band);
              }
              frequency0 = (stlfreq.toInt()) / 10000;
              radio.SetFreq(frequency0);
            }
            if ((stlfreq.toInt()) / 1000 > 144 && (stlfreq.toInt()) / 1000 < 27000) {
              if (band != 5) {
                band = 5;
                RF(band);
              }
              frequency5 = (stlfreq.toInt()) / 1000;
              radio.SetFreqAM(frequency5);
            }
            radio.clearRDS(fullsearchrds);
            ShowFreq();
            store = true;
          }
        }
      }

      if (Server.hasClient()) {
        if (RemoteClient.connected()) {
          Server.available().stop();
        } else {
          wificonnect = true;
          RemoteClient = Server.available();
          passwordcrypt();
          RemoteClient.print(saltkey + "\n");
          Display.writeNum("tm2.en", 1);
        }
      } else {
        if (Server.hasClient()) Server.available().stop();
      }

      if (wificonnect && !RemoteClient.connected()) {
        wificonnect = false;
        RDSSpy = false;
        XDRGTKTCP = false;
        Display.writeNum("tm2.en", 0);
        Display.writeStr("vis wifilogo,1");
      }


      if (!XDRGTKTCP && wificonnect && RemoteClient.available()) {
        String data_str = RemoteClient.readStringUntil('\n');
        Serial.println(data_str);
        if (data_str.length() > 30 && data_str.equals(cryptedpassword)) {
          radio.setFMABandw();
          if (band != 0) {
            band = 0;
            RF(band);
          }
          XDRGTKTCP = true;
          RemoteClient.print("o1,0\n");
          store = true;
        } else if (!RDSSpy && !XDRGTKTCP && data_str.length() < 5 && data_str == ("*R?F")) {
          RDSSpy = true;
        } else if (RDSSpy) {
          int symPos = data_str.indexOf("*F");
          if (symPos >= 5) {
            String freq = data_str.substring(0, symPos);
            freq = freq.substring(0, freq.length() - 1);
            frequency0 = freq.toInt();
            radio.SetFreq(frequency0);
            radio.clearRDS(fullsearchrds);
            if (band != 0) {
              band = 0;
              RF(0);
            }
            ShowFreq();
            store = true;
          }
        } else {
          RemoteClient.print("a0\n");
        }
      }

      if (!XDRGTK && Serial.available()) {
        String data_str = Serial.readStringUntil('\n');
        if (data_str.length() > 1 && data_str == ("*D*R?F")) {
          USBstatus = true;
          RDSSpy = true;
        }
        int symPos = data_str.indexOf("*F");
        if (symPos >= 5) {
          String freq = data_str.substring(0, symPos);
          freq = freq.substring(0, freq.length() - 1);
          frequency0 = freq.toInt();
          radio.SetFreq(frequency0);
          if (band != 0) {
            band = 0;
            RF(0);
          }
          ShowFreq();
          store = true;
        }
        if (data_str.charAt(0) == 'x') {
          radio.setFMABandw();
          if (band != 0) {
            band = 0;
            RF(band);
          }
          Serial.print("OK\nT" + String(frequency0 * 10) + "\n");
          store = true;
          USBstatus = true;
          XDRGTK = true;
        }
      }

      if (XDRGTK || XDRGTKTCP) XDRGTKRoutine();
    }
  }
}

void XDRGTKprint(String string) {
  if (XDRGTK) Serial.print(string);
  if (XDRGTKTCP) RemoteClient.print(string);
}

void XDRGTKRoutine(void) {
  if (XDRGTK) {
    while (Serial.available() > 0) {
      char c = Serial.read();
      if (buff_pos < 16 && c != '\n') {
        buff[buff_pos++] = c;
      } else {
        buff[buff_pos] = '\0';
        buff_pos = 0;
        XDRGTKdata = true;
        break;
      }
    }
  }

  if (XDRGTKTCP && RemoteClient.available() > 0) {
    while (RemoteClient.available() > 0) {
      char c = RemoteClient.read();
      if (buff_pos < 16 && c != '\n') {
        buff[buff_pos++] = c;
      } else {
        buff[buff_pos] = '\0';
        buff_pos = 0;
        XDRGTKdata = true;
        break;
      }
    }
  }

  if (XDRGTKdata) {
    switch (buff[0])
    {
      case 'A':
        int AGC;
        AGC = atol(buff + 1);
        XDRGTKprint("A" + String(AGC) + "\n");
        switch (AGC) {
          case 0: if (band != 5) radio.setAGC(92); else radio.setAMAGC(102); break;
          case 1: if (band != 5) radio.setAGC(90); else radio.setAMAGC(99); break;
          case 2: if (band != 5) radio.setAGC(87); else radio.setAMAGC(96); break;
          case 3: if (band != 5) radio.setAGC(84); else radio.setAMAGC(94); break;
        }
        break;

      case 'C':
        byte scanmethod;
        scanmethod = atol(buff + 1);
        if (scanmethod == 1) {
          XDRGTKprint("C1\n");
          direction = false;
          Seek(direction);
          ShowFreq();
        }
        if (scanmethod == 2) {
          XDRGTKprint("C2\n");
          direction = true;
          Seek(direction);
          ShowFreq();
        }
        XDRGTKprint("C0\n");
        break;

      case 'N':
        doStereoToggle();
        break;

      case 'D':
        byte XDRdemp;
        XDRdemp = atol(buff + 1);
        XDRGTKprint("D" + String(XDRdemp) + "\n");
        demp = XDRdemp + 1;
        radio.setDeemphasis(demp);
        break;

      case 'F':
        XDRBWset = atol(buff + 1);
        XDRGTKprint("F" + String(XDRBWset) + "\n");
        if (XDRBWset < 0) {
          XDRBWsetold = XDRBWset;
          BWset = 0;
        } else if (XDRBWset < 16) {
          BWset = XDRBWset + 1;
          XDRBWsetold = XDRBWset;
        } else {
          XDRBWset = XDRBWsetold;
        }
        doBW();
        break;

      case 'G':
        byte offsetg;
        offsetg = atol(buff + 1);
        if (offsetg == 0) {
          iMSset = 1;
          EQset = 1;
          iMSEQ = 3;
          XDRGTKprint("G00\n");
        }
        if (offsetg == 10) {
          iMSset = 1;
          EQset = 0;
          iMSEQ = 1;
          XDRGTKprint("G10\n");
        }
        if (offsetg == 1) {
          iMSset = 0;
          EQset = 1;
          iMSEQ = 2;
          XDRGTKprint("G01\n");
        }
        if (offsetg == 11) {
          iMSset = 0;
          EQset = 0;
          iMSEQ = 0;
          XDRGTKprint("G11\n");
        }
        ShowiMS();
        ShowEQ();
        EEPROM.writeByte(EE_UINT8T_IMSSET, iMSset);
        EEPROM.writeByte(EE_UINT8T_EQSET, EQset);
        EEPROM.commit();
        break;

      case 'M':
        byte XDRband;
        XDRband = atol(buff + 1);
        if (XDRband == 0) {
          band = 0;
          XDRGTKprint("M0\n");
          RF(band);

        } else {
          band = 5;
          XDRGTKprint("M1\n");
          RF(band);
        }
        ShowFreq();
        break;

      case 'T':
        unsigned int XDRfreq;
        XDRfreq = atoi(buff + 1);
        if (XDRfreq != freq * 10) {
          if (XDRfreq > 27001) {
            XDRGTKprint("M0\n");
            XDRGTKTune(XDRfreq / 10);
          } else if (XDRfreq > 143) {
            frequency5 = XDRfreq;
            if (band != 5) {
              band = 5;
              RF(band);
              XDRGTKprint("M1\n");
            } else {
              radio.SetFreqAM(frequency5);
            }
          }
          ShowFreq();
          XDRshowmillis = millis();
          store = true;
        }
        break;

      case 'Q':
        Squelch = atoi(buff + 1);
        if (Squelch == -1) {
          XDRGTKprint("Q-1\n");
        } else {
          Squelch *= 10;
          XDRGTKprint("Q\n");
          XDRGTKprint(String(Squelch / 10));
        }
        break;

      case 'S':
        radio.setMute();
        if (buff[1] == 'a') {
          XDRscanner_start = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'b') {
          XDRscanner_end = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'c') {
          XDRscanner_step = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'f') {
          XDRscanner_filter = atol(buff + 2);
        } else if (XDRscanner_start > 0 && XDRscanner_end > 0 && XDRscanner_step > 0 && XDRscanner_filter >= 0) {
          XDRscanner_old = frequency0;
          if (XDRscanner_filter < 0) {
            BWset = 1;
          } else if (XDRscanner_filter < 16) {
            BWset = XDRscanner_filter + 1;
          }
          doBW();
          XDRGTKprint("U");
          for (XDRfreq_scan = XDRscanner_start; XDRfreq_scan <= XDRscanner_end; XDRfreq_scan += XDRscanner_step)
          {
            radio.SetFreq(XDRfreq_scan);
            Display.writeNum("freq.val", XDRfreq_scan);
            XDRGTKprint(String(XDRfreq_scan * 10, DEC));
            XDRGTKprint("=");
            delay(10);
            radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
            XDRGTKprint(String((SStatus / 10) + 10, DEC));
            XDRGTKprint(",");
          }
          XDRGTKprint("\n");
        }
        radio.SetFreq(XDRscanner_old);
        ShowFreq();
        BWset = XDRBWsetold;
        doBW();
        radio.setUnMute();
        break;

      case 'Y':
        VolSet = atoi(buff + 1);
        radio.setUnMute();
        radio.setVolume((VolSet - 70) / 10);
        XDRGTKprint("Y" + String(VolSet) + "\n");
        break;

      case 'x':
        XDRGTKprint("OK\nT" + String(frequency0 * 10) + "\n");
        store = true;
        break;

      case 'X':
        XDRGTKTCP = false;
        XDRGTK = false;
        store = true;
        XDRMute = false;
        USBstatus = false;
        break;

      case 'Z':
        byte ANT;
        ANT = atol(buff + 1);
        switch (ANT) {
          case 0:
            if (!UHF) digitalWrite(RFC, LOW);
            break;

          case 1:
            if (!UHF) digitalWrite(RFC, HIGH);
            break;

          case 2:
            // Antenna C
            break;

          case 3:
            // Antenna D
            break;
        }
        XDRGTKprint("Z" + String(ANT) + "\n");
        break;
    }
    XDRGTKdata = false;
  }

  if (millis() >= signalstatustimer + 66) {
    if (band == 5) {
      XDRGTKprint("Sm");
    } else {
      if (!StereoToggle ) {
        XDRGTKprint("SS");
      } else if (Stereostatus) {
        XDRGTKprint("Ss");
      } else {
        XDRGTKprint("Sm");
      }
    }
    XDRGTKprint(String(((SStatus * 100) + 10875) / 1000) + "." + String(abs(((SStatus * 100) + 10875) / 100 % 10)) + "," + String(WAM / 10) + ",-1\n\n");
    signalstatustimer = millis();
  }
}

void XDRGTKTune(unsigned int freqtemp) {
  if (freqtemp >= LowEdgeSet0 * 100 && freqtemp <= HighEdgeSet0 * 100) {
    frequency0 = freqtemp;
    if (band != 0) {
      RF(0);
      band = 0;
    } else {
      radio.SetFreq(frequency0);
    }
  } else if (UHF && freqtemp >= LowEdgeSet1 * 100 && freqtemp <= HighEdgeSet1 * 100) {
    frequency1 = freqtemp;
    if (band != 1) {
      RF(1);
      band = 1;
    } else {
      Frontend.SetFreq(frequency1 - (IF * 100), offset);
    }
  } else if (UHF && freqtemp >= LowEdgeSet2 * 100 && freqtemp <= HighEdgeSet2 * 100) {
    frequency2 = freqtemp;
    if (band != 2) {
      RF(2);
      band = 2;
    } else {
      Frontend.SetFreq(frequency2 - (IF * 100), offset);
    }
  } else if (UHF && freqtemp >= LowEdgeSet3 * 100 && freqtemp <= HighEdgeSet3 * 100) {
    frequency3 = freqtemp;
    if (band != 3) {
      RF(3);
      band = 3;
    } else {
      Frontend.SetFreq(frequency3 - (IF * 100), offset);
    }
  } else if (UHF && freqtemp >= LowEdgeSet4 * 100 && freqtemp <= HighEdgeSet4 * 100) {
    frequency4 = freqtemp;
    if (band != 4) {
      RF(4);
      band = 4;
    } else {
      Frontend.SetFreq(frequency4 - (IF * 100), offset);
    }
  } else if (!UHF && freqtemp >= LowEdgeSet6 * 100 && freqtemp <= HighEdgeSet6 * 100) {
    frequency6 = freqtemp;
    if (band != 6) {
      RF(6);
      band = 6;
    } else {
      radio.SetFreq(frequency6 - converteroffset * 100);
    }
  } else {
    switch (band) {
      case 0: freqtemp = frequency0; break;
      case 1: freqtemp = frequency1; break;
      case 2: freqtemp = frequency2; break;
      case 3: freqtemp = frequency3; break;
      case 4: freqtemp = frequency4; break;
      case 6: freqtemp = frequency6; break;
    }
  }
  freq = freqtemp;
}

void passwordcrypt(void) {
  int generated = 0;
  while (generated < 16) {
    byte randomValue = random(0, 26);
    char letter = randomValue + 'a';
    if (randomValue > 26) letter = (randomValue - 26);
    saltkey.setCharAt(generated, letter);
    generated ++;
  }

  salt = saltkey + password;
  cryptedpassword = String(sha1(salt));
}

void passwordgenerator(void) {
  int generated = 0;
  while (generated < 5) {
    byte randomValue = random(0, 26);
    char letter = randomValue + 'A';
    if (randomValue > 26) letter = (randomValue - 26);
    password.setCharAt(generated, letter);
    generated ++;
  }
}

void tryWiFi(void) {
  if (wc.autoConnect()) {
    Server.begin();
    if (stationlist == 1) Udp.begin(9031);
  } else {
    wifiretry = true;
    Display.writeStr("page 26");
    while (wifiretry) Display.NextionListen();
  }
}
#endif