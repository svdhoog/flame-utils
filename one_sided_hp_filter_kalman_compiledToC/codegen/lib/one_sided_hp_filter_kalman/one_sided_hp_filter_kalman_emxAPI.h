/*
 * one_sided_hp_filter_kalman_emxAPI.h
 *
 * Code generation for function 'one_sided_hp_filter_kalman_emxAPI'
 *
 */

#ifndef ONE_SIDED_HP_FILTER_KALMAN_EMXAPI_H
#define ONE_SIDED_HP_FILTER_KALMAN_EMXAPI_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "one_sided_hp_filter_kalman_types.h"

/* Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (one_sided_hp_filter_kalman_emxAPI.h) */
