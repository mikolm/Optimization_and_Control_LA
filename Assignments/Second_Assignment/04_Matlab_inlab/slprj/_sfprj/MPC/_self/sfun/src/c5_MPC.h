#ifndef __c5_MPC_h__
#define __c5_MPC_h__

/* Type Definitions */
#include "qpOASES_wrapper_Simulink.h"
#ifndef typedef_SFc5_MPCInstanceStruct
#define typedef_SFc5_MPCInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  boolean_T c5_doneDoubleBufferReInit;
  uint8_T c5_is_active_c5_MPC;
  real_T c5_m;
  real_T c5_Nc;
  real_T c5_initialized;
  boolean_T c5_initialized_not_empty;
  qpOASES_Options c5_options;
  boolean_T c5_options_not_empty;
  void *c5_fEmlrtCtx;
  real_T (*c5_W_delta)[441];
  real_T *c5_delta_u_k;
  real_T (*c5_c_delta)[21];
  real_T (*c5_A_iq)[4221];
  real_T (*c5_b_iq)[201];
  int32_T *c5_iter;
  int32_T *c5_error;
} SFc5_MPCInstanceStruct;

#endif                                 /*typedef_SFc5_MPCInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_MPC_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c5_MPC_get_check_sum(mxArray *plhs[]);
extern void c5_MPC_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
