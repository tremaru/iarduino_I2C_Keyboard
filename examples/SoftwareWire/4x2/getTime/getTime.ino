// ДАННЫЙ ПРИМЕР РЕАГИРУЕТ НА УДЕРЖАНИЕ КЛАВИШ КЛАВИАТУРЫ:          // * Строки со звёздочкой являются необязательными.
// (удерживайте кнопки клавиатуры)                                  //
                                                                    //
// Требуется установить библиотеку <iarduino_I2C_Software.h>        //   https://iarduino.ru/file/627.html
                                                                    //
// Клавиатура 4x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:                     //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                       //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                                    //
#include <iarduino_I2C_Software.h>                                  //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
SoftTwoWire sWire(3,4);                                             //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                                    //
#include <iarduino_I2C_Keyboard.h>                                  //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(0x09,4,2);                                //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указывая адрес модуля на шине I2C, количество кнопок в линии, количество линий с кнопками.
                                                                    //   Если объявить объект без указания адреса (iarduino_I2C_Keyboard kbd(false,4,2);), то адрес будет найден автоматически.
void setup(){                                                       //
    delay(500);                                                     // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                                             //   Инициируем передачу данных по шине UART на скорости 9600 бит/сек.
    while(!Serial){;}                                               // * Ждём завершения инициализации шины UART.
    kbd.begin(&sWire);                                              //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (по умолчанию &Wire).
    kbd.setEncoding(4,1,'w');                                       // * Присваиваем 4 кнопке в 1 ряду символ 'w'.
}                                                                   //   (по умолчанию кнопкам присвоены символы "12345678").
                                                                    //
void loop(){                                                        //
//  Выполняем действия по событию нажатия клавиши:                  //
    if(kbd.getTime(2,1,KEY_HOLD)>2000){Serial.println("2к в 1р");}  //   Если 2 кнопка в 1 ряду удерживается тольше 2 секунд, то выводим сообщение.
    if(kbd.getTime(3,2,KEY_HOLD)>3000){Serial.println("3к в 2р");}  //   Если 3 кнопка в 2 ряду удерживается тольше 3 секунд, то выводим сообщение.
    if(kbd.getTime('w',KEY_HOLD)>4000){Serial.println("4к в 1р");}  //   Так как функцией setEncoding(), в коде Setup(), 4 кнопке 1 ряда был присвоен символ 'w', то обращаться к этой кнопке можно либо по номеру и ряду, либо по привоенному ей символу.
}                                                                   //
                                                                    //
//  ПРИМЕЧАНИЕ:                                                     //
//  Данный пример реагирует на удержание кнопок (KEY_HOLD) проверяя //
//  длительность удержания.                                         //
//  Если вместо KEY_HOLD указать KEY_FREE, то функция getTime()     //
//  будет возвращать не время удержания, а время простоя кнопки.    //
//  Если Вам нужно узнать время удержания кнопки с точностью до 1/2 //
//  секунд, то лучше воспользоваться функцией getKey() указав в     //
//  качестве типа получаемых данных, значение KEY_HOLD_05.          //
//  см. примечание в примере getKeyState.                           //