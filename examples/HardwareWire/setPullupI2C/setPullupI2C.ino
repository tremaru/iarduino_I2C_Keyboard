// ПРИМЕР УПРАВЛЕНИЯ ПОДТЯЖКОЙ ЛИНИЙ ШИНЫ I2C:       // * Строки со звёздочкой являются необязательными.
                                                     //
// Клавиатура 4x2, FLASH-I2C:                        //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                        //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:      //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:        //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                     //
bool flgPullUp = true;                               //   Флаг установки подтяжки линий шины I2C (true - установить, false - сбросить).
                                                     //
#include <Wire.h>                                    //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
#include <iarduino_I2C_Keyboard.h>                   //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(0x09,5,2);                 //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указав адрес модуля на шине I2C (0x09), количество кнопок в линии (5) и количество линий с кнопками (2).
                                                     //   Если объявить объект без указания адреса (iarduino_I2C_Keyboard kbd(false,5,2);), то адрес будет найден автоматически.
void setup(){                                        //
    delay(500);                                      // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                              //   Инициируем передачу данных по шине UART на скорости 9600 бит/сек.
    while(!Serial){;}                                // * Ждём завершения инициализации шины UART.
    kbd.begin(&Wire); // &Wire1, &Wire2 ...          //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (по умолчанию &Wire).
    Serial.print(F("Подтяжка линий шины I2C "));     //
    if(!kbd.setPullI2C(flgPullUp)){                  //   Устанавливаем или сбрасываем подтяжку линий шины I2C (зависит от состояния флага flgPullUp).
        Serial.print(F("не поддерживается"));        //   Если функция setPullI2C() вернула false значит управление подтяжкой не поддерживается модулем.
    }else{                                           //   Если функция setPullI2C() вернула true значит подтяжка был успешно сброшена или установлена (зависит от состояния флага flgPullUp).
        if(!kbd.getPullI2C()){Serial.print("не");}   //   Функция getPullI2C() возвращает наличие включённой модулем подтяжки линий шины I2C.
        Serial.print(F(" установлена"));             //
    }   Serial.println(F(" модулем."));              //
}                                                    //
                                                     //
void loop(){                                         //
}                                                    //
                                                     //
//  ПРИМЕЧАНИЕ:                                      //
//  Установка или сброс подтяжки линий шины I2C,     //   Для отключения подтяжки линий шины I2C модулем,
//  обращением к функции setPullI2C(), сохраняется в //   присвойте флагу flgPullUp (в начале скетча)
//  энергонезависимой памяти модуля.                 //   значение false вместо true.
//                                                   //
//  Не используйте функцию setPullI2C() если Вы не   //
//  знаете зачем нужна подтяжка линий шины I2C.      //