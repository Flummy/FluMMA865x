// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
//    MMA865x Accelerometer Driver Library for Arduino, Version 1, 2015-11-12
//    http://koffein.org/E/FluMMA865x/
//    This work is based on the efforts of other open source engineers, please see Credits.txt
//    Copyright (c) 2015 Herwig Wittmann <lab15@koffein.org>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// Basic Layout of all Registers: Registers can be accessed by field .f or by value .v, see below
// Data Source registers have an additional .print() method to display their status
// Only features that are actually used consume flash program storage space.

// Summary:
// enum  RegisterList
// union StatusRegT         // Register 0x00 STATUS
// union IntSourceRegT      // Register 0x0C INT_SOURCE
// union XyzDataCfgRegT     // Register 0x0E XYZ_DATA_CFG Datasheet p. 31
// union HpFilterCutoffRegT // Register 0x0F HP_FILTER_CUTOFF AN4071 p. 5
// union FfMtCfgRegT        // Register 0x15 FF_MT_CFG Freefall/Motion
// union FfMtSrcRegT        // Register 0x16 FF_MT_SRC
// union FfMtThsRegT        // Reguster 0x17 FF_MT_THS 
// union TransientCfgRegT   // Register 0x1D TRANSIENT_CFG Datasheet p. 42
// union TransientSrcRegT   // Register 0x1E TRANSIENT_SRC Datasheet p. 43
// union TransientThsRegT   // Register 0x1F TRANSIENT_THS
// union PulseCfgRegT       // Register 0x21 PULSE_CFG
// union PulseSrcRegT       // Register 0x22 PULSE_SRC
// union CtrlReg1T          // Register 0x2A CTRL_REG1 System Control 1: ACTIVE/STANDBY, fas read, etc
// union CtrlReg2T          // Register 0x2B CTRL_REG2 System Control 2: Oversampling Mode, etc.
// union CtrlReg3T          // Register 0x2C CTRL_REG3 Interrupt Control/Configuration
// union CtrlReg4T          // Register 0x2D CTRL_REG4 Enables functional blocks
// union CtrlReg5T          // Register 0x2E CTRL_REG5 Routes interrupts to pins


#pragma once

#include <Streaming.h>


class FluMMA865xR
{
public:
  enum RegisterList
  {
    STATUS   = 0,     // 0x00 - MMA8652 only
    F_STATUS = 0,     // 0x00
    OUT_X_MSB,        // 0x01    
    OUT_X_LSB,        // 0x02
    OUT_Y_MSB,        // 0x03
    OUT_Y_LSB,        // 0x04
    OUT_Z_MSB,        // 0x05
    OUT_Z_LSB,        // 0x06
    RSVD_0,
    RSVD_1,
    F_SETUP,          // 0x09 - MMA8652 only
    TRIG_CFG,         // 0x0A - MMA8652 only
    SYSMOD,           // 0x0B
    INT_SOURCE,       // 0x0C
    WHO_AM_I,         // 0x0D   
    XYZ_DATA_CFG,     // 0x0E
    HP_FILTER_CUTOFF, // 0x0F - MMA8652 only
    PL_STATUS,        // 0x10
    PL_CFG,           // 0x11
    PL_COUNT,         // 0x12
    PL_BF_ZCOMP,      // 0x13
    P_L_THS_REG,      // 0x14
    FF_MT_CFG,        // 0x15
    FF_MT_SRC,        // 0x16
    FF_MT_THS,        // 0x17
    FF_MT_COUNT,      // 0x18
    RSVD_2,
    RSVD_3,
    RSVD_4,
    RSVD_5,
    TRANSIENT_CFG,    // 0x1D - MMA8652 only
    TRANSIENT_SRC,    // 0x1E - MMA8652 only
    TRANSIENT_THS,    // 0x1F - MMA8652 only
    TRANSIENT_COUNT,  // 0x20 - MMA8652 only
    PULSE_CFG,        // 0x21 - MMA8652 only
    PULSE_SRC,        // 0x22 - MMA8652 only
    PULSE_THSX,       // 0x23 - MMA8652 only
    PULSE_THSY,       // 0x24 - MMA8652 only
    PULSE_THSZ,       // 0x25 - MMA8652 only
    PULSE_TMLT,       // 0x26 - MMA8652 only
    PULSE_LTCY,       // 0x27 - MMA8652 only
    PULSE_WIND,       // 0x28 - MMA8652 only
    ASLP_COUNT,       // 0x29
    CTRL_REG1,        // 0x2A
    CTRL_REG2,        // 0x2B
    CTRL_REG3,        // 0x2C
    CTRL_REG4,        // 0x2D
    CTRL_REG5,        // 0x2E
    OFF_X,            // 0x2F
    OFF_Y,            // 0x30
    OFF_Z,            // 0x31
  };


