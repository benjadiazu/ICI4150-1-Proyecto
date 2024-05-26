import serial
import pyfirmata2
import time

board=pyfirmata2.Arduino('COM3')

class Motor():

    def __init__(self, In1A, In2A, In1B, In2B):
        self.In1A = board.get_pin('d:{}:p'.format(In1A)) 
        self.In2A = board.get_pin('d:{}:p'.format(In2A)) 
        self.In1B = board.get_pin('d:{}:p'.format(In1B)) 
        self.In2B = board.get_pin('d:{}:p'.format(In2B))
    
    def forward(self, speed):
        self.In1A.write(speed)
        self.In2A.write(0)
        self.In1B.write(speed)
        self.In2B.write(0)

    def backward(self, speed):
        self.In1A.write(0)
        self.In2A.write(speed)
        self.In1B.write(0)
        self.In2B.write(speed)

    def turn_right(self, speed):
        self.In1A.write(speed)
        self.In2A.write(0)
        self.In1B.write(0)
        self.In2B.write(speed)

    def turn_left(self, speed):
        self.In1A.write(0)
        self.In2A.write(speed)
        self.In1B.write(speed)
        self.In2B.write(0)

    def stop(self):
        self.In1A.write(0)
        self.In2A.write(0)
        self.In1B.write(0)
        self.In2B.write(0)


if __name__=="__main__":
    arduino = serial.Serial('COM3', 9600)
    data = arduino.readline()
    distance=int(data)
    print(distance)
    motor=Motor(5, 6, 9, 10)
    
    # Avanzar durante 3 segundos con velocidad 0.2
    motor.forward(0.5)
    time.sleep(2)

    # Girar a la derecha durante 1 segundo
    motor.turn_right(0.5)  # Velocidad arbitraria
    time.sleep(1)

    # Girar a la izquierda durante 1 segundo
    motor.turn_left(0.5)  # Velocidad arbitraria
    time.sleep(1)

    # Retroceder durante 3 segundos con velocidad 0.2
    motor.backward(0.5)
    time.sleep(2)

    # Detener el motor
    motor.stop()
    arduino.close()
        
