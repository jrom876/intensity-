// intensity.h //
#ifndef INTENSITY_H
#define INTENSITY_H

/**
	Copyright (C) 2023 
	Jacob Romero, Creative Engineering Solutions, LLC
	cesllc876@gmail.com
**/

double calc_intensity(int c, double ari, double eps0, double efield);
double calc_irradiance(int c, double mu0, double efield);
double calc_Electric_Field(double num_charges, double charge, double radius);
double calc_Lux(double received_illuminance, double reflectance);

//~ float calc_parallel_resistance(float resistor_value, int num_branches);
//~ float calc_power(float voltage, float current);
//~ //float calc_power(float voltage, float resistance);
//~ float total_current(float voltage, float resistance, int num_branches);
//~ float branch_current(float voltage, float resistance);

//~ void doseEdge_ResToLux(float resistor);
//~ void doseEdge_ResToPercent(float resistor);
//~ void doseEdge_ResToAll(float resistor);

#endif
