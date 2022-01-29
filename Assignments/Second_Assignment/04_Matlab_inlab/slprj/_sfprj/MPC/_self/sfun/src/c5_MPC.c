/* Include files */

#include "MPC_sfun.h"
#include "c5_MPC.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "MPC_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c5_const_m                     (1.0)
#define c5_const_Nc                    (20.0)
#define c5_b_m                         (1.0)
#define c5_b_Nc                        (20.0)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[16] = { "A_iq_tr", "delta_u_hat_k",
  "lambda", "J", "m", "Nc", "nargin", "nargout", "W_delta", "c_delta", "A_iq",
  "b_iq", "delta_u_k", "iter", "error", "initialized" };

/* Function Declarations */
static void initialize_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void initialize_params_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void enable_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void disable_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_MPC(SFc5_MPCInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void set_sim_state_c5_MPC(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_st);
static void finalize_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void sf_gateway_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void mdl_start_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void c5_chartstep_c5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void initSimStructsc5_MPC(SFc5_MPCInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static void c5_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[4221]);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_b_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[20]);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_c_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[222]);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_d_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_J, const char_T *c5_identifier);
static real_T c5_e_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_i_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_f_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_b_iter, const char_T *c5_identifier);
static int32_T c5_g_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_j_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_h_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_b_initialized, const char_T *c5_identifier, boolean_T *c5_svPtr);
static real_T c5_i_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T *c5_svPtr);
static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_j_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_MPC, const char_T *c5_identifier);
static uint8_T c5_k_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_MPCInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc5_MPCInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc5_MPC(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_initialized_not_empty = false;
  chartInstance->c5_options_not_empty = false;
  chartInstance->c5_is_active_c5_MPC = 0U;
}

static void initialize_params_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  real_T c5_d0;
  real_T c5_d1;
  sf_mex_import_named("m", sf_mex_get_sfun_param(chartInstance->S, 1U, 0U),
                      &c5_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c5_m = c5_d0;
  sf_mex_import_named("Nc", sf_mex_get_sfun_param(chartInstance->S, 0U, 0U),
                      &c5_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c5_Nc = c5_d1;
}

static void enable_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_MPC(SFc5_MPCInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  const mxArray *c5_b_y = NULL;
  int32_T c5_b_hoistedGlobal;
  const mxArray *c5_c_y = NULL;
  int32_T c5_c_hoistedGlobal;
  const mxArray *c5_d_y = NULL;
  real_T c5_d_hoistedGlobal;
  const mxArray *c5_e_y = NULL;
  uint8_T c5_e_hoistedGlobal;
  const mxArray *c5_f_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(5, 1), false);
  c5_hoistedGlobal = *chartInstance->c5_delta_u_k;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = *chartInstance->c5_error;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_hoistedGlobal, 6, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_hoistedGlobal = *chartInstance->c5_iter;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_hoistedGlobal, 6, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  c5_d_hoistedGlobal = chartInstance->c5_initialized;
  c5_e_y = NULL;
  if (!chartInstance->c5_initialized_not_empty) {
    sf_mex_assign(&c5_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_hoistedGlobal, 0, 0U, 0U, 0U,
      0), false);
  }

  sf_mex_setcell(c5_y, 3, c5_e_y);
  c5_e_hoistedGlobal = chartInstance->c5_is_active_c5_MPC;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c5_y, 4, c5_f_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_MPC(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_st)
{
  const mxArray *c5_u;
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  *chartInstance->c5_delta_u_k = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 0)), "delta_u_k");
  *chartInstance->c5_error = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 1)), "error");
  *chartInstance->c5_iter = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 2)), "iter");
  chartInstance->c5_initialized = c5_h_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 3)), "initialized",
    &chartInstance->c5_initialized_not_empty);
  chartInstance->c5_is_active_c5_MPC = c5_j_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 4)), "is_active_c5_MPC");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_MPC(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  int32_T c5_i0;
  int32_T c5_i1;
  int32_T c5_i2;
  int32_T c5_i3;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c5_sfEvent);
  for (c5_i0 = 0; c5_i0 < 201; c5_i0++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c5_b_iq)[c5_i0], 3U);
  }

  for (c5_i1 = 0; c5_i1 < 4221; c5_i1++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c5_A_iq)[c5_i1], 2U);
  }

  for (c5_i2 = 0; c5_i2 < 21; c5_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c5_c_delta)[c5_i2], 1U);
  }

  for (c5_i3 = 0; c5_i3 < 441; c5_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c5_W_delta)[c5_i3], 0U);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_MPC(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_delta_u_k, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c5_iter, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c5_error, 6U);
}

