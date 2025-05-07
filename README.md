#### **[[ENGLISH]](#spanish)**

# TouchExtend

TouchButton es una biblioteca diseñada para simplificar el uso de los pines táctiles capacitivos de las placas ESP32, lo que le permite detectar fácilmente interacciones táctiles como clics, toque sostenido y soltar, ademas permite usar pines ADC como pines capacitivos esto amplia el numero de pines disponibles para ser usados con este fin, Esta libreria te permite usar pines con soporte ADC como si fueran touch en placas ESP32-C3. 

<p align="center">
<img width="25%" src='https://i.postimg.cc/15tXcXJD/touch.png' title=''/>
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

- **Board** : Probado en tarjetas Esp32.
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
#include <TouchExt.h>
#define TOUCH_PIN T0  // Define the touch pin (T0 is an example)
tb touchButton(TOUCH_PIN, 70); // Create a touchButton instance with a 70% sensitivity threshold.

void setup() {
  Serial.begin(115200);
}
void loop() {
  if (touchButton.isClick())     { Serial.println("Single click detected!"); }
  if (touchButton.isHold(500))   { Serial.println("Hold detected for 500ms!"); }
  if (touchButton.isHolded(1000)){ Serial.println("Hold detected once at 1000ms!"); }
  if (touchButton.isRelease(300)){ Serial.println("Button released after being held for 300ms."); }
  delay(100);
}
```

## API

### Constructor

tb(uint8_t pin, uint8_t umbral = 70): inicializa la instancia TouchButton con el pin táctil y el umbral de sensibilidad especificados.

## Metodos

* <b> bool isTouched():</b> Devuelve verdadero si se está tocando el pin táctil.
* <b> bool isHold(short HoldTIME = 400):</b> Devuelve verdadero si se mantuvo presionado el toque durante el tiempo especificado en milisegundos.
* <b> bool isHolded(short HoldedTIME = 400):</b> Devuelve verdadero una vez si se mantuvo presionado el toque durante el tiempo especificado y luego se reinicia cuando se suelta.
* <b> bool isRelease(short ReleaseTIME = 400):</b> Devuelve verdadero cuando se suelta el toque después de mantenerlo presionado durante el tiempo especificado.
* <b> bool isClick():</b> Devuelve verdadero si se detecta un solo clic.
* <b> bool isClicks(uint8_t count):</b> Devuelve verdadero si se detecta la cantidad especificada de clics.

### NOTAS

La biblioteca utiliza la funcionalidad touch_pad interna del ESP32, lo que garantiza una detección táctil precisa.
El parámetro de umbral le permite ajustar la sensibilidad de la detección táctil.
Los valores de tiempo (ClickTIME, HoldTIME, ResetTIME) se pueden ajustar en función de la capacidad de respuesta deseada.

## Ejemplos

En la carpeta de examples del repositorio, encontrarás ejemplos adicionales que muestran cómo utilizar la librería TouchButton con el ESP32.

## Contribuciones

Las contribuciones son bienvenidas. Si encuentras un problema o tienes una sugerencia, por favor abre un issue o envía un pull request.


#### **[[SPANISH]](#english)** 

# TouchButton

TouchButton is a library designed to simplify the use of capacitive touch inputs with the ESP32, allowing you to easily detect touch interactions like clicks, holds, and releases.

<p align="center">
<img width="25%" src='https://i.postimg.cc/15tXcXJD/touch.png' title=''/>
</p>

## Features

- **Optimized for ESP32**: Uses the built-in touch_pad functionality.
- **Customizable Sensitivity**: Set the touch sensitivity threshold to adapt to different needs.
- **Touch Interactions**: Detects various touch events including single clicks, multiple clicks, holds, and releases.
- **Threshold Adjustment**: Automatically sets the sensitivity based on an initial reading.

## Requirements

- **Board** : Tested on Esp32 board.
- **Arduino IDE** : Recommended 1.8.10 or higher

## Instalation

1. Download the library ZIP file from GitHub .
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library... .
3. Select the downloaded ZIP file to install the library.

Or you can extract the ZIP file from step 1 into your Arduino libraries directory.

## Sample code

```
#include <TouchButton.h>
#define TOUCH_PIN T0  // Define the touch pin (T0 is an example)
tb touchButton(TOUCH_PIN, 70); // Create a touchButton instance with a 70% sensitivity threshold.

void setup() {
  Serial.begin(115200);
}
void loop() {
  if (touchButton.isClick())     { Serial.println("Single click detected!"); }
  if (touchButton.isHold(500))   { Serial.println("Hold detected for 500ms!"); }
  if (touchButton.isHolded(1000)){ Serial.println("Hold detected once at 1000ms!"); }
  if (touchButton.isRelease(300)){ Serial.println("Button released after being held for 300ms."); }
  delay(100);
}
```

## API

### Builder

tb(uint8_t pin, uint8_t threshold = 70): Initializes the TouchButton instance with the specified touch pin and sensitivity threshold.

## Methods

* <b> bool isTouched():</b> Returns true if the touch pad is currently being touched.
* <b> bool isHold(short HoldTIME = 400):</b> Returns true if the touch has been held for the specified time in milliseconds.
* <b> bool isHolded(short HoldedTIME = 400):</b> Returns true once if the touch has been held for the specified time, then resets when released.
* <b> bool isRelease(short ReleaseTIME = 400):</b> Returns true when the touch is released after being held for the specified time.
* <b> bool isClick():</b> Returns true if a single click is detected.
* <b> bool isClicks(uint8_t count):</b> Returns true if the specified number of clicks is detected.

### NOTES

The library uses the ESP32's internal touch_pad functionality, ensuring precise touch detection.
The threshold parameter allows you to adjust the sensitivity of the touch detection.
The time values (ClickTIME, HoldTIME, ResetTIME) can be adjusted based on the desired responsiveness.

## Examples

In the examples folder of the repository, you will find additional examples demonstrating how to use the TouchButton library with the ESP32.

## Contributions

Contributions are welcome. If you find a problem or have a suggestion, please open an issue or send a pull request.
