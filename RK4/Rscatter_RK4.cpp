#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

// constant
const double eV = 1.60217662e-19; // J
const double qe = 1.602176621e-19; // C
const double eps0 = 8.854187817e-12; // F/m
const double me = 9.1093837e-31; // kg
const double pi = 3.1415926535899;
const double c = 299792458;

// normalization constant
const double nor_position = 1e-15;
const double nor_time = nor_position / c;
const double nor_velocity = c;
const double nor_charge = qe;
const double nor_ke = 4 * pi * eps0;
const double nor_mass = me;
const double nor_energy = nor_mass * nor_velocity * nor_velocity;
const double nor_force = nor_charge * nor_charge / nor_ke / nor_position / nor_position;

double nor_const = nor_charge * nor_charge / nor_velocity / nor_velocity / nor_mass / nor_position / nor_ke;


// impact parameter
const double b1 = 45 * 1e-15 / nor_position;
// alpha particle
int q1 = 2 * qe / nor_charge;
double m1 = 6.644657230e-27 / nor_mass;
double E_in = 5 * 1e6 * eV / nor_energy;
double v_in = sqrt(2 * E_in / m1);
// golden nucleus
int q2 = 79 * qe / nor_charge;

const double ke = q1 * q2;

double ax(double x, double y, double vx, double vy, double time){
    double dist = sqrt(x*x+y*y);
    return ke / m1 / pow(dist,3) * (x - 0) * nor_const; 
}
double ay(double x, double y, double vx, double vy, double time){
    double dist = sqrt(x*x+y*y);
    return ke / m1 / pow(dist,3) * (y - 0) * nor_const; 
}

double x_new = 0, y_new = 0, vx_new = 0, vy_new = 0;

void rk4(double x_old, double y_old, double vx_old, double vy_old, double time, double tau){

    double  x_RK1,  x_RK2,  x_RK3,  x_RK4,  y_RK1,  y_RK2,  y_RK3,  y_RK4;
    double vx_RK1, vx_RK2, vx_RK3, vx_RK4, ax_RK1, ax_RK2, ax_RK3, ax_RK4;
    double vy_RK1, vy_RK2, vy_RK3, vy_RK4, ay_RK1, ay_RK2, ay_RK3, ay_RK4;

     x_RK1 =  x_old;
     y_RK1 =  y_old;
    vx_RK1 = vx_old;
    vy_RK1 = vy_old;
    ax_RK1 = ax(x_RK1, y_RK1, vx_RK1, vy_RK1, time);
    ay_RK1 = ay(x_RK1, y_RK1, vx_RK1, vy_RK1, time);

     x_RK2 =  x_old + 0.5 * tau * vx_RK1;
     y_RK2 =  y_old + 0.5 * tau * vy_RK1;
    vx_RK2 = vx_old + 0.5 * tau * ax_RK1;
    vy_RK2 = vy_old + 0.5 * tau * ay_RK1;
    ax_RK2 = ax(x_RK2, y_RK2, vx_RK2, vy_RK2, time + 0.5 * tau);
    ay_RK2 = ay(x_RK2, y_RK2, vx_RK2, vy_RK2, time + 0.5 * tau);

     x_RK3 =  x_old + 0.5 * tau * vx_RK2;
     y_RK3 =  y_old + 0.5 * tau * vy_RK2;
    vx_RK3 = vx_old + 0.5 * tau * ax_RK2;
    vy_RK3 = vy_old + 0.5 * tau * ay_RK2;
    ax_RK3 = ax(x_RK3, y_RK3, vx_RK3, vy_RK3, time + 0.5 * tau);
    ay_RK3 = ay(x_RK3, y_RK3, vx_RK3, vy_RK3, time + 0.5 * tau);

     x_RK4 =  x_old + tau * vx_RK3;
     y_RK4 =  y_old + tau * vy_RK3;
    vx_RK4 = vx_old + tau * ax_RK3;
    vy_RK4 = vy_old + tau * ay_RK3;
    ax_RK4 = ax(x_RK4, y_RK4, vx_RK4, vy_RK4, time + tau);
    ay_RK4 = ay(x_RK4, y_RK4, vx_RK4, vy_RK4, time + tau);

    vx_new = vx_old + tau / 6 * (ax_RK1 + 2 * ax_RK2 + 2 * ax_RK3 + ax_RK4);
    vy_new = vy_old + tau / 6 * (ay_RK1 + 2 * ay_RK2 + 2 * ay_RK3 + ay_RK4);
     x_new =  x_old + tau / 6 * (vx_RK1 + 2 * vx_RK2 + 2 * vx_RK3 + vx_RK4);
     y_new =  y_old + tau / 6 * (vy_RK1 + 2 * vy_RK2 + 2 * vy_RK3 + vy_RK4);

}

int main(){
    double ini_x = -1e-12 / nor_position;
    double total_time = 2 * abs(ini_x) / v_in; // unit: nor_time  
    int steps = 200;
    double dt = total_time / steps; 
    double vx[steps+1], vy[steps+1], x[steps+1], y[steps+1], t_now[steps+1];
    vx[0] = v_in; vy[0] = 0; x[0] = ini_x; y[0] = b1, t_now[0] = 0;
  
    for (int i = 1; i <= steps; i++){
        rk4(x[i-1], y[i-1], vx[i-1], vy[i-1], t_now[i-1], dt);
        vx[i] = vx_new;
        vy[i] = vy_new;
         x[i] = x_new;
         y[i] = y_new;
        t_now[i] = t_now[i-1] + dt;
    }

    cout << "diagnosis degree: " << atan(vy[steps-1] * nor_velocity / vx[steps-1] / nor_velocity) / pi * 180;
    cout << " " << 2 * atan(2 * q1 * q2 * qe * qe / m1 / nor_mass / v_in / v_in / nor_velocity / nor_velocity / nor_ke / 2 / b1 / nor_position) / pi * 180;
    cout << endl;
    double p0 = 2 * q1 * q2 * qe * qe / m1 / nor_mass / v_in / v_in / nor_velocity / nor_velocity / nor_ke;
    cout << "diagnosis energy: " << v_in * v_in << " " << vx[steps-1] * vx[steps-1] + vy[steps-1] * vy[steps-1] << endl;
    if (p0 > b1 * nor_position){
        cout << "reflect" << endl;
    }
    else{
        cout << "go through" << endl;
    }

    std::ofstream ofs;
    ofs.open("output.txt");
    for (int i = 0; i <= steps; i++){
        ofs << x[i] * nor_position << "," << y[i] * nor_position << endl;
    }

}






