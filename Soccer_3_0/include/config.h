#pragma once
#include "Arduino.h"
#include "Servo.h"


#define M1_P1 6
#define M1_P2 7


#define M2_P1 12 
#define M2_P2 5  

#define M3_P1 10 
#define M3_P2 11 

#define M4_P1 8
#define M4_P2 9

#define ADDR_P1 24
#define ADDR_P2 25
#define ADDR_P3 26
#define ADDR_P4 27


#define BALL_SEN_SIGNAL_1 28
#define BALL_SEN_SIGNAL_2 29

#define SEN_LEADLE1 A1
#define SEN_LEADLE2 A2


#define BUT_DOWN 47  
#define BUT_UP 48    
#define BUT_ENTER 49 

/////см физ плата
#define LED_CALIBRATION 41
#define LED_YELLOW 42     
#define LED_BLUE 43      
#define LED_EXTRA 45       


#define KICK_PIN1 2

#define DRIBLER_PIN 46


#define CHARGE_PIN A6 

/////см физ плата
#define CHARGE_LED_PIN 41

#define ec 2.7182
#define ROLE 1 // 1 - f, 2 - g

Servo esc;