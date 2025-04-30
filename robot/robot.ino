

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
//const int v_capture = 100;

//Для камеры
byte data_camera[5];
int yellow_local_angle, yellow_distance, blue_local_angle, blue_distance;
bool if_notice_yellow = false, if_notice_blue = false;
bool if_notice_our = false, if_notice_enemy = false;


//Для функции update
int yaww, robot_local_angle, errOld, robot_speed;

//Для датчиков мяча в ковше
int sen_leadle = 0;

//Для расчета координат
int blue_goal_y, blue_goal_x = 38;
int yellow_goal_y, yellow_goal_x = 38;
int y_robot, x_robot;
int o_a, e_a, x_o, y_o, x_e, y_e;

int our_goal_y = 5, our_goal_x = 38, enemy_goal_y = 215, enemy_goal_x = 38;
int our_local_angle, our_distance, enemy_local_angle, enemy_distance;


//Для гироскопа
int null_angle = 0;
int gyro_angle = 0;


//Определение наших ворот, роли роботa
char our_goal = 'Y';
char robot_role = 'F';

//Поворот
const float kP = 0.8;
int u_angle;

//Для моторов
bool stop_motor = true;

//Время
int8_t timer;
int8_t timer_kick;

//Датчик мяча в ковше
bool if_ball_in_leadle = false;


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

  timer = millis();
  timer_kick = millis();


  //calibration_imu();
}

void loop()
{

  robot_update();
  //coordinates_robot();
  Serial.println(analogRead(SEN_LEADLE));
  if (stop_motor == false)
  {
    ball_capture(150, 0);
    //move_angle_speed (0, 180, 0);
  }
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
