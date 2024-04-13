//	Package:	intensity
//	File:		intensity.c 
//	Purpose:	Calculate light intensity
//	Author:		jrom876

/**
	Copyright (C) 2023 
	Jacob Romero, Creative Engineering Solutions, LLC
	cesllc876@gmail.com
**/

/** References:	
 * https://refractiveindex.info/?shelf=other&book=air&page=Ciddor
 * https://en.wikipedia.org/wiki/Intensity_(physics)
 * https://en.wikiversity.org/wiki/Physics_Formulae/Equations_of_Light
 * https://physics.stackexchange.com/questions/771985/calculating-measured-intensity-of-a-gaussian-beam?rq=1https://phys.libretexts.org/Bookshelves/University_Physics/Book%3A_University_Physics_(OpenStax)/Book%3A_University_Physics_II_-_Thermodynamics_Electricity_and_Magnetism_(OpenStax)/05%3A_Electric_Charges_and_Fields/5.05%3A_Electric_Field
 * https://www.rp-photonics.com/optical_intensity.html
 * https://www.rp-photonics.com/gaussian_beams.html
 * https://en.wikipedia.org/wiki/Lux
**/

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <check.h>
#include "intensity.h"

/// STANDARD DEFINITIONS FOR PROJECT SCICALC 
#define PI	3.14159265358979323846 // ad infinitum
#define LIGHT_SPEED		299792458.0 // meters per second
#define DATA_SIZE 1000
#define MICRO 1.0e-6
#define NANO 1.0e-9
#define PICO 1.0e-12
#define KILO 1.0e3
#define MEGA 1.0e6
#define GIGA 1.0e9
#define TERA 1.0e12 
#define AIR_REFRACTIVE_INDEX 1.00027717
#define E0 8.8541878128*PICO				// Permittivity of Free Space in Farads per meter
#define MU0 1.25663706212*MICRO				// Permeability of Free Space in Newtons per square meter
#define EPSILON_0 1/(MU0*(LIGHT_SPEED*LIGHT_SPEED))	// Permittivity of Free Space Equation
#define ELECTRON_CHARGE 1.6e-19 // Charge of an electron in Coulombs
#define RADIUS_HELIUM_ATOM 26.5e-12
#define LED_ARRAY_RADIUS 0.35 // meters from LED array to sample plate
#define E_CONSTANT 1/(4*PI*EPSILON_0)

#define TXT_FILE "intensity.txt"

///===============================================
/** This data structure holds the test inputs for our intensity object. 
	All we need are:
		1. The speed of light in whatever medium we are in
		2. The refractive index of light in whatever medium we are in
		3. The permittivity of free space
		4. The strength of our electric field 
**/
struct I_test {
    float 	c;		// speed of light in medium
    float 	ri;		// refractive index of medium
    float 	e0;		// permittivity of free space 
    double 	Efield;	// electric field
};
///===============================================

/** This data structure holds the test inputs for our circuit object. 
	All we need are:
		1. voltage at the Feedback input
		2. current value
		2. resistor value
		3. number of branches
**/
struct C_test {
    float 	v;		// voltage
    float 	i; 		// current
    float 	r;		// resistor
    float 	num;	// number of branches 
};
///===============================================

/** calc_intensity(int c, double ri, double eps0, double efield) 
 * 	calculate the local intensity of a plane wave or Gaussian Beam
 * 	c = speed of light
 * 	ri = refractive index
 * 	eps0 = permittivity of free space 
 * 	efield = electric field
**/
double calc_intensity(int c, double ri, double eps0, double efield) {
	 double result = ((c * ri * eps0)/(2)) * (efield*efield);
	 printf("intensity = %e\n",result);
	 return result;
}
///===============================================

/** calc_irradiance(int c, double mu0, double efield)
 * calculate light intensity. Poynting Vector magnitude
 * 	c = speed of light
 * 	mu0 = permeability of free space 
 * 	efield = electric field
**/
double calc_irradiance(int c, double mu0, double efield) { 
	 double result = (efield*efield)/(c * mu0);
	 printf("intensity = %e\n",result);
	 return result;
}
///===============================================

double calc_Electric_Field(double num_charges, double charge, double radius) {
	 double result = E_CONSTANT * (2*(charge))/(radius*radius);
	 printf("E field = %e\n",result);
	 return result;
}
///===============================================

double calc_Lux(double received_illuminance, double reflectance) {
	 double result = (received_illuminance * reflectance)/PI;
	 printf("Lux = %e\n",result);
	 return result;
}
///===============================================

//~ float calc_parallel_resistance(float resistor_value, int num_branches) {
	 //~ double result = 1/(num_branches * (1/resistor_value));
	 //~ printf("net resistance = %.8f\n",result);
	 //~ return result;
//~ }
//~ ///===============================================

//~ float total_current(float voltage, float resistance, int num_branches) {
	 //~ double result = num_branches*(voltage/resistance);
	 //~ printf("total current = %.8f Amps\n",result);
	 //~ return result;
//~ }///===============================================

//~ float branch_current(float voltage, float resistance) {
	 //~ double result = (voltage/resistance);
	 //~ printf("total current = %.8f Amps\n",result);
	 //~ return result;
//~ }
//~ ///===============================================

//~ float calc_power(float voltage, float current) {
	 //~ double result = voltage*current;
	 //~ printf("total power = %.8f Watts\n",result);
	 //~ return result;
//~ }
//~ ///===============================================

//~ void doseEdge_ResToLux(float resistor) {
	 //~ const float Luxslope = 30;
	 //~ const int maxLux = 1900, minRes = 10;
	 //~ resistor = (resistor >= minRes) ? resistor : 10;
	 //~ float result = (maxLux - (resistor * Luxslope) >= 0) ? maxLux - (resistor * Luxslope) : 0;
	 //~ printf("LUX = %.2f\tlumen/m^2\t for resistor value = %.2f\n",result, resistor);
//~ }

//~ void doseEdge_ResToPercent(float resistor) {
	 //~ const float PercentSlope = 1.875;
	 //~ const float maxPercent = 118.75, minRes = 10;
	 //~ resistor = (resistor >= minRes) ? resistor : 10;
	 //~ float result = (maxPercent - (resistor * PercentSlope) >= 0) ? maxPercent - (resistor * PercentSlope) : 0;
	 //~ printf("Percent of Max = %.4f\t for resistor value = %.2f\n",result, resistor);
//~ }

//~ void doseEdge_ResToAll(float resistor) {
	 //~ const float slope = 30;
	 //~ const int maxLux = 1900, minRes = 10;
	 //~ const float PercentSlope = 1.875;
	 //~ const float maxPercent = 118.75;
	 //~ resistor = (resistor >= minRes) ? resistor : 10;
	 //~ float LUX = (maxLux - (resistor * slope) >= 0) ? maxLux - (resistor * slope) : 0;
	 //~ float PERCENT = (maxPercent - (resistor * PercentSlope) >= 0) ? maxPercent - (resistor * PercentSlope) : 0;
	 //~ printf("LUX = %.2f\tlumen/m^2\tPercent of Max = %.4f\tfor resistor value = %.2f\n",LUX, PERCENT, resistor);
	 //~ float PERCENT = (maxPercent - (resistor * PercentSlope) >= 0) ? maxPercent - (resistor * PercentSlope) : 0;
	 //~ printf("Percent of Max = %.4f\t for resistor value = %.2f\n",PERCENT, resistor);
	 //~ printf("\n");
//~ }
//~ ///===============================================
