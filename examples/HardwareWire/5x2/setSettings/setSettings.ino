// ДАННЫЙ ПРИМЕР ПОСИМВОЛЬНО ВЫВОДИТ СТРОКУ:         // * Строки со звёздочкой являются необязательными.
// (нажимайте или удерживайте кнопки клавиатуры)     //
                                                     //
// Клавиатура 4x2, FLASH-I2C:                        //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                        //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:      //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:        //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                     //
#include <Wire.h>                                    //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
#include <iarduino_I2C_Keyboard.h>                   //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(0x09,5,2);                 //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указывая адрес модуля на шине I2C, количество кнопок в линии, количество линий с кнопками.
                                                     //   Если объявить объект без указания адреса (iarduino_I2C_Keyboard kbd(false,5,2);), то адрес будет найден автоматически.
void setup(){                                        //
    delay(500);                                      // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                              //   Инициируем передачу данных по шине UART на скорости 9600 бит/сек.
    while(!Serial){;}                                // * Ждём завершения инициализации шины UART.
    kbd.begin(&Wire); // &Wire1, &Wire2 ...          //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (по умолчанию &Wire).
    kbd.setEncoding("abcde01234");                   // * Присваиваем символы всем кнопкам клавиатуры. По умолчанию кнопкам присвоены символы "1234567890".
    kbd.setEncoding(5,1,'f');                        // * Символ можно присвоить каждой кнопке по отдельности (присвоить 5 кнопке, в 1 ряду, символ 'f').
    kbd.setEncoding(5,2,'\n');                       // * Символ можно присвоить каждой кнопке по отдельности (присвоить 5 кнопке, в 2 ряду, символ '\n' - перенос строки).
//  Определяем скорость повтора нажатой кнопки:      //
    kbd.setDelay(1000);                              // * Указываем что удержание кнопки наступает через 1000 мс после её нажатия. Допускаются значения от 100мс до 25'500мс (по умолчанию 500 мс).
    kbd.setPeriod(10);                               // * Указываем что при удержании кнопки, её символы должны повторться каждые 10 мс. Допускаются значения от 10мс до 2'550мс (по умолчанию 50 мс).
}                                                    //
                                                     //
void loop(){                                         //
//  Получаем и выводим символы с клавиатуры:         //
    if( kbd.available() ){                           //   Если в буфере истории нажатий кнопок есть символы, то ...
        Serial.print( kbd.readChar() );              //   Выводим очередной символ из буфера истории нажатий кнопок.
    }                                                //
}                                                    //
                                                     //
//  ПРИМЕЧАНИЕ:                                      //
//  Задержка до удержания кнопки setDelay() и        //
//  скорость повтора setPeriod() сохраняются в       //
//  энергонезависимой памяти модуля клавиатуры.      //


