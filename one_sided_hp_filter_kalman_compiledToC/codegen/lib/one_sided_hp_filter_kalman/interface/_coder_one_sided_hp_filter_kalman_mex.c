/*
 * _coder_one_sided_hp_filter_kalman_mex.c
 *
 * Code generation for function '_coder_one_sided_hp_filter_kalman_mex'
 *
 */

/* Include files */
#include "_coder_one_sided_hp_filter_kalman_api.h"
#include "_coder_one_sided_hp_filter_kalman_mex.h"

/* Function Declarations */
static void c_one_sided_hp_filter_kalman_me(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[2]);

/* Function Definitions */
static void c_one_sided_hp_filter_kalman_me(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[2])
{
  int32_T n;
  const mxArray *inputs[2];
  const mxArray *outputs[2];
  int32_T b_nlhs;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        26, "one_sided_hp_filter_kalman");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 26,
                        "one_sided_hp_filter_kalman");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  one_sided_hp_filter_kalman_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  one_sided_hp_filter_kalman_terminate();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(one_sided_hp_filter_kalman_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  one_sided_hp_filter_kalman_initialize();

  /* Dispatch the entry-point. */
  c_one_sided_hp_filter_kalman_me(nlhs, plhs, nrhs, prhs);
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_one_sided_hp_filter_kalman_mex.c) */
