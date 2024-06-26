#include <Wire.h>
#include <Arduino_APDS9960.h>
#include <Servo.h>
#include <SparkFun_APDS9960.h>

//#include <queue>
//#include <vector>

// Creación de un objeto APDS9960
SparkFun_APDS9960 apds = SparkFun_APDS9960();

#define DUMP_REGS

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define SIGNAL 3
#define PIN_SERVO 13

#define INT1 5 
#define INT2 6
#define INT3 9
#define INT4 10
#define INF 32767

// Dimensiones del mapa
#define N 3
#define M 6

long distance;
int intensidad;
long posicion_servo_inicial = 100;
int anguloMaximo = 50;
long filtro_max = 100;
long filtro_min = 5;

long umbralDistancia = 5;

int posX = N - 1;
int posY = M - 1;

// Mapa de ejemplo (0s: camino, 1s: obstáculo)
int mapa[N][M] = {
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0},
};

struct Nodo {
    int x, y;
    int distancia;
    bool visitado;
    int numero;

    Nodo() : x(0), y(0), distancia(INF), visitado(false) {}
    Nodo(int _x, int _y) : x(_x), y(_y), distancia(INF), visitado(false) {}
};

Nodo nodos[N][M]; // Matriz de nodos
int camino[N * M]; // Arreglo para almacenar el camino óptimo

class RobotMovements {

public:
    RobotMovements(); // Constructor
    void moveForward(int velocity);
    void moveBackward(int velocity);
    void moveRight(int velocity);
    void moveLeft(int velocity);
    void stop();
    void rotateClockwise(int degrees, int velocity);
    void rotateCounterClockwise(int degrees, int velocity);
    const float timeForFullRotation = 2000;
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
    Serial.println("Ahora avanzo hacia adelante");
}

void RobotMovements::moveBackward(int velocity) {
    analogWrite(INT1,velocity);
    analogWrite(INT2,LOW);
    
    analogWrite(INT3,LOW);
    analogWrite(INT4,velocity);
    //this->motorA('R', velocity);
    //this->motorB('A', velocity);
    Serial.println("Ahora retrocedo");
}

void RobotMovements::moveRight(int velocity) {
    analogWrite(INT1,LOW);
    analogWrite(INT2,velocity);
    
    analogWrite(INT3,LOW);
    analogWrite(INT4,LOW);
    //this->motorA('R', velocity);
    //this->motorB('A', 0);
    Serial.println("Derecha");
}

void RobotMovements::moveLeft(int velocity) {
    analogWrite(INT1,LOW);
    analogWrite(INT2,LOW);
    
    analogWrite(INT3,velocity);
    analogWrite(INT4,LOW);
    //this->motorA('A', 0);
    //this->motorB('R', velocity);
    Serial.println("Izquierda");
}

void RobotMovements::stop() {
    analogWrite(INT1,LOW);
    analogWrite(INT2,LOW);
    
    analogWrite(INT3,LOW);
    analogWrite(INT4,LOW);
    Serial.println("Parp");
}

void RobotMovements::rotateClockwise(int degrees, int velocity) {
    float rotationTime = (degrees / 360.0) * timeForFullRotation * (255.0 / velocity);
    analogWrite(INT1, velocity);
    analogWrite(INT2, LOW);
    analogWrite(INT3, velocity);
    analogWrite(INT4, LOW);
    delay(rotationTime);
    stop();
    Serial.print("Girado ");
    Serial.print(degrees);
    Serial.println(" grados en sentido horario");
}

void RobotMovements::rotateCounterClockwise(int degrees, int velocity) {
    float rotationTime = (degrees / 360.0) * timeForFullRotation * (255.0 / velocity);
    analogWrite(INT1, LOW);
    analogWrite(INT2, velocity);
    analogWrite(INT3, LOW);
    analogWrite(INT4, velocity);
    delay(rotationTime);
    stop();
    Serial.print("Girado ");
    Serial.print(degrees);
    Serial.println(" grados en sentido antihorario");
}


RobotMovements robot;
Servo servo;
int nodo_actual = 0;  // Índice del camino
int indice_actual = 0;
int largo_total = 0;
bool final_camino = false;

void setup() {
  servo.attach(PIN_SERVO); 
  servo.write(posicion_servo_inicial);

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
  explorarMapa();
}

