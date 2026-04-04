#pragma once
#include "Arduino.h"

const float k_coordinates = 0.8;
const int speed_constrain = 120;
const float kP_turn_angle = 2.3;
const float kD_turn_angle = 0;
const float kI_turn_angle = 0.005;
bool if_ball_in_leadle2 = 0;
bool if_ball_in_leadle1 = 0;
bool stop_motors = true;
double x_soft= 0, y_soft = 0, k_ball = 0.2;

//Дистанция до мяча при которой (или меньше) начинается объезд по окружности
const float min_dist_to_ball = 7;

bool dribler = 0;
struct tssop
{
    const static inline int ir_addr[16][4] = {
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

    const static inline float delta_angle = 11.25;
    
};

struct ball
{
  static inline double prev_angle = 0;
  static inline float distance = 0;
    static inline float distance_tssop = 0;
  static inline float distance_camera = 0;
    static inline double angle = 0;
    static inline double angle_tssop = 0;
    static inline double angle_camera = 0;
    static inline float prev_distance = 0;
    #if ROLE == 1
    static inline double null_angle = 8;
    #else
    static inline double null_angle = 8;
    #endif
    
};

struct robot
{
    static inline int role = ROLE;
    static inline double local_angle = 0;
    static inline int x = 0, y = 0;

};

struct forward
{
  static inline double angle = 0;
  static inline int speed = 0;
  struct outs
  {
    static inline int dist_slowdown = 10;

    struct right_near_point
    {
      static inline int x = -40;
      static inline int y = 70;
    };

    struct left_far_point
    {
      static inline int x = 40;
      static inline int y = 150;
    };
  };

  
    

};

struct gyro
{
    static inline double angle = 0;
    static inline double null_angle = 0;
};


struct goal
{
    static inline char our_color = 'Y';
    struct yellow
    {
        static inline double local_angle = 0;
        static inline float distance = 0;
    };

    struct blue
    {
        static inline double local_angle = 0;
        static inline float distance = 0;
    };

    struct our
    {
        static inline bool if_notice = 0;
        static inline float distance = 0;
        static inline double local_angle = 0;
        static inline constexpr int y = 5;
        static inline constexpr int x = 0;
    };

    struct enemy
    {
        static inline bool if_notice = 0;
        static inline const int y = 220;
        static inline const int x = 0;
        static inline float distance = 0;
        static inline double local_angle = 0;
    };
    
};

struct timers
{
    static inline int32_t kick, leadle2, leadle1, ball_capture, ball_state, forward_state ,test, d_capture, state_forward1;
    static inline int32_t state_forward2;
};

struct goalkeeper
{
  static inline const int R = 45;
  static inline int constrain_y = 210;
  static inline int constrain_x = 210;
  
  static inline int constrain_y1 = 100;
  static inline int constrain_x1 = 100;
  static inline double angle = 0;
  static inline int speed = 0;
  struct outs
    {
      static inline int dist_slowdown = 7;

    struct right_point
    {
      static inline int x = -45;
      static inline int y = 30;
    };

    struct left_point
    {
      static inline int x = 45;
      static inline int y = goalkeeper::outs::right_point::y;
    };
  };

  struct line_ball_goal
  {
    static inline int major_semi_axis = 50;
    static inline int minor_axis = 45;
    static inline int y_center = goal::our::y;
    static inline int x_center = goal::our::x;
  };

  struct k
  {
    struct y
    {
      static inline float kP = 2.8;
      static inline float kD = 0;
      static inline float kI = 0.01;
    };
    
    struct x
    {
      static inline float kP = 2.5;
      static inline float kD = 0;
      static inline float kI = 0.005;
    };

  };
  
};






