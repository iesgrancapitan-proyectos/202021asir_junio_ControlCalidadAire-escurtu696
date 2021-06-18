# Sistema IoT Cloud para la monitorización y visualización

## Proyecto final C.F.G.S Administración Sistemas Informáticos en Red

## Introducción
Hablar, toser, reír o gritar son actividades cotidianas que hasta hace unos meses no suponían ningún peligro. Ahora en espacios cerrados son bombas de relojería. Y es que ventilar es tu aliado para frenar los contagios de la COVID-19. Abrir las ventanas cinco veces en un aula de 100 metros cuadrados, con 25 personas, permite renovar 14 litros de aire por persona y segundo. 

Reemplaza el aire contaminado por aire limpio del exterior y, además, se eliminan las partículas en suspensión, que pueden contener el virus. Eso sí, en ningún caso esta renovación de aire sustituye al mantenimiento de la distancia, el uso de mascarilla y el lavado de manos. Son herramientas complementarias para luchar contra el coronavirus. Juntas forman un escudo perfecto. Ahora bien, ¿cómo es posible comprobar si la ventilación es la adecuada? Los expertos tienen claro que el riesgo cero no existe, si bien es posible trabajar para reducir el número de infectados. Con este objetivo hemos desarrollado un sistema que mide el dióxido de carbono, la temperatura y la humedad.

¿Cómo funciona? Hemos creado un sistema que recibe datos medioambientales emitidos por unos sensores que se sitúan en el interior de las clases. En ellos encuentra la información sobre el estado actual de la ventilación. «Esto es muy relevante, ya que los sensores han de ubicarse en los lugares más desfavorables de ventilación y los que tienen pantalla no sirven, puesto que hay que acercarse a ellos para leer los valores>>. Por ello nuestro sistema es seguro ya que emite alertas a una sola persona puede controlar todas las ventilaciones de todas las aulas. 

De esta forma creamos un entorno más seguro y todo el personal que compartimos espacios (profesores, alumnos, personal de otro tipo) tenemos la seguridad de que la calidad del aire está controlada. «Los encargados pueden ventilar lo justo, sin gasto energético innecesario», y comentar que la red de datos que se genera se puede usar para transmitir a su vez otro tipo de mediciones de forma gratuita.

## Despliegue
El objetivo del proyecto es implementar una red IoT (Internet of Things) en diferentes aulas del instituto para recoger valores medioambientales como serían temperatura, humedad y nivel de CO2. El despliegue necesario para este proyecto se basa básicamente en el microcontrolador ESP8266 y varios sensores que recogerían valores medioambientales y que enviarán a través de Wifi. Estos datos son procesados por un broker MQTT y enviados para su almacenamiento una base de datos a través de una aplicación llamada Telegraf. Para acceder a la información se usará Grafana, una herramienta que monitoriza y visualiza datos mediante representación con gráficas y tablas, con la finalidad de que la información representada sea más fácil de interpretar.

Un uso apropiado y útil de este proyecto de IoT, por la situación de pandemia actual, es el de medir los niveles de CO2 en las diferentes aulas, y si los niveles se superan en base a unos valores predefinidos, enviar alertas para que se actúe de forma inmediata. La implementación de un medidor de CO2 (dióxido de carbono) consta de una una placa con un microcontrolador ESP8266, a la que están conectados los sensores, el del CO2, temperatura y humedad. Mediante esa placa lo que haremos es configurarla para que recoja los datos de los sensores de una forma periódica, cada minuto. Los sensores son clientes publicadores en un Broker MQTT, que recoge los datos para posteriormente enviarlos al agente Telegraf, y que a su vez inserta los valores recogidos en una base de datos temporal InfluxDB. Por último y mediante los datos de la base de datos temporal lo que se hará es generar unos gráficos mediante Grafana.

Una vez hecho todo el despliegue y visto que funciona correctamente le añadiremos un sistema de avisos mediante correo electrónico, esto es por ejemplo si se llega a una situación en la que hay demasiado CO2 en el aula, se pueda notificar y hacer el cambio de clase y ventilarlo.


## Autores

* [Emilian Scurtu](https://github.com/escurtu696)

## Wiki

[Ver wiki](https://github.com/iesgrancapitan-proyectos/202021asir_junio_ControlCalidadAire-escurtu696/wiki)
