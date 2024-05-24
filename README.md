# ICI4150-1-Proyecto

Integrantes:
<br>
Benjamín Díaz
<br>
Benjamín Fernández
<br>
Thomas Molina


EP 1.1: ¿Qué tipo de robot es? (Justifique)
	
R: En base a su estructura y a su tipo de desplazamiento, este sería un robot móvil. El robot es capaz de desplazarse libremente en su eje “x” e “y” mediante cuatro ruedas, partiendo desde un punto inicial arbitrario. Además, por su comportamiento sería un robot autónomo, puesto a que el controlador tomará decisiones que cambien la dirección del movimiento en base a los obstáculos del laberinto, añadido a esto, el robot sería capaz de identificar por si mismo a un sujeto ileso o herido mediante el color, o identificar si se encuentra en una zona peligrosa que no debe explorar.

EP1.2: ¿Qué tipo de sensores incluirá su robot?, ¿Cómo se puede extraer información de los sensores? (Justifique, debe incluir al menos dos sensores)

R: Los sensores a utilizar en el proyecto serán los siguientes:
 
Sensor RGB: Es indispensable que el robot pueda distinguir colores, esto debido a que se necesita identificar el tipo de víctima mediante su color (rojo o verde). La forma en que se extrae información de los sensores es mediante tres sensores acoplados que permiten la separación de la luz incidente en sus componentes rojo, verde y azul, entregando un valor asociado cada uno de aquellos, y que permitirá su identificación en un esquema de colores predefinido.
Sensor Ultrasónico: Para guiar el movimiento del robot dentro de un laberinto, resulta necesario tener un sensor que pueda medir la distancia de los objetos que existan en el escenario, de forma que controlador pueda obtener información sobre la cercanía de posibles obstáculos y lo lleve a tomar una decisión correcta para continuar su misión. Para saber la distancia exacta entre el sensor y algún objeto, el sensor emite una onda ultrasónica, la cuál tomará un tiempo determinado en ir hacia el objeto, rebotar y volver. Luego se calcula la distancia, en base a la velocidad del sonido y el tiempo que tardó en recorrer el camino de ida y vuelta.

EP1.3: ¿Cómo podemos representar el error y cómo podemos razonar ante la incertidumbre?

R: El error se puede representar de tres formas:
El número de veces que el sensor captura información de manera incorrecta o falsa del entorno. Por ejemplo, el sensor de ultrasonido podría detectar una pared que no existe por una onda disparada anteriormente que hace eco dentro del laberinto.
La diferencia producida entre la medida del valor real y el capturado por el sensor. Un posible caso es la descalibración del sensor de ultrasonido, en el trigger o el eco, produciendo cálculos de distancias menos precisas.
El número de veces que el sensor no detecta algún objeto relevante en el ambiente cuando este sí existe. Un ejemplo sería una mala calibración del TRIGGER producido por la disminución de pulso emitido.
	
Acerca de la incertidumbre, el robot no puede tener seguridad sobre los siguientes parámetros:
La posición: El robot no tiene datos exactos sobre su posición, ya que no recibe señales visuales, además de que no puede guardar datos sobre el entorno como para generar un mapeo. Por ende, para que el robot pueda orientarse, deberá reaccionar frente a los obstáculos.
Configuración del Entorno: Relacionado al punto anterior, el robot no tiene una imagen del entorno en el que se desenvolverá, por lo que no puede tener alguna pista de qué movimientos podrían recorrer el mapa de una forma óptima. El uso del sensor RGB servirá para identificar obstáculos y personas. Mientras que el sensor ultrasonido deberá definir los movimientos a realizar lo más “tarde” posible, para que el robot pueda recorrer lo máximo posible del mapa.
EP1.4: ¿Cómo se mueve el robot? (Puede existir un dibujo o gráfico)

R: El robot sólo se podrá desplazar en el eje “x” e “y”, de manera lateral (izquierda o derecha) o hacia adelante y hacia atrás. Su desplazamiento está sujeto a cuatro ruedas, de las cuales las dos delanteras son las que se encargan de otorgar los movimientos tanto laterales como rectos.
 
EP1.5: ¿Cuántos grados de libertad dispone el robot con el que va a trabajar? (Justifique)
	
R:  El robot cuenta con 3 grados de libertad distribuidos en sus 3 articulaciones:
Las primeras dos articulaciones están relacionadas con las ruedas delanteras del robot, que posee actuadores que le permiten realizar movimientos de izquierda a derecha, como también hacia adelante y hacia atrás. Al ser dos direcciones de movimiento distintas, se contarían dos grados de libertad en total para desencadenar el desplazamiento.
La tercera articulación está en la “cabeza” del robot, la cual puede girar a conveniencia y permite que el sensor ubicado en la zona tenga un mayor alcance. Al ser un solo tipo de movimiento, este contaría como un grado de libertad.

EP1.6: ¿Cómo se puede controlar la velocidad de las ruedas para alcanzar una posición deseada?

R: Para ajustar la velocidad de las ruedas del robot se hace uso del algoritmo PID. Cuando se define una posición deseada se calcula la diferencia entre la variable de proceso (la posición del robot) y el valor setPoint (la posición deseada), obteniendo el error. Posteriormente a ello, el algoritmo recibe de entrada este valor y ajusta la velocidad de las ruedas, minimizando este error y con ello permite llegar a la posición deseada con una velocidad controlada. Con este ajuste de velocidades el robot es capaz de, por ejemplo, reducir la velocidad si está llegando a la posición deseada, o bien aumentarla si está lejos de ella.

EP1.7: ¿Qué sistema embebido usaría? (Arduino UNO, Raspberry Pi, Jetson Nano, etc) (Justifique)

R: Se usará Arduino UNO, porque el microcontrolador permite obtener respuestas en tiempo real para las señales recibidas durante la operación. Además ninguna de las operaciones o procesos a calcular debería ser muy complicada, por lo que no se requiere un procesador más avanzado.

EP1.8: ¿Qué respuestas de retroalimentación tendrá el robot? (Justifique)
	
R: El robot emitirá dos respuestas de retroalimentación, ambas relacionadas a los sensores que utilizará:
En primer lugar, el robot utilizará un control de lazo cerrado ligado al sensor ultrasónico. Este sensor recibirá una señal en forma de onda sonora que estará relacionada a un valor que indicará la distancia actual con algún obstáculo presente, basado en el tiempo que tardará el sonido en ir y regresar. Así el controlador podrá determinar el movimiento a realizar, el cual será la respuesta que entregue el robot, un cambio en las velocidades de las ruedas que determinarán el movimiento que realizará robot.
La segunda respuesta, está ligada al sensor RGB, la retroalimentación será una señal que recibirá la interfaz con la información del color identificado, marcando aquel lugar del laberinto como una zona donde se encontró una persona herida de gravedad, una persona sin heridas, o una zona peligrosa para la exploración.

EP2.1: Implementar la captura y almacenamiento de los datos de los sensores. (el almacenamiento de los datos puede ser JSON)

EP2.2: Realizar diagramas de la propuesta, eso implica considerar aspectos como : (1) la comunicación con la UI, (2) si tiene asignado un robot móvil debe presentar mapa topográfico. De lo contrario análisis de los movimientos (Cinemática) , (3) Interacción (guión), (4) arquitectura de control.

EP2.3: Ubicación de los sensores y actuadores que se requieren en el robot seleccionado (hacer diagrama o tomar foto)
