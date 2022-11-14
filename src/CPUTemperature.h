/*
	Библиотека для получения температуры процессора микроконтроллеров AVR
	GitHub: https://github.com/alexkor433/CPUTemp.git
	
	Совместимость:
	ATmega8 : No
	ATmega8L : No
	ATmega8A : No
	ATmega168 : No
	ATmega168A : Yes
	ATmega168P : Yes
	ATmega328 : Yes
	ATmega328P : Yes
	ATmega1280 (Arduino Mega) : No
	ATmega2560 (Arduino Mega 2560) : No
	ATmega32U4 (Arduino Leonardo) : Yes
	
	Возможности:
	- получение температуры процессора
	- настройка параметра смещения температуры
	
	MIT License
	
	Версии:
	v1.0 - релиз
*/

#pragma once
#include <Arduino.h>
class CPUTemperature {
public:
	CPUTemperature(double tempSizing = 324.31) { // 324.31 - параметр по умолчанию
		_tempSizing = tempSizing;
	}

	double getCPUTemp(void) {
		unsigned int wADC;

		/*Измерение внутренней температуры должно использоваться
		с внутренним опорным напряжением 1.1V.
		8 канал не может больше использоваться с
		функцией analogRead.*/

		// Установка опорного напряжения и мультиплексора.
		ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
		ADCSRA |= _BV(ADEN);  // Включение АЦП

		delay(20);            // ждём пока напряжение стабилизируется.

		ADCSRA |= _BV(ADSC);  // Старт АЦП

		// Определение окончания конверсии
		while (bit_is_set(ADCSRA, ADSC));

		// Чтение регистра "ADCW" позаботится о том, как читать ADCL и ADCH.
		wADC = ADCW;

		// Температура в градусах Цельсия
		return (wADC - _tempSizing ) / 1.22;
	}

private:
	double _tempSizing;
};