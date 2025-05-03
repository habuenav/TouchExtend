#ifndef TouchExt_h
#define TouchExt_h

#include <Arduino.h>
#ifdef SOC_TOUCH_SENSOR_SUPPORTED
#define TOUCH_SUPPORT  
#include "driver/touch_pad.h"
#endif

#define interrupt_trigger_type RISING // Interrupción activada en un flanco ascendente
#define pulldownTHRESHOLD 350 // Umbral para detectar toque
#define pullupTHRESHOLD 4000 // Umbral para detectar toque
#define READ_TIME 35  // Tiempo en milisegundos para evaluar el toque
#ifndef ClickTIME
#define ClickTIME 35
#endif
#ifndef ResetTIME
#define ResetTIME 700
#endif
#define THRESHOLD_MULTIPLIER 0.66666f
#define THRESHOLD_PERCENTAGE_FACTOR 0.01f

// Modos de operación
enum TouchMode {
  TOUCH_NATIVE, // Pines touch nativos (T0-T9)
  ADC_PULLDOWN, // Pines ADC requiere resistencia pulldown externa de 1M ohm o mas
  ADC_NO_RESISTOR // Pines ADC no requiere resistencia externa
};

// Variable global para interrupciones
volatile bool interruptTriggered = false;
// Manejador de interrupciones para pines ADC con resistencia
void button_interrupt_handler() {
  if (!interruptTriggered) {
    interruptTriggered = true;
  }
}

class touchExt {
public:
     touchExt(uint8_t pin, uint16_t threshold = 70, TouchMode mode = TOUCH_NATIVE);
    inline bool isTouched();
    bool isHold(short holdTime = 400);
    bool isReleased(short releaseTime = 400);
    bool isHolded(short holdedTime = 400);
    bool isClick();
    bool isClicks(uint8_t count);
    int pulldownRead();
    int pullupRead();
    uint16_t valor;

private:
    inline long _touchTime(unsigned long now = millis());
    uint8_t _pin;
    uint8_t _threshold;
    uint16_t _adcPulldownThreshold; // Umbral para ADC_PULLDOWN
    uint16_t _adcPullupThreshold; // Umbral para ADC_NO_RESISTOR
    TouchMode _mode;
    unsigned long _touchStart = 0;
    unsigned long _lastTouchStart = 0;
    uint8_t _clickCount = 0;
    bool _isTouched = false;
    bool _isHolding = false;
    float _initialThreshold;
};

// Constructor
touchExt::touchExt(uint8_t pin, uint16_t threshold, TouchMode mode) : _pin(pin), _threshold(threshold),_mode(mode) {

     #ifdef TOUCH_SUPPORT
     if (digitalPinToTouchChannel(_pin) >= 0 && _mode == TOUCH_NATIVE) {
    touch_pad_init();
    touch_pad_io_init(static_cast<touch_pad_t>(_pin));
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    delay(10);
    touch_pad_set_cnt_mode(static_cast<touch_pad_t>(_pin), TOUCH_PAD_SLOPE_7, TOUCH_PAD_TIE_OPT_HIGH);
    touch_pad_config(static_cast<touch_pad_t>(_pin), 0);
    delay(40);
    touch_pad_read(static_cast<touch_pad_t>(_pin), &valor);
    _initialThreshold = valor * _threshold * THRESHOLD_PERCENTAGE_FACTOR;
    touch_pad_set_thresh(static_cast<touch_pad_t>(_pin), valor * THRESHOLD_MULTIPLIER);
     }
    #else
     Serial.println("Pin no soporta touch nativo o modo touch incorrecto");
    #endif
 
  if (_mode == ADC_PULLDOWN && digitalPinToAnalogChannel(_pin) >= 0) {
     _adcPulldownThreshold = _threshold ? _threshold :  pulldownTHRESHOLD;
     pinMode(_pin, INPUT);
     attachInterrupt(digitalPinToInterrupt(_pin), button_interrupt_handler, RISING);
    }  
  else if (_mode == ADC_NO_RESISTOR && digitalPinToAnalogChannel(_pin) >= 0) { _adcPullupThreshold = _threshold ? _threshold :  pullupTHRESHOLD; }
 }

