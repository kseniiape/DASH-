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

//Все для тсопов
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

void setup()
{
  Serial.begin(115200);

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
