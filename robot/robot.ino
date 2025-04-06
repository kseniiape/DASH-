#define M1_P1 2
#define M1_P2 3

#define M2_P1 5
#define M2_P2 6

#define M3_P1 7
#define M3_P2 8

#define M4_P1 10
#define M4_P2 9

#define ADDR_P1 23
#define ADDR_P2 25
#define ADDR_P3 27
#define ADDR_P4 29

#define BALL_SEN_SIGNAL_1 31
#define BALL_SEN_SIGNAL_2 26

#define SEN_LEADLE A2

#define BUT_DOWN 38

//Для тсопов
float d_alpha = 11.25;
int ball_angle = 0, ball_distance = 0;

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
const int min_dist_to_ball = 5;
const int v_capture = 170;

//Для камеры
byte data_camera[5];
int yellow_local_angle, yellow_distance, blue_local_angle, blue_distance;

//Для функции update
int yaww, robot_local_angle, errOld, robot_speed;

//Для датчиков мяча в ковше 
int sen_leadle = 0;

//Для расчета координат
const int blue_goal_y, blue_goal_x;
const int yellow_goal_y, yellow_goal_x;
int y_robot, x_robot;

//Для гироскопа
int null_angle = 0;
int gyro_angle = 0;

//Определение наших ворот и чужих (1 - желтые)
int our_goal = 1;


void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);

  pinMode(M1_P1, OUTPUT);
  pinMode(M1_P2, OUTPUT);

  pinMode(M2_P1, OUTPUT);
  pinMode(M2_P2, OUTPUT);

  pinMode(M3_P1, OUTPUT);
  pinMode(M3_P2, OUTPUT);

  pinMode(M4_P1, OUTPUT);
  pinMode(M4_P2, OUTPUT);

  pinMode( ADDR_P1, OUTPUT);
  pinMode( ADDR_P2, OUTPUT);
  pinMode( ADDR_P3, OUTPUT);
  pinMode( ADDR_P4, OUTPUT);
  pinMode( BALL_SEN_SIGNAL_1, INPUT_PULLUP);
  pinMode( BALL_SEN_SIGNAL_2, INPUT_PULLUP);

  pinMode(SEN_LEADLE, INPUT);
  
  pinMode(BUT_DOWN, INPUT);
}

void loop()
{
  reset_imu();
  gyro_angle = gyro_data();
  robot_local_angle = gyro_angle - null_angle;
  detect_ball();
  camera_data();
  ball_capture();
  if (our_goal == 1)
  {
    if (abs(ball_angle) < 30)
    {
      if (abs(blue_local_angle + robot_local_angle) < 30) move_angle_speed(0, v_capture);
    }
  }
  else 
  {
    if ((abs(ball_angle) < 30) )
    {
      if (abs(yellow_local_angle + robot_local_angle) < 30) move_angle_speed(0, v_capture);
    }
  }
}