static void mdl_start_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void c5_chartstep_c5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  int32_T c5_i4;
  int32_T c5_i5;
  real_T c5_b_W_delta[441];
  int32_T c5_i6;
  real_T c5_b_c_delta[21];
  int32_T c5_i7;
  real_T c5_b_A_iq[4221];
  uint32_T c5_debug_family_var_map[16];
  real_T c5_b_b_iq[201];
  real_T c5_A_iq_tr[4221];
  real_T c5_delta_u_hat_k[20];
  real_T c5_lambda[222];
  real_T c5_J;
  real_T c5_c_m;
  real_T c5_c_Nc;
  real_T c5_nargin = 6.0;
  real_T c5_nargout = 3.0;
  real_T c5_b_delta_u_k;
  int32_T c5_b_iter;
  int32_T c5_b_error;
  int32_T c5_i8;
  int32_T c5_i9;
  int32_T c5_i10;
  int32_T c5_i11;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c5_sfEvent);
  for (c5_i4 = 0; c5_i4 < 441; c5_i4++) {
    c5_b_W_delta[c5_i4] = (*chartInstance->c5_W_delta)[c5_i4];
  }

  for (c5_i5 = 0; c5_i5 < 21; c5_i5++) {
    c5_b_c_delta[c5_i5] = (*chartInstance->c5_c_delta)[c5_i5];
  }

  for (c5_i6 = 0; c5_i6 < 4221; c5_i6++) {
    c5_b_A_iq[c5_i6] = (*chartInstance->c5_A_iq)[c5_i6];
  }

  for (c5_i7 = 0; c5_i7 < 201; c5_i7++) {
    c5_b_b_iq[c5_i7] = (*chartInstance->c5_b_iq)[c5_i7];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 16U, 16U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_A_iq_tr, 0U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_delta_u_hat_k, 1U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_lambda, 2U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_J, 3U, c5_d_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_c_m, 4U, c5_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_c_Nc, 5U, c5_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 6U, c5_d_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 7U, c5_d_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_b_W_delta, 8U, c5_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_b_c_delta, 9U, c5_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_b_A_iq, 10U, c5_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_b_b_iq, 11U, c5_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_delta_u_k, 12U, c5_d_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_iter, 13U, c5_i_sf_marshallOut,
    c5_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_error, 14U, c5_i_sf_marshallOut,
    c5_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_initialized, 15U,
    c5_j_sf_marshallOut, c5_f_sf_marshallIn);
  c5_c_Nc = c5_b_Nc;
  c5_c_m = c5_b_m;
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 5);
  c5_i8 = 0;
  for (c5_i9 = 0; c5_i9 < 201; c5_i9++) {
    c5_i10 = 0;
    for (c5_i11 = 0; c5_i11 < 21; c5_i11++) {
      c5_A_iq_tr[c5_i11 + c5_i8] = c5_b_A_iq[c5_i10 + c5_i9];
      c5_i10 += 201;
    }

    c5_i8 += 21;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 7);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 8);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 10);
  c5_b_iter = 180;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 12);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c5_initialized_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 13);
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 14);
    chartInstance->c5_options_not_empty = true;
    qpOASES_Options_init(&chartInstance->c5_options, 2);
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 15);
    QProblem_setup(21, 201, 6);
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
    chartInstance->c5_initialized = 1.0;
    chartInstance->c5_initialized_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 20);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 21);
  QProblem_init(c5_b_W_delta, c5_b_c_delta, c5_A_iq_tr, NULL, NULL, NULL,
                c5_b_b_iq, &c5_b_iter, NULL, &chartInstance->c5_options,
                c5_delta_u_hat_k, c5_lambda, &c5_J, &c5_b_error);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
  c5_b_delta_u_k = c5_delta_u_hat_k[0];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -26);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c5_delta_u_k = c5_b_delta_u_k;
  *chartInstance->c5_iter = c5_b_iter;
  *chartInstance->c5_error = c5_b_error;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_MPC(SFc5_MPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)(c5_machineNumber);
  (void)(c5_chartNumber);
  (void)(c5_instanceNumber);
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i12;
  int32_T c5_i13;
  const mxArray *c5_y = NULL;
  int32_T c5_i14;
  real_T c5_u[4221];
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_i12 = 0;
  for (c5_i13 = 0; c5_i13 < 201; c5_i13++) {
    for (c5_i14 = 0; c5_i14 < 21; c5_i14++) {
      c5_u[c5_i14 + c5_i12] = (*(real_T (*)[4221])c5_inData)[c5_i14 + c5_i12];
    }

    c5_i12 += 21;
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 21, 201),
                false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[4221])
{
  real_T c5_dv0[4221];
  int32_T c5_i15;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv0, 1, 0, 0U, 1, 0U, 2, 21,
                201);
  for (c5_i15 = 0; c5_i15 < 4221; c5_i15++) {
    c5_y[c5_i15] = c5_dv0[c5_i15];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_A_iq_tr;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[4221];
  int32_T c5_i16;
  int32_T c5_i17;
  int32_T c5_i18;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_A_iq_tr = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_A_iq_tr), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_A_iq_tr);
  c5_i16 = 0;
  for (c5_i17 = 0; c5_i17 < 201; c5_i17++) {
    for (c5_i18 = 0; c5_i18 < 21; c5_i18++) {
      (*(real_T (*)[4221])c5_outData)[c5_i18 + c5_i16] = c5_y[c5_i18 + c5_i16];
    }

    c5_i16 += 21;
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i19;
  const mxArray *c5_y = NULL;
  real_T c5_u[20];
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i19 = 0; c5_i19 < 20; c5_i19++) {
    c5_u[c5_i19] = (*(real_T (*)[20])c5_inData)[c5_i19];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 20), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_b_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[20])
{
  real_T c5_dv1[20];
  int32_T c5_i20;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv1, 1, 0, 0U, 1, 0U, 1, 20);
  for (c5_i20 = 0; c5_i20 < 20; c5_i20++) {
    c5_y[c5_i20] = c5_dv1[c5_i20];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_delta_u_hat_k;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[20];
  int32_T c5_i21;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_delta_u_hat_k = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_delta_u_hat_k), &c5_thisId,
                        c5_y);
  sf_mex_destroy(&c5_delta_u_hat_k);
  for (c5_i21 = 0; c5_i21 < 20; c5_i21++) {
    (*(real_T (*)[20])c5_outData)[c5_i21] = c5_y[c5_i21];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i22;
  const mxArray *c5_y = NULL;
  real_T c5_u[222];
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i22 = 0; c5_i22 < 222; c5_i22++) {
    c5_u[c5_i22] = (*(real_T (*)[222])c5_inData)[c5_i22];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 222), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_c_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[222])
{
  real_T c5_dv2[222];
  int32_T c5_i23;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv2, 1, 0, 0U, 1, 0U, 1, 222);
  for (c5_i23 = 0; c5_i23 < 222; c5_i23++) {
    c5_y[c5_i23] = c5_dv2[c5_i23];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_lambda;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[222];
  int32_T c5_i24;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_lambda = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_lambda), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_lambda);
  for (c5_i24 = 0; c5_i24 < 222; c5_i24++) {
    (*(real_T (*)[222])c5_outData)[c5_i24] = c5_y[c5_i24];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_d_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_J, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_J), &c5_thisId);
  sf_mex_destroy(&c5_J);
  return c5_y;
}

