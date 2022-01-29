/*
 * MPC.c
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

#include "MPC.h"
#include "MPC_private.h"
#include "MPC_dt.h"

/* Block signals (default storage) */
B_MPC_T MPC_B;

/* Block states (default storage) */
DW_MPC_T MPC_DW;

/* Real-time model */
RT_MODEL_MPC_T MPC_M_;
RT_MODEL_MPC_T *const MPC_M = &MPC_M_;

/* Forward declaration for local functions */
static void MPC_emxInit_real_T(emxArray_real_T_MPC_T **pEmxArray, int32_T
  numDimensions);
static void MPC_emxEnsureCapacity_real_T(emxArray_real_T_MPC_T *emxArray,
  int32_T oldNumel);
static void MPC_repmat(const real_T a[2], real_T varargin_1,
  emxArray_real_T_MPC_T *b);
static void MPC_emxFree_real_T(emxArray_real_T_MPC_T **pEmxArray);
static void MPC_emxInit_real_T(emxArray_real_T_MPC_T **pEmxArray, int32_T
  numDimensions)
{
  emxArray_real_T_MPC_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T_MPC_T *)malloc(sizeof(emxArray_real_T_MPC_T));
  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)malloc(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void MPC_emxEnsureCapacity_real_T(emxArray_real_T_MPC_T *emxArray,
  int32_T oldNumel)
{
  int32_T newNumel;
  int32_T i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i <<= 1;
      }
    }

    newData = calloc((uint32_T)i, sizeof(real_T));
    if (emxArray->data != NULL) {
      memcpy(newData, (void *)emxArray->data, sizeof(real_T) * oldNumel);
      if (emxArray->canFreeData) {
        free((void *)emxArray->data);
      }
    }

    emxArray->data = (real_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

/* Function for MATLAB Function: '<Root>/build_matrices_inlab_opt' */
static void MPC_repmat(const real_T a[2], real_T varargin_1,
  emxArray_real_T_MPC_T *b)
{
  int32_T ibcol;
  int32_T itilerow;
  itilerow = b->size[0];
  b->size[0] = (int32_T)varargin_1 << 1;
  MPC_emxEnsureCapacity_real_T(b, itilerow);
  for (itilerow = 1; itilerow <= (int32_T)varargin_1; itilerow++) {
    ibcol = (itilerow - 1) << 1;
    b->data[ibcol] = a[0];
    b->data[ibcol + 1] = a[1];
  }
}

static void MPC_emxFree_real_T(emxArray_real_T_MPC_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T_MPC_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T_MPC_T *)NULL;
  }
}

