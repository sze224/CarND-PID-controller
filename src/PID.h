#ifndef PID_H
#define PID_H
#include <uWS/uWS.h>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double previous_error;
  double steer_angle;

  /*
  * Coefficients
  */ 
  double Kp = 0.188;
  double Ki = 1.1e-05;
  double Kd = 1.57078;

  /* Twiddle Variables */
  double dp = .1;
  double di = .00001;
  double dd = .1;
  int dir = 1;
  int c_pos = 0; 
  double Twiddle_error;
  int steps;
  int t_step = 1;
  int d_step = 1;
  double best_error;
  int first_twiddle = 0;
  /* set this value to 0 if not using twiddle to find gains */
  int use_twiddle = 0;



  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error and return steering angle.
  */
  double UpdateError(double cte);

  /*
  * Calculate the total error for Twiddle use.
  */
  void TotalError(double cte);

  /* get cte for twiddle use */
  double returnError(double cte);

  int get_step();


  /* Twiddle */
  void twiddle(double current_error);

  void Restart(uWS::WebSocket<uWS::SERVER> ws);
  
};

#endif /* PID_H */
