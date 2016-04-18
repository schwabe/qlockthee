/**
 * LedDriverLPD8806
 * Implementierung auf der Basis von LPD8806-Streifen.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  9.2.2015
 * @updated  16.2.2015
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 *
 * Verkabelung: Einspeisung oben links, dann schlangenfoermig runter,
 * dann Ecke unten links, oben links, oben rechts, unten rechts.
 *
 * Achtung! LPD8806-Streifen koennen nur in Vielfachen von 2 getrennt werden! Daher bleiben am Rand LEDs uebrig (und dunkel)!
 *
 */
#ifndef LED_DRIVER_LPD8806_H
#define LED_DRIVER_LPD8806_H

#include "Arduino.h"
#include "LedDriver.h"
#include <LPD8806.h>

class LedDriverLPD8806 : public LedDriver {
public:
    LedDriverLPD8806(byte dataPin, byte clockPin);

    void init();

    void printSignature();

    void writeScreenBufferToMatrix(word matrix[16], boolean onChange);

    void setBrightness(byte brightnessInPercent);
    byte getBrightness();

    void setLinesToWrite(byte linesToWrite);

    void shutDown();
    void wakeUp();

    void clearData();

private:
    byte _brightnessInPercent;

    boolean _dirty;

    void _setPixel(byte x, byte y, uint32_t c);
    void _setPixel(byte num, uint32_t c);

    uint32_t _wheel(byte wheelPos);

    void _clear();

    byte _brightnessScaleColor(byte colorPart);

    byte _dataPin, _clockPin;
    LPD8806 *_strip;
};

#endif
