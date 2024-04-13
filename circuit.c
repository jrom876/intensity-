
///	Package:	circuit
///	File:		circuit.c 
///	Purpose:	Modeling LED circuit performance
///	Author:		jrom876

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
#include <stdbool.h>
#include <math.h>
//~ #include <check.h>
#include "circuit.h"

/// STANDARD DEFINITIONS FOR PROJECT SCICALC 
#define PI		3.14159265358979323846 // ad infinitum
#define LIGHT_SPEED	299792458 // meters per second
#define DATA_SIZE 1000
#define DELTA 	1.0e-6
#define MILLI 	1.0e-3
#define MICRO 	1.0e-6
#define NANO 	1.0e-9
#define PICO 	1.0e-12
#define KILO 	pow(10,3) 			//1000
#define MEGA 	pow(10,6) 			//1000000
#define GIGA 	pow(10,9) 			//1000000000
#define TERA 	pow(10,12) 			//1000000000000 
#define HALF 	pow(10,0.30102999566398119802)
#define FOURTH 	pow(10,0.60205999132796239603)
#define EIGHTH 	pow(10,0.90308998699194353854)
#define true 1
#define false 0

/// STANDARD DEFINITIONS FOR LIGHT INTENSITY AND ELECTRIC FIELD CALCULATIONS
#define AIR_REFRACTIVE_INDEX 1.00027717
#define E0 8.8541878128*PICO				// Permittivity of Free Space in Farads per meter
#define MU0 1.25663706212*MICRO				// Permeability of Free Space in Newtons per square meter
#define EPSILON_0 1/(MU0*(LIGHT_SPEED*LIGHT_SPEED))	// Permittivity of Free Space Equation
#define E_CONSTANT 1/(4*PI*EPSILON_0)
#define ELECTRON_CHARGE 1.6e-19 			// Charge of an electron in Coulombs
#define RADIUS_HELIUM_ATOM 26.5e-12			// Radius of a Helium atom in meters
#define LED_ARRAY_RADIUS 0.35 				// meters from LED array to sample plate

/// DEFINITIONS FOR DOSEEDGE LED ARRAY THERMAL CALCULATIONS
#define R_THETA_JA_TPS61169	263.8			// Junction to Ambient, in degrees C/Watt
#define ROOM_TEMP1 25.0				// = 77 deg F
#define ROOM_TEMP2 26.7 			// = 80.1 deg F
#define ROOM_TEMP3 40.0 			// = 104.0 deg F
#define MAX_TEMP_TPS61169 100.0			// = 212.0 deg F
#define MAX_OP_JUNCT_TEMP_TPS61169 125.0	// = 257.0 deg F

#define TXT_FILE "circuit.txt"

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
/// Calculates and returns the net parallel resistance when 
/// all resistors are of the same value.
/// Used for LED array current limiting resistor calculations.

float calc_parallel_resistance(float resistor_value, int num_branches) {
	 float result = 1/(num_branches * (1/resistor_value));
	 printf("net parallel resistance\t\t\t = %.8f Ohms\n",result);
	 return result;
}
///===============================================
/// Calculates and returns the variable resistance setting required to be placed
/// in parallel with a fixed resistor in order to obtain a desired net resistance.
/// For use with DoseEdge LED experiments.

float calc_var_resistance(float desired_res, float fixed_res) {
	 float result = (fixed_res*desired_res)/(fixed_res-desired_res);
	 printf("variable resistance\t\t\t = %.8f Ohms\n",result);
	 return result;
}

///===============================================
/// Calculates and returns the equivalent parallel resistance of 
/// a fixed resistor and a variable resistor  

float calc_output_resistance(float fixed_res, float var_res) {
	 float result = (fixed_res*var_res)/(fixed_res+var_res);
	 printf("output resistance\t\t\t = %.8f Ohms\n",result);
	 return result;
}
///===============================================
/// Calculates and returns the total current of multiple branches in a circuit
/// as a function of voltage, resistance, and the number of branches

float total_current(float voltage, float resistance, int num_branches) {
	 float result = num_branches*(voltage/resistance);
	 //~ printf("total current = %.8f Amps\t\tVoltage = %.4f\tres = %.4f\n",result,voltage,resistance);
	 printf("total current = %.8f Amps\t\tNum Branches = %i\n",result, num_branches);
	 return result;
}///===============================================
/// Calculates and returns the current of a single branch in a circuit
/// as a function of voltage and resistance