static real_T c5_e_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d2;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d2, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d2;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_J;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_J = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_J), &c5_thisId);
  sf_mex_destroy(&c5_J);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i25;
  int32_T c5_i26;
  const mxArray *c5_y = NULL;
  int32_T c5_i27;
  real_T c5_u[441];
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_i25 = 0;
  for (c5_i26 = 0; c5_i26 < 21; c5_i26++) {
    for (c5_i27 = 0; c5_i27 < 21; c5_i27++) {
      c5_u[c5_i27 + c5_i25] = (*(real_T (*)[441])c5_inData)[c5_i27 + c5_i25];
    }

    c5_i25 += 21;
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 21, 21), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i28;
  const mxArray *c5_y = NULL;
  real_T c5_u[21];
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i28 = 0; c5_i28 < 21; c5_i28++) {
    c5_u[c5_i28] = (*(real_T (*)[21])c5_inData)[c5_i28];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 21), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i29;
  int32_T c5_i30;
  const mxArray *c5_y = NULL;
  int32_T c5_i31;
  real_T c5_u[4221];
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_i29 = 0;
  for (c5_i30 = 0; c5_i30 < 21; c5_i30++) {
    for (c5_i31 = 0; c5_i31 < 201; c5_i31++) {
      c5_u[c5_i31 + c5_i29] = (*(real_T (*)[4221])c5_inData)[c5_i31 + c5_i29];
    }

    c5_i29 += 201;
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 201, 21),
                false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i32;
  const mxArray *c5_y = NULL;
  real_T c5_u[201];
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i32 = 0; c5_i32 < 201; c5_i32++) {
    c5_u[c5_i32] = (*(real_T (*)[201])c5_inData)[c5_i32];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 201), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_i_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_f_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_b_iter, const char_T *c5_identifier)
{
  int32_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_iter), &c5_thisId);
  sf_mex_destroy(&c5_b_iter);
  return c5_y;
}

