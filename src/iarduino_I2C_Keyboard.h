//	Библиотека для работы с модулями клавиатура, I2C-flash для Arduino: https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
//  Версия: 1.0.4
//  Последнюю версию библиотеки Вы можете скачать по ссылке: https://iarduino.ru/file/528.html
//  Подробное описание функций бибилиотеки доступно по ссылке: https://wiki.iarduino.ru/page/keyboard-i2c-flash/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел.
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_I2C_Keyboard_h																														//
#define iarduino_I2C_Keyboard_h																														//
																																					//
#if defined(ARDUINO) && (ARDUINO >= 100)																											//
#include		<Arduino.h>																															//
#else																																				//
#include		<WProgram.h>																														//
#endif																																				//
																																					//
#include		"iarduino_I2C_Keyboard_I2C.h"																										//	Подключаем библиотеку выбора реализации шины I2C.
																																					//
#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega2560__) || defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(RENESAS_CORTEX_M4) // Если подключена библиотека Wire или платы её поддерживают...
#include		<Wire.h>																															//	Разрешаем использовать библиотеку Wire в данной библиотеке.
#endif																																				//
#if defined( iarduino_I2C_Software_h )																												//	Если библиотека iarduino_I2C_Software подключена в скетче...
#include		<iarduino_I2C_Software.h>																											//	Разрешаем использовать библиотеку iarduino_I2C_Software в данной библиотеке.
#endif																																				//
																																					//
#define			DEF_CHIP_ID_FLASH		0x3C																										//	ID линейки чипов - константа для всех чипов серии Flash (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_CHIP_ID_METRO		0xC3																										//	ID линейки чипов - константа для всех чипов серии Metro (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_MODEL_KBD			0x13																										//	Идентификатор модели - константа.
//				Адреса регистров модуля:																											//
#define			REG_FLAGS_0				0x00																										//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_0				0x01																										//	Адрес регистра битов  управления для чтения и записи.
#define			REG_FLAGS_1				0x02																										//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_1				0x03																										//	Адрес регистра битов  управления для чтения и записи.
#define			REG_MODEL				0x04																										//	Адрес регистра содержащего номер типа модуля.
#define			REG_VERSION				0x05																										//	Адрес регистра содержащего версию прошивки.
#define			REG_ADDRESS				0x06																										//	Адрес регистра содержащего текущий адрес модуля на шине I2C. Если адрес указан с флагом IF-PIN-ADDRES то адрес установится (и запишется в регистр) только при наличии 1 на входе PIN_ADDRES.
#define			REG_CHIP_ID				0x07																										//	Адрес регистра содержащего ID линейки чипов «Flash». По данному ID можно определить принадлежность чипа к линейки «Flash».
#define			REG_KBD_KEYS			0x10																										//	Адрес регистра содержащего флаги состояния и событий первой из 10 кнопок.
#define			REG_KBD_LED_L			0x1A																										//	Адрес регистра содержащего биты управления первой пятёркой светодиодов.
#define			REG_KBD_LED_H			0x1B																										//	Адрес регистра содержащего биты управления второй пятёркой светодиодов.
#define			REG_KBD_FIFO_HOLD		0x1C																										//	Адрес регистра содержащего время удержания кнопки (в десятых долях секунд) после которого начнётся цикл заполнения буфера FIFO номером удерживаемой кнопки.
#define			REG_KBD_FIFO_REPLAY		0x1D																										//	Адрес регистра содержащего период (в сотых долях секунд) цикла заполнения буфера FIFO номером удерживаемой кнопки.
#define			REG_KBD_FIFO_COUNTER	0x1E																										//	Адрес регистра содержащего счётчик буфера FIFO (содержит количество байт в буфере). Запись любого значения приведёт к сбросу регистра и очистке буфера FIFO.
#define			REG_KBD_FIFO			0x1F																										//	Адрес регистра содержащего данные  буфера FIFO (строка из номеров кнопок является историей их нажатий). Чтение данных из этого регистра не приводит к увеличению адреса регистра. Запись значения 0x00 приводит к очистке всего буфера FIFO.
#define			REG_KBD_TIME_KEYS		0x20																										//	Адрес регистра содержащего время удержания или простоя первой из 10 кнопок (в десятых долях секунд). Счетчик времени удержания останавливается на значении 255 (25,5сек).
#define			REG_KBD_ANIMATION		0x2A																										//	Адрес регистра содержащего номер светодиодной анимации.
#define			REG_KBD_TIME_ANIM		0x2B																										//	Адрес регистра содержащего время свечения светодиода при выполнении анимации.
//				Позиция битов и флагов:																												//
#define			KBD_FLG_PUSHED			0x80																										//	Флаг нажатия на кнопку.			Устанавливается в момент нажатия на кнопку и остаётся установленным пока не будет прочитан. Флаг сбрасывается самостоятельно после чтении регистра «REG_KEY».
#define			KBD_FLG_RELEASED		0x40																										//	Флаг отпускания кнопки.			Устанавливается в момент отпускания кнопки и остаётся установленным пока не будет прочитан. Флаг сбрасывается самостоятельно после чтении регистра «REG_KEY».
#define			KBD_FLG_CHANGED			0x20																										//	Флаг смены состояния кнопки.	Устанавливается в момент нажатия или отпускания кнопки и остаётся установленным пока не будет прочитан. Флаг сбрасывается самостоятельно после чтении регистра «REG_KEY».
#define			KBD_FLG_STATE			0x10																										//	Флаг состояния кнопки.			Установлен пока кнопка нажата и сброшен если она отпущена.
#define			KBD_FLG_TRIGGER			0x08																										//	Флаг триггер.					Меняет своё состояние с каждым новым нажатием на кнопку (нажали - установился, нажали - сбросился, нажали - установился, ...).
#define			KBD_TIM_HOLD			0x07																										//	время удержания кнопки.			Устанавливается если кнопка удерживается дольше времени указанного в регистре «REG_TIME_HOLD_3» и сбрасывается при отпускании кнопки.
																																					//
