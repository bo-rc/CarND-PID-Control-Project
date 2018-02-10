# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

This repo implements a simple PID controller for lateral control of a simulation car running on a track.

# Compile and Run
```bash
mkdir build && cd build
cmake .. && make
./pid
```

# Implementaion

The `PID` class:
* follows the algorithm in the lectures.
* uses a ring buffer, an instance of the [`Ring_Buffer`]() class, to model memory for the integral term: rather than taking account of all history of previous errors, the ring buffer only records a short history of errors and the [`integrate()`]() method gives the integral error. The purpose is to limit the acummulation of the integral term, otherwise the integral term can be arbitrarily large if the car is bogged down.
* uses [`Control()`]() method to ouput steering command.
  * in this method, the control output is scaled by a hyperparameter `cte_range`, which is hardcoded to be twice the magnitude of `cte` if the car is about to fall off track. This hyperparameter can be tuned.

## Tuning
The tuning is done manually. The binary `pid` program accepts arguments (demonstrated in [`main.cpp`]()) such that I coubld quickly try different parameters.

The tuning is performed using a heuristic method as follows:
* First tune P gain, with D and I gain turned off: increase P gain until the car ossilates right and left on a straight lane. 
* Then, lower P by 10% and add D gain until the ossilation is gone on a straight lane.
* Finally, tune I gain on a turn. Without an integral term, the accumulation of errors on a turn could not be handled by just the P gain. So the best place to tune the I gain, in my experience, is during a turn. Gradually increase I gain until the turning of the car slightly overshoot, then increase D gain a little bit to dampen the overshooting.

Finally, I use a set of tuned parameters to initialize the `PID` controller for steering in the `main.cpp` file. Without arguments with `./pid`, those tuned parameters will be used.

## Full-lap run



# Reflection

* The P component is like the gas pedal of a car, larger P gain means that going to a target faster. 
* But, using only P gain, metaphorically using only the gas pedal of a car, will overshoot the target. Therefore, the D gain is useful; it is like the breaking pedal of a car, which tends to slow down the motion when the car is driven by the gas pedal and shooting for the target. 
* The I component models systematic bias. On a straight flat road, with a neutral-trimed steering wheel, the I component is not necessary. However, if error would accumulate with respect to time or if the steering has a systematic bias, e.g. the steering wheel is not perfectly centered, the I component can be used to counter the bias effect.

For example, during a turn the error would accumulate faster such that the P component alone would not be able to make good turn. As shown in the following tests:

__turning w/o I component__:



__turning w/ I component__:


Finally, I found that the tuning of the PID gains also depend on which computer the simulation is running. This is likely due to the fact that different computer runs at different speed but the `dt` term in our PID controller is implicitly assumed as 1.0. However, more realistic modeling should use the true time duration of the feedback control.
