#pragma once

#include "Arduino.h"

double _data, angK, distK;

//Для тсопов
float d_alpha = 11.25;
double ball_angle = 0;
float ball_distance = 0;

int ir_addr[16][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 1, 0, 0},
  {0, 1, 0, 1},
  {0, 1, 1, 0},
  {0, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 1},
  {1, 0, 1, 0},
  {1, 0, 1, 1},
  {1, 1, 0, 0},
  {1, 1, 0, 1},
  {1, 1, 1, 0},
  {1, 1, 1, 1}
};

int ball_data[32];

//Дистанция до мяча при которой (или меньше) начинается объезд по окружности
const float min_dist_to_ball = 6;

//const int v_capture = 100;
//double angK;
//double distK;
//float _data;

//Для камеры
byte data_camera[5];
float yellow_local_angle, yellow_distance, blue_local_angle, blue_distance;
bool if_notice_yellow = false, if_notice_blue = false;
bool if_notice_our = false, if_notice_enemy = false;


//Для функции update
int yaww, robot_local_angle, errOld, robot_speed;

//Для датчиков мяча в ковше
int sen_leadle = 0;

//Для расчета координат
//int blue_goal_y, blue_goal_x = 120;
//int yellow_goal_y, yellow_goal_x = 120;
int y_robot, x_robot;
float o_a, e_a, x_o, y_o, x_e, y_e;

int our_goal_y = 10, our_goal_x = 75, enemy_goal_y = 220, enemy_goal_x = 75;
float our_local_angle, our_distance, enemy_local_angle, enemy_distance;
//float k;


//Для гироскопа
int null_angle = 0;
int gyro_angle = 0;


//Определение наших ворот, роли роботa
char our_goal = 'Y';
char robot_role = 'F';

//Поворот
const float kP = 1.8;
const float kD = 23;
const float kI = 0;
int err_old_angle;
float err_i_angle = 0;
int u_angle;

//Для моторов
bool stop_motor = true;

//Время
int32_t timer;
int32_t timer_kick;
int32_t timer_ball;

//Датчик мяча в ковше
bool if_ball_in_leadle = false;

//Вратарь
double angle_rout_goalkeeper;
double angle_goalkeeper;
float speed_goalkeeper;
const float Kp_line_goal = 3.5;
const float Kd_line_goal = 5;
const float Ki_line_goal = 0.002;
float err_old_y = 0;
int y_goalkepeer1 = 50;
int R = 65;
//int y_goalkepeer;
int x_goalkepeer;
const float Kp_line_goal_ball = 3.5;
const float Kd_line_goal_ball = 5;
const float Ki_line_goal_ball = 0.002;
float err_i_y = 0;
float err_i_x = 0;
float err_old_x = 0;
double angle_x;
double angle_y;
float u_y, u_x;
double angle_xy;
int err_x, err_y;
const int x2 = 88;
const int x1 = 150;
const int y1 = 45;
double xy;
int x_robot_point1;
double angle2_robot_point;

double x_soft = 0, y_soft = 0;
double k_ball = 0.2;
uint32_t dash_clowns = 0;

double k_coordinates = 0.9;
double x_soft_c = 0, y_soft_c = 0;

//Нападающий
double angle_forward;
int speed_forward;

//Ауты нападающего
const int out1_x = 120, out1_y = 160, out2_x = 5 , out3_y = 60; //основные границы
const int out1_x2 = 110, out1_y2 = 170, out2_x2 = 15, out3_y2 = 70;  //границы замедления

//Ауты вратаря
const int out1_y_g = 20, out1_x_g = 140, out2_x_g = 10; //основные границы
const int out1_y2_g = 25, out1_x2_g = 135, out2_x2_g = 15; //границы замедления