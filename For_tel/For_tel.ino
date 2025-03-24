

#define M1_P1 A1
#define M1_P2 A2
#define M1_PWM 9

#define M2_P1 A0
#define M2_P2 A3
#define M2_PWM 8

#define M3_P1 32
#define M3_P2 40
#define M3_PWM 4

#define M4_P1 36
#define M4_P2 46
#define M4_PWM 6

#define ADDR_P1 50
#define ADDR_P2 51
#define ADDR_P3 52
#define ADDR_P4 53

#define BALL_SEN_SIGNAL_1 A8
#define BALL_SEN_SIGNAL_2 A9


int yaww, robot_local_angle, errOld, robot_speed;
float kP = -3.5;
float kD = -2;
float ds = 0.1;
float x1 = 0, y1 = 0, err_angle, speed_new ;
double angle_new;
uint32_t timer;
int k = -600;
byte data_camera[5];
int yellow_local_angle, yellow_distance, blue_local_angle, blue_distance;
int y_robot, x_robot;
const int blue_goal_y, blue_goal_x;
const int yellow_goal_y, yellow_goal_x;
const int min_dist_to_ball;

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


struct point
{
  int x;
  int y;
  int angle;
};

void setup()
{
  pinMode(M1_P1, OUTPUT);
  pinMode(M1_P2, OUTPUT);

  pinMode(M2_P1, OUTPUT);
  pinMode(M2_P2, OUTPUT);

  pinMode(M3_P1, OUTPUT);
  pinMode(M3_P2, OUTPUT);

  pinMode(M4_P1, OUTPUT);
  pinMode(M4_P2, OUTPUT);

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial3.begin(9600);
  uint32_t timer = millis();
  //soft_move_angle_speed(0, 10);
  Serial.print("abv");

  pinMode( ADDR_P1, OUTPUT);
  pinMode( ADDR_P2, OUTPUT);
  pinMode( ADDR_P3, OUTPUT);
  pinMode( ADDR_P4, OUTPUT);
  pinMode( BALL_SEN_SIGNAL_1, INPUT_PULLUP);
  pinMode( BALL_SEN_SIGNAL_2, INPUT_PULLUP);
}

void loop()
{
  detect_ball();
  Serial.println(" ");
  for (int i = 0; i < 32; i++)
  {
    Serial.print(ball_data[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  Serial.print(ball_distance);
  Serial.print(" ");
  Serial.println(ball_angle);
}
