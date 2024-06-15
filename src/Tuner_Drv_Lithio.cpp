#include "TEF6686.h"
#include <stdarg.h>

#define High_16bto8b(a) ((uint8_t)((a) >> 8))
#define Low_16bto8b(a) ((uint8_t)(a ))
#define Convert8bto16b(a) ((uint16_t)(((uint16_t)(*(a))) << 8 |((uint16_t)(*(a+1)))))

void devTEF_Set_Cmd(TEF_MODULE module, uint8_t cmd, uint16_t len, ...) {
  uint16_t i;
  uint8_t buf[20];
  uint16_t temp;
  va_list vArgs;
  va_start(vArgs, len);
  buf[0] = module;
  buf[1] = cmd;
  buf[2] = 1;

  for (i = 3; i < len; i++) {
    temp = va_arg(vArgs, int);
    buf[i++] = High_16bto8b(temp);
    buf[i] = Low_16bto8b(temp);
  }

  va_end(vArgs);
  Tuner_WriteBuffer(buf, len);
}

bool devTEF_Get_Cmd(TEF_MODULE module, uint8_t cmd, uint8_t *receive, uint16_t len) {
  uint8_t buf[3];
  buf[0] = module;
  buf[1] = cmd;
  buf[2] = 1;

  Tuner_WriteBuffer(buf, 3);
  return Tuner_ReadBuffer(receive, len);
}

void devTEF_Radio_Tune_To (uint16_t frequency) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 4, frequency);
}

void devTEF_Radio_Tune_AM (uint16_t frequency) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Tune_To, 7, 1, frequency);
}

void devTEF_Radio_Set_Bandwidth(uint8_t mode, uint16_t bandwidth, uint16_t control_sensitivity, uint16_t low_level_sensitivity) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Bandwidth, 11, mode, bandwidth, control_sensitivity, low_level_sensitivity);
}

void devTEF_Radio_Set_BandwidthAM(uint8_t mode, uint16_t bandwidth, uint16_t control_sensitivity, uint16_t low_level_sensitivity) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_Bandwidth, 7, mode, bandwidth, control_sensitivity, low_level_sensitivity);
}

void devTEF_Radio_Set_Noiseblanker_AM(uint8_t mode, uint16_t start) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_NoiseBlanker, 7, mode, start);
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_NoiseBlanker_Audio, 7, mode, 1000);
}

void devTEF_Radio_Set_Attenuator_AM(uint16_t start) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_Antenna, 5, start);
}

void devTEF_Radio_Set_CoChannel_AM(uint8_t mode, uint16_t start, uint8_t level) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_CoChannelDet, 11, mode, 2, start, 1000, level);
}

void devTEF_Radio_Set_LevelOffset(int16_t offset) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_LevelOffset, 5, offset - 70);
}

void devTEF_Radio_Set_AMLevelOffset(int16_t offset) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_LevelOffset, 5, offset - 70);
}

void devTEF_Radio_Set_RDS(bool fullsearchrds) {
  if (fullsearchrds) devTEF_Set_Cmd(TEF_FM, Cmd_Set_RDS, 9, 3, 1, 0); else devTEF_Set_Cmd(TEF_FM, Cmd_Set_RDS, 9, 1, 1, 0);
}

void devTEF_Radio_Set_Highcut_Level(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Highcut_Level, 9, mode, start, slope);
}

void devTEF_Radio_Set_Highcut_Noise(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Highcut_Noise, 9, mode, start, slope);
}

void devTEF_Radio_Set_Highcut_Mph(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Highcut_Mph, 9, mode, start, slope);
}

void devTEF_Radio_Set_Highcut_Max(uint8_t mode, uint16_t limit) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Highcut_Max, 7, mode, limit);
}

void devTEF_Radio_Set_StHiBlend_Level(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StHiBlend_Level, 9, mode, start, slope);
}

void devTEF_Radio_Set_StHiBlend_Noise(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StHiBlend_Noise, 9, mode, start, slope);
}

void devTEF_Radio_Set_StHiBlend_Mph(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StHiBlend_Mph, 9, mode, start, slope);
}

void devTEF_Radio_Set_StHiBlend_Max(uint8_t mode, uint16_t limit) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StHiBlend_Max, 7, mode, limit);
}

void devTEF_Radio_Set_Stereo_Level(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Stereo_Level, 9, mode, start, slope);
}

void devTEF_Radio_Set_NoisBlanker(uint8_t mode, uint16_t start) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_NoiseBlanker, 7, mode, start);
}

void devTEF_Radio_Set_Stereo_Noise(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Stereo_Noise, 9, mode, start, slope);
}

void devTEF_Radio_Set_Stereo_Mph(uint8_t mode, uint16_t start, uint16_t slope) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Stereo_Mph, 9, mode, start, slope);
}

