#include "PID.h"
#include <cmath>

const double p_gain = 6.0;
const double i_gain = 2.0;
const double d_gain = 300;
const double cte_range = 40;
const int buf_size = 10;

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() :
    curr_delta(0.0),
    prev_delta(0.0),
    p_error(0.0),    i_error(0.0),
    d_error(0.0),
    Kp(p_gain),
    Ki(i_gain),
    Kd(d_gain),
    dt(1.0),
    buf(buf_size)
{
    // nothing to do
}

PID::~PID() {}

void PID::Init(double dt_in, int buff_size, double Kp_in, double Ki_in, double Kd_in) {
    dt = dt_in;
    buf.set_buf_size(buff_size);
    Kp = Kp_in;
    Ki = Ki_in;
    Kd = Kd_in;
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

