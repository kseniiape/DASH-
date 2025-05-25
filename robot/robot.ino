
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

#define BALL_SEN_SIGNAL_1 26
#define BALL_SEN_SIGNAL_2 31

#define SEN_LEADLE A1 //A2 - 2   A1 - 1

#define BUT_DOWN 38
#define BUT_UP 36
#define BUT_ENTER 40

#define LED_CALIBRATION 42
#define LED_YELLOW 48
#define LED_BLUE 44

#define KICK_PIN1 14

#define CHARGE_PIN A0
#define CHARGE_LED_PIN 46

#define ec 2.7182

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
const int min_dist_to_ball = 6;

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

int our_goal_y = 10, our_goal_x = 85, enemy_goal_y = 210, enemy_goal_x = 85;
float our_local_angle, our_distance, enemy_local_angle, enemy_distance;
//float k;


//Для гироскопа
int null_angle = 0;
int gyro_angle = 0;


//Определение наших ворот, роли роботa
char our_goal = 'Y';
char robot_role = 'F';

//Поворот
const float kP = 1.1;
const float kD = 15;
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

double k_coordinates = 0.2;
double x_soft_c = 0, y_soft_c = 0;

//Нападающий
double angle_forward;
int speed_forward;


//Ауты
int out1_x, out2_x, out3_x, out4_x, out2_y, out1_y, out3_y, out4_y;
int out1_x2, out2_x2, out3_x2, out4_x2, out2_y2, out1_y2, out3_y2, out4_y2;
int out1_y_g, out1_x_g, out2_x_g, out1_y2_g, out1_x2_g, out2_x2_g;


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
  pinMode(BUT_UP, INPUT);
  pinMode(BUT_ENTER, INPUT);

  pinMode(LED_CALIBRATION, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(KICK_PIN1, OUTPUT);

  pinMode(CHARGE_PIN, INPUT);
  pinMode(CHARGE_LED_PIN, OUTPUT);

  timer = millis();
  timer_kick = millis();
  timer_ball = millis();


  out2_y = 150;//
  out1_y = 150;//
  out3_y = 80;//
  out4_y = 80;//
  out1_x = 120;//
  out4_x = 120;//
  out2_x = 30;//
  out3_x = 30;//

  out2_y2 = 150;//
  out1_y2 = 150;//
  out3_y2 = 85;//
  out4_y2 = 85;//
  out1_x2 = 110;//
  out4_x2 = 110;//
  out2_x2 = 45;//
  out3_x2 = 45;/////

  out1_y_g = 50;
  out1_x_g = 130;
  out2_x_g = 50;
  out1_y2_g = 45;
  out1_x2_g = 125;
  out2_x2_g = 55;
  

  //calibration_imu();
}

void loop()
{
  //Serial.println(abs(lead_to_degree_borders(ball_angle + robot_local_angle)));
  robot_update();
  coordinates_robot();
  //Serial.println(x_robot);
  /*Serial.print(enemy_distance);
    Serial.print(" ");
    Serial.print(our_distance);
    Serial.print(" ");
    Serial.print(x_robot);
    Serial.print(" ");
    Serial.print(y_robot);
    Serial.print(" ");
    Serial.print(if_notice_our);
    Serial.print(" ");
    Serial.print(if_notice_enemy);
    Serial.print(" ");
    //Serial.print(k);
    Serial.println(" ");*/
  /*Serial.print(x_robot);
    Serial.print(" ");
    Serial.print(y_robot);
    Serial.println(" ");*/
  /*Serial.print(x_robot);
    Serial.print(" ");
    Serial.print(y_robot);
    Serial.print(" ");
    Serial.print(ball_distance);
    Serial.print(" ");
    Serial.println(angle_forward);*/
  //Serial.println(sign(2));
  //Serial.println(analogRead(SEN_LEADLE));
  //Serial.println(x_robot);
  //Serial.println(ball_angle);
  if (stop_motor == false)
  {
   if (robot_role == 'G') goalkeeper();
    else forward();
    //move_angle_speed(0, 0, 0);
    //forward();
  }
  else stop_m();
  /*Serial.print(enemy_distance);
    Serial.print(" ");
    Serial.print(our_distance);
    Serial.print(" ");
    Serial.print(x_robot);
    Serial.print(" ");
    Serial.print(y_robot);
    Serial.println(" ");*/

 /*Serial.println(" ");
    for (int i = 0; i < 32; i++)
    {
    Serial.print(ball_data[i]);
    Serial.print(" ");
    }
    Serial.println(" ");
    Serial.print(ball_distance);
    Serial.print(" ");
    Serial.println(ball_angle);*/


}
