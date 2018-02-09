#ifndef PID_H
#define PID_H
#include "ring_buffer.h"

class PID {
public:
  /*
  * Errors
  */
  double curr_delta;
  double prev_delta;
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
   * dt
   */
  double dt;

  Ring_Buffer buf;

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
  void Init(double dt_in, int buff_size, double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID control signal.
  */
  double Control();
};

#endif /* PID_H */
