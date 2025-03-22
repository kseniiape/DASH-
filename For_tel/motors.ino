void motor1 (int16_t power) {
  power = constrain (power, -255, 255);
  if (power < 0) {
    digitalWrite (M1_P1, HIGH);
    digitalWrite (M1_P2, LOW);
    analogWrite (M1_PWM, abs(power));
  }
  else {
    digitalWrite (M1_P1, LOW);
    digitalWrite (M1_P2, HIGH);
    analogWrite (M1_PWM, power);
  }
}

void motor2 (int16_t power) {
  power = constrain (power, -255, 255);
  if (power < 0) {
    digitalWrite (M2_P1, HIGH);
    digitalWrite (M2_P2, LOW);
    analogWrite (M2_PWM, abs(power));
  }
  else {
    digitalWrite (M2_P1, LOW);
    digitalWrite (M2_P2, HIGH);
    analogWrite (M2_PWM, power);
  }
}

void motor3 (int16_t power) {
  power = constrain (power, -255, 255);
  if (power < 0) {
    digitalWrite (M3_P1, LOW);
    digitalWrite (M3_P2, HIGH);
    analogWrite (M3_PWM, abs(power));
  }
  else {
    digitalWrite (M3_P1, HIGH);
    digitalWrite (M3_P2, LOW);
    analogWrite (M3_PWM, power);
  }
}

void motor4 (int16_t power) {
  power = constrain (power, -255, 255);
  if (power < 0) {
    digitalWrite (M4_P1, HIGH);
    digitalWrite (M4_P2, LOW);
    analogWrite (M4_PWM, abs(power));
  }
  else {
    digitalWrite (M4_P1, LOW);
    digitalWrite (M4_P2, HIGH);
    analogWrite (M4_PWM, power);
  }
}

void stop_m () {
  digitalWrite (M1_P1, HIGH);
  digitalWrite (M1_P2, HIGH);

  digitalWrite (M2_P1, HIGH);
  digitalWrite (M2_P2, HIGH);

  digitalWrite (M3_P1, HIGH);
  digitalWrite (M3_P2, HIGH);

  digitalWrite (M4_P1, HIGH);
  digitalWrite (M4_P2, HIGH);
}