void loop() {

    long distanciaFrontal = Ultrasonido(TRIGGER_PIN, ECHO_PIN);
    robot.moveForward(255);
    if(final_camino){
      robot.stop();
    }

    //Si robot detecta un muro entonces se detiene y evalua su posición
    robot.moveForward(255);
    if (distanciaFrontal < umbralDistancia) {
      Serial.println("Obstáculo detectado. Ajustando camino.");
      delay(500);
            // Rotar a un lado y comprobar muro
      robot.stop();
            
            
      //Actualizar posición actual
      for(int i = 0; i < N*M -1; i++){
        
        if(i < indice_actual){
          continue;
        }
        //Hay un muro
        if(camino[i] != camino[i+1]){
          nodo_actual = camino[i];
          indice_actual = i;
        }
      }
      //LLego al final del camino
      if(indice_actual >= largo_total){
        final_camino = true;
        return;
      } 

      if(camino[indice_actual] < camino[indice_actual+1])  {
        robot.rotateClockwise(90, 255);
      }

      if(camino[indice_actual] > camino[indice_actual+1])  {
        robot.rotateCounterClockwise(90, 255);
      }
    }
    Serial.print("Camino a seguir: ");
    for(int i = 0; i < largo_total; i++){
      if(i == indice_actual){
        Serial.print("x ");
      }else{
        Serial.print(camino[i]);
        Serial.print(" ");
      }
    }
    delay(1000);
}

void mirarDerecha(){
  for (int angulo = posicion_servo_inicial - anguloMaximo -30; angulo <= posicion_servo_inicial + anguloMaximo; angulo++) {
    servo.write(angulo);
    delay(15);  // Pequeño delay para suavizar el movimiento
  }
}

void mirarIzquierda(){
  for (int angulo = posicion_servo_inicial + anguloMaximo; angulo >= posicion_servo_inicial - anguloMaximo; angulo--) {
    servo.write(angulo);
    delay(15);  // Pequeño delay para suavizar el movimiento
  }
}

bool hayCaminoLibre(){
  int distanciaMedida = Ultrasonido(TRIGGER_PIN, ECHO_PIN);
  return distanciaMedida > umbralDistancia;
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
  distance = (duration*0.034)/2; 
  /*
  if (distance <= filtro_min ){
    distance = 0;
  }
  */
  Serial.println(distance);
  return distance;
}

// Función principal de exploración
void explorarMapa() {
    //inicializar(); // Inicialización de hardware y sensores

    int xi = 0, yi = 0; // Punto de inicio (ejemplo)
    dijkstra(xi, yi);   // Calcular rutas desde el punto de inicio

    /*
    while (true) {
        moveForward(); // Mover hacia adelante por defecto (ejemplo)

        // Lógica para detección de obstáculos y ajuste de ruta
        long distancia = medicionUltrasonido(); // Medir distancia con el ultrasonido
        if (distancia < 10) { // Ejemplo de umbral de distancia
            // Girar a la derecha (ejemplo)
            turnRight(); 
        }

        delay(500); // Delay entre movimientos para estabilizar lecturas
    }
    */
    //seguirCamino(xi, yi);
}

Nodo extraerMinimo() {
    int minDistancia = INF;
    Nodo minNodo;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!nodos[i][j].visitado && nodos[i][j].distancia <= minDistancia) {
                minDistancia = nodos[i][j].distancia;
                minNodo = nodos[i][j];
            }
        }
    }

    return minNodo;
}

// Función para relajar los nodos adyacentes a uno dado
void relajarNodos(int uX, int uY) {
    // Definir los movimientos posibles (arriba, abajo, izquierda, derecha)
    int movimientos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Iterar sobre los nodos adyacentes
    for (int i = 0; i < 4; ++i) {
        int vX = uX + movimientos[i][0];
        int vY = uY + movimientos[i][1];

        // Verificar límites del mapa y si el nodo adyacente no es un obstáculo
        if (vX >= 0 && vX < N && vY >= 0 && vY < M && mapa[vX][vY] == 0) {
            // Si v no ha sido visitado y hay un camino más corto a través de u
            if (!nodos[vX][vY].visitado && nodos[uX][uY].distancia + 1 < nodos[vX][vY].distancia) {
                nodos[vX][vY].distancia = nodos[uX][uY].distancia + 1;
            }
        }
    }
}