#ifndef			KEY_PUSHED																															//
#define			KEY_PUSHED				1																											//	getKey( - , нажимается ).
#endif																																				//
																																					//
#ifndef			KEY_RELEASED																														//
#define			KEY_RELEASED			2																											//	getKey( - , отпускается ).
#endif																																				//
																																					//
#ifndef			KEY_STATE																															//
#define			KEY_STATE				3																											//	getKey( - , нажата ).
#endif																																				//
																																					//
#ifndef			KEY_TRIGGER																															//
#define			KEY_TRIGGER				4																											//	getKey( - , переключатель ).
#endif																																				//
																																					//
#ifndef			KEY_HOLD_05																															//
#define			KEY_HOLD_05				5																											//	getKey( - , удерживается ).
#endif																																				//
																																					//
#ifndef			KEY_HOLD																															//
#define			KEY_HOLD				6																											//	getTime( время удержания ).
#endif																																				//
																																					//
#ifndef			KEY_FREE																															//
#define			KEY_FREE				7																											//	getTime( время простоя ).
#endif																																				//
																																					//
#ifndef			KEY_CHANGED																															//
#define			KEY_CHANGED				8																											//	getKey( - , состояние изменилось ).
#endif																																				//
																																					//
#ifndef			KEY_ALL																																//
#define			KEY_ALL					0xFF																										//	getKey( все кнопки, - ).
#endif																																				//
																																					//
#ifndef			LED_ALL																																//
#define			LED_ALL					0xFF																										//	setLed( все светодиоды, - ).
#endif																																				//
																																					//
