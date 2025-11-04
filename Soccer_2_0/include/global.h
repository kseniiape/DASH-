#pragma once
#include "Arduino.h"

const float k_coordinates = 0.8;
const int speed_constrain = 110;
const float kP_turn_angle = 1.8;
const float kD_turn_angle = 5;
bool if_ball_in_leadle2 = 0;
bool if_ball_in_leadle1 = 0;
bool stop_motors = true;

//Дистанция до мяча при которой (или меньше) начинается объезд по окружности
const float min_dist_to_ball = 4.5;

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
    static inline double angle = 0;
    static inline float distance = 0;
    static inline double null_angle = 6;
    
};

struct robot
{
    static inline int role = ROLE;
    static inline int local_angle = 0;
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
      static inline int x = -55;
      static inline int y = 50;
    };

    struct left_far_point
    {
      static inline int x = 55;
      static inline int y = 155;
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
        static inline constexpr int y = 0;
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
    static inline int32_t kick, leadle2, leadle1, ball_capture, ball_state, forward_state ,test, d_capture;
};

struct goalkeeper
{
  static inline const int R = 60;
  static inline int constrain_y = 200;
  static inline int constrain_x = 200;
  static inline double angle = 0;
  static inline int speed = 0;
  struct outs
    {
      static inline int dist_slowdown = 5;

    struct right_point
    {
      static inline int x = -55;
      static inline int y = 10;
    };

    struct left_point
    {
      static inline int x = 55;
      static inline int y = goalkeeper::outs::right_point::y;
    };
  };

  struct line_ball_goal
  {
    static inline int major_semi_axis = 62;
    static inline int minor_axis = 62;
    static inline int y_center = goal::our::y;
    static inline int x_center = goal::our::x;
  };

  struct k
  {
    struct y
    {
      static inline float kP = 3.2;
      static inline float kD = 10;
      static inline float kI = 0.0015;
    };
    
    struct x
    {
      static inline float kP = 3.7;
      static inline float kD = 10;
      static inline float kI = 0.002;
    };

  };
  
};






