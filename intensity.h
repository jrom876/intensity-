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

#endif
