# ICI4150-1-Proyecto

### Integrantes:
<br>
Benjamín Díaz
<br>
Benjamín Fernández
<br>
Thomas Molina


## EP 1.1: ¿Qué tipo de robot es? (Justifique)
	
R: En base a su estructura y a su tipo de desplazamiento, este sería un robot móvil. El robot es capaz de desplazarse libremente en su eje “x” e “y” mediante cuatro ruedas, partiendo desde un punto inicial arbitrario. Además, por su comportamiento sería un robot autónomo, puesto a que el controlador tomará decisiones que cambien la dirección del movimiento en base a los obstáculos del laberinto, añadido a esto, el robot sería capaz de identificar por si mismo a un sujeto ileso o herido mediante el color, o identificar si se encuentra en una zona peligrosa que no debe explorar.

## EP1.2: ¿Qué tipo de sensores incluirá su robot?, ¿Cómo se puede extraer información de los sensores? (Justifique, debe incluir al menos dos sensores)

R: Los sensores a utilizar en el proyecto serán los siguientes:
 
Sensor RGB: Es indispensable que el robot pueda distinguir colores, esto debido a que se necesita identificar el tipo de víctima mediante su color (rojo o verde). La forma en que se extrae información de los sensores es mediante tres sensores acoplados que permiten la separación de la luz incidente en sus componentes rojo, verde y azul, entregando un valor asociado cada uno de aquellos, y que permitirá su identificación en un esquema de colores predefinido.
Sensor Ultrasónico: Para guiar el movimiento del robot dentro de un laberinto, resulta necesario tener un sensor que pueda medir la distancia de los objetos que existan en el escenario, de forma que controlador pueda obtener información sobre la cercanía de posibles obstáculos y lo lleve a tomar una decisión correcta para continuar su misión. Para saber la distancia exacta entre el sensor y algún objeto, el sensor emite una onda ultrasónica, la cuál tomará un tiempo determinado en ir hacia el objeto, rebotar y volver. Luego se calcula la distancia, en base a la velocidad del sonido y el tiempo que tardó en recorrer el camino de ida y vuelta.

## EP1.3: ¿Cómo podemos representar el error y cómo podemos razonar ante la incertidumbre?

R: El error se puede representar de tres formas:
El número de veces que el sensor captura información de manera incorrecta o falsa del entorno. Por ejemplo, el sensor de ultrasonido podría detectar una pared que no existe por una onda disparada anteriormente que hace eco dentro del laberinto.
La diferencia producida entre la medida del valor real y el capturado por el sensor. Un posible caso es la descalibración del sensor de ultrasonido, en el trigger o el eco, produciendo cálculos de distancias menos precisas.
El número de veces que el sensor no detecta algún objeto relevante en el ambiente cuando este sí existe. Un ejemplo sería una mala calibración del TRIGGER producido por la disminución de pulso emitido.
	
Acerca de la incertidumbre, el robot no puede tener seguridad sobre los siguientes parámetros:
La posición: El robot no tiene datos exactos sobre su posición, ya que no recibe señales visuales, además de que no puede guardar datos sobre el entorno como para generar un mapeo. Por ende, para que el robot pueda orientarse, deberá reaccionar frente a los obstáculos.
Configuración del Entorno: Relacionado al punto anterior, el robot no tiene una imagen del entorno en el que se desenvolverá, por lo que no puede tener alguna pista de qué movimientos podrían recorrer el mapa de una forma óptima. El uso del sensor RGB servirá para identificar obstáculos y personas. Mientras que el sensor ultrasonido deberá definir los movimientos a realizar lo más “tarde” posible, para que el robot pueda recorrer lo máximo posible del mapa.

## EP1.4: ¿Cómo se mueve el robot? (Puede existir un dibujo o gráfico)

R: El robot sólo se podrá desplazar en el eje “x” e “y”, de manera lateral (izquierda o derecha) o hacia adelante y hacia atrás. Su desplazamiento está sujeto a cuatro ruedas, de las cuales las dos delanteras son las que se encargan de otorgar los movimientos tanto laterales como rectos.
 
## EP1.5: ¿Cuántos grados de libertad dispone el robot con el que va a trabajar? (Justifique)
	