// Promediar lecturas analógicas
int touchExt::pulldownRead() {
       int val1 = analogRead(_pin);
       if(val1<pulldownTHRESHOLD) { delayMicroseconds(3); int val1 = analogRead(_pin); }
       delayMicroseconds(2);
       int val2 = analogRead(_pin);
       if(val2<pulldownTHRESHOLD) { delayMicroseconds(3); int val2 = analogRead(_pin); }
    return (val1+val2)/2;
}

int touchExt::pullupRead()
{
    pinMode(_pin, OUTPUT);
    //delayMicroseconds(3);   
    digitalWrite(_pin, HIGH);
    //delayMicroseconds(3);
    pinMode(_pin, INPUT_PULLUP);
    //delayMicroseconds(3);
    return analogRead(_pin);
}

// Detectar si el pin está tocado
inline bool touchExt::isTouched() {
  
  #ifdef TOUCH_SUPPORT
  if (_mode == TOUCH_NATIVE) {
        touch_pad_read(static_cast<touch_pad_t>(_pin), &valor);
         return (valor < _initialThreshold);
    }
 else if
 #else
    if 
 #endif
  (_mode == ADC_PULLDOWN) // tecnica aplicable a pines ADC requiere el uso de resistencia de 1M ohm o mas.
        {
          if (interruptTriggered) {
          unsigned long startTime = millis();
         while (millis() - startTime < READ_TIME) {
          int val = pulldownRead();
           if (val > pulldownTHRESHOLD) {  return true;   }
    }
    interruptTriggered = false; // Reabre el ISR
    return false;
  }
 }
 else if (_mode == ADC_NO_RESISTOR) // tecnica a pines adc y no requiere usar resistencias, solo un truco de cambiar el pinmode y por eso no puede usarse interrupciones.
   { 
          unsigned long startTime = millis();
         while (millis() - startTime < READ_TIME) {
          int val = pullupRead();
            if (val < pullupTHRESHOLD) {  return true;   }
    }
    return false;
  }
}

inline long touchExt::_touchTime(unsigned long now) {
    long duration = 0;
    bool touching = isTouched();
  if (_touchStart) { duration = now - _touchStart; } 
  if (touching && !_touchStart) { _touchStart = now; }
   if(!touching) { _touchStart = 0; }    
     return touching ? duration : 0;
}

bool touchExt::isClick() {
    long touchDuration = _touchTime(millis()); // Captura el tiempo una sola vez
    long timeSinceLastTouch = _touchStart - _lastTouchStart;
    if (timeSinceLastTouch > ResetTIME) {_clickCount = 0;}
    if (touchDuration > ClickTIME) {
        if (!_isTouched) {
            _lastTouchStart = _touchStart;
            _clickCount++;
            _isTouched = true;
            return true;
        }
    } 
  else { _isTouched = false; }
    return false;
}

bool touchExt::isClicks(uint8_t count) {
    if (isClick() && _clickCount == count) {
        _clickCount = 0;
        return true;
    }
    return false;
}

bool touchExt::isHold(short holdTime) {     return _touchTime(millis()) > holdTime; }

bool touchExt::isHolded(short holdedTime) {
    bool triggered = false;
    if (isHold(holdedTime) && !_isHolding) {
        _isHolding = true;
        triggered = true;
    }
    if (!isHold(holdedTime)) {
        _isHolding = false;
    }
    return triggered;
}

bool touchExt::isReleased(short releaseTime) {
      bool released = false;
    if (isHold(releaseTime)) { _isHolding = true; }
    if (_isHolding && !isHold(releaseTime)) {
        _isHolding = false;
        released = true;
    }
    return released;
}
#endif
