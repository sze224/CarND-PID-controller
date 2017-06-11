#include "PID.h"
#include <iostream>
#include <math.h>
#include <uWS/uWS.h>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_i, double Ki_i, double Kd_i) {
	Kp = Kp_i;
	Ki = Ki_i;
	Kd = Kd_i;
	previous_error = 0;
	p_error = 0;
	i_error = 0;
	d_error = 0;

	/* Initialize Twiddle parameter */
	steps = 0;
	Twiddle_error = 0;
}

double PID::UpdateError(double cte) {
	p_error = cte;
	i_error = i_error + cte;
	d_error = cte - previous_error;
	previous_error = cte;
	double steer_angle = -Kp * p_error + -Ki * i_error + -Kd * d_error;
	if (steer_angle > 1){
		steer_angle = 1;
	}else if(steer_angle < -1){
		steer_angle = -1;
	}
	return steer_angle;
}

void PID::TotalError(double cte) {
	Twiddle_error = Twiddle_error + fabs(cte);
}


int PID::get_step(){
	steps = steps + 1;
	return steps;
}

void PID::twiddle(double current_error){
	/* 
	outline of twiddle (go through pid)
	1) update gain in the increasing direction, get new error
		1) new error is better than previous best error - going the right direction, increase delta
		2) new error is worst than previous best error - going the wrong direction, update gain in the decreasing direction
			1) new error is better than previous best error, increase delta
			2) new error is worst than previous error, go back to original gains, decrease delta
	*/
	if (c_pos > 2){/* reset back to changing the p gain */
		c_pos = 0;
	}

	switch (t_step){	
		case 1:
			/* update gain in the increasing direction, get new error */
			switch(c_pos){
				case 0:
					Kp = Kp + dp; 
					break;
				case 1:	
					Ki = Ki + di;
					break;
				case 2:	
					Kd = Kd + dd;
					break;
			}
			t_step = t_step + 1;
			d_step = 1;
			break;

		case 2: /* go through the two possible outcome */
			/* new error is better than previous best */
			if(current_error < best_error && d_step == 1){
				best_error = current_error;
				switch(c_pos){
					case 0:
						dp = dp * 1.1; 
						break;
					case 1:	
						di = di * 1.1;
						break;
					case 2:	
						dd = dd * 1.1;
						break;
				}
				/* back to step 1 for the next gain */
				t_step = 1;
				c_pos = c_pos + 1;
			}else{
				/* new error is not better than previous best */
				switch(d_step){
					case 1:
						switch(c_pos){
							case 0:
								Kp = Kp - 2 * dp; 
								break;
							case 1:	
								Ki = Ki - 2 * di;
								break;
							case 2:	
								Kd = Kd - 2 * dd;
								break;
						}
						d_step = d_step + 1;
						break;
					case 2:
						if(current_error < best_error){
							best_error = current_error;
							switch(c_pos){
								case 0:
									dp = dp * 1.1; 
									break;
								case 1:	
									di = di * 1.1;
									break;
								case 2:	
									dd = dd * 1.1;
									break;
							}
							t_step = 1;
							c_pos = c_pos + 1;
						}else{
							switch(c_pos){	
								case 0:
									Kp = Kp + dp;
									dp = dp * 0.9;
									break;
								case 1:	
									Ki = Ki + di;
									di = di * 0.9;
									break;
								case 2:	
									Kd = Kd + dd;
									dd = dd * 0.9;
									break;
							}
							t_step = 1;
							c_pos = c_pos + 1;
						}
					}
			}
			break;
			
	}
}

void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  steps = 0;
  Twiddle_error = 0;
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}