/* Model output function */
void MPC_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadAnalog1_o3;
  real_T rtb_HILReadAnalog1_o4;
  real_T rtb_HILReadAnalog1_o1;
  real_T rtb_Saturation;
  real_T u_min;
  real_T x_min[2];
  static const int8_T c[21] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1 };

  int32_T iter;
  real_T delta_u_hat_k[20];
  real_T lambda[222];
  real_T J;
  real_T rtb_c_delta[21];
  real_T rtb_b_iq[201];
  real_T rtb_Sum12[80];
  real_T rtb_W_delta[441];
  emxArray_real_T_MPC_T *tmp;
  real_T x_min_0[2];
  emxArray_real_T_MPC_T *tmp_0;
  int32_T i;
  int32_T i_0;
  real_T tmp_1[400];
  real_T tmp_2;
  real_T tmp_3[40];
  real_T rtb_Sum1_idx_0;
  real_T rtb_Sum1_idx_1;
  int32_T i_1;

  /* S-Function (hil_read_analog_block): '<S1>/HIL Read Analog1' */

  /* S-Function Block: MPC/3Tank Modell 1/HIL Read Analog1 (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(MPC_DW.HILInitialize_Card,
      MPC_P.HILReadAnalog1_channels, 4, &MPC_DW.HILReadAnalog1_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(MPC_M, _rt_error_message);
    }

    rtb_HILReadAnalog1_o1 = MPC_DW.HILReadAnalog1_Buffer[0];
    rtb_Saturation = MPC_DW.HILReadAnalog1_Buffer[1];
    rtb_HILReadAnalog1_o3 = MPC_DW.HILReadAnalog1_Buffer[2];
    rtb_HILReadAnalog1_o4 = MPC_DW.HILReadAnalog1_Buffer[3];
  }

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain'
   */
  MPC_B.Sum = MPC_P.gainh1 * rtb_HILReadAnalog1_o1 + MPC_P.offseth1;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Gain: '<S1>/Gain1'
   */
  MPC_B.Sum1 = MPC_P.gainh2 * rtb_Saturation + MPC_P.offseth2;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant7'
   *  Sum: '<Root>/Sum6'
   */
  rtb_Sum1_idx_0 = (MPC_P.Constant7_Value[0] + MPC_B.Sum) - MPC_P.x_eq[0];
  rtb_Sum1_idx_1 = (MPC_P.Constant7_Value[1] + MPC_B.Sum1) - MPC_P.x_eq[1];

  /* Sum: '<Root>/Sum12' incorporates:
   *  Gain: '<Root>/Gain11'
   *  Gain: '<Root>/Gain12'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  for (iter = 0; iter < 80; iter++) {
    rtb_Sum12[iter] = (MPC_P.Fx[iter + 80] * rtb_Sum1_idx_1 + MPC_P.Fx[iter] *
                       rtb_Sum1_idx_0) + MPC_P.Gx[iter] *
      MPC_DW.UnitDelay1_DSTATE;
  }

  /* End of Sum: '<Root>/Sum12' */

  /* MATLAB Function: '<Root>/build_matrices_inlab_opt' incorporates:
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant4'
   *  Gain: '<Root>/Gain5'
   *  Gain: '<Root>/Gain6'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<Root>/Sum8'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  /* MATLAB Function 'build_matrices_inlab_opt': '<S2>:1' */
  /* '<S2>:1:48' */
  /* '<S2>:1:12' */
  u_min = -MPC_P.u_eq[0] + MPC_P.u_lower_limit;

  /* '<S2>:1:13' */
  /* '<S2>:1:14' */
  J = MPC_DW.UnitDelay1_DSTATE - u_min;
  u_min = ((u_min + MPC_P.u_upper_limit) - MPC_P.u_lower_limit) -
    MPC_DW.UnitDelay1_DSTATE;

  /* '<S2>:1:17' */
  x_min[0] = (-MPC_P.x_eq[0] + MPC_P.h[0]) + MPC_P.x_lower_limit[0];
  x_min[1] = (-MPC_P.x_eq[1] + MPC_P.h[1]) + MPC_P.x_lower_limit[1];

  /* '<S2>:1:18' */
  /* '<S2>:1:19' */
  /* '<S2>:1:20' */
  /* '<S2>:1:22' */
  /* '<S2>:1:24' */
  /* '<S2>:1:25' */
  /* '<S2>:1:27' */
  /* '<S2>:1:41' */
  /* '<S2>:1:43' */
  /* '<S2>:1:46' */
  /* '<S2>:1:48' */
  /* '<S2>:1:51' */
  for (iter = 0; iter < 20; iter++) {
    for (i = 0; i < 40; i++) {
      i_1 = iter + 20 * i;
      MPC_B.dv0[i_1] = 0.0;
      for (i_0 = 0; i_0 < 40; i_0++) {
        MPC_B.dv0[i_1] = MPC_P.H[40 * iter + i_0] * MPC_P.Q[40 * i + i_0] +
          MPC_B.dv0[20 * i + iter];
      }
    }

    for (i = 0; i < 20; i++) {
      tmp_2 = 0.0;
      for (i_1 = 0; i_1 < 40; i_1++) {
        tmp_2 += MPC_B.dv0[20 * i_1 + iter] * MPC_P.H[40 * i + i_1];
      }

      tmp_1[iter + 20 * i] = MPC_P.R[20 * i + iter] + tmp_2;
    }
  }

  for (iter = 0; iter < 20; iter++) {
    for (i = 0; i < 20; i++) {
      rtb_W_delta[i + 21 * iter] = tmp_1[20 * iter + i] * 2.0;
    }

    rtb_W_delta[420 + iter] = 0.0;
  }

  for (iter = 0; iter < 21; iter++) {
    rtb_W_delta[20 + 21 * iter] = 0.0;
  }

  for (iter = 0; iter < 20; iter++) {
    for (i = 0; i < 40; i++) {
      i_1 = iter + 20 * i;
      MPC_B.dv0[i_1] = 0.0;
      for (i_0 = 0; i_0 < 40; i_0++) {
        MPC_B.dv0[i_1] = MPC_P.H[40 * iter + i_0] * 2.0 * MPC_P.Q[40 * i + i_0]
          + MPC_B.dv0[20 * i + iter];
      }
    }
  }

  for (iter = 0; iter < 40; iter++) {
    tmp_3[iter] = ((MPC_P.F[iter + 40] * rtb_Sum1_idx_1 + MPC_P.F[iter] *
                    rtb_Sum1_idx_0) + MPC_P.G[iter] * MPC_DW.UnitDelay1_DSTATE)
      - (MPC_P.Constant4_Value[iter] - MPC_P.x_eq[1]);
  }

  for (iter = 0; iter < 20; iter++) {
    delta_u_hat_k[iter] = 0.0;
    for (i = 0; i < 40; i++) {
      delta_u_hat_k[iter] += MPC_B.dv0[20 * i + iter] * tmp_3[i];
    }

    rtb_c_delta[iter] = delta_u_hat_k[iter];
  }

  MPC_emxInit_real_T(&tmp, 1);

  /* MATLAB Function: '<Root>/build_matrices_inlab_opt' */
  rtb_c_delta[20] = MPC_P.roh;
  MPC_repmat(x_min, MPC_P.Np, tmp);
  x_min_0[0] = (x_min[0] + MPC_P.x_upper_limit[0]) - MPC_P.x_lower_limit[0];
  x_min_0[1] = (x_min[1] + MPC_P.x_upper_limit[1]) - MPC_P.x_lower_limit[1];
  MPC_emxInit_real_T(&tmp_0, 1);

  /* MATLAB Function: '<Root>/build_matrices_inlab_opt' */
  MPC_repmat(x_min_0, MPC_P.Np, tmp_0);
  for (iter = 0; iter < 20; iter++) {
    rtb_b_iq[iter] = MPC_P.L[iter] * J;
    rtb_b_iq[iter + 20] = MPC_P.L[iter] * u_min;
  }

  for (iter = 0; iter < 80; iter++) {
    rtb_b_iq[iter + 40] = rtb_Sum12[iter] - tmp->data[iter];
  }

  MPC_emxFree_real_T(&tmp);

  /* MATLAB Function: '<Root>/build_matrices_inlab_opt' */
  for (iter = 0; iter < 80; iter++) {
    rtb_b_iq[iter + 120] = tmp_0->data[iter] - rtb_Sum12[iter];
  }

  MPC_emxFree_real_T(&tmp_0);

  /* MATLAB Function: '<Root>/build_matrices_inlab_opt' */
  rtb_b_iq[200] = 0.0;

  /* MATLAB Function: '<Root>/qpOASES-native' incorporates:
   *  MATLAB Function: '<Root>/build_matrices_inlab_opt'
   */
  /* MATLAB Function 'qpOASES-native': '<S3>:1' */
  /* '<S3>:1:22' */
  /* '<S3>:1:5' */
  for (iter = 0; iter < 20; iter++) {
    for (i = 0; i < 20; i++) {
      MPC_B.A_iq_tr[i + 21 * iter] = -MPC_P.M[20 * i + iter];
      MPC_B.A_iq_tr[i + 21 * (iter + 20)] = MPC_P.M[20 * i + iter];
    }
  }

  for (iter = 0; iter < 80; iter++) {
    for (i = 0; i < 20; i++) {
      MPC_B.A_iq_tr[i + 21 * (iter + 40)] = -MPC_P.Hx[80 * i + iter];
      MPC_B.A_iq_tr[i + 21 * (iter + 120)] = MPC_P.Hx[80 * i + iter];
    }
  }

  for (iter = 0; iter < 200; iter++) {
    MPC_B.A_iq_tr[20 + 21 * iter] = -1.0;
  }

  for (iter = 0; iter < 21; iter++) {
    MPC_B.A_iq_tr[4200 + iter] = c[iter];
  }

  /* '<S3>:1:7' */
  /* '<S3>:1:8' */
  /* '<S3>:1:9' */
  /* '<S3>:1:10' */
  iter = 180;
  if (!MPC_DW.initialized_not_empty) {
    /* '<S3>:1:12' */
    qpOASES_Options_init(&MPC_DW.options, 2);
    QProblem_setup(21, 201, 6);
    MPC_DW.initialized_not_empty = true;
  }

  /* '<S3>:1:20' */
  QProblem_init(rtb_W_delta, rtb_c_delta, MPC_B.A_iq_tr, NULL, NULL, NULL,
                rtb_b_iq, &iter, NULL, &MPC_DW.options, delta_u_hat_k, lambda,
                &J, &MPC_B.error);

  /* '<S3>:1:26' */
  MPC_B.iter = iter;

  /* DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn1' incorporates:
   *  MATLAB Function: '<Root>/qpOASES-native'
   */
  MPC_DW.DiscreteTransferFcn1_tmp = (delta_u_hat_k[0] -
    MPC_P.DiscreteTransferFcn1_DenCoef[1] * MPC_DW.DiscreteTransferFcn1_states) /
    MPC_P.DiscreteTransferFcn1_DenCoef[0];
  MPC_B.DiscreteTransferFcn1 = MPC_P.DiscreteTransferFcn1_NumCoef[0] *
    MPC_DW.DiscreteTransferFcn1_tmp + MPC_P.DiscreteTransferFcn1_NumCoef[1] *
    MPC_DW.DiscreteTransferFcn1_states;

  /* Sum: '<Root>/Sum7' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  MPC_B.Sum7 = MPC_B.DiscreteTransferFcn1 + MPC_P.u_eq[0];

  /* Stop: '<S1>/Stop Simulation' incorporates:
   *  Constant: '<S5>/Constant'
   *  RelationalOperator: '<S5>/Compare'
   */
  if (MPC_B.Sum >= MPC_P.CompareToConstant2_const) {
    rtmSetStopRequested(MPC_M, 1);
  }

  /* End of Stop: '<S1>/Stop Simulation' */

  /* Stop: '<S1>/Stop Simulation1' incorporates:
   *  Constant: '<S4>/Constant'
   *  RelationalOperator: '<S4>/Compare'
   */
  if (MPC_B.Sum1 >= MPC_P.CompareToConstant1_const) {
    rtmSetStopRequested(MPC_M, 1);
  }

  /* End of Stop: '<S1>/Stop Simulation1' */

  /* Saturate: '<S1>/Saturation' */
  if (MPC_B.Sum7 > MPC_P.Saturation_UpperSat) {
    rtb_Saturation = MPC_P.Saturation_UpperSat;
  } else if (MPC_B.Sum7 < MPC_P.Saturation_LowerSat) {
    rtb_Saturation = MPC_P.Saturation_LowerSat;
  } else {
    rtb_Saturation = MPC_B.Sum7;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* ManualSwitch: '<Root>/Manual Switch' incorporates:
   *  Clock: '<Root>/Clock'
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/Gain'
   *  Trigonometry: '<Root>/Trigonometric Function'
   */
  if (MPC_P.ManualSwitch_CurrentSetting == 1) {
    J = MPC_P.Gain_Gain * sin(MPC_M->Timing.t[0]);
  } else {
    J = MPC_P.Constant_Value;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* Saturate: '<S1>/Saturation1' */
  if (J > MPC_P.Saturation1_UpperSat) {
    MPC_B.Saturation1 = MPC_P.Saturation1_UpperSat;
  } else if (J < MPC_P.Saturation1_LowerSat) {
    MPC_B.Saturation1 = MPC_P.Saturation1_LowerSat;
  } else {
    MPC_B.Saturation1 = J;
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* S-Function (hil_write_analog_block): '<S1>/HIL Write Analog2' */

  /* S-Function Block: MPC/3Tank Modell 1/HIL Write Analog2 (hil_write_analog_block) */
  {
    t_error result;
    MPC_DW.HILWriteAnalog2_Buffer[0] = rtb_Saturation;
    MPC_DW.HILWriteAnalog2_Buffer[1] = MPC_B.Saturation1;
    result = hil_write_analog(MPC_DW.HILInitialize_Card,
      MPC_P.HILWriteAnalog2_channels, 2, &MPC_DW.HILWriteAnalog2_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(MPC_M, _rt_error_message);
    }
  }
}

/* Model update function */
void MPC_update(void)
{
  /* Update for UnitDelay: '<Root>/Unit Delay1' */
  MPC_DW.UnitDelay1_DSTATE = MPC_B.DiscreteTransferFcn1;

  /* Update for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn1' */
  MPC_DW.DiscreteTransferFcn1_states = MPC_DW.DiscreteTransferFcn1_tmp;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++MPC_M->Timing.clockTick0)) {
    ++MPC_M->Timing.clockTickH0;
  }

  MPC_M->Timing.t[0] = MPC_M->Timing.clockTick0 * MPC_M->Timing.stepSize0 +
    MPC_M->Timing.clockTickH0 * MPC_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.5s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++MPC_M->Timing.clockTick1)) {
      ++MPC_M->Timing.clockTickH1;
    }

    MPC_M->Timing.t[1] = MPC_M->Timing.clockTick1 * MPC_M->Timing.stepSize1 +
      MPC_M->Timing.clockTickH1 * MPC_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void MPC_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: MPC/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &MPC_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(MPC_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(MPC_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(MPC_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(MPC_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(MPC_M, _rt_error_message);
      return;
    }

    if ((MPC_P.HILInitialize_AIPStart && !is_switching) ||
        (MPC_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &MPC_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (MPC_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &MPC_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = MPC_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_AIChannels, 8U,
        &MPC_DW.HILInitialize_AIMinimums[0], &MPC_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if ((MPC_P.HILInitialize_AOPStart && !is_switching) ||
        (MPC_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &MPC_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (MPC_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &MPC_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = MPC_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_AOChannels, 8U,
        &MPC_DW.HILInitialize_AOMinimums[0], &MPC_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if ((MPC_P.HILInitialize_AOStart && !is_switching) ||
        (MPC_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &MPC_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = MPC_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_AOChannels, 8U, &MPC_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if (MPC_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &MPC_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = MPC_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (MPC_DW.HILInitialize_Card, MPC_P.HILInitialize_AOChannels, 8U,
         &MPC_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if ((MPC_P.HILInitialize_EIPStart && !is_switching) ||
        (MPC_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &MPC_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = MPC_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &MPC_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if ((MPC_P.HILInitialize_EIStart && !is_switching) ||
        (MPC_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &MPC_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = MPC_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_EIChannels, 8U,
        &MPC_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if ((MPC_P.HILInitialize_POPStart && !is_switching) ||
        (MPC_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &MPC_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = MPC_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &MPC_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          MPC_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &MPC_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            MPC_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            MPC_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              MPC_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            MPC_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              (p_HILInitialize_POChannels[i1]);
            MPC_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              MPC_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(MPC_DW.HILInitialize_Card,
          &MPC_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &MPC_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(MPC_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(MPC_DW.HILInitialize_Card,
          &MPC_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &MPC_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(MPC_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &MPC_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = MPC_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &MPC_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = MPC_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &MPC_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = MPC_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &MPC_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &MPC_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &MPC_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &MPC_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = MPC_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &MPC_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = MPC_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_POChannels, 8U,
        &MPC_DW.HILInitialize_POSortedFreqs[0], &MPC_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if ((MPC_P.HILInitialize_POStart && !is_switching) ||
        (MPC_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &MPC_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = MPC_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_POChannels, 8U, &MPC_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }

    if (MPC_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &MPC_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = MPC_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(MPC_DW.HILInitialize_Card,
        MPC_P.HILInitialize_POChannels, 8U, &MPC_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(MPC_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay1' */
  MPC_DW.UnitDelay1_DSTATE = MPC_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn1' */
  MPC_DW.DiscreteTransferFcn1_states = MPC_P.DiscreteTransferFcn1_InitialSta;

  /* SystemInitialize for MATLAB Function: '<Root>/qpOASES-native' */
  MPC_DW.initialized_not_empty = false;
}

/* Model terminate function */
void MPC_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: MPC/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(MPC_DW.HILInitialize_Card);
    hil_monitor_stop_all(MPC_DW.HILInitialize_Card);
    is_switching = false;
    if ((MPC_P.HILInitialize_AOTerminate && !is_switching) ||
        (MPC_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &MPC_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = MPC_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((MPC_P.HILInitialize_POTerminate && !is_switching) ||
        (MPC_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &MPC_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = MPC_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(MPC_DW.HILInitialize_Card
                         , MPC_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , MPC_P.HILInitialize_POChannels, num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &MPC_DW.HILInitialize_AOVoltages[0]
                         , &MPC_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(MPC_DW.HILInitialize_Card,
            MPC_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &MPC_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(MPC_DW.HILInitialize_Card,
            MPC_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &MPC_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(MPC_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(MPC_DW.HILInitialize_Card);
    hil_monitor_delete_all(MPC_DW.HILInitialize_Card);
    hil_close(MPC_DW.HILInitialize_Card);
    MPC_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  MPC_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  MPC_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  MPC_initialize();
}

void MdlTerminate(void)
{
  MPC_terminate();
}

/* Registration function */
RT_MODEL_MPC_T *MPC(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)MPC_M, 0,
                sizeof(RT_MODEL_MPC_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&MPC_M->solverInfo, &MPC_M->Timing.simTimeStep);
    rtsiSetTPtr(&MPC_M->solverInfo, &rtmGetTPtr(MPC_M));
    rtsiSetStepSizePtr(&MPC_M->solverInfo, &MPC_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&MPC_M->solverInfo, (&rtmGetErrorStatus(MPC_M)));
    rtsiSetRTModelPtr(&MPC_M->solverInfo, MPC_M);
  }

  rtsiSetSimTimeStep(&MPC_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&MPC_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = MPC_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    MPC_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    MPC_M->Timing.sampleTimes = (&MPC_M->Timing.sampleTimesArray[0]);
    MPC_M->Timing.offsetTimes = (&MPC_M->Timing.offsetTimesArray[0]);

    /* task periods */
    MPC_M->Timing.sampleTimes[0] = (0.0);
    MPC_M->Timing.sampleTimes[1] = (0.5);

    /* task offsets */
    MPC_M->Timing.offsetTimes[0] = (0.0);
    MPC_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(MPC_M, &MPC_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = MPC_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    MPC_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(MPC_M, -1);
  MPC_M->Timing.stepSize0 = 0.5;
  MPC_M->Timing.stepSize1 = 0.5;

  /* External mode info */
  MPC_M->Sizes.checksums[0] = (1898036993U);
  MPC_M->Sizes.checksums[1] = (3557365220U);
  MPC_M->Sizes.checksums[2] = (2283798973U);
  MPC_M->Sizes.checksums[3] = (3462276186U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    MPC_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(MPC_M->extModeInfo,
      &MPC_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(MPC_M->extModeInfo, MPC_M->Sizes.checksums);
    rteiSetTPtr(MPC_M->extModeInfo, rtmGetTPtr(MPC_M));
  }

  MPC_M->solverInfoPtr = (&MPC_M->solverInfo);
  MPC_M->Timing.stepSize = (0.5);
  rtsiSetFixedStepSize(&MPC_M->solverInfo, 0.5);
  rtsiSetSolverMode(&MPC_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  MPC_M->blockIO = ((void *) &MPC_B);
  (void) memset(((void *) &MPC_B), 0,
                sizeof(B_MPC_T));

  /* parameters */
  MPC_M->defaultParam = ((real_T *)&MPC_P);

  /* states (dwork) */
  MPC_M->dwork = ((void *) &MPC_DW);
  (void) memset((void *)&MPC_DW, 0,
                sizeof(DW_MPC_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    MPC_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  MPC_M->Sizes.numContStates = (0);    /* Number of continuous states */
  MPC_M->Sizes.numY = (0);             /* Number of model outputs */
  MPC_M->Sizes.numU = (0);             /* Number of model inputs */
  MPC_M->Sizes.sysDirFeedThru = (0);   /* The model is not direct feedthrough */
  MPC_M->Sizes.numSampTimes = (2);     /* Number of sample times */
  MPC_M->Sizes.numBlocks = (48);       /* Number of blocks */
  MPC_M->Sizes.numBlockIO = (8);       /* Number of block outputs */
  MPC_M->Sizes.numBlockPrms = (5361);  /* Sum of parameter "widths" */
  return MPC_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
