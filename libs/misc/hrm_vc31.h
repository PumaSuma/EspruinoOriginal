/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2019 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * VC31 heart rate sensor - additional info
 * ----------------------------------------------------------------------------
 */

#ifndef EMULATED

// Hack to fix Eclipse syntax lint
#ifndef PACKED_FLAGS
#define PACKED_FLAGS
#endif
// ---

// VC31 info shared between VC31A/B
typedef struct {
  bool isWearing;
  int8_t isWearCnt, unWearCnt; // counters for switching worn/unworn state
  uint16_t ppgValue; // current PPG value
  uint16_t ppgLastValue; // last PPG value
  int16_t ppgOffset; // PPG 'offset' value. When PPG adjusts we change the offset so it matches the last value, then slowly adjust 'ppgOffset' back down to 0
  uint8_t wasAdjusted; // true if LED/etc adjusted since the last reading
  uint16_t envValue; // env value (but VC31B has 3 value slots so we just use the one we know is ok here)
  // the meaning of these is device-dependent but it's nice to have them in one place
  uint8_t irqStatus;
  uint8_t raw[12];
  // settings
  bool allowGreenAdjust; // allow automatic adjustment of LED power
  bool allowWearDetect; // allow automatic check for whether HRM is worn
  bool pushEnvData; // call jsbangle_push_event to push data for every received ENV sample
  bool useStaticSampleTime; // use a static time period for samples, rather than the time between them
} PACKED_FLAGS VC31Info;

extern VC31Info vcInfo;


typedef struct {
  uint16_t ppg_raw;      // raw VC31 sample, before offset correction / amplification
  uint8_t ps_raw;        // raw proximity slot value (0..15 on VC31B)
  uint8_t env_raw;       // raw environment slot value (0..15 on VC31B)
  uint8_t led_current;   // current LED current for SLOT0
  uint8_t pd_res;        // current PD resistance for SLOT0
  uint8_t irq_status;    // latest IRQ status register value
  bool worn_stable;      // hysteresis-based wear detect status
  bool ppg_valid;        // worn + not obviously saturated
  bool ppg_sat_high;     // near full-scale saturation
  bool ppg_sat_low;      // near zero saturation
  bool ppg_fresh;        // new sample since last read
} PACKED_FLAGS DriverHrmRawStatus;

bool hrmGetDriverRawStatus(DriverHrmRawStatus *out);


#endif
