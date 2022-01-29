/*
 * MPC_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "MPC".
 *
 * Model version              : 1.200
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C source code generated on : Fri Jan 28 12:38:48 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_card),
  sizeof(qpOASES_Options)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_card",
  "qpOASES_Options"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&MPC_B.Sum), 0, 0, 5 },

  { (char_T *)(&MPC_B.iter), 6, 0, 2 }
  ,

  { (char_T *)(&MPC_DW.UnitDelay1_DSTATE), 0, 0, 73 },

  { (char_T *)(&MPC_DW.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&MPC_DW.HILReadAnalog1_PWORK), 11, 0, 5 },

  { (char_T *)(&MPC_DW.HILInitialize_ClockModes[0]), 6, 0, 43 },

  { (char_T *)(&MPC_DW.HILInitialize_POSortedChans[0]), 7, 0, 8 },

  { (char_T *)(&MPC_DW.initialized_not_empty), 8, 0, 1 },

  { (char_T *)(&MPC_DW.options), 15, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  9U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&MPC_P.F[0]), 0, 0, 5204 },

  { (char_T *)(&MPC_P.HILReadAnalog1_channels[0]), 7, 0, 6 },

  { (char_T *)(&MPC_P.Gain_Gain), 0, 0, 71 },

  { (char_T *)(&MPC_P.HILInitialize_CKChannels[0]), 6, 0, 9 },

  { (char_T *)(&MPC_P.HILInitialize_AIChannels[0]), 7, 0, 33 },

  { (char_T *)(&MPC_P.HILInitialize_Active), 8, 0, 37 },

  { (char_T *)(&MPC_P.ManualSwitch_CurrentSetting), 3, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  7U,
  rtPTransitions
};

/* [EOF] MPC_dt.h */
