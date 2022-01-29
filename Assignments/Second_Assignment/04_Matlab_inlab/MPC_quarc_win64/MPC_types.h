/*
 * MPC_types.h
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

#ifndef RTW_HEADER_MPC_types_h_
#define RTW_HEADER_MPC_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"

/* Custom Type definition for MATLAB Function: '<Root>/qpOASES-native' */
#include "qpOASES_wrapper_Simulink.h"
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T_MPC_T
#define typedef_emxArray_real_T_MPC_T

typedef struct emxArray_real_T emxArray_real_T_MPC_T;

#endif                                 /*typedef_emxArray_real_T_MPC_T*/

/* Parameters (default storage) */
typedef struct P_MPC_T_ P_MPC_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_MPC_T RT_MODEL_MPC_T;

#endif                                 /* RTW_HEADER_MPC_types_h_ */
