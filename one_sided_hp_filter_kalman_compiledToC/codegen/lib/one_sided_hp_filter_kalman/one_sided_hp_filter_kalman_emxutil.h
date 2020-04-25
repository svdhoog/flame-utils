/*
 * one_sided_hp_filter_kalman_emxutil.h
 *
 * Code generation for function 'one_sided_hp_filter_kalman_emxutil'
 *
 */

#ifndef ONE_SIDED_HP_FILTER_KALMAN_EMXUTIL_H
#define ONE_SIDED_HP_FILTER_KALMAN_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "one_sided_hp_filter_kalman_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (one_sided_hp_filter_kalman_emxutil.h) */