class iarduino_I2C_Keyboard{																														//
	public:																																			//
	/**	Конструктор класса **/																														//
		iarduino_I2C_Keyboard						(uint8_t address=0, uint8_t cols=5, uint8_t rows=2){											//	Конструктор класса													(Параметры: address - адрес модуля на шине I2C, если не указан (=0), то адрес будет определён, cols - количество кнопок в линии, rows - количество линий с кнопками).
													if(address>0x7F){ address>>=1; }																//	Корректируем адрес, если он указан с учётом бита RW.
							valAddrTemp			=	address;																						//	Сохраняем переданный адрес модуля.
							valCols				=	cols;																							//	Сохраняем переданное количество кнопок в одной линии.
							valRows				=	rows;																							//	Сохраняем переданное количество линий с кнопками.
							selI2C				=	new iarduino_I2C_Select;																		//	Переопределяем указатель selI2C на объект производного класса iarduino_I2C_Select.
		}																																			//
	/**	Пользовательские функции **/																												//
		#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__)																			//
		bool				begin					(TwoWire* i=&Wire		){ selI2C->init(i); return _begin(); }									//	Определяем функцию инициализации модуля								(Параметр:  объект для работы с аппаратной шиной I2C).
		#endif																																		//
		#if defined(iarduino_I2C_Software_h)																										//
		bool				begin					(SoftTwoWire* i			){ selI2C->init(i); return _begin(); }									//	Определяем функцию инициализации модуля								(Параметр:  объект для работы с программной шиной I2C).
		#endif																																		//
		bool				reset					(void					);																		//	Объявляем  функцию перезагрузки модуля								(Параметр:  отсутствует).
		bool				changeAddress			(uint8_t				);																		//	Объявляем  функцию смены адреса модуля на шине I2C					(Параметр:  новый адрес модуля).
		uint8_t				getAddress				(void					){ return valAddr;	}													//	Определяем функцию возвращающую текущий адрес модуля на шине I2C	(Параметр:  отсутствует).
		uint8_t				getVersion				(void					){ return valVers;	}													//	Определяем функцию возвращающую текущую версию прошивки модуля		(Параметр:  отсутствует).
		bool				getPullI2C				(void					);																		//	Определяем функцию возвращающую флаг наличия подтяжки шины I2C		(Параметр:  отсутствует).
		bool				setPullI2C				(bool=true				);																		//	Определяем функцию установки подтяжки шины I2C						(Параметр:  флаг подтяжки).
		uint8_t				available				(void					);																		//	Определяем функцию получения количества байтов доступных для чтения	(Параметр:  отсутствует).
		char				readChar				(void					);																		//	Определяем функцию чтения одного символа из буфера истории			(Параметр:  отсутствует).
		uint8_t				readString				(char*,uint8_t,bool=true);																		//	Определяем функцию чтения строки из буфера истории нажатий клавиш	(Параметры: строка получатель, ограничение размера (1-254), флаг символа конца строки).
		void				flush					(void					);																		//	Определяем функцию очистки буфера истории нажатий клавиш			(Параметр:  отсутствует).
		void				setEncoding				(uint8_t, uint8_t, char	);																		//	Определяем функцию присвоения символа кнопке						(Параметры: номер кнопки в ряду (1-5), номер ряда кнопки (1-3), символ присваиваемый кнопке (кроме символа с кодом 255)).
		void				setEncoding				(const char*			);																		//	Определяем функцию присвоения символов множеству кнопок				(Параметры: строка присваиваемых символов).
		void				setEncoding				(String i				){char j[i.length()+1]; i.toCharArray(j,i.length()+1); setEncoding(j);}	//	Объявляем  функцию присвоения символов множеству кнопок				(Параметры: строка присваиваемых символов).
		char				getEncoding				(uint8_t, uint8_t		);																		//	Определяем функцию получения символа присвоенного кнопке			(Параметры: номер кнопки в ряду (1-5), номер ряда кнопки (1-3), символ присваиваемый кнопке (кроме символа с кодом 255)).
		uint8_t				getEncoding				(const char				);																		//	Определяем функцию получения порядкового номера кнопки по символу	(Параметр:  символ присвоенный кнопке).
		void				setDelay				(uint16_t				);																		//	Определяем функцию установки задержки до удержания кнопки			(Параметр:  время до 25'500 мс).
		uint16_t			getDelay				(void					);																		//	Определяем функцию получения задержки до удержания кнопки			(Параметр:  отсутствует).
		void				setPeriod				(uint16_t				);																		//	Определяем функцию установки периода повтора записи удержив. кнопки	(Параметр:  время до 2'550 мс).
		uint16_t			getPeriod				(void					);																		//	Определяем функцию получения периода повтора записи удержив. кнопки	(Параметр:  отсутствует).
		uint16_t			getKey					(uint8_t,uint8_t,uint8_t);																		//	Определяем функцию получения состояния, события или времени кнопки	(Параметры: номер кнопки в ряду (1-5), номер ряда кнопки (1-3), тип получаемого состояния или собития).
		uint16_t			getKey					(char   ,        uint8_t);																		//	Определяем функцию получения состояния, события или времени кнопки	(Параметры: символ присвоенный кнопке или значение KEY_ALL, тип получаемого состояния или собития).
		uint16_t			getTime					(uint8_t,uint8_t,uint8_t);																		//	Определяем функцию получения времени удержания/простоя кнопки в мс	(Параметры: номер кнопки в ряду (1-5), номер ряда кнопки (1-3), тип получаемого времени).
		uint16_t			getTime					(char   ,        uint8_t);																		//	Определяем функцию получения времени удержания/простоя кнопки в мс	(Параметры: символ присвоенный кнопке, тип получаемого времени).
		void				setLed					(uint8_t,uint8_t,uint16_t);																		//	Определяем функцию установки состояния светодиода					(Параметры: номер светодиода в ряду (1-5), номер ряда светодиода (1-3), флаг(и) устанавливаемого состояния светодиода (0/1)).
		void				setLed					(char   ,        uint16_t);																		//	Определяем функцию установки состояния светодиода(ов)				(Параметры: символ присвоенный кнопке светодиода или значение LED_ALL, флаг(и) устанавливаемого состояния светодиода (0/1)).
		uint16_t			getLed					(uint8_t, uint8_t		);																		//	Определяем функцию получения состояния светодиода					(Параметры: номер светодиода в ряду (1-5), номер ряда светодиода (1-3)).
		uint16_t			getLed					(char					);																		//	Определяем функцию получения состояния светодиода(ов)				(Параметр:  символ присвоенный кнопке светодиода или значение LED_ALL).
		void				setLight				(uint8_t,uint8_t=LED_ALL);																		//	Определяем функцию установки яркости свечения светодиодов			(Параметры: яркость (0-7), группа светодиодов (LED_ALL/1/2)).
		uint8_t				getLight				(uint8_t=LED_ALL		);																		//	Определяем функцию получения яркости свечения светодиодов			(Параметр:  группа светодиодов (LED_ALL/1/2)).
		void				setAnimation			(uint8_t, uint16_t=200	);																		//	Определяем функцию установки светодиодной анимации					(Параметры: номер светодиодной анимации, время свечения светодиода в мс, до 2550 мс).
		uint8_t				getAnimation			(void					);																		//	Определяем функцию получения номера светодиодной анимации			(Параметр:  отсутствует).
	private:																																		//
	/**	Внутренние переменные **/																													//
		iarduino_I2C_VirtualSelect* selI2C;																											//	Объявляем  указатель  на  объект полиморфного класса iarduino_I2C_VirtualSelect, но в конструкторе текущего класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C_Select.
		uint8_t				valAddrTemp			=	0;																								//	Определяем переменную для хранения адреса модуля на шине I2C который был указан, но не был проверен.
		uint8_t				valAddr				=	0;																								//	Определяем переменную для хранения адреса модуля на шине I2C.
		uint8_t				valVers				=	0;																								//	Определяем переменную для хранения версии прошивки модуля.
		uint8_t				valCols				=	0;																								//	Определяем переменную для хранения количества кнопок в одной линии.
		uint8_t				valRows				=	0;																								//	Определяем переменную для хранения количества линий с кнопками.
		uint8_t				arrREG_KBD_KEYS[10]	=	{0,0,0,0,0,0,0,0,0,0};																			//	Определяем массив     для хранения значений регистров статусных флагов клавиш «REG_KBD_KEYS_0-9».
		char				arrEncoding[11];																										//	Объявляем  строку     для хранения символов присваиваемых клавишам. Строка заполняется функцией begin() в соответствии с количеством колонок и рядов клавиш в клавиатуре.
		uint8_t				data[10];																												//	Объявляем  массив     для хранения получаемых/передаваемых данных.
	/**	Внутренние функции **/																														//
		bool				_begin					(void							);																//	Объявляем  функцию инициализации модуля								(Параметр:  отсутствует).
		bool				_readBytes				(uint8_t, uint8_t				);																//	Объявляем  функцию чтения данных в  массив  data					(Параметры: номер первого регистра, количество байт).
		bool				_writeBytes				(uint8_t, uint8_t, uint8_t=0	);																//	Объявляем  функцию записи данных из массива data					(Параметры: номер первого регистра, количество байт, номер первого элемента массива data).
};																																					//
																																					//
#endif																																				//