static int32_T c5_g_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i33;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i33, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i33;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_iter;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_b_iter = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_iter), &c5_thisId);
  sf_mex_destroy(&c5_b_iter);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_j_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_initialized_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_h_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_b_initialized, const char_T *c5_identifier, boolean_T *c5_svPtr)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_initialized),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_initialized);
  return c5_y;
}

static real_T c5_i_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T *c5_svPtr)
{
  real_T c5_y;
  real_T c5_d3;
  (void)chartInstance;
  if (mxIsEmpty(c5_u)) {
    *c5_svPtr = false;
  } else {
    *c5_svPtr = true;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d3, 1, 0, 0U, 0, 0U, 0);
    c5_y = c5_d3;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_initialized;
  const char_T *c5_identifier;
  boolean_T *c5_svPtr;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)chartInstanceVoid;
  c5_b_initialized = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_svPtr = &chartInstance->c5_initialized_not_empty;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_initialized),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_initialized);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_MPC_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c5_nameCaptureInfo;
}

static uint8_T c5_j_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_MPC, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_is_active_c5_MPC),
    &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_MPC);
  return c5_y;
}

static uint8_T c5_k_emlrt_marshallIn(SFc5_MPCInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_MPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc5_MPCInstanceStruct *chartInstance)
{
  chartInstance->c5_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c5_W_delta = (real_T (*)[441])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c5_delta_u_k = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_c_delta = (real_T (*)[21])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_A_iq = (real_T (*)[4221])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c5_b_iq = (real_T (*)[201])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c5_iter = (int32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c5_error = (int32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c5_MPC_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1793642756U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(268267496U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1813405014U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1403342252U);
}

mxArray* sf_c5_MPC_get_post_codegen_info(void);
mxArray *sf_c5_MPC_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("85S6937glKdro1oVFeRg4F");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(21);
      pr[1] = (double)(21);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(21);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(201);
      pr[1] = (double)(21);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(201);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c5_MPC_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_MPC_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_MPC_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("qpOASES_Options_init");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c5_MPC_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c5_MPC_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c5_MPC(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"delta_u_k\",},{M[1],M[21],T\"error\",},{M[1],M[19],T\"iter\",},{M[4],M[0],T\"initialized\",S'l','i','p'{{M1x2[97 108],M[0],}}},{M[8],M[0],T\"is_active_c5_MPC\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_MPC_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_MPCInstanceStruct *chartInstance = (SFc5_MPCInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MPCMachineNumber_,
           5,
           1,
           1,
           0,
           9,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_MPCMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_MPCMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _MPCMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"W_delta");
          _SFD_SET_DATA_PROPS(1,1,1,0,"c_delta");
          _SFD_SET_DATA_PROPS(2,1,1,0,"A_iq");
          _SFD_SET_DATA_PROPS(3,1,1,0,"b_iq");
          _SFD_SET_DATA_PROPS(4,2,0,1,"delta_u_k");
          _SFD_SET_DATA_PROPS(5,2,0,1,"iter");
          _SFD_SET_DATA_PROPS(6,2,0,1,"error");
          _SFD_SET_DATA_PROPS(7,10,0,0,"Nc");
          _SFD_SET_DATA_PROPS(8,10,0,0,"m");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1159);
        _SFD_CV_INIT_EML_IF(0,1,0,408,433,-1,742);

        {
          unsigned int dimVector[2];
          dimVector[0]= 21U;
          dimVector[1]= 21U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 21U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 201U;
          dimVector[1]= 21U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 201U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)c5_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_i_sf_marshallOut,(MexInFcnForType)c5_e_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_i_sf_marshallOut,(MexInFcnForType)c5_e_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)c5_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)c5_d_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _MPCMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_MPCInstanceStruct *chartInstance = (SFc5_MPCInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c5_W_delta);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c5_delta_u_k);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c5_c_delta);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c5_A_iq);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c5_b_iq);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c5_iter);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c5_error);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)&chartInstance->c5_m);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)&chartInstance->c5_Nc);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "scWrpz3oZP9kU2u2QAWggPE";
}

