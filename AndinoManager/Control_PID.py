import time
import serial
from json_ import read_json, write_json
import datetime

setPoint=100 #Set point for speed control, using ultrasonic sensor
time_PID = 0
integral = 0
time_prev = -1e-6
e_prev = 0
curSpeed = 0
deltat = 0.1

def PID(Kp, Ki, Kd, setpoint, measurement):
    global time_PID, integral, time_prev, e_prev
    # Value of offset - when the error is equal zero
    offset = 320

    # PID calculations
    e = setpoint - measurement

    P = Kp*e
    integral = integral + Ki*e*(time_PID - time_prev)
    D = Kd*(e - e_prev)/(time_PID - time_prev)
    # calculate manipulated variable - MV 
    MV = offset + P + integral + D

    # update stored data for next iteration
    e_prev = e
    time_prev = time_PID
    return MV

if __name__=="__main__":
    n=100
    arduino = serial.Serial('COM3', 9600)

    list_distances = []

    for i in range(0, n):
        try:
            data=arduino.readline()
            distance=float(data)
            time_PID= i * deltat
            pid_out=PID(0.6,0.2,0.1,setPoint, distance)
            time_prev = time_PID

            val = {}
            date_hour = datetime.datetime.now()
            date = date_hour.date()
            hour = date_hour.time()
            val["id"] = f"{date}|{hour}"
            val["distance"] = f"{distance}"

            list_distances.append(val)

            if pid_out < 0 or pid_out > 1000: continue
            print(distance, " | ",pid_out, ";", i)
            if pid_out>300:
                curSpeed=255 #velocidad alta
            if 50<pid_out<200:
                curSpeed=100 #velocidad media
            if pid_out<30:
                curSpeed=0 #velocidad baja

            arduino.write(bytes([curSpeed]))
            print("Velocidad en byte: ", curSpeed)
            time.sleep(0.5)
        except:
            print("Lectura erronea")
        
    write_json(list_distances, "files/distances.json")
    arduino.close()