void devTEF_Radio_Set_MphSuppression(bool mph) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_MphSuppression, 5, mph);
}

void devTEF_Radio_Set_ChannelEqualizer(bool eq) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_ChannelEqualizer, 5, eq);
}

void devTEF_Radio_Set_Stereo_Min(bool mode) {
  if (mode) devTEF_Set_Cmd(TEF_FM, Cmd_Set_Stereo_Min, 7, 2); else devTEF_Set_Cmd(TEF_FM, Cmd_Set_Stereo_Min, 7, 0);
}

void devTEF_Radio_Set_RFAGC(uint16_t agc) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_RFAGC, 7, agc * 10, 0);
}

void devTEF_Radio_Set_AMRFAGC(uint16_t agc) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_RFAGC, 7, agc * 10, 0);
}

void devTEF_Radio_Set_Deemphasis(uint16_t timeconstant) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Deemphasis, 5, timeconstant);
}

void devTEF_Radio_Specials(uint16_t audio) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Specials, 5, audio);
}

void devTEF_Audio_Set_Volume(int16_t volume) {
  devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_Volume, 5, volume * 10);
}

void devTEF_Audio_Set_Mute(uint8_t mode) {
  devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_Mute, 5, mode);
}

void devTEF_APPL_Set_OperationMode(bool mode) {
  devTEF_Set_Cmd(TEF_APPL, Cmd_Set_OperationMode, 5, mode);
}

void devTEF_APPL_Set_StereoImprovement(bool mode) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StereoImprovement, 5, mode);
}

void devTEF_APPL_Set_StereoBandBlend_Time(uint16_t attack, uint16_t decay) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StBandBlend_Time, 7, attack, decay);
}

void devTEF_APPL_Set_StereoBandBlend_Gain(uint16_t band1, uint16_t band2, uint16_t band3, uint16_t band4) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StBandBlend_Gain, 11, band1, band2, band3, band4);
}

void devTEF_APPL_Set_StereoBandBlend_Bias(int16_t band1, int16_t band2, int16_t band3, int16_t band4) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_StBandBlend_Bias, 11, band1, band2, band3, band4);
}

void devTEF_Radio_Set_Softmute_Max_FM(uint8_t mode) {
  devTEF_Set_Cmd(TEF_FM, Cmd_Set_Softmute_Max, 7, uint16_t(mode), uint16_t(200));
}

void devTEF_Radio_Set_Softmute_Max_AM(uint8_t mode) {
  devTEF_Set_Cmd(TEF_AM, Cmd_Set_Softmute_Max, 7, uint16_t(mode), uint16_t(250));
}

bool devTEF_APPL_Get_Operation_Status (uint8_t *bootstatus) {
  uint8_t buf[2];
  uint16_t r = devTEF_Get_Cmd(TEF_APPL, Cmd_Get_Operation_Status, buf, sizeof(buf));
  *bootstatus = Convert8bto16b(buf);
  return r;
}

bool devTEF_Radio_Get_Processing_Status (uint16_t *highcut, uint16_t *stereo, uint16_t *sthiblend, uint8_t *stband_1, uint8_t *stband_2, uint8_t *stband_3, uint8_t *stband_4) {
  uint8_t buf[12];
  uint16_t r = devTEF_Get_Cmd(TEF_FM, Cmd_Get_Processing_Status, buf, sizeof(buf));
  *highcut = Convert8bto16b(buf + 2) / 10;
  *stereo = Convert8bto16b(buf + 4) / 10;
  *sthiblend = Convert8bto16b(buf + 6) / 10;
  uint16_t stband_1_2 = Convert8bto16b(buf + 8);
  uint16_t stband_3_4 = Convert8bto16b(buf + 10);
  *stband_1 = High_16bto8b(stband_1_2);
  *stband_2 = Low_16bto8b(stband_1_2);
  *stband_3 = High_16bto8b(stband_3_4);
  *stband_4 = Low_16bto8b(stband_3_4);
  return r;
}

bool devTEF_Radio_Get_Quality_Status (uint16_t *status, int16_t *level, uint16_t *usn, uint16_t *wam, int16_t *offset, uint16_t *bandwidth, uint16_t *mod, int8_t *snr) {
  uint8_t buf[14];
  uint16_t r = devTEF_Get_Cmd(TEF_FM, Cmd_Get_Quality_Data, buf, sizeof(buf));
  *status = Convert8bto16b(buf);
  *level = Convert8bto16b(buf + 2);
  *usn = Convert8bto16b(buf + 4);
  *wam = Convert8bto16b(buf + 6);
  *offset = Convert8bto16b(buf + 8);
  *bandwidth = Convert8bto16b(buf + 10) / 10;
  *mod = Convert8bto16b(buf + 12) / 10;
  if (*level < -200) *level = -200;
  if (*level > 1200) *level = 1200;
  *snr = int(0.46222375 * (float)(*level) / 10 - 0.082495118 * (float)(*usn) / 10) + 10;
  return r;
}

