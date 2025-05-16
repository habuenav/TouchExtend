#### **[[ENGLISH]](#spanish)**

# TouchExtend

TouchButton es una biblioteca diseñada para simplificar el uso de los pines táctiles capacitivos de las placas ESP32, lo que le permite detectar fácilmente interacciones táctiles como clics, toque sostenido y soltar, ademas permite usar pines ADC como pines capacitivos esto amplia el numero de pines disponibles para ser usados con este fin, Esto habilita en placas como la ESP32-C3 que no tiene pines touch nativos usar pines ADC como capacitivos por medio de dos tecnicas distintas.

<p align="center">
  <img width="25.5%" src='https://i.postimg.cc/15tXcXJD/touch.png' title='ESP32 Touch nativo.'/>
  <img width="23%" src='https://i.postimg.cc/Bbmw6CrS/Esp32-C3-Touch.png' title='ESP32-C3 Touch PullDown'/>
  <img width="22%" src='https://i.postimg.cc/gcs7NYnC/Esp32-C3-Touch-B.png' title='ESP32-C3 Touch Internal PullUp'/>
</p>

## Video demo
[![Video](https://i9.ytimg.com/vi_webp/CZT4Cc9K-DI/mq2.webp?sqp=CMD0h7kG-oaymwEmCMACELQB8quKqQMa8AEB-AG-AoAC4AOKAgwIABABGGUgXihaMA8=&rs=AOn4CLAyH8MoagsQNR8sYxJ0jhskvQ-MVQ)](https://www.youtube.com/watch?v=CZT4Cc9K-DI)

## Caracteristicas

- **Optimizado para ESP32**: utiliza la funcionalidad del sensor táctil integrado.
- **Mas pines touch**: utiliza tecnicas que permite usar pines con soporte ADC como pines capacitivos.
- **Sensibilidad personalizable**: establece el umbral de sensibilidad táctil para adaptarse a diferentes necesidades.
- **Interacciones táctiles**: detecta varios eventos táctiles, incluidos clics únicos, clics múltiples, presiones y liberaciones.
- **Ajuste del umbral**: establece automáticamente la sensibilidad en función de una lectura inicial.

## Requirementos

- **Board** : Probado en tarjetas Esp32,Esp32-S2,Esp-32-C3.
- **Arduino IDE** : Recommended 1.8.10 or superior
El uso de pines ADC como pines touch o capacitivos, puede requerir el uso de una resistencia de entre 2 y 4 M Ohm, recomendado 3.3M Ohm, esta resistencia solo es necesaria con una de las tecnicas disponibles.

## Instalacion

1. Descargue el archivo ZIP de la biblioteca desde GitHub.
2. En el IDE de Arduino, vaya a Sketch > Incluir biblioteca > Agregar biblioteca .ZIP...
3. Seleccione el archivo ZIP descargado para instalar la biblioteca.

O puedes extraer el archivo ZIP del paso 1 en el directorio de bibliotecas de Arduino.

## Montaje 


## Ejemplo

```
//Este ejemplo esta hecho para ejecutarse en una placa Lolin32 lite
#include <TouchExt.h>

touchExt button1(T0,80); //T0 hace referencia a un pin touch nativo del Esp32
touchExt button2(25,4000,ADC_PULLUP); // El pin 25 no es un pin touch nativo pero si es ADC y puede activarse la resistencia interna pullup
touchExt button3(36,400,ADC_PULLDOWN); // El pin 36 no es un pin touch nativo, usamos una resistencia pulldown para usarlo como pin capacitivo 
void setup() {
  Serial.begin(115200);
}
void loop() {
  if (button1.isClick())     { Serial.println("Click boton 1 detected!"); }
  if (button1.isHold(500))   { Serial.println("Hold detected for 500ms!"); }
  if (button2.Click(2)){ Serial.println("Doble Click detectado boton 2"); }
  if (button3.isRelease(500)){ Serial.println("Boton 3 liberado despues de 500ms."); }
  delay(100);
}
```

## API

### Constructor

 touchExt(uint8_t pin, uint16_t threshold = 70, TouchMode mode = TOUCH_NATIVE): inicializa la instancia TouchExt con el pin táctil y el umbral de sensibilidad especificados.
 los otros dos metodos son 
 TOUCH_NATIVE, // Pines touch nativos (T0-T9)
 ADC_PULLDOWN, // Pines ADC requiere resistencia pulldown externa de 3.3 Mohm 
 ADC_PULLUP // Pines ADC no requiere resistencia externa


## Metodos

* <b> bool isTouched():</b> Devuelve verdadero si se está tocando el pin táctil.
* <b> bool isHold(short HoldTIME = 400):</b> Devuelve verdadero si se mantuvo presionado el toque durante el tiempo especificado en milisegundos.
* <b> bool isHolded(short HoldedTIME = 400):</b> Devuelve verdadero una vez si se mantuvo presionado el toque durante el tiempo especificado y luego se reinicia cuando se suelta.
* <b> bool isRelease(short ReleaseTIME = 400):</b> Devuelve verdadero cuando se suelta el toque después de mantenerlo presionado durante el tiempo especificado.
* <b> bool isClick():</b> Devuelve verdadero si se detecta un solo clic.
* <b> bool isClicks(uint8_t count):</b> Devuelve verdadero si se detecta la cantidad especificada de clics.

### NOTAS

La biblioteca utiliza la funcionalidad touch_pad interna del ESP32, lo que garantiza una detección táctil precisa cuando se usan pines touch nativos.
la deteccion tactil cuando se usan los otros dos modos tambien es bastante buena, sobre todo cuando se usa una resistencia externa (3.3Mohm) ADC_PULLDOWN 
El parámetro de umbral le permite ajustar la sensibilidad de la detección táctil.
Los valores de tiempo (ClickTIME, HoldTIME, ResetTIME) se pueden ajustar en función de la capacidad de respuesta deseada.

## Ejemplos

En la carpeta de examples del repositorio, encontrarás ejemplos adicionales que muestran cómo utilizar la librería TouchExt con el ESP32.

## Contribuciones

Las contribuciones son bienvenidas. Si encuentras un problema o tienes una sugerencia, por favor abre un issue o envía un pull request.


#### **[[SPANISH]](#english)** 

# TouchExtend

TouchButton is a library designed to simplify the use of capacitive touch pins on ESP32 boards, allowing you to easily detect touch interactions such as clicks, hold and release, and also allows you to use ADC pins as capacitive pins, this expands the number of pins available to be used for this purpose. This enables boards like the ESP32-C3 that do not have native touch pins to use ADC pins as capacitive pins using two different techniques.

<p align="center">
  <img width="25.5%" src='https://i.postimg.cc/15tXcXJD/touch.png' title='ESP32 Touch nativo.'/>
  <img width="23%" src='https://i.postimg.cc/Bbmw6CrS/Esp32-C3-Touch.png' title='ESP32-C3 Touch PullDown'/>
  <img width="22%" src='https://i.postimg.cc/gcs7NYnC/Esp32-C3-Touch-B.png' title='ESP32-C3 Touch Internal PullUp'/>
</p>

## Features

- **Optimized for ESP32**: Uses the built-in touch sensor functionality.
- **More touch pins**: Uses techniques that allow ADC-supported pins to be used as capacitive pins.
- **Customizable sensitivity**: Set the touch sensitivity threshold to suit different needs.
- **Touch interactions**: Detects various touch events, including single clicks, multiple clicks, presses, and releases.
- **Threshold tuning**: Automatically sets the sensitivity based on an initial reading.

## Requirements

- **Board**: Tested on ESP32, ESP32-S2, and ESP-32-C3 boards.

- **Arduino IDE**: Recommended 1.8.10 or higher
Using ADC pins as touch or capacitive pins may require the use of a resistor between 2 and 4 M Ohms, recommended 3.3 M Ohms. This resistor is only necessary with one of the available techniques.

## Installation

1. Download the library ZIP file from GitHub.
2. In the Arduino IDE, go to Sketch > Include Library > Add Library .ZIP...
3. Select the downloaded ZIP file to install the library.

Or you can extract the ZIP file from step 1 to your Arduino libraries directory.

## Sample code
```
//Este ejemplo esta hecho para ejecutarse en una placa Lolin32 lite
#include <TouchExt.h>

touchExt button1(T0,80); //T0 hace referencia a un pin touch nativo del Esp32
touchExt button2(25,4000,ADC_PULLUP); // El pin 25 no es un pin touch nativo pero si es ADC y puede activarse la resistencia interna pullup
touchExt button3(36,400,ADC_PULLDOWN); // El pin 36 no es un pin touch nativo, usamos una resistencia pulldown para usarlo como pin capacitivo 
void setup() {
  Serial.begin(115200);
}
void loop() {
  if (button1.isClick())     { Serial.println("Click boton 1 detected!"); }
  if (button1.isHold(500))   { Serial.println("Hold detected for 500ms!"); }
  if (button2.Click(2)){ Serial.println("Doble Click detectado boton 2"); }
  if (button3.isRelease(500)){ Serial.println("Boton 3 liberado despues de 500ms."); }
  delay(100);
}
```

## API

### Constructor

 touchExt(uint8_t pin, uint16_t threshold = 70, TouchMode mode = TOUCH_NATIVE): inicializa la instancia TouchExt con el pin táctil y el umbral de sensibilidad especificados.
 los otros dos metodos son 
 TOUCH_NATIVE, // Pines touch nativos (T0-T9)
 ADC_PULLDOWN, // Pines ADC requiere resistencia pulldown externa de 3.3 Mohm 
 ADC_PULLUP // Pines ADC no requiere resistencia externa


## Metodos

* <b> bool isTouched():</b> Devuelve verdadero si se está tocando el pin táctil.
* <b> bool isHold(short HoldTIME = 400):</b> Devuelve verdadero si se mantuvo presionado el toque durante el tiempo especificado en milisegundos.
* <b> bool isHolded(short HoldedTIME = 400):</b> Devuelve verdadero una vez si se mantuvo presionado el toque durante el tiempo especificado y luego se reinicia cuando se suelta.
* <b> bool isRelease(short ReleaseTIME = 400):</b> Devuelve verdadero cuando se suelta el toque después de mantenerlo presionado durante el tiempo especificado.
* <b> bool isClick():</b> Devuelve verdadero si se detecta un solo clic.
* <b> bool isClicks(uint8_t count):</b> Devuelve verdadero si se detecta la cantidad especificada de clics.

### NOTAS

La biblioteca utiliza la funcionalidad touch_pad interna del ESP32, lo que garantiza una detección táctil precisa cuando se usan pines touch nativos.
la deteccion tactil cuando se usan los otros dos modos tambien es bastante buena, sobre todo cuando se usa una resistencia externa (3.3Mohm) ADC_PULLDOWN 
El parámetro de umbral le permite ajustar la sensibilidad de la detección táctil.
Los valores de tiempo (ClickTIME, HoldTIME, ResetTIME) se pueden ajustar en función de la capacidad de respuesta deseada.

## Examples

In the examples folder of the repository, you will find additional examples demonstrating how to use the TouchExtend library with the ESP32.

## Contributions

Contributions are welcome. If you find a problem or have a suggestion, please open an issue or send a pull request.
