# CPUTemperature
### Библиотека для получения температуры процессора микроконтроллеров AVR

## Содержание
- [Совместимость](#compatibility)
- [Возможности](#capabilities)
- [Пример](#example)
- [Версии](#versions)

<a id="compatibility"></a>
## Совместимость
- ATmega8 : No
- ATmega8L : No
- ATmega8A : No
- ATmega168 : No
- ATmega168A : Yes
- ATmega168P : Yes
- ATmega328 : Yes
- ATmega328P : Yes
- ATmega1280 (Arduino Mega) : No
- ATmega2560 (Arduino Mega 2560) : No
- ATmega32U4 (Arduino Leonardo) : Yes

`Канал 8 невозможно больше использовать с функцией analogRead`

<a id="capabilities"></a>
## Возможности
- получение температуры процессора
- настройка параметра смещения температуры

<a id="example"></a>
## Пример
```cpp
#include <CPUTemperature.h>
CPUTemperature temp (331.0);//объявляем конструктор с калибровочным значением (зависит от питания, подобрать)
//CPUTemperature temp // можно не указывать параметры (будет по умолчанию - 324.31)

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {
  Serial.println(temp.getCPUTemp());
  delay(1000);
}
```

<a id="versions"></a>
## Версии
- v1.0 - релиз
