/*
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "one_sided_hp_filter_kalman.h"
#include "main.h"
#include "one_sided_hp_filter_kalman_terminate.h"
#include "one_sided_hp_filter_kalman_emxAPI.h"
#include "one_sided_hp_filter_kalman_initialize.h"

/* Function Declarations */
static emxArray_real_T *argInit_Unboundedx1_real_T(void);
static double argInit_real_T(void);
static void main_one_sided_hp_filter_kalman(void);

/* Function Definitions */
static emxArray_real_T *argInit_Unboundedx1_real_T(void)
{
  emxArray_real_T *result;
  static int iv1[1] = { 2 };

  int idx0;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real_T(1, iv1);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[idx0] = argInit_real_T();
  }

  return result;
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void main_one_sided_hp_filter_kalman(void)
{
  emxArray_real_T *ytrend;
  emxArray_real_T *ycycle;
  emxArray_real_T *y;
  emxInitArray_real_T(&ytrend, 1);
  emxInitArray_real_T(&ycycle, 1);

  /* Initialize function 'one_sided_hp_filter_kalman' input arguments. */
  /* Initialize function input argument 'y'. */
  y = argInit_Unboundedx1_real_T();

  /* Call the entry-point 'one_sided_hp_filter_kalman'. */
  one_sided_hp_filter_kalman(y, argInit_real_T(), ytrend, ycycle);
  emxDestroyArray_real_T(ycycle);
  emxDestroyArray_real_T(ytrend);
  emxDestroyArray_real_T(y);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  one_sided_hp_filter_kalman_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_one_sided_hp_filter_kalman();

  /* Terminate the application.
     You do not need to do this more than one time. */
  one_sided_hp_filter_kalman_terminate();
  return 0;
}

/* End of code generation (main.c) */
