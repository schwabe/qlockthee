/**
 * Settings
 * Die vom Benutzer getaetigten Einstellungen werden hier verwaltet
 * und im EEPROM persistiert.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.3
 * @created  23.1.2013
 * @updated  16.2.2015
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - LDR-Modus aufgenommen.
 * V 1.2:  - Brightness aufgenommen.
 *         - EnableAlarm aufgenommen.
 *         - DcfSignalIsInverted aufgenommen.
 *         - TimeShift aufgenommen.
 * V 1.3:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 */
#include "Settings.h"
#include <EEPROM.h>
#include "Renderer.h"

#define SETTINGS_MAGIC_NUMBER 0xCA
#define SETTINGS_VERSION 4

/**
 *  Konstruktor.
 */
Settings::Settings() {
    _language = LANGUAGE_DE_DE;
    _renderCornersCw = true;
    _use_ldr = true;
    _brightness = 75;
    _enableAlarm = false;
    _dcfSignalIsInverted = false;
    _timeShift = 0;

    // Versuche alte Einstellungen zu laden...
    loadFromEEPROM();
}

/**
 * Die Sprache. Werte siehe Renderer.h
 */
byte Settings::getLanguage() {
    return _language;
}

void Settings::setLanguage(byte language) {
    _language = language;
}

/**
 * Die Laufrichtung der Eck-LEDs.
 */
boolean Settings::getRenderCornersCw() {
    return _renderCornersCw;
}

void Settings::setRenderCornersCw(boolean cw) {
    _renderCornersCw = cw;
}

/**
 * Der LDR-Modus.
 */
boolean Settings::getUseLdr() {
    return _use_ldr;
}

void Settings::setUseLdr(boolean useLdr) {
    _use_ldr = useLdr;
}

/**
 * Die Helligkeit.
 */
byte Settings::getBrightness() {
    return _brightness;
}

void Settings::setBrightness(byte brightness) {
    _brightness = brightness;
}

/**
 * Wecker enablen?
 */
boolean Settings::getEnableAlarm() {
    return _enableAlarm;
}

void Settings::setEnableAlarm(boolean enableAlarm) {
    _enableAlarm = enableAlarm;
}

/**
 * Ist das DCF-Signal invertiert?
 */
boolean Settings::getDcfSignalIsInverted() {
    return _dcfSignalIsInverted;
}

void Settings::setDcfSignalIsInverted(boolean dcfSignalIsInverted) {
    _dcfSignalIsInverted = dcfSignalIsInverted;
}

/**
 * Zeitverschiebung
 */
char Settings::getTimeShift() {
    return _timeShift;
}

void Settings::setTimeShift(char timeShift) {
    _timeShift = timeShift;
}

/**
 * Die Einstellungen laden.
 */
void Settings::loadFromEEPROM() {
    if ((EEPROM.read(0) == SETTINGS_MAGIC_NUMBER) && (EEPROM.read(1) == SETTINGS_VERSION)) {
        // es sind gueltige Einstellungen vorhanden...
        _language = EEPROM.read(2);
        _renderCornersCw = EEPROM.read(3);
        _use_ldr = EEPROM.read(4);
        _brightness = EEPROM.read(5);
        _enableAlarm = EEPROM.read(6);
        _dcfSignalIsInverted = EEPROM.read(7);
        _timeShift = EEPROM.read(8);
    }
}

/**
 * Die Einstellungen speichern.
 */
void Settings::saveToEEPROM() {
    if (EEPROM.read(0) != SETTINGS_MAGIC_NUMBER) {
        EEPROM.write(0, SETTINGS_MAGIC_NUMBER);
    }
    if (EEPROM.read(1) != SETTINGS_VERSION) {
        EEPROM.write(1, SETTINGS_VERSION);
    }
    if (EEPROM.read(2) != _language) {
        EEPROM.write(2, _language);
    }
    if (EEPROM.read(3) != _renderCornersCw) {
        EEPROM.write(3, _renderCornersCw);
    }
    if (EEPROM.read(4) != _use_ldr) {
        EEPROM.write(4, _use_ldr);
    }
    if (EEPROM.read(5) != _brightness) {
        EEPROM.write(5, _brightness);
    }
    if (EEPROM.read(6) != _enableAlarm) {
        EEPROM.write(6, _enableAlarm);
    }
    if (EEPROM.read(7) != _dcfSignalIsInverted) {
        EEPROM.write(7, _dcfSignalIsInverted);
    }
    if (EEPROM.read(8) != _timeShift) {
        EEPROM.write(8, _timeShift);
    }
}