  union StatusRegT // Register 0x00 STATUS
  {
    struct
    {
      boolean XDR   :1;  
      boolean YDR   :1;
      boolean ZDR   :1;
      boolean ZYXDR :1;
      boolean XOW   :1;
      boolean YOW   :1;
      boolean ZOW   :1;                        
      boolean ZYXOW :1;
    } f;
  
    uint8_t v;

    void print()
    {
      Serial << F("status ");
      if(f.ZYXDR) Serial << F("ZYXDR ");
      if(f.XDR)   Serial << F("XDR ");
      if(f.YDR)   Serial << F("YDR ");
      if(f.ZDR)   Serial << F("ZDR ");
      if(f.ZYXOW) Serial << F("ZYXOW ");
      if(f.XOW)   Serial << F("XOW ");
      if(f.YOW)   Serial << F("YOW ");
      if(f.ZOW)   Serial << F("ZOW");
      Serial << "\n";
    };
  };


  union IntSourceRegT // Register 0x0C INT_SOURCE
  {
    struct
    {
      boolean SRC_DRDY   :1;
      boolean SRC_RSVD   :1;
      boolean SRC_FF_MT  :1;
      boolean SRC_PULSE  :1;
      boolean SRC_LNDPRT :1;
      boolean SRC_TRANS  :1;
      boolean SRC_FIFO   :1;  
      boolean SRC_ASLP   :1;
    } f;

    uint8_t v;

    void print()
    {
      Serial << F("intSource ");
      if(f.SRC_DRDY)   Serial << F("DRDY ");
      if(f.SRC_RSVD)   Serial << F("RSVD! ");
      if(f.SRC_FF_MT)  Serial << F("FF_MT ");
      if(f.SRC_PULSE)  Serial << F("PULSE ");
      if(f.SRC_LNDPRT) Serial << F("LNDPRT ");
      if(f.SRC_TRANS)  Serial << F("TRANS ");
      if(f.SRC_FIFO)   Serial << F("FIFO ");
      if(f.SRC_ASLP)   Serial << F("ASLP");
      Serial << "\n";
    }
  };


  union XyzDataCfgRegT // Register 0x0E XYZ_DATA_CFG Datasheet p. 31
  {
    enum AccelFsrT
    {
      AFS_2g = 0, AFS_4g, AFS_8g
    };

    struct
    {
      uint8_t FS      :2; // 00 = +/- 2g; 01 = +/- 4g; 10 = +/- 8g
      uint8_t RSVD23  :2;
      boolean HPF_OUT :1; // if set, FIFO and DATA registers both will contain high-pass filtered data
      uint8_t RSVD567 :3;
    } f;

    uint8_t v;
  };


  union HpFilterCutoffRegT // Register 0x0F HP_FILTER_CUTOFF AN4071 p. 5
  {
    struct
    {
      uint8_t SEL           :2;
      uint8_t RSVD01        :2;
      boolean Pulse_LPF_EN  :1;
      boolean Pulse_HPF_BYP :1;
      uint8_t RSVD67        :2;
    } f;

    uint8_t v;
  };


