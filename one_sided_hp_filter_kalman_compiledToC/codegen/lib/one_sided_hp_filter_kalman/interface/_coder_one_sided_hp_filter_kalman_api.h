/*
 * _coder_one_sided_hp_filter_kalman_api.h
 *
 * Code generation for function '_coder_one_sided_hp_filter_kalman_api'
 *
 */

#ifndef _CODER_ONE_SIDED_HP_FILTER_KALMAN_API_H
#define _CODER_ONE_SIDED_HP_FILTER_KALMAN_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_one_sided_hp_filter_kalman_api.h"

/* Type Definitions */
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

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void one_sided_hp_filter_kalman(emxArray_real_T *y, real_T lambda,
  emxArray_real_T *ytrend, emxArray_real_T *ycycle);
extern void one_sided_hp_filter_kalman_api(const mxArray *prhs[2], const mxArray
  *plhs[2]);
extern void one_sided_hp_filter_kalman_atexit(void);
extern void one_sided_hp_filter_kalman_initialize(void);
extern void one_sided_hp_filter_kalman_terminate(void);
extern void one_sided_hp_filter_kalman_xil_terminate(void);

#endif

/* End of code generation (_coder_one_sided_hp_filter_kalman_api.h) */
