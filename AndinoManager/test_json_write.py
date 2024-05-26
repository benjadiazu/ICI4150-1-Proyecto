from json_ import write_json
import random
import datetime
import time

if __name__=="__main__":
    n = 10
    data = []
    for idx in range(10):
        fecha_hora_actual = datetime.datetime.now()

        fecha = fecha_hora_actual.date()
        hora = fecha_hora_actual.time()

        val = {}
        val["id"] = f"{fecha}|{hora}"
        val["distance"] = f"{random.randint(0, 11)}"
        data.append(val)

        time.sleep(1)

    write_json(data, "files/test.json")