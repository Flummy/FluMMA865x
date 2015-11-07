// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
// (c) Flummy 2015 <lab15@koffein.org> All rights reserved.

// Summary:
// enum  RegisterList
// union StatusRegT         // Register 0x00 STATUS
// union IntSourceRegT      // Register 0x0C INT_SOURCE
// union XyzDataCfgRegT     // Register 0x0E XYZ_DATA_CFG Datasheet p. 31
// union HpFilterCutoffRegT // Register 0x0F HP_FILTER_CUTOFF AN4071 p. 5
// union TransientCfgRegT   // Register 0x1D TRANSIENT_CFG Datasheet p. 42
// union TransientSrcRegT   // Register 0x1E TRANSIENT_SRC Datasheet p. 43
// union CtrlReg1T          // Register 0x2A CTRL_REG1
// union CtrlReg2T          // Register 0x2B CTRL_REG2
// union CtrlReg4T          // Register 0x2D CTRL_REG4 Enables functional blocks


#pragma once

#include <Streaming.h>


class MMA865x_Reg
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
    };
  
    uint8_t value;

    void print()
    {
      Serial << F("statusReg=");
      if(ZYXDR) Serial << F("ZYXDR ");
      if(XDR)   Serial << F("XDR ");
      if(YDR)   Serial << F("YDR ");
      if(ZDR)   Serial << F("ZDR ");
      if(ZYXOW) Serial << F("ZYXOW ");
      if(XOW) Serial << F("XOW ");
      if(YOW) Serial << F("YOW ");
      if(ZOW) Serial << F("ZOW");
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
    };

    uint8_t value;

    void print()
    {
      Serial << F("intSourceReg=");
      if(SRC_DRDY)   Serial << F("DRDY ");
      if(SRC_RSVD)   Serial << F("RSVD! ");
      if(SRC_FF_MT)  Serial << F("FF_MT ");
      if(SRC_PULSE)  Serial << F("PULSE ");
      if(SRC_LNDPRT) Serial << F("LNDPRT ");
      if(SRC_TRANS)  Serial << F("TRANS ");
      if(SRC_FIFO)   Serial << F("FIFO ");
      if(SRC_ASLP)   Serial << F("ASLP");
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
    };

    uint8_t value;
  };


  union HpFilterCutoffRegT // Register 0x0F HP_FILTER_CUTOFF AN4071 p. 5
  {
    struct
    {
      uint8_t SEL    :2;
      uint8_t RSVD01 :2;
      boolean Pulse_LPF_EN  :1;
      boolean Pulse_HPF_BYP :1;
      uint8_t RSVD67 :2;
    };

    uint8_t value;
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
    };
    uint8_t value;
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
    };

    void print() //(TransientSrcRegT t)
    {
      Serial << F("Transient=");
      if(EA) Serial << F("EA ");
      if(XTRANSE) Serial << F("XTRANSE ");
      if(YTRANSE) Serial << F("YTRANSE ");
      if(ZTRANSE) Serial << F("ZTRANSE ");
      Serial << "\n";
    };
  
    uint8_t value;
  };




  union CtrlReg1T // Register 0x2A CTRL_REG1
  {
    enum AccelOdrT 
    {
      AODR_800HZ = 0, AODR_400HZ, AODR_200HZ, AODR_100HZ, AODR_50HZ, AODR_12_5HZ, AODR_6_25HZ, AODR_1_56HZ
    };
  
    struct // Stosstrupp said this is type system abuse
    {
      boolean   ACTIVE    :1;
      boolean   F_READ    :1;
      boolean   LNOISE    :1;
      AccelOdrT DR        :3; // DR2 DR1 DR0
      uint8_t   ASLP_RATE :2; // ASLP_RATE1 ASLP_RATE0
    };
  
    uint8_t value;

    void print()
    {
      Serial << F("ctrlReg1=");
      if(ACTIVE)    Serial << F("ACTIVE ");
      if(F_READ)    Serial << F("F_READ ");
      if(DR)        Serial << F("DR=") << DR << " ";
      if(ASLP_RATE) Serial << F("ASLP_RATE=") << ASLP_RATE;
      Serial << "\n";
    }
  };




  union CtrlReg2T // Register 0x2B CTRL_REG2
  {
    enum ModeT { Normal = 0, LowNoiseLowPower, HighResolution, LowPower }; // Datasheet Tables 7-8, p. 8
  
    struct // Stosstrupp said this is type system abuse
    {
      uint8_t MODS  :2;
      boolean SLPE  :1;
      uint8_t SMODS :2;
      boolean RSVD  :1;
      boolean RST   :1;
      boolean ST    :1;
    };
  
    uint8_t value;

    void print()
    {
      Serial << F("ctrlReg2=");
      if(MODS)  Serial << F("MODS=") << MODS << " ";
      if(SLPE)  Serial << F("SLPE ");
      if(SMODS) Serial << F("SMODS=") << SMODS << " ";
      if(RSVD)  Serial << F("RSVD! ");
      if(RST)   Serial << F("RST ");
      if(ST)    Serial << F("ST");
      Serial << "\n";
    }
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
    };
  
    uint8_t value;

    void print()
    {
      Serial << F("ctrlReg4=TODO");
      Serial << "\n";
    }
  };

};

