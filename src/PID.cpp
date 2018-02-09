#include "PID.h"
#include <cmath>

const double p_gain = 0.5;
const double i_gain = 0.1;
const double d_gain = 0.25;
const double cte_range = 30;

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID(int ring_buffer_size) :
    curr_delta(0.0),
    prev_delta(0.0),
    p_error(0.0),
    i_error(0.0),
    d_error(0.0),
    Kp(p_gain),
    Ki(i_gain),
    Kd(d_gain),
    dt(1.0),
    buf(ring_buffer_size)
{
    // nothing to do
}

PID::~PID() {}

void PID::Init(double Kp_in, double Ki_in, double Kd_in, double dt_in) {
    Kp = Kp_in;
    Ki = Ki_in;
    Kd = Kd_in;
    dt = dt_in;
}

void PID::UpdateError(double cte) {
    curr_delta = cte;

    // update p, i, d errors
    p_error = curr_delta;
    buf.insert(curr_delta);
    i_error = buf.integrate();
    d_error = (curr_delta - prev_delta) / dt;
    prev_delta = curr_delta;
}

double PID::Control() {
    auto pid = -Kp * p_error - Ki * i_error - Kd * d_error;
    auto ctrl = pid / (cte_range / 2.0);
//    if (ctrl > 1.0) {
//        return 1.0;
//    } else if (ctrl < -1.0) {
//        return -1.0;
//    } else {
//        return ctrl;
//    }
    return ctrl;
}