  union FfMtCfgRegT // Register 0x15 FF_MT_CFG Freefall/Motion config
  {
    struct
    {
      uint8_t RSVD012 :3;
      boolean XEFE    :1; // Event flag enable on X event: raise flag on accel > FF_MT_THS threshold
      boolean YEFE    :1;
      boolean ZEFE    :1;
      boolean OAE     :1; // OAE = 1 "logical OR" motion detection; OAE = 0 "logical AND) freefall detection 
      boolean ELE     :1; // Event Latch Enable = 0: realtime status
                          // Event Latch Enable = 1: FF_MT_SRC event flags are frozen when EA bit gets set
                          // reading FF_MT_SRC clears EA and all FF_MT_SRC bits
    } f;

    uint8_t v;
  };


  union FfMtSrcRegT // Register 0x16 FF_MT_SRC Freefall/Motion source register
  {
    struct
    {                  // All bits read zero if corresponding XEFE/YEFE/ZEFE control bit is set to zero
      boolean XHP  :1; // X-motion polarity flag: 0 event was positive g, 1 event was negative g
      boolean XHE  :1; // X-motion flag:          0 no x motion event,    1 x motion exceeded FF_MT_THS threshold
      boolean YHP  :1;
      boolean YHE  :1;
      boolean ZHP  :1;
      boolean ZHE  :1;
      boolean RSVD :1;
      boolean EA   :1; // Event Active flag: 1 one or more event flags have been asserted, see FfNtCfgReg:OAE
    } f;

    uint8_t v;

    void print()
    {
      if(!f.EA) return;
      Serial << F("motion ");
      if(f.XHE) Serial << "X" << (f.XHP ? "-" : "+") << " ";
      if(f.YHE) Serial << "Y" << (f.YHP ? "-" : "+") << " ";
      if(f.ZHE) Serial << "Z" << (f.ZHP ? "-" : "+");
      Serial << "\n";
    };
  };


  union FfMtThsRegT // Register 0x17 FF_MT_THS Freefall/Motion treshhold register
  {
    struct
    {
      uint8_t THS    :7; // freefall: X/Y/Z values are lower or equal; resolution 0.063g/LSB independent of range
                         // motion: X/Y/Z is higher
      boolean DBCNTM :1; // Debounce counter mode: 1 counter cleared to 0 when event no longer active
                         // 0: decrement by 1 when event no longer true 
                         //    until counter reaches 0 or event becomes active
    } f;

    uint8_t v;
  };


  union TransientCfgRegT // Register 0x1D TRANSIENT_CFG Datasheet p. 42
  {
    struct
    {
      boolean HPF_BYP :1; // bypass high-pass filter: false: Data to transient accel detection is through high-pass  (default)
      boolean XTEFE   :1; // event flag enable for x-transient acceleration > treshhold
      boolean YTEFE   :1;
      boolean ZTEFE   :1;
      boolean ELE     :1; // transient event flags are latched into TRANSIENT_SRC reg = not cleared until read
      uint8_t RSVD567 :3;
    } f;
    uint8_t v;
  };


  union TransientSrcRegT // Register 0x1E TRANSIENT_SRC Datasheet p. 43
  {
    struct
    {
      boolean X_Trans_Pol :1; // Polarity of X-Transient Event 0=pos 1=neg
      boolean XTRANSE     :1; // X-transient event: X-transient acceleration > TRANSIENT_THS has occured
      boolean Y_Trans_Pol :1;
      boolean YTRANSE     :1;
      boolean Z_Trans_Pol :1;
      boolean ZTRANSE     :1;
      boolean EA          :1; // Event Active flag =1: One or more event flags have been asserted
    } f;

    void print()
    {
      if(!f.EA) return;
      Serial << F("transient ");
      if(f.XTRANSE) Serial << "X" << (f.X_Trans_Pol ? "-" : "+") << " ";
      if(f.YTRANSE) Serial << "Y" << (f.Y_Trans_Pol ? "-" : "+") << " ";
      if(f.ZTRANSE) Serial << "Z" << (f.Z_Trans_Pol ? "-" : "+");
      Serial << "\n";
    };
  