R:  El robot cuenta con 3 grados de libertad distribuidos en sus 3 articulaciones:
Las primeras dos articulaciones están relacionadas con las ruedas delanteras del robot, que posee actuadores que le permiten realizar movimientos de izquierda a derecha, como también hacia adelante y hacia atrás. Al ser dos direcciones de movimiento distintas, se contarían dos grados de libertad en total para desencadenar el desplazamiento.
La tercera articulación está en la “cabeza” del robot, la cual puede girar a conveniencia y permite que el sensor ubicado en la zona tenga un mayor alcance. Al ser un solo tipo de movimiento, este contaría como un grado de libertad.

## EP1.6: ¿Cómo se puede controlar la velocidad de las ruedas para alcanzar una posición deseada?

R: Para ajustar la velocidad de las ruedas del robot se hace uso del algoritmo PID. Cuando se define una posición deseada se calcula la diferencia entre la variable de proceso (la posición del robot) y el valor setPoint (la posición deseada), obteniendo el error. Posteriormente a ello, el algoritmo recibe de entrada este valor y ajusta la velocidad de las ruedas, minimizando este error y con ello permite llegar a la posición deseada con una velocidad controlada. Con este ajuste de velocidades el robot es capaz de, por ejemplo, reducir la velocidad si está llegando a la posición deseada, o bien aumentarla si está lejos de ella.

## EP1.7: ¿Qué sistema embebido usaría? (Arduino UNO, Raspberry Pi, Jetson Nano, etc) (Justifique)

R: Se usará Arduino UNO, porque el microcontrolador permite obtener respuestas en tiempo real para las señales recibidas durante la operación. Además ninguna de las operaciones o procesos a calcular debería ser muy complicada, por lo que no se requiere un procesador más avanzado.

## EP1.8: ¿Qué respuestas de retroalimentación tendrá el robot? (Justifique)
	
R: El robot emitirá dos respuestas de retroalimentación, ambas relacionadas a los sensores que utilizará:
En primer lugar, el robot utilizará un control de lazo cerrado ligado al sensor ultrasónico. Este sensor recibirá una señal en forma de onda sonora que estará relacionada a un valor que indicará la distancia actual con algún obstáculo presente, basado en el tiempo que tardará el sonido en ir y regresar. Así el controlador podrá determinar el movimiento a realizar, el cual será la respuesta que entregue el robot, un cambio en las velocidades de las ruedas que determinarán el movimiento que realizará robot.
La segunda respuesta, está ligada al sensor RGB, la retroalimentación será una señal que recibirá la interfaz con la información del color identificado, marcando aquel lugar del laberinto como una zona donde se encontró una persona herida de gravedad, una persona sin heridas, o una zona peligrosa para la exploración.

## EP2.1: Implementar la captura y almacenamiento de los datos de los sensores. (el almacenamiento de los datos puede ser JSON)

## EP2.2: Realizar diagramas de la propuesta, eso implica considerar aspectos como : (1) la comunicación con la UI, (2) si tiene asignado un robot móvil debe presentar mapa topográfico. De lo contrario análisis de los movimientos (Cinemática) , (3) Interacción (guión), (4) arquitectura de control.

La propuesta será la de un robot que pueda recorrer un laberinto, evitando chocar contra las paredes y pasar sobre placas de color negro (obstáculos), a su vez, debe reconocer cuadrados rojos y verdes colocados en el suelo del laberinto, envíando señales de cada cambio en su desplazamiento, y cada cuadrado de color encontrado. La ruta que seguirá el robot estará determinada por las placas de color, y una vez haya encontrado la última, el robot debe regresar a su punto inicial.

### Diagrama de comunicación con la UI

Un usuario podrá ver en su dispositivo móvil desde la aplicación los datos en tiempo real del robot mediante el Frontend, por ejemplo, la ruta que está siguiendo el robot, esto se logrará rescatando los datos desde el Backend que tendrá constante comunicación con el robot almacenando sus datos.

![Diagrama de comunicación](/Images/Diagrama_UI.png)

### Diagrama del Laberinto:

El laberinto estará compuesto de un conjunto de placas cuadradas de cartón de 15x15 cm, que contendrán un espacio de movimiento libre para el robot, y las paredes (delimitaciones) que separan una placa de otra. Cabe señalar que estas paredes temdrán una altura de 11 cm.

![Medidas a considerar](/Images/Medidas.png)

