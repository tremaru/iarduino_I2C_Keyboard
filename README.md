[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

**This is a library for Arduino IDE. It allows to work with [Joystick](https://iarduino.ru/shop/Expansion-payments/dzhoystik-i2c---flash-trema-modul.html) module made by iArduino.ru**

**Данная библиотека для Arduino IDE позволяет работать с модулем [Джойстик](https://iarduino.ru/shop/Expansion-payments/dzhoystik-i2c---flash-trema-modul.html) от [iArduino.ru](https://iarduino.ru)**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте на нашей [wiki](https://wiki.iarduino.ru/page/joystick-i2c/#h3_3)


| Модель | Ссылка на магазин |
|---|---|
| <p></p> <img src="https://wiki.iarduino.ru/img/resources/1235/1235.svg" width="100px"></img>| https://iarduino.ru/shop/Expansion-payments/dzhoystik-i2c---flash-trema-modul.html |

## Назначение функций:

**Подключаем библиотеку** 

```C++
#include <iarduino_I2C_Joystick> // Подключаем библиотеку iarduino_I2C_Joystick для работы с модулем.
```

**Создаём объект** 

```C++
iarduino_I2C_Joystick ОБЪЕКТ; // Создаём объект для работы с методами библиотеки без указания адреса модуля на шине I2C.

iarduino_I2C_Joystick ОБЪЕКТ( АДРЕС ); // Создаём объект для работы с методами библиотеки указывая адрес модуля на шине I2C.
```

**Инициализация работы** 

```C++
ОБЪЕКТ.begin(); // Инициализация работы с модулем.
```

**Изменение адреса модуля** 

```C++
ОБЪЕКТ.changeAddress( АДРЕС ); // Изменение адреса модуля на шине I2C.
```

**Перезагрузка модуля**

```C++
ОБЪЕКТ.reset(); // Перезагрузка модуля.
```

**Получение текущего адреса** 

```C++
ОБЪЕКТ.getAddress(); // Получение текущего адреса модуля на шине I2C.
```

**Получение версии прошивки** 

```C++
ОБЪЕКТ.getVersion(); // Получение версии прошивки модуля.
```

**Запрос текущей X координаты** 

```C++
ОБЪЕКТ.getPosition_X(); // Запрос текущей координаты джойстика по оси X.
```

**Запрос текущей Y координаты** 

```C++
ОБЪЕКТ.getPosition_Y(); // Запрос текущей координаты джойстика по оси Y.
```

**Запрос текущих координат** 

```C++
ОБЪЕКТ.getPosition( X , Y ); // Запрос текущих координат по осям X и Y.
```

**Запрос значений АЦП оси X** 

```C++
ОБЪЕКТ.getADC_X(); // Запрос сырого значения АЦП по оси X.
```

**Запрос значений АЦП оси Y** 

```C++
ОБЪЕКТ.getADC_Y(); // Запрос сырого значения АЦП по оси Y.
```

**Запрос значений АЦП** 

```C++
ОБЪЕКТ.getADC( X , Y ); // Запрос сырых значений АЦП по осям X и Y.
```

**Получение состояний кнопки**

```C++
ОБЪЕКТ.getButton( ЗАПРОС ); // Получение времени, состояния, или события кнопки.
```

**Калибровка координат X** 

```C++
ОБЪЕКТ.setCalibration_X( ЛЕВО , ЦЕНТР , ПРАВО ); // Калибровка координат по оси X.
```

**Калибровка координат Y** 

```C++
ОБЪЕКТ.setCalibration_Y( НИЗ , ЦЕНТР , ВЕРХ ); // Калибровка координат по оси Y.
```

**Запрос калибровочных значений X** 

```C++
ОБЪЕКТ.getCalibration_X( ЛЕВО , ЦЕНТР , ПРАВО ); // Запрос калибровочных значений.
```

**Запрос калибровочных значений Y** 

```C++
ОБЪЕКТ.getCalibration_Y( НИЗ , ЦЕНТР , ВЕРХ ); // Запрос калибровочных значений.
```

**Установка мертвой зоны** 

```C++
ОБЪЕКТ.setDeadZone( ЗОНА ); // Установка мертвой зоны центрального положения.
```

**Установка усреднения показаний** 

```C++
ОБЪЕКТ.setAveraging( КОЭФФИЦИЕНТ ); // Установка коэффициента усреднения показаний.
```