    uint8_t v;
  };


  union TransientThsRegT // Register 0x1F TRANSIENT_THS transient treshhold register
  {
    struct
    {
      uint8_t THS    :7; // event if high-pass filtered acel value exceeds treshhold
      boolean DBCNTM :1; // Debounce counter mode: 1 Increments or clears counter
                         // 0: Increments or decrements debounce (default)
    } f;

    uint8_t v;
  };


  union PulseCfgRegT // Register 0x21 PULSE_CFG
  {
    struct
    {
      boolean XSPEFE :1; // Event flag enable for single pulse event on X-axis
      boolean XDPEFE :1; // --"--                 double --"--
      boolean YSPEFE :1;
      boolean YDPEFE :1;
      boolean ZSPEFE :1;
      boolean ZDPEFE :1;
      boolean ELE    :1; // =1 Pulse event flags are latched into PULSE_SRC, reading PULSE_SRC clears event flag
      boolean DPA    :1; // Double Pulse abort: 0= Double pulse detection is not aborted if the start of a pulse
                         // is detected during the time period specified by the PULSE_LTCY register. (Default.)
                         // =1: Momentarily suspends double tap detection if start of a pulse is detected
                         // during PULSE_LTCY, and the pulse ends before the end of PULSE_LTCY period.
    } f;

    uint8_t v;
  };

  
  union PulseSrcRegT // Register 0x22 PULSE_SRC
  {
    struct
    {
      boolean PolX :1; // Pulse polarity of X-axis event: 0= Pulse event that triggered interrupt was positive
      boolean PolY :1;
      boolean PolZ :1;
      boolean DPE  :1; // Double pulse on first event: 0= Single pulse event triggered interrupt; 1= Double...
      boolean AxX  :1; // X-axis event 0= No interrupt 1= X-axis event has occured
      boolean AxY  :1;
      boolean AxZ  :1;
      boolean EA   :1; // Event Active Flag 0= No interrupt has been generated 1= One ore more interrupt events
    } f;

    uint8_t v;

    void print()
    {
      if(!f.EA) return;
      Serial << F("tap ");
      if(f.DPE) Serial << F("DOUBLE ");
      else      Serial << F("SINGLE ");

      if(f.AxX) Serial << "X" << (f.PolX ? "-" : "+") << " ";
      if(f.AxY) Serial << "Y" << (f.PolY ? "-" : "+") << " ";
      if(f.AxZ) Serial << "Z" << (f.PolZ ? "-" : "+");
      Serial << "\n";
    };
  };


  union CtrlReg1T // Register 0x2A CTRL_REG1 System Control 1 register
  {
    enum AccelOdrT 
    {
      AODR_800HZ = 0, AODR_400HZ, AODR_200HZ, AODR_100HZ, AODR_50HZ, AODR_12_5HZ, AODR_6_25HZ, AODR_1_56HZ
    };
  
    struct
    {
      boolean   ACTIVE    :1; // 0= STANDBY mode (default); 1= ACTIVE mode
      boolean   F_READ    :1; // 1= Fast-read mode: Data format is limited to single byte
      boolean   LNOISE    :1; // RSVD?
      AccelOdrT DR        :3; // DR2 DR1 DR0 Data rate selection
      uint8_t   ASLP_RATE :2; // ASLP_RATE1 ASLP_RATE0 Auto-WAKE sample frequency when device in SLEEP mode
    } f;
  
    uint8_t v;

    void print()
    {
      Serial << F("ctrlReg1=");
      if(f.ACTIVE)    Serial << F("ACTIVE ");
      if(f.F_READ)    Serial << F("F_READ ");
      if(f.DR)        Serial << F("DR=") << f.DR << " ";
      if(f.ASLP_RATE) Serial << F("ASLP_RATE=") << f.ASLP_RATE;
      Serial << "\n";
    }
  };


