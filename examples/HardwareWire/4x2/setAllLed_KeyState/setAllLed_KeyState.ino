// ДАННЫЙ ПРИМЕР ОТОБРАЖАЕТ СОСТОЯНИЯ ВСЕХ КЛАВИШ НА ИХ СВЕТОДИОДАХ:// * Строки со звёздочкой являются необязательными.
// (нажимайте кнопки клавиатуры)                                    //
                                                                    //
// Клавиатура 4x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:                     //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                       //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                                    //
#include <Wire.h>                                                   //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
#include <iarduino_I2C_Keyboard.h>                                  //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(0x09,4,2);                                //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указывая адрес модуля на шине I2C, количество кнопок в линии, количество линий с кнопками.
                                                                    //   Если объявить объект без указания адреса (iarduino_I2C_Keyboard kbd(false,4,2);), то адрес будет найден автоматически.
void setup(){                                                       //
    delay(500);                                                     // * Ждём завершение переходных процессов связанных с подачей питания.
    kbd.begin(&Wire); // &Wire1, &Wire2 ...                         //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (по умолчанию &Wire).
}                                                                   //
                                                                    //
void loop(){                                                        //
    uint8_t i = kbd.getKey(KEY_ALL, KEY_STATE);                     //   Получаем флаги текущих состояний всех кнопок в переменную i.
    kbd.setLed(LED_ALL, i);                                         //   Устанавливаем работу всех светодиодов в соответствии с флагами в переменной i.
}                                                                   //   Для клавиатур у которых более 8 кнопок, переменная i определяется типом uint16_t.
                                                                    //
//  ПРИМЕЧАНИЕ:                                                     //
//  Данный пример включает светодиоды в соответствии с состоянием   //
//  их клавиш.                                                      //
//  Попробуйте изменить тип получаемых данных о состоянии кнопок со //
//  значения KEY_STATE на одно из ниже перечисленных:               //
//  KEY_PUSHED   - вернуть 1 только при «нажимании» на клавишу.     //
//  KEY_RELEASED - вернуть 1 только при «отпускании» клавиши.       //
//  KEY_CHANGED  - вернуть 1 и при «нажимании», и при «отпускании». //
//  KEY_STATE    - вернуть состояние кнопки (1-нажата, 0-отпущена). //
//  KEY_TRIGGER  - вернуть состояние переключателя кнопки.          //
//  KEY_HOLD_05  - вернуть дискретное время удержания кнопки.       //
//                 время возвращается числом полусекунд от 0 до 7.  //
//                 время в секундах = полученное число * 0,5 сек.   //
//  Работа со всеми типами описана в примере setLed_KeyState.       //