// Función principal de Dijkstra para explorar el laberinto
void dijkstra(int xi, int yi) {
    // Inicialización de los nodos
    inicializarNodos();

    imprimirAsignacion();
    // Establecer la distancia del nodo inicial como 0
    nodos[xi][yi].distancia = 0;

    // Algoritmo de Dijkstra adaptado para explorar el laberinto
    for (int count = 0; count < N * M; ++count) {
        Nodo u = extraerMinimo();
        int uX = u.x;
        int uY = u.y;

        // Marcar el nodo como visitado
        nodos[uX][uY].visitado = true;

        // Relajar los nodos adyacentes
        relajarNodos(uX, uY);
    }

    // Construir el camino óptimo (opcional)
    int index = 0;
    int posX = N - 1;
    int posY = M - 1;

    while (posX != xi || posY != yi) {
        camino[index++] = posX * M + posY;
        int movimientos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i) {
            int vX = posX + movimientos[i][0];
            int vY = posY + movimientos[i][1];
            if (vX >= 0 && vX < N && vY >= 0 && vY < M) {
                if (nodos[vX][vY].distancia + 1 == nodos[posX][posY].distancia) {
                    posX = vX;
                    posY = vY;
                    break;
                }
            }
        }
    }
    largo_total = index - 1;
    // Mostrar resultados o realizar acciones basadas en los cálculos de Dijkstra
    Serial.print("Camino óptimo: ");
    for (int i = index - 1; i >= 0; --i) {
        Serial.print(camino[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void inicializarNodos() {
    int contador = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            nodos[i][j].x = i;
            nodos[i][j].y = j;
            nodos[i][j].numero = contador++; // Asignación de número único a cada nodo
            nodos[i][j].distancia = INF;
            nodos[i][j].visitado = false;
        }
    }
}

void imprimirAsignacion(){
  // Imprimir asignación de números de nodo
  for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
          Serial.print("Nodo (");
          Serial.print(nodos[i][j].x);
          Serial.print(",");
          Serial.print(nodos[i][j].y);
          Serial.print(") tiene número ");
          Serial.println(nodos[i][j].numero);
      }
  }
}

void seguirCamino(int xi, int yi) {
    int posX = N - 1;
    int posY = M - 1;
    int index = 0;

    // Recorremos el camino calculado en orden inverso (desde la meta hasta el inicio)
    while (!(posX == xi && posY == yi)) {
        int prevPosX = posX;
        int prevPosY = posY;
        long distanciaFrontal = Ultrasonido(TRIGGER_PIN, ECHO_PIN);

        robot.moveForward(255);
        if (distanciaFrontal < umbralDistancia) {
            Serial.println("Obstáculo detectado. Ajustando camino.");
            delay(500);
            // Rotar a un lado y comprobar muro
            robot.stop();
            robot.rotateClockwise(90, 255);
            delay(500);
            //Hay muro gira al otro lado
            if (Ultrasonido(TRIGGER_PIN, ECHO_PIN) < umbralDistancia){
              robot.stop();
              robot.rotateCounterClockwise(180, 255);
              delay(500);
            }else{
              robot.stop();
              robot.rotateCounterClockwise(90, 255);
              delay(500);
            }
            continue; 
        }

        if (camino[index] == prevPosX * M + (prevPosY - 1)) {
            Serial.println("Este giro izquierdo");
            robot.moveLeft(255); // Mover hacia la izquierda
            posY--;
        } else if (camino[index] == prevPosX * M + (prevPosY + 1)) {
            Serial.println("Este giro izquierdo");
            robot.moveRight(255); // Mover hacia la derecha
            posY++;
        } else if (camino[index] == (prevPosX - 1) * M + prevPosY) {
            robot.moveForward(255); // Mover hacia adelante
            posX--;
        } else if (camino[index] == (prevPosX + 1) * M + prevPosY) {
            robot.moveBackward(255); // Mover hacia atrás
            posX++;
        }
        Serial.print("Imprimir iteración: ");
        Serial.println(index);
        index++;
        delay(500); // Pequeño retraso entre movimientos
    }

    robot.stop(); // Detener el robot al final del camino
}