  union CtrlReg2T // Register 0x2B CTRL_REG2 System Control 2 register
  {
    enum ModeT { Normal = 0, LowNoiseLowPower, HighResolution, LowPower }; // Datasheet Tables 7-8, p. 8
  
    struct
    {
      uint8_t MODS  :2; // ACTIVE mode power scheme selection / Oversampling mode
      boolean SLPE  :1; // 1= Auto-Sleep is enabled
      uint8_t SMODS :2; // SLEEP mode power scheme selection / Oversampling mode
      boolean RSVD  :1;
      boolean RST   :1; // Writing 1 to the RST bit immediately resets the device, no matter which mode it is in
      boolean ST    :1; // Self-Test enable: When ST is set, the X/Y/Z outputs will shift
    } f;
  
    uint8_t v;

    void print()
    {
      Serial << F("ctrlReg2=");
      if(f.MODS)  Serial << F("MODS=") << f.MODS << " ";
      if(f.SLPE)  Serial << F("SLPE ");
      if(f.SMODS) Serial << F("SMODS=") << f.SMODS << " ";
      if(f.RSVD)  Serial << F("RSVD! ");
      if(f.RST)   Serial << F("RST ");
      if(f.ST)    Serial << F("ST");
      Serial << "\n";
    }
  };


  union CtrlReg3T // Register 0x2C CTRL_REG3 Interrupt Control register
  {
    struct
    {
      boolean PP_OD :1; // Push-Pull/Open Drain selection on interrupt pad 0=Push-Pull 1=Open drain
                        // Open-Drain can be used for connecting multiple interrupt signals on the same int line
      boolean IPOL  :1; // Interrupt polarity 0= ACTIVE low (default); 1= ACTIVE high
      boolean RSVD  :1;
      boolean WAKE_FF_MT  :1; // 1= Wake from Freefall/Motion interrupt
      boolean WAKE_PULSE  :1; // 1= Wake from Pulse interrupt
      boolean WAKE_LNDPRT :1; // 1= Wake from Orientation interrupt (Landscape/Portrait)
      boolean WAKE_TRANS  :1; // 1= Wake from Transient interrupt
      boolean FIFO_GATE   :1; // 0 FIFO gate is bypassed, FIFO flushed on transition between WAKE/SLEEP
    } f;
    
  };


  union CtrlReg4T // Register 0x2D CTRL_REG4 Enables functional blocks, routed by interrupt controller to INT1 or 2
  {
    struct
    {
      boolean INT_EN_DRDY   :1; // 0 Data Ready Interrupt Enable
      boolean RSVD          :1;
      boolean INT_EN_FF_MT  :1; // 2 Freefall/Motion IE
      boolean INT_EN_PULSE  :1; // 3 Pulse Detection IE
      boolean INT_EN_LNDPRT :1; // 4 Orientation (Landscape/Portrait) IE
      boolean INT_EN_TRANS  :1; // 5 Transient IE
      boolean INT_EN_FIFO   :1; // 6 FIFO IE
      boolean INT_EN_ASLP   :1; // 7 Auto-SLEEP/WAKE IE
    } f;
  
    uint8_t v;
  };


  union CtrlReg5T // Register 0x2E CTRL_REG5 Interrupt Configuration register
  {
    struct
    {
      boolean INT_CFG_DRDY   :1; // Data Ready 0= Interrupt is routed to INT2 pin (default;) 1= INT1 pin
      boolean RSVD           :1;
      boolean INT_CFG_FF_MT  :1; // Freefall/Motion
      boolean INT_CFG_PULSE  :1; // Pulse
      boolean INT_CFG_LNDPRT :1; // Orientation (Landscape/Portrait)
      boolean INT_CFG_TRANS  :1; // Transient
      boolean INT_CFG_FIFO   :1; // FIFO
      boolean INT_CFG_ASLP   :1; // Auto-Sleep/WAKE
    } f;
  };


};

