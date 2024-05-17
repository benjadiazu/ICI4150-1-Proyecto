#include<SoftwareSerial.h>


#define TRIGGER_PIN 12
#define ECHO_PIN 11

#define INT1 5 
#define INT2 6
#define INT3 9
#define INT4 10

int speedMotor = 255;

long distance;

const float setPoint = 100; // Set point for speed control, using ultrasonic sensor
float time_PID = 0;
float integral = 0;
float time_prev = -1e-6;
float e_prev = 0;
float curSpeed = 0;
const float deltat = 0.1;



class RobotMovements {
public:
    RobotMovements(); // Constructor
    void moveForward(int velocity);
    void moveBackward(int velocity);
    void moveRight(int velocity);
    void moveLeft(int velocity);
    void stop();
protected:
    void motorA(char d, int velocity);
    void motorB(char d, int velocity);
};

RobotMovements::RobotMovements() {
    // Constructor, si necesitas inicializar algo
}

void RobotMovements::moveForward(int velocity) {
    this->motorA('A',velocity);
    this->motorB('R',velocity);
}

void RobotMovements::moveBackward(int velocity) {
    this->motorA('R', velocity);
    this->motorB('A', velocity);
}

void RobotMovements::moveRight(int velocity) {
    this->motorA('A', velocity);
    this->motorB('R', 0);
}

void RobotMovements::moveLeft(int velocity) {
    this->motorA('A', 0);
    this->motorB('R', velocity);
}

void RobotMovements::stop() {
    this->motorA('A',0);
    this->motorB('R',0);
}

void RobotMovements::motorA(char d, int velocity){
  if(d =='A'){
    analogWrite(INT1,LOW);
    analogWrite(INT2,velocity); 
  }else if (d =='R'){
    analogWrite(INT1,velocity);
    analogWrite(INT2,LOW); 
  }else{
    digitalWrite(INT1,LOW);
    digitalWrite(INT2,LOW); 
  }
}

void RobotMovements::motorB(char d, int velocity){
  if(d =='A'){
    analogWrite(INT3,LOW);
    analogWrite(INT4,velocity); 
  }else if (d =='R'){
    analogWrite(INT3,velocity);
    analogWrite(INT4,LOW); 
  }else{
    analogWrite(INT3,LOW);
    analogWrite(INT4,LOW); 
  }
}


SoftwareSerial BT(11,10);
RobotMovements robot;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  //Serial.println("Listo");
  //miBT.begin(38400);

  pinMode(INT1,OUTPUT);
  pinMode(INT2,OUTPUT);
  pinMode(INT3,OUTPUT);
  pinMode(INT4,OUTPUT);
}

void loop() {

  const int n = 50;
  for (int i = 1; i < n; i++) {

      distance = Ultrasonido(TRIGGER_PIN, ECHO_PIN);

      time_PID = i * deltat;
      float pid_out = PID(0.6, 0.2, 0.1, setPoint, distance);
      time_prev = time_PID;
      Serial.println("------------");
      Serial.println(distance);
      Serial.println(pid_out);
      Serial.println("------------");

      if (pid_out > 300) {
          Serial.println("Avanza muy rapido");
          robot.moveForward(200);
      }
      if (50 < pid_out && pid_out < 200) {
          Serial.println("Avanza lento");
          robot.moveForward(50);
      }
      if (pid_out < 30) {
          Serial.println("Se para");
          robot.stop();
      }

      delay(0.1); // Delay in milliseconds
    }

  /*
  if(distancia <= 1000){
    if(distancia<=15){
      motorA('A',0);
      motorB('R',0);
    }else{
      motorA('A',128);
      motorB('R',128);
    }
    //Serial.println((distancia));
  } 
  
  */
  delay(0.1);
}

void write_in_bluetooh(){
  if(BT.available())
    Serial.write(BT.read());

  if(Serial.available())
    BT.write(Serial.read());
}
//11 echo
//12 trigger
long Ultrasonido(int trigger, int eco){ 
  long duration; //timepo que demora en llegar el eco
  long distance; //distancia en centimetros
  
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration = pulseIn(eco, HIGH); //obtenemos el ancho del pulso
  distance = (duration*.0343)/2; 
  return distance;
}


void motorA(char d, int velocity)
{
  if(d =='A'){
    analogWrite(INT1,LOW);
    analogWrite(INT2,velocity); 
  }else if (d =='R'){
    analogWrite(INT1,velocity);
    analogWrite(INT2,LOW); 
  }else{
    digitalWrite(INT1,LOW);
    digitalWrite(INT2,LOW); 
  }
}

void motorB(char d,int velocity)
{
  if(d =='A'){
    analogWrite(INT3,LOW);
    analogWrite(INT4,velocity); 
  }else if (d =='R'){
    analogWrite(INT3,velocity);
    analogWrite(INT4,LOW); 
  }else{
    analogWrite(INT3,LOW);
    analogWrite(INT4,LOW); 
  }
}

float PID(float Kp, float Ki, float Kd, int setpoint, int measurement) {
    // Value of offset - when the error is equal zero
    float offset = 320;

    // PID calculations
    float e = setpoint - measurement;

    float P = Kp * e;
    integral = integral + Ki * e * (time_PID - time_prev);
    float D = Kd * (e - e_prev) / (time_PID - time_prev);
    // calculate manipulated variable - MV
    float MV = offset + P + integral + D;

    // update stored data for next iteration
    e_prev = e;
    time_prev = time_PID;
    return MV;
}

