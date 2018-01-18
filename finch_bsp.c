#include "finch_pin.h"
#include "finch_bsp.h"
#include "nrf_delay.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

static const  uint8_t finch_leds[TOTAL_RC] = ALL_LED;
static const  uint8_t rows_leds[TOTAL_LEDS] = LEDS_ROWS;
static const  uint8_t columns_leds[TOTAL_LEDS] = LEDS_COLUMNS;

typedef struct led_address
{
	uint8_t row;
	uint8_t column;

}led_address;

led_address LED_ARRAY[TOTAL_LEDS];

void init_led_address(void)
{
	int i=0;
	
	for(i=0;i<TOTAL_LEDS ;i++)
	{
		LED_ARRAY[i].row = rows_leds[i];
		LED_ARRAY[i].column = columns_leds[i];
	}
}

void init_LEDs(void)
{
  int i=0;
	for(i=0;i< TOTAL_RC;i++)
	{
		if(i < TOTAL_C )
		{
			nrf_gpio_cfg_output(finch_leds[i]);
		  nrf_gpio_pin_set(finch_leds[i]);
		}
		else
		{
			nrf_gpio_cfg_output(finch_leds[i]);
		  nrf_gpio_pin_clear(finch_leds[i]);
		}
	}
	init_led_address();
	
}

void set_all_led_once(uint32_t  set_led)
{
	//Find columns which require 
	int i =0;
	volatile int array_leds_set[TOTAL_LEDS];
	volatile int LED_ROW_1[10];
	volatile int LED_ROW_2[10];
	volatile int LED_ROW_3[10];
	
	int led_row_1_count = 0;
	int led_row_2_count = 0;
	int led_row_3_count = 0;

	
	for(i=0;i<TOTAL_LEDS;i++)
	{
		 array_leds_set[i]= ((set_led >> i) & (0x00000001));
	}
	for(i=0;i<TOTAL_LEDS;i++)
	{
			if(array_leds_set[i] == 1)
			{
				if(LED_ARRAY[i].row == 1 )
				{
					LED_ROW_1[led_row_1_count] = i;
					led_row_1_count++;
				}
			  else if(LED_ARRAY[i].row == 2 )
			  {
					LED_ROW_2[led_row_2_count] = i;
					led_row_2_count++;
			  }
			  else if(LED_ARRAY[i].row == 3 )
			  {
					LED_ROW_3[led_row_3_count] = i;
					led_row_3_count++;
			  }
				//LED_ARRAY[1].column =	  		;
			 }
	}

	//Switch on ROW1
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+ROW_1_Value]);
	for(i=0;i<led_row_1_count;i++)
	{
		nrf_gpio_pin_clear(finch_leds[LED_ARRAY[LED_ROW_1[i]].column - 1]);
	}
	//delay
	nrf_delay_ms(2);
	//Switch off ROW1
	for(i=0;i<led_row_1_count;i++)
	{
		nrf_gpio_pin_set(finch_leds[LED_ARRAY[LED_ROW_1[i]].column - 1]);
	}
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+ROW_1_Value]);
	
	
	//Switch on ROW2
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+ROW_2_Value]);
	for(i=0;i<led_row_2_count;i++)
	{
		nrf_gpio_pin_clear(finch_leds[LED_ARRAY[LED_ROW_2[i]].column - 1]);
	}
	//delay
	nrf_delay_ms(2);
	//Switch off ROW2
	for(i=0;i<led_row_2_count;i++)
	{
		nrf_gpio_pin_set(finch_leds[LED_ARRAY[LED_ROW_2[i]].column - 1]);
	}
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+ROW_2_Value]);
	
	
	//Switch on ROW3
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+ROW_3_Value]);
	for(i=0;i<led_row_3_count;i++)
	{
		nrf_gpio_pin_clear(finch_leds[LED_ARRAY[LED_ROW_3[i]].column - 1]);
	}
	//delay
	nrf_delay_ms(2);
	//Switch off ROW3
	for(i=0;i<led_row_3_count;i++)
	{
		nrf_gpio_pin_clear(finch_leds[LED_ARRAY[LED_ROW_3[i]].column - 1]);
	}
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+ROW_3_Value]);
	
	
}

void set_led_row_column(uint8_t row, uint8_t column)
{
	
}

void test_LED_1(void)
{
		int i =0;
   	nrf_gpio_pin_set(finch_leds[9]);
	  for(i=0; i< TOTAL_C ;i++)
	  {
				nrf_gpio_pin_clear(finch_leds[i]);
	  }
	
}

void test_LED_2(int led_no)
{
	led_no = led_no - 1;
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[led_no].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[led_no].column - 1]);
}

void test_LED_4()
{
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[6].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[6].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[6].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[6].column - 1]);
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[8].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[8].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[8].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[8].column - 1]);
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[16].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[16].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[16].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[16].column - 1]);
	//

	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[18].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[18].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[18].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[18].column - 1]);
	
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[22].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[22].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[22].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[22].column - 1]);
	
	//
}


void test_LED_3(void)
{
	int i = 0;
	for (i=0;i< TOTAL_LEDS ;i++)
	{
		nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[i].row]);
		nrf_gpio_pin_clear(finch_leds[LED_ARRAY[i].column - 1]);
		nrf_delay_ms(1000);
		nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[i].row]);
		nrf_gpio_pin_set (finch_leds[LED_ARRAY[i].column - 1]);
	}
	
}


void happy_ledscreen()
{
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[6].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[6].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[6].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[6].column - 1]);
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[8].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[8].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[8].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[8].column - 1]);
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[16].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[16].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[16].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[16].column - 1]);
	//

	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[18].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[18].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[18].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[18].column - 1]);
	
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[22].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[22].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[22].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[22].column - 1]);
	
}

void sad_ledscreen()
{
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[6].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[6].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[6].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[6].column - 1]);
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[8].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[8].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[8].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[8].column - 1]);
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[17].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[17].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[17].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[17].column - 1]);
	//

	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[21].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[21].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[21].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[21].column - 1]);
	
	//
	nrf_gpio_pin_set (finch_leds[TOTAL_C-1+LED_ARRAY[23].row]);
	nrf_gpio_pin_clear(finch_leds[LED_ARRAY[23].column - 1]);
	nrf_delay_ms(2);
	nrf_gpio_pin_clear (finch_leds[TOTAL_C-1+LED_ARRAY[23].row]);
	nrf_gpio_pin_set (finch_leds[LED_ARRAY[23].column - 1]);
	
}