Además, el laberinto estará rodeado por paredes en su exterior, impidiendo que el robot escape por accidente. A continuación, se presenta una representación del laberinto.

![Laberinto propuesto](/Images/Maze-v2.png)

### Representación Matricial del Mapa:

El robot recibirá de antemano un mapa topográfico, que será representado por una matriz cuadrada de 11x11 que se definirá según el script adjuntado en el repositorio (Maze.py). Este script entrega una matriz como la que se ve a continuación.

![Matriz binaria del mapa topográfico](/Images/Binary_Maze-2.png)


Para esta propuesta, los 1 son espacios que se consideran obstáculos, y por ende, el robot no puede pasar por ellos, mientras que los espacios marcados por 0, son espacios que el robot si puede atravesar.

### Interacción:

Para este punto, consideramos que hay 4 direcciones posibles para el robot (Arriba, Abajo, Izquierda, Derecha). Los pasos a seguir por el robot entonces serían los siguientes.

1.	El robot iniciará en un punto arbitrario del laberinto. 
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso1.png)
2.	Identificar la ruta de exploración a seguir del mapa topográfico asignado. Para definir un nodo, se toma en cuenta las sigueintes reglas:
        1. Si un espacio marcado como 0, tiene un solo vecino marcado como 0, representará un cruce y será un nodo;
  	2. Si un espacio marcado como 0 tiene vecinos marcados como 0 en direcciones pertencientes a ejes distintos (vertical y horizontal), entonces también es un cruce y será considerado como nodo.
	En cualquier otro caso, el espacio marcado como 0, será un arco.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso2.png)
3.	Utilizar los motores para desplazarse en el laberinto, con las siguientes acciones:
	1.	Ir hacia adelante.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso3-1.png)
	2.	Girar a la derecha.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso3-2.png)
	3.	Girar a la izquierda.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso3-3.png)
	4.	Retroceder.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso3-4.png)
	5.	Detenerse.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso3-5.png)
4. 	Para cambiar de nodo, además de los motores, el robot utilizará el sensor ultrasonido, para medir su posición en base a la distancia a la siguiente pared.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso4.png)
5. 	Para ejecutar el siguiente paso de la ruta, el robot se decidirá por uno de los dos caminos posibles a seguir, efectuando un giro antes de continuar. En el caso de que sólo sea posible devolver por donde llegó, el robot deberá girar en 180 grados 	antes de continuar.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso5.png)
6.	A medida que recorre el laberinto, tanto en nodos como arcos, el robot utilizará el sensor RGB, para identificar uno de los casos posibles:
	1.	Zona verde: Correspondiente a una persona que no necesita auxilio inmediato. El robot notifica a la aplicación de que se encontró una víctima sin atención urgente y sigue con la ruta pudiendo atravesar la zona verde para continuar su ruta.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso6-1.png)
	2.	Zona roja: Es una persona que necesita ayuda urgente. El robot notifica a la aplicación de que se encontró una victima con necesidad de atención inmediata y sigue con la ruta pudiendo atravesar la zona verde para continuar su ruta.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso6-2.png)
	3.	Zona negra: Son las secciones de peligro, las cuales el robot no debe seguir su camino. Se notificará a la aplicación de que hay una zona de peligro, por lo cual, se debe volver al último nodo visitado y recalcular una nueva ruta hacia el nodo objetivo.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso6-3.png)
7.	Una vez recorrido todos los nodos del mapa, el robot vuelve al origen y se detiene, indicando a la aplicación que se finalizó la exploración.
![Inicio en un punto arbitrario](/Images/Diagramas_Robot_Pasos/Interaccion-Paso7.png)
### Tipo de Arquitectura:

En base a lo anterior, el robot funcionará a partir de una arquitectura Reactiva basada en comportamientos, ya que definirá ciertas acciones posibles de realizar, pero se ejecutarán según el entorno lo permita y el módulo de control (Arduino UNO) lo dictamine. Las acciones en este caso serían las de: Monitorear Distancia, Monitorear Color, Girar Izquierda/Derecha, Avanzar/Retroceder, Emitir señal.

## EP2.3: Ubicación de los sensores y actuadores que se requieren en el robot seleccionado (hacer diagrama o tomar foto)

![Sensores y actuadores del robot](/Images/Robot.png)
