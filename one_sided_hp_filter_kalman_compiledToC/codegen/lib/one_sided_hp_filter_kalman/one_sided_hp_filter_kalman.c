/*
 * one_sided_hp_filter_kalman.c
 *
 * Code generation for function 'one_sided_hp_filter_kalman'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "one_sided_hp_filter_kalman.h"
#include "one_sided_hp_filter_kalman_emxutil.h"

/* Function Definitions */
void one_sided_hp_filter_kalman(const emxArray_real_T *y, double lambda,
  emxArray_real_T *ytrend, emxArray_real_T *ycycle)
{
  int i0;
  int i;
  double Q[4];
  double x[2];
  double P[4];
  static const int iv0[4] = { 100000, 0, 0, 100000 };

  int j;
  double dv0[2];
  double b_y;
  double F[4];
  int i1;
  double d0;
  double K[2];
  double d1;
  double Temp[4];
  double b_x[2];
  static const signed char b_F[4] = { 2, 1, -1, 0 };

  double b_Temp[4];
  double b_K[4];

  /*  One-sided HP filter using the Kalman filter to optimally one-sidedly  */
  /*  filter the series that renders the standard two-sided HP filter optimal. */
  /* % Inputs   */
  /*  y         Txn matrix, with T time series obs. and n variables */
  /*  lambda    scalar, smoothing parameter */
  /*  x_user    2xn matrix with initial values of the state estimate for each  */
  /*            variable in y. The underlying state vector is 2x1m hence two values are needed */
  /*            for each variable in y. Optional: if not entered, default backwards extrapolations based on the */
  /*            first two observations will be used. */
  /*  P_user    a structural array with n elements, each a two */
  /*            2x2 matrix of intial MSE estimates for each */
  /*            variable in y.  Optional: if not entered, */
  /*            default matrix with large variances used. */
  /*  discard   scalar. The first discard periods will be */
  /*            discarded resulting in output matrices of size */
  /*            (T-discard)xn. Optional: if not entered, a default */
  /*            value of 0 will be used. */
  /* % Outputs */
  /*  ytrend   (T-discard)xn matrix of extracted trends for each of the n variables. */
  /*  ycycle   (T-discard)xn matrix of deviations from the extracted trends for */
  /*           each of the n variables. Optional. */
  /* if nargin < 2 || isempty(lambda),  lambda = 1600; end */
  i0 = ytrend->size[0];
  ytrend->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)ytrend, i0, (int)sizeof(double));
  i = y->size[0];
  for (i0 = 0; i0 < i; i0++) {
    ytrend->data[i0] = rtNaN;
  }

  /*  The notation follows Chapter 13 of Hamilton, J.D. (1994). Time Series Analysis. with the exception of H, which is equivalent to his H'. */
  /*  signal-to-noise ratio: i.e. var eta_t / var epsilon_t */
  /*  state transition matrix */
  /*  observation matrix */
  Q[0] = 1.0 / lambda;
  Q[2] = 0.0;
  for (i0 = 0; i0 < 2; i0++) {
    Q[1 + (i0 << 1)] = 0.0;
  }

  /*  variance-covariance matrix of the errors in the state equation */
  /*  variance of the error in the observation equation */
  /*  run Kalman filter for each variable */
  x[0] = 2.0 * y->data[0] - y->data[1];
  x[1] = 3.0 * y->data[0] - 2.0 * y->data[1];

  /*  If the user didn't provide an intial value for state estimate, extrapolate back two periods from the observations */
  for (i0 = 0; i0 < 4; i0++) {
    P[i0] = iv0[i0];
  }

  /*  If the user didn't provide an intial value for the MSE, set a rather high one */
  for (j = 0; j < y->size[0]; j++) {
    b_y = 0.0;
    for (i0 = 0; i0 < 2; i0++) {
      dv0[i0] = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        dv0[i0] += (1.0 - (double)i1) * P[i1 + (i0 << 1)];
      }

      b_y += dv0[i0] * (1.0 - (double)i0);
    }

    /*  Kalman gain */
    d0 = 0.0;
    for (i0 = 0; i0 < 2; i0++) {
      d1 = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        F[i0 + (i1 << 1)] = 0.0;
        for (i = 0; i < 2; i++) {
          F[i0 + (i1 << 1)] += (double)b_F[i0 + (i << 1)] * P[i + (i1 << 1)];
        }

        d1 += F[i0 + (i1 << 1)] * (1.0 - (double)i1);
      }

      K[i0] = d1 / (b_y + 1.0);
      d0 += (1.0 - (double)i0) * x[i0];
    }

    b_y = y->data[j] - d0;

    /*  state estimate */
    for (i0 = 0; i0 < 2; i0++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        d0 += (double)b_F[i0 + (i1 << 1)] * x[i1];
        Temp[i0 + (i1 << 1)] = (double)b_F[i0 + (i1 << 1)] - K[i0] * (1.0 -
          (double)i1);
      }

      b_x[i0] = d0 + K[i0] * b_y;
    }

    /*  MSE estimate */
    for (i = 0; i < 2; i++) {
      x[i] = b_x[i];
      for (i0 = 0; i0 < 2; i0++) {
        F[i + (i0 << 1)] = 0.0;
        for (i1 = 0; i1 < 2; i1++) {
          F[i + (i0 << 1)] += Temp[i + (i1 << 1)] * P[i1 + (i0 << 1)];
        }
      }

      for (i0 = 0; i0 < 2; i0++) {
        d0 = 0.0;
        for (i1 = 0; i1 < 2; i1++) {
          d0 += F[i + (i1 << 1)] * Temp[i0 + (i1 << 1)];
        }

        b_Temp[i + (i0 << 1)] = d0 + Q[i + (i0 << 1)];
        b_K[i + (i0 << 1)] = K[i] * K[i0];
      }
    }

    for (i0 = 0; i0 < 2; i0++) {
      for (i1 = 0; i1 < 2; i1++) {
        P[i1 + (i0 << 1)] = b_Temp[i1 + (i0 << 1)] + b_K[i1 + (i0 << 1)];
      }
    }

    ytrend->data[j] = b_x[1];

    /*  second element of the state is the estimate of the trend */
  }

  /*  Compute gap in case it was requested */
  i0 = ycycle->size[0];
  ycycle->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)ycycle, i0, (int)sizeof(double));
  i = y->size[0];
  for (i0 = 0; i0 < i; i0++) {
    ycycle->data[i0] = y->data[i0] - ytrend->data[i0];
  }

  /*  If the user provided discard parameter */
  /* if nargin==5  */
  /*     ytrend=ytrend(discard+1:end,:);% remove the first "discard" periods from the trend series */
  /*     if nargout==2 % should the user have requested the gap */
  /*         ycycle=ycycle(discard+1:end,:); */
  /*     end */
  /* end */
}

/* End of code generation (one_sided_hp_filter_kalman.c) */
