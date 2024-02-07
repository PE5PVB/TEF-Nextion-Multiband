#ifndef ADF4351_H
#define ADF4351_H

#include <Arduino.h>

class ADF4351 {
  public:
    void Power(bool OnOff);
    void Init(uint8_t LE, uint32_t Ref);
    void SetFreq(uint32_t freq_Hz, int8_t offset);

  private:
    struct {
      uint16_t Integer;
      uint16_t Frac;
    } R0;
	
    struct {
      uint16_t Mod;
    } R1;
	
    struct {
      uint8_t  Div;
    } R4;
	
    uint32_t RefIn;
    uint8_t pin_LE;
    void WriteRegister(uint32_t data);
};
#endif