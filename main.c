//	Package:	intensity
//	File:		main.c 
//	Purpose:	Calculate light intensity
//	Author:		jrom876

/**
	Copyright (C) 2019, 2021 
	Jacob Romero, Creative Engineering Solutions, LLC
	cesllc876@gmail.com

	This program is free software; you can redistribute it
	and/or modify it under the terms of the GNU General Public 
	License as published by the Free Software Foundation, version 2.

	This program is distributed in the hope that it will be
	useful, but WITHOUT ANY WARRANTY; without even the implied 
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	
	See the GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public
	License along with this program; if not, write to:
	The Free Software Foundation, Inc.
	59 Temple Place, Suite 330
	Boston, MA 02111-1307 USA
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
#include "circuit.h"

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

void getUserInput(){
	int exitFlag = 0;	
	int ch;
	float res, fixed_res, var_res; 
	printf("Please choose from the following: \n");
	printf("1 to enter resistor value and get LUX values\n");
	printf("2 to enter resistor value and get percentage\n");
	printf("3 to enter resistor value and get LUX and percentage\n");
	printf("4 to enter resistor values and get resultant parallel resistance\n");
	printf("10 for quit\n");
	printf("Enter any other values to exit\n");
	scanf(" %i", &ch);
	
	switch (ch) {
		case 1:	
			printf("Enter Resistor value\n");
			scanf(" %f", &res);
			//~ DE_ResToLux(res);
			break;
		case 2:
			printf("Enter Resistor value\n");
			scanf(" %f", &res);
			//~ DE_ResToPercent(res);
			break;
		case 3:
			printf("Enter Resistor value\n");
			scanf(" %f", &res);
			//~ DE_ResToAll(res);
			break;
		case 4:
			printf("Enter Fixed Resistor value\n");
			scanf(" %f", &fixed_res);
			printf("Enter Variable Resistor value\n");
			scanf(" %f", &var_res);
			
			//~ DE_ResToAll(19*calc_output_resistance(fixed_res, var_res));
			/////~ calc_parallel_resistance(count, 19);
			///calc_var_resistance(calc_parallel_resistance(count, 19), fixed_res);
			//~ branch_current(0.21, count);
			//~ float tc = total_current(0.21, count, 19);
			//~ calc_power_VI(0.21, tc);
			
			//~ calc_output_resistance(fixed_res, var_res);
			break;
		case 10:
			printf("Quitting\n");
			exitFlag = 1;
			break;
		default:
			printf("Now exiting.\n");
			exit(0);
			exitFlag = 1;
			break;
	}
	if(0 != exitFlag) exit(0);
	//~ else getUserInput();
}

int main(int argc, char const *argv[]) {
  printf("\nRunning main\n");
  getUserInput();
  //~ double ari = AIR_REFRACTIVE_INDEX;
  //~ double e0 = EPSILON_0;
  //double radiusHelium = RADIUS_HELIUM_ATOM; // distance between nucleus and electron of a Helium atom
  //~ double E = calc_Electric_Field(1, ELECTRON_CHARGE, RADIUS_HELIUM_ATOM);
 //~ calc_Electric_Field(1, ELECTRON_CHARGE, RADIUS_HELIUM_ATOM);
  //double E = (1/((4*PI)*(e0))) * ((2*(ELECTRON_CHARGE))/(radiusHelium*radiusHelium)); // in Newtons per Coulomb * rhat
  //~ double intensity = calc_intensity(LIGHT_SPEED, ari, e0, E);
  
  //~ calc_intensity(LIGHT_SPEED, AIR_REFRACTIVE_INDEX, EPSILON_0, calc_Electric_Field(1, ELECTRON_CHARGE, RADIUS_HELIUM_ATOM));
  //~ calc_parallel_resistance(3.3,19);
  //~ calc_parallel_resistance(calc_parallel_resistance(2.0,3),19);
  
  //~ printf("Electric Field = %.12lf\t Newtons per Coulomb\n", E);
  //~ printf("intensity = %.2lf\n", intensity);
  printf("done\n\n");
  return 0;
}
