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
