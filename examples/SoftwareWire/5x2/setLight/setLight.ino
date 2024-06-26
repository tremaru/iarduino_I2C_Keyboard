// ДАННЫЙ ПРИМЕР УПРАВЛЯЕТ ЯРКОСТЬЮ СВЕТОДИОДОВ:             // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// Клавиатура 4x2, FLASH-I2C:                                //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                                //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_Keyboard.h>                           //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(0x09,5,2);                         //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указывая адрес модуля на шине I2C, количество кнопок в линии, количество линий с кнопками.
                                                             //   Если объявить объект без указания адреса (iarduino_I2C_Keyboard kbd(false,5,2);), то адрес будет найден автоматически.
void setup(){                                                //
    delay(500);                                              // * Ждём завершение переходных процессов связанных с подачей питания.
    kbd.begin(&sWire);                                       //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (по умолчанию &Wire).
    kbd.setLight( 7 );                                       //   Устанавливаем максимальную яркость свечения светодиодов.
    kbd.setLed(KEY_ALL,0b1111111111);                        //   Включаем все светодиоды.
}                                                            //
                                                             //
void loop(){                                                 //
}                                                            //
                                                             //
//  ПРИМЕЧАНИЕ:                                              //
//  Яркость светодиодов, устанавливаемая функцией setLight() //
//  сохраняется в энергонезависимой памяти модуля клавиатуры.//
//  Не используйте функию setLight() в циклах.               //
