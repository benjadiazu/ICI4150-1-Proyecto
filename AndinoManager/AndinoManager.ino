#include<SoftwareSerial.h>
#include<Servo.h>


#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define SIGNAL 2

#define INT1 5 
#define INT2 6
#define INT3 9
#define INT4 10

int speedMotor = 255;

long distance;
int intensidad;

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
    analogWrite(INT1,LOW);
    analogWrite(INT2,velocity);
    
    analogWrite(INT3,velocity);
    analogWrite(INT4,LOW);
    //this->motorA('A',0);
    //this->motorB('R',0);
}

void RobotMovements::moveBackward(int velocity) {
    analogWrite(INT1,velocity);
    analogWrite(INT2,LOW);
    
    analogWrite(INT3,LOW);
    analogWrite(INT4,velocity);
    //this->motorA('R', velocity);
    //this->motorB('A', velocity);
}

void RobotMovements::moveRight(int velocity) {
    analogWrite(INT1,LOW);
    analogWrite(INT2,velocity);
    
    analogWrite(INT3,LOW);
    analogWrite(INT4,LOW);
    //this->motorA('R', velocity);
    //this->motorB('A', 0);
}

void RobotMovements::moveLeft(int velocity) {
    analogWrite(INT1,LOW);
    analogWrite(INT2,LOW);
    
    analogWrite(INT3,velocity);
    analogWrite(INT4,LOW);
    //this->motorA('A', 0);
    //this->motorB('R', velocity);
}

void RobotMovements::stop() {
    analogWrite(INT1,LOW);
    analogWrite(INT2,LOW);
    
    analogWrite(INT3,LOW);
    analogWrite(INT4,LOW);
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
Servo servoMotor;

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

  //servoMotor.attach(SIGNAL);
  //servoMotor.write(90);
  robot.stop();
}

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


void loop(){
  distance = Ultrasonido(TRIGGER_PIN, ECHO_PIN);
  Serial.println(distance);
  
  if(Serial.available()){
    intensidad = Serial.read();
    if(intensidad != 0){
      robot.moveForward(intensidad);
    }else{
      robot.stop();
    }
  }
  delay(500);
}


/*
void write_in_bluetooh(){
  if(BT.available())
    Serial.write(BT.read());

  if(Serial.available())
    BT.write(Serial.read());
}
//11 echo
//12 trigger


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
*/
