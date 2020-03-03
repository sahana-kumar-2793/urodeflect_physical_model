#include "sensor.h"
#include "Arduino.h"
#include "HX711.h" 
#include "config.h"
// Please refer to: https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide


template <class C>
sensor<C>::sensor(){};

template <class C>
void sensor<C>::setup(int pin)
{
  input_pin = pin;
  pinMode(input_pin, INPUT);
}

template <class C>
void sensor<C>::raw_measure()
// to be called at a rate higher than the PID update steps, 
// measurements stored in an array, with average calculated for each PID update step
{
  raw_val_sum += analogRead(input_pin);
  ++ cur_raw_count;
}

template <class C>
void sensor<C>::measure()
// calculates the average of measurements instead of making real measurements
{
  cur_val = (float)raw_val_sum / (float)cur_raw_count; // cur_val serves as an intermediate step, can be used for further processing.
  cur_out = cur_val; 
  cur_raw_count = 0;  
  raw_val_sum = 0;
}

template <class C>
void sensor<C>::update_value(){
  measure();
}

template <class C>
float sensor<C>::get_value()
// Your typical and lonely getter method
{
  return cur_out;
}

template <class C>
float* sensor<C>::get_p_value()
{
  return & cur_out;
}

load_cell::load_cell() : sensor<float>(){}

void load_cell::setup(int n_DOUT, int n_CLK, int n_coef)
{
  CLK = n_CLK;
  input_pin = n_DOUT;
  coef = n_coef;
  pinMode(CLK, INPUT);
  pinMode(input_pin, INPUT);
  scale.begin(input_pin, CLK);
  scale.set_scale(coef);
  
  scale.tare();
}

void load_cell::raw_measure(){
  if(1){
    raw_val_sum += scale.get_units(5);
    ++ cur_raw_count;  
  }
}

void load_cell::update_value(){
  measure();
}



//potentiometer::potentiometer() : sensor<float>(){]
//void potentiometer:: setup(int pin, int pulse_per_rotation) 
//{
//  input_pin = pin;
//  pinMode(pin, INPUT);
//  
//}

// Sort out the template issues:
template class sensor<int>;
template class sensor<float>;