static void sf_opaque_initialize_c5_MPC(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_MPCInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c5_MPC((SFc5_MPCInstanceStruct*) chartInstanceVar);
  initialize_c5_MPC((SFc5_MPCInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_MPC(void *chartInstanceVar)
{
  enable_c5_MPC((SFc5_MPCInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_MPC(void *chartInstanceVar)
{
  disable_c5_MPC((SFc5_MPCInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_MPC(void *chartInstanceVar)
{
  sf_gateway_c5_MPC((SFc5_MPCInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_MPC(SimStruct* S)
{
  return get_sim_state_c5_MPC((SFc5_MPCInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_MPC(SimStruct* S, const mxArray *st)
{
  set_sim_state_c5_MPC((SFc5_MPCInstanceStruct*)sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c5_MPC(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_MPCInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MPC_optimization_info();
    }

    finalize_c5_MPC((SFc5_MPCInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_MPC((SFc5_MPCInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_MPC(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_MPC((SFc5_MPCInstanceStruct*)sf_get_chart_instance_ptr
      (S));
  }
}

static void mdlSetWorkWidths_c5_MPC(SimStruct *S)
{
  /* Actual parameters from chart:
     Nc m
   */
  const char_T *rtParamNames[] = { "Nc", "m" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for Nc*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for m*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MPC_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetSupportedForRowMajorCodeGen(S, 1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 5);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1534994557U));
  ssSetChecksum1(S,(4158472213U));
  ssSetChecksum2(S,(1572428451U));
  ssSetChecksum3(S,(1139038496U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetSimStateCompliance(S, DISALLOW_SIM_STATE);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_MPC(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_MPC(SimStruct *S)
{
  SFc5_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc5_MPCInstanceStruct *)utMalloc(sizeof
    (SFc5_MPCInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc5_MPCInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  if (ssGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME && ssGetOffsetTime(S, 0) ==
      0 && ssGetNumContStates(ssGetRootSS(S)) > 0) {
    sf_error_out_about_continuous_sample_time_with_persistent_vars(S);
  }

  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_MPC;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_MPC;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_MPC;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_MPC;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_MPC;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_MPC;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_MPC;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_MPC;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_MPC;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_MPC;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_MPC;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c5_MPC(chartInstance);
}

void c5_MPC_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_MPC(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_MPC(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_MPC(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_MPC_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
