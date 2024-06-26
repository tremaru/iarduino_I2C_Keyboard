// ПРИМЕР СМЕНЫ АДРЕСА МОДУЛЯ:                       // * Строки со звёздочкой являются необязательными.
                                                     //
// Клавиатура 4x2, FLASH-I2C:                        //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                        //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:      //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:        //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                     //
// Данный скетч демонстрирует не только              //
// возможность смены адреса на указанный в           //
// переменной newAddress, но и обнаружение,          //
// и вывод текущего адреса модуля на шине I2C.       //
                                                     //
// Библиотека <iarduino_I2C_Keyboard.h>              //
// предназначена для работы с клавиатурами I2C-flash //
// и меняет только их адреса.                        //
// Но, в разделе Файл/Примеры/.../findSortDevices    //
// находятся примеры смены и сортировки адресов      //
// любых модулей iarduino серии Flash I2C.           //
                                                     //
uint8_t newAddress = 0x09;                           //   Назначаемый модулю адрес (0x07 < адрес < 0x7F).
                                                     //
#include <Wire.h>                                    //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
#include <iarduino_I2C_Keyboard.h>                   //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(false,5,2);                //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указав количество кнопок в линии (5) и количество линий с кнопками (2).
                                                     //   Если при объявлении объекта указать адрес, например, kbd(0xBB,5,2), то пример будет работать с тем модулем, адрес которого был указан.
void setup(){                                        //
    delay(500);                                      // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                              //   Инициируем передачу данных по шине UART на скорости 9600 бит/сек.
    while(!Serial){;}                                // * Ждём завершения инициализации шины UART.
    if( kbd.begin(&Wire) ){                          //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (Wire, Wire1, Wire2 ...).
        Serial.print("Найдена клавиатура 0x");       //
        Serial.println( kbd.getAddress(), HEX );     //   Выводим текущий адрес модуля.
        if( kbd.changeAddress(newAddress) ){         //   Меняем адрес модуля на newAddress.
            Serial.print("Адрес изменён на 0x");     //
            Serial.println( kbd.getAddress(), HEX ); //   Выводим текущий адрес модуля.
        }else{                                       //
            Serial.println("Адрес не изменён!");     //
        }                                            //
    }else{                                           //
        Serial.println("Клавиатура не найдена!");    //
    }                                                //
}                                                    //
                                                     //
void loop(){                                         //
}                                                    //
