double sensorPrev;
double sensorCurr;
bool motorOn;
int buttonState = 0;
double getDegrees(double prev, double curr) {
  double grade = curr - prev;
  grade = grade * 180 / 0.1;
  return grade;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  analogWrite(9, 0);
  analogWrite(10, 0);
  Serial.begin(9600);
  motorOn = false;
  sensorPrev = (double) analogRead(A1) * 5 / 1023;
  delay(100);
  sensorCurr = (double) analogRead(A1) * 5 / 1023;
  delay(100);
}

void motor(float grade) {
  if ((grade > 10 || grade < -10) && motorOn) {
    if (grade >= 0) {
      analogWrite(9, 0);
      analogWrite(10, 255);
      Serial.println(grade * 10);
      delay(grade / 2.5);
    }
    else {
      analogWrite(9, 255);
      analogWrite(10, 0);
      Serial.println(grade * 10);
      delay(-1 * grade / 2.5);
    }
  }
  Serial.println("este in functia motor");
  analogWrite(9, 0);
  analogWrite(10, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorPrev = sensorCurr;
  double sum = 0;
  for (int i = 0; i < 30; i++) {
    sum += (double) analogRead(A1) * 5 / 1023;
    delay(20);
  }
  sensorCurr = sum / 30;
  buttonState = digitalRead(2);
  if (buttonState == HIGH) {
    Serial.println("se schimba");
    motorOn = !motorOn;
  }
  motor(getDegrees(sensorPrev, sensorCurr));
  Serial.println(motorOn);
  Serial.println(sensorPrev);
  Serial.println(sensorCurr);
  Serial.println(getDegrees(sensorPrev, sensorCurr));
  Serial.println();
  Serial.println();
  Serial.println();
}
