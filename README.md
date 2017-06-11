# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## Reflections:

PID controller:
PID controller is one of the most commonly used controller in the industry. 
The way that a PID controller works is that it will calculate the desired input to a system based on the error of the system.
In this case, the error mwan the difference between the desired state and the current state.

The effect of the PID components:
* P - P stands for Porportional. Just as it sound, the contribution of the Porportional term depends on the size of the error. If the error is big, the controller will create a big input to offset the error. If the error is small, the porpotional term will have a small contribution.
* I - I stands for Integral. The contribution of this term depending on the accumlation of the errors over time. The significant of this term is to get zero steady state error. In other word, this term will help the system get to the desired state once the system reaches steady state, which the porportional term alone will not be able to achieve. 
* D - D stands for Derivative. The contribution of this term depending on the rate of change in error. This term can be think of as a predictive term. If the rate of change in error is larger, we can deduct that the system might be oscillating. With the derivative term, we can damp out the osciallation and reduce the overshoot of the system.

Derivation of hyperparameters:

This hyperparameters in this project (Kp, Ki, Kd) were chosen by the combination of manual tuning and the twiddle method. The first thing that I do was manually finding out a set of value where it will allow the car to roughly stay in the track. This manual tuning does not have to be pretty as the twiddle method will take care of that.
Once I get gains that allow the car to stay in the track (doesn't matter if the car oscillate and overshot the desired state), I being to apply the twiddle method.  

How does twiddle work:

In order to use twiddle, there is a few things that we need to define:
1) we will need to come up with a way to score how the current set of gains is performing. In this case, I am accumlating the cte of 1500 time step and treating that as the benchmark of the performance. 
2) The stop condition for twiddle
3) The predefined delta value of individual gain

With these things defined, twiddle is just a really simple but effective method to optimize gains.

Twiddle will increase the gain by the predefined delta value and then calculate the resulting performance benchmark. 

If the performance benchmark is better than the best benckmark recorded, then twiddle will increase the predefined delta value and go to the next gain.

If the performance benchmark is worst than the best benchmark recorded, then twiddle will try go the opposite direction and decrease the gain by the predefined delta value and calculate the resulting performance benchmark.

Again, if the performance is better than the best benchmark recorded, twiddle will increase the predefined delta value and go to the next gain. However, if the performance is worst than the best benchmark recorded, twiddle will retore the gain in the beginning of the loop, decrease the predefined delta value and move on to the next gain.

This above steps will be repeated until we hit the stop condition.

Using the methods above, I was able to obtain the gains of:
Final result: Kp - 0.188 Ki - 1.1e-05 Kd - 1.57078

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