float branch_current(float voltage, float resistance) {
	 float result = (voltage/resistance);
	 printf("branch current = %.8f Amps\tVoltage = %.2f\t\tres = %.2f Ohms\n",result,voltage,resistance);
	 return result;
}  
///===============================================
/// Calculates and returns the power disspated in a circuit
/// as a function of voltage and current

float calc_power_VI(float voltage, float current) {
	 float result = voltage*current;
	 printf("total power = %.8f Watts\n",result);
	 return result;
}///===============================================
/// Calculates and returns the total power dissipated in multiple branches in a circuit
/// as a function of voltage, current, and the number of branches

float calc_total_power(float voltage, float current, int num_branches) {
	 float result = num_branches*voltage*current;
	 printf("total power = %.8f Watts\n",result);
	 return result;
}
///===============================================
/// Thermal Calculator functions for Electronic Components: 

/// Calculates and returns the temperature rise of a component as a function of
/// Power Dissipated, Junction to Ambient Thermal Resistance (R Theta JA, from datasheet),
/// and Ambient Temperature

float calc_temp_rise (float inVoltage, float outVoltage, float curr, float rtja, float amb) {
	float Vdrop = inVoltage - outVoltage;
	//~ printf("Voltage Drop = %.4f Volts\n",Vdrop);
	float pow_diss = Vdrop*curr;
	//~ printf("pow_diss = %.4f Watts\n",pow_diss);
	float temp_rise = (rtja*pow_diss) + amb;
	printf("rtja*pow_diss = %.4f Deg C\t\t",rtja*pow_diss);
	printf("amb = %.2f Deg C\n",amb);
	printf("Temperature Rise = %.4f Deg C\n",temp_rise);
	return temp_rise;
}

/// Determines whether the Operating Junction Temperature (TJ)
/// has been exceeded.
/// Generates a boolean output: 1 == true, 0 == false.

int junct_temp_exceeded(float tempRise, float opJunct_Temp) {
  int result; 
  result = (tempRise >= opJunct_Temp) ? true : false;
  printf("Operating Junction Temp (%0.2f) Exceeded = %d\n",opJunct_Temp, result);
  return result;
}

/// Calculates and returns the difference between the 
/// Operating Junction Temperature (TJ) and the Temperature Rise.

float temp_diff_OJT_TR(float tempRise, float opJunct_Temp) {
  float result; 
  result = opJunct_Temp - tempRise;
  printf("OJT (%0.2f) - Temp Rise (%0.4f) = %0.4f\n",opJunct_Temp,tempRise, result);
  return result;
}

///=============================================== 
/// DoseEdge LED array specific functions:

/// Calculates and returns the LUX output of a DoseEdge LED array 
/// as a function of th current limiting resistor value

void doseEdge_ResToLux(float resistor) {
	 const float Luxslope = 30;
	 const int maxLux = 1900, minRes = 10;
	 resistor = (resistor >= minRes) ? resistor : 10;
	 float result = (maxLux - (resistor * Luxslope) >= 0) ? maxLux - (resistor * Luxslope) : 0;
	 printf("LUX = %.2f\tlumen/m^2\t res = %.2f\n",result, resistor);
}

/// Calculates and returns the LUX output as a percetage of maximum 
/// of a DoseEdge LED array as a function of the current limiting resistor value

void doseEdge_ResToPercent(float resistor) {
	 const float PercentSlope = 1.875;
	 const float maxPercent = 118.75, minRes = 10;
	 resistor = (resistor >= minRes) ? resistor : 10;
	 float result = (maxPercent - (resistor * PercentSlope) >= 0) ? maxPercent - (resistor * PercentSlope) : 0;
	 printf("Percent of Max = %.4f\t for resistor value = %.2f\n",result, resistor);
}
/// Calculates and returns multiple useful values of a DoseEdge LED array 
/// for circuit analysis purposes

void doseEdge_ResToAll(float resistor) {
	 const float slope = 30;
	 const int maxLux = 1900, minRes = 10;
	 const float PercentSlope = 1.875;
	 const float maxPercent = 118.75;
	 resistor = (resistor >= minRes) ? resistor : 10;
	 float LUX = (maxLux - (resistor * slope) >= 0) ? maxLux - (resistor * slope) : 0;
	 float PERCENT = (maxPercent - (resistor * PercentSlope) >= 0) ? maxPercent - (resistor * PercentSlope) : 0;
	 printf("LUX = %.2f\tlumen/m^2\t\t%% of Max = %.6f\tres = %.2f Ohms\n",LUX, PERCENT, resistor);
	 //~ float PERCENT = (maxPercent - (resistor * PercentSlope) >= 0) ? maxPercent - (resistor * PercentSlope) : 0;
	 //~ printf("Percent of Max = %.4f\t for resistor value = %.2f\n",PERCENT, resistor);
	 //~ printf("\n");
} 
///===============================================

