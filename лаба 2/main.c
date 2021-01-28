#define F_CPU 16000000UL // Директива устновки частоты процессора

#include <avr/io.h>
// Библиотека для работы с портами ввода-вывода
#include <util/delay.h> // Библиотека для работы с паузой

int main ()
{
	DDRE |= (1 << PE0); // Настройка вывода PE0 на выход
	DDRE |= (1 << PE1); // Настройка вывода PE1 на выход
	DDRE |= (1 << PE2); // Настройка вывода PE2 на выход
	
	DDRE &= ~(1 << PE5); // Настройка вывода PE5 на вход
	// DDRE &= ~(1 << PE5); - команда выставляет сбрасывает бит PE5 в ноль
	PORTE &= ~(1 << PE0); // Отключение напряжения на выводе PE0
	PORTE &= ~(1 << PE1); // Отключение напряжения на выводе PE1
	PORTE &= ~(1 << PE2); // Отключение напряжения на выводе PE2
	
	PORTE |= (1 << PE5); // Активация подтягивающего к напряжению питания
	// (pull-up) резистора

	uint8_t btn_click_counter = 0; // Счетчик нажатий
	uint8_t btn_ticks_counter = 0; // Счетчик тиков удержания кнопки
	
	// Главный цикл работы МК
	while (1)
	{
	// Проверка бита PE5
		if ((PINE & (1 << PE5)) == 0)
		{
			_delay_ms(10);
			// Короткая пауза для стабилизации
			if (btn_ticks_counter == 0)
			{
				btn_click_counter++; // Увеличиваем на 1 счетчик нажатий
			}
			// Увеличиваем счетчик тиков, пока он не станет равен 10
			if (btn_ticks_counter < 10)
			{
				btn_ticks_counter++; // Увеличиваем на 1 счетчик тиков
			}
		} else
		{
			btn_ticks_counter = 0; // Обнуление счетчика тиков
		}
		
		// Определение количества нажатий
		if (btn_click_counter == 1)
		{
			// Выполнение действия, если нажали 2 раза
			// Например: включение напряжения на выводе PE0
			PORTE |= (1 << PE0);
			PORTE &= ~(1 << PE2);
		} 
		
		if (btn_click_counter == 2)
		{
			// Выполнение действия, если нажали 4 раза
			// Отключение напряжения на выводе PE0
			PORTE |= (1 << PE1);
			PORTE &= ~(1 << PE0);
			
		}
		if (btn_click_counter == 3) {
			PORTE |= (1 << PE2);
			PORTE &= ~(1 << PE1);
			btn_click_counter = 0;
		}
		
	}
}
