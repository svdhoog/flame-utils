/*
 * one_sided_hp_filter_kalman.h
 *
 * Code generation for function 'one_sided_hp_filter_kalman'
 *
 */

#ifndef ONE_SIDED_HP_FILTER_KALMAN_H
#define ONE_SIDED_HP_FILTER_KALMAN_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "one_sided_hp_filter_kalman_types.h"

/* Function Declarations */
extern void one_sided_hp_filter_kalman(const emxArray_real_T *y, double lambda,
  emxArray_real_T *ytrend, emxArray_real_T *ycycle);

#endif

/* End of code generation (one_sided_hp_filter_kalman.h) */