int main(int argc, char const *argv[]) {
	printf("\nRunning DoseEdge Circuit Model Tests\n\n");
	
	/** Uncomment this section for general range calculations**/	
	//~ float count = 0.0;
	//~ for (count = 1; count <= 63.0; count = count + 0.5) {
		//~ if (count<= 11.0) {
			//~ printf("100%% range\n");
			//~ doseEdge_ResToAll(count);
			//~ calc_var_resistance(calc_parallel_resistance(count, 19), 3.3);
			//~ branch_current(0.21, count);
			//~ float tc = total_current(0.21, count, 19);
			//~ float cpvi = calc_power_VI(0.21, tc);
			//~ // float inV, float outV, float curr, float rtja, float amb
			//~ float tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP1);
			//~ temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169); 
			//~ junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
		//~ printf("\n");
		//~ }
		//~ if (count>=22.0 && count<=25.0) {
			//~ printf("\n75%% range\n");
			//~ doseEdge_ResToAll(count);
			//~ calc_var_resistance(calc_parallel_resistance(count, 19), 3.3);
			//~ branch_current(0.21, count);
			//~ float tc = total_current(0.21, count, 19);
			//~ float cpvi = calc_power_VI(0.21, tc);
			//~ float tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP1);
			//~ temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169); 
			//~ junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
		//~ printf("\n");
		//~ }
		//~ if (count>= 35.0 && count<=37.0) {			
			//~ printf("\n50%% range\n");
			//~ doseEdge_ResToAll(count);
			//~ calc_var_resistance(calc_parallel_resistance(count, 19), 3.3);
			//~ branch_current(0.21, count);
			//~ float tc = total_current(0.21, count, 19);
			//~ float cpvi = calc_power_VI(0.21, tc);
			//~ float tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP1);
			//~ temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169); 
			//~ junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
		//~ printf("\n");
		//~ }
		//~ if (count>= 49.0 && count<=51.0) {
			//~ printf("\n25%% range\n");
			//~ doseEdge_ResToAll(count);
			//~ calc_var_resistance(calc_parallel_resistance(count, 19), 3.3);
			//~ branch_current(0.21, count);
			//~ float tc = total_current(0.21, count, 19);
			//~ float cpvi = calc_power_VI(0.21, tc);
			//~ float tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP1);
			//~ temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169); 
			//~ junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
		//~ printf("\n");
		//~ }
	//~ }
	
	/** Uncomment this section for specific calculations**/
		  float resVal = 3.3;
		  doseEdge_ResToAll(resVal);
		  calc_var_resistance(calc_parallel_resistance(resVal, 19), 3.3);
		  branch_current(0.21, resVal);
		  float tc = total_current(0.21, resVal, 19);
		  float cpvi = calc_power_VI(0.21, tc);
		  float tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP3);
		  temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169);
		  junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
		  printf("\n");
		  
		  resVal = 10.0;	
		  doseEdge_ResToAll(resVal);
		  calc_var_resistance(calc_parallel_resistance(resVal, 19), 3.3);
		  branch_current(0.21, resVal);
		  tc = total_current(0.21, resVal, 19);
		  cpvi = calc_power_VI(0.21, tc);
		  tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP3);
		  temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169); 	
		  junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
		  printf("\n");		
		  
		  resVal = 24.9;	
		  doseEdge_ResToAll(resVal);
		  calc_var_resistance(calc_parallel_resistance(resVal, 19), 3.3);
		  branch_current(0.21, resVal);
		  tc = total_current(0.21, resVal, 19);
		  cpvi = calc_power_VI(0.21, tc);
		  tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP1);
		  temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169); 
		  junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
	
	/** Uncomment this section for full range calculations
	printf("Fixed resistor = 10 Ohms\n\n");
	for (count = 10; count <= 63.0; count = count + 0.5) {
		doseEdge_ResToAll(count);
		calc_var_resistance(calc_parallel_resistance(count, 19), 3.3);
		branch_current(0.21, count);
		float tc = total_current(0.21, count, 19);
		float cpvi = calc_power_VI(0.21, tc);
		float tRise = calc_temp_rise(0.21,0,tc,R_THETA_JA_TPS61169,ROOM_TEMP3);
		temp_diff_OJT_TR(tRise, MAX_TEMP_TPS61169);
		junct_temp_exceeded(tRise, MAX_TEMP_TPS61169);
		printf("\n");
	} **/
}
