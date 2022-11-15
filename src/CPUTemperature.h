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
	- настройка параметра смещения (компансации, offset) температуры
	- настройка параметра прироста (gain) температуры
	
	MIT License
	
	Версии:
	v1.0 - релиз
	v1.1 - добавлен параметр настройки усиления (прироста) gain температуры
	для более точной настройки (без объявления установлен по умолчанию - 1.22)
*/

#pragma once
#include <Arduino.h>
class CPUTemperature {
public:
	CPUTemperature(double tempOffset = 324.31, double tempGain = 1.22) { // 324.31, 1.22 - параметры по умолчанию
		_tempOffset = tempOffset;
		_tempGain = tempGain;
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
		return (wADC - _tempOffset ) / _tempGain;
	}

private:
	double _tempOffset;
	double _tempGain;
};