bool devTEF_Radio_Get_Quality_Status_AM (int16_t *level, uint16_t *noise, uint16_t *cochannel, int16_t *offset, uint16_t *bandwidth, uint16_t *mod, int8_t *snr) {
  uint8_t buf[14];
  uint16_t r = devTEF_Get_Cmd(TEF_AM, Cmd_Get_Quality_Data, buf, sizeof(buf));

  *level = Convert8bto16b(buf + 2);
  *noise = Convert8bto16b(buf + 4);
  *cochannel = Convert8bto16b(buf + 6);
  *offset = Convert8bto16b(buf + 8);
  *bandwidth = Convert8bto16b(buf + 10) / 10;
  *mod = Convert8bto16b(buf + 12) / 10;
  if (*level < -200) *level = -200;
  if (*level > 1200) *level = 1200;
  *snr = int(0.46222375 * (float)(*level) / 10 - 0.082495118 * (float)(*noise / 50) / 10) + 10;
  return r;
}


bool devTEF_Radio_Get_RDS_Status (uint16_t *status, uint16_t *A_block, uint16_t *B_block, uint16_t *C_block, uint16_t *D_block, uint16_t *dec_error) {
  uint8_t buf[12];
  uint8_t r = devTEF_Get_Cmd(TEF_FM, Cmd_Get_RDS_Status, buf, sizeof(buf));
  *status = Convert8bto16b(buf);
  *A_block = Convert8bto16b(buf + 2);
  *B_block = Convert8bto16b(buf + 4);
  *C_block = Convert8bto16b(buf + 6);
  *D_block = Convert8bto16b(buf + 8);
  *dec_error = Convert8bto16b(buf + 10);
  return r;
}

bool devTEF_Radio_Get_RDS_Data (uint16_t *status, uint16_t *A_block, uint16_t *B_block, uint16_t *C_block, uint16_t *D_block, uint16_t *dec_error) {
  uint8_t buf[12];
  uint8_t r = devTEF_Get_Cmd(TEF_FM, Cmd_Get_RDS_Data, buf, sizeof(buf));
  *status = Convert8bto16b(buf);
  *A_block = Convert8bto16b(buf + 2);
  *B_block = Convert8bto16b(buf + 4);
  *C_block = Convert8bto16b(buf + 6);
  *D_block = Convert8bto16b(buf + 8);
  *dec_error = Convert8bto16b(buf + 10);
  return r;
}

bool devTEF_Radio_Get_Stereo_Status(uint16_t *status) {
  uint8_t buf[2];
  uint16_t r = devTEF_Get_Cmd(TEF_FM, Cmd_Get_Signal_Status, buf, sizeof(buf));

  *status = Convert8bto16b(buf);
  return r;
}

bool devTEF_Radio_Get_Identification (uint16_t *device, uint16_t *hw_version, uint16_t *sw_version) {
  uint8_t buf[6];
  uint16_t r = devTEF_Get_Cmd(TEF_APPL, Cmd_Get_Identification, buf, sizeof(buf));

  *device = Convert8bto16b(buf);
  *hw_version = Convert8bto16b(buf + 2);
  *sw_version = Convert8bto16b(buf + 4);
  return r;
}

void devTEF_Radio_Set_Wavegen(bool mode, int16_t amplitude, uint16_t freq) {
  if (mode) {
    devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_Input, 5, 240);
    devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_WaveGen, 15, 5, 0, amplitude * 10, freq, amplitude * 10 , freq);
  } else {
    devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_Input, 5, 0);
    devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_WaveGen, 15, 0);
  }
}

void devTEF_Radio_Set_I2S_Input(bool mode) {
  if (mode) {
    devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_Input, 5, 32);
  } else {
    devTEF_Set_Cmd(TEF_AUDIO, Cmd_Set_Input, 5, 0);
  }
}

void devTEF_Radio_Set_GPIO(uint8_t mode) {
  if (mode == 0) devTEF_Set_Cmd(TEF_APPL, Cmd_Set_GPIO, 9, 0, 33, 2);
  if (mode == 1) devTEF_Set_Cmd(TEF_APPL, Cmd_Set_GPIO, 9, 0, 33, 3);
  if (mode == 2) devTEF_Set_Cmd(TEF_APPL, Cmd_Set_GPIO, 9, 0, 32, 2);
  if (mode == 3) devTEF_Set_Cmd(TEF_APPL, Cmd_Set_GPIO, 9, 0, 32, 3);
}