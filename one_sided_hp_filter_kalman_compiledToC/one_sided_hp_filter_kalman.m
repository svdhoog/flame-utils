function [ytrend,ycycle] = one_sided_hp_filter_kalman(y,lambda)

% One-sided HP filter using the Kalman filter to optimally one-sidedly 
% filter the series that renders the standard two-sided HP filter optimal.

%% Inputs  
% y         Txn matrix, with T time series obs. and n variables
% lambda    scalar, smoothing parameter
% x_user    2xn matrix with initial values of the state estimate for each 
%           variable in y. The underlying state vector is 2x1m hence two values are needed
%           for each variable in y. Optional: if not entered, default backwards extrapolations based on the
%           first two observations will be used.
% P_user    a structural array with n elements, each a two
%           2x2 matrix of intial MSE estimates for each
%           variable in y.  Optional: if not entered,
%           default matrix with large variances used.
% discard   scalar. The first discard periods will be
%           discarded resulting in output matrices of size
%           (T-discard)xn. Optional: if not entered, a default
%           value of 0 will be used.

%% Outputs
% ytrend   (T-discard)xn matrix of extracted trends for each of the n variables.
% ycycle   (T-discard)xn matrix of deviations from the extracted trends for
%          each of the n variables. Optional.

%if nargin < 2 || isempty(lambda),  lambda = 1600; end
[T,n] = size(y);
ytrend = NaN(T,n);

% The notation follows Chapter 13 of Hamilton, J.D. (1994). Time Series Analysis. with the exception of H, which is equivalent to his H'.
q = 1/lambda; % signal-to-noise ratio: i.e. var eta_t / var epsilon_t
F = [2,-1;1,0]; % state transition matrix
H = [1,0]; % observation matrix
Q = [q,0;0,0]; % variance-covariance matrix of the errors in the state equation
R = 1; % variance of the error in the observation equation

x_user = [];
P_user = [];

for k=1:n % run Kalman filter for each variable
    if nargin < 4 || isempty(x_user), x=[2*y(1,k)-y(2,k); 3*y(1,k)-2*y(2,k)]; else x=x_user(:,k);end % If the user didn't provide an intial value for state estimate, extrapolate back two periods from the observations
    if nargin < 4 || isempty(P_user), P= [1e5 0;0 1e5]; else P=P_user{k}; end % If the user didn't provide an intial value for the MSE, set a rather high one

    for j=1:T
        [x,P] = kalman_update(F,H,Q,R,y(j,k),x,P);
        ytrend(j,k) = x(2);  % second element of the state is the estimate of the trend
    end
end

% Compute gap in case it was requested
if nargout==2 
    ycycle = y-ytrend;
end

% If the user provided discard parameter
%if nargin==5 
%    ytrend=ytrend(discard+1:end,:);% remove the first "discard" periods from the trend series
%    if nargout==2 % should the user have requested the gap
%        ycycle=ycycle(discard+1:end,:);
%    end
%end

end

function [x,P] = kalman_update(F,H,Q,R,obs,x,P)

S = H*P*H'+R; 
K = F*P*H';
K = K/S; % Kalman gain
x = F*x+K*(obs-H*x); % state estimate
Temp = F-K*H;
P = Temp*P*Temp';
P = P+Q+K*R*K'; % MSE estimate

end