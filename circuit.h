// intensity.h //
#ifndef CIRCUIT_H
#define CIRCUIT_H

/**
	Copyright (C) 2023 
	Jacob Romero, ERI Group, LLC
	jromero@erigroup.com
**/

float calc_parallel_resistance(float resistor_value, int num_branches);
float calc_total_power(float voltage, float current, int num_branches);
float calc_var_resistance(float desired_res, float fixed_res);
float calc_output_resistance(float fixed_res, float var_res);
float calc_power_VI(float voltage, float current);
//float calc_power_VR(float voltage, float resistance);
float branch_current(float voltage, float resistance);
float total_current(float voltage, float resistance, int num_branches);

float calc_temp_rise (float inVoltage, float outVoltage, float curr, float rtja, float amb);
int junct_temp_exceeded (float tempRise, float opJunct_Temp);

void doseEdge_ResToLux(float resistor);
void doseEdge_ResToPercent(float resistor);
void doseEdge_ResToAll(float resistor);

#endif
