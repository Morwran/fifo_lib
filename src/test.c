/*
 ******************************************************************************
 * @file           : test.c
 * @brief         Testing of FIFO
 ******************************************************************************
 *  Created on: 24.07.2020
 *      Author: kvb
 *      mail: mat3x@mail.ru
 */

#include "stdio.h"
#include "fifo.h"

typedef uint8_t fifo_mem_struct[256];

/** @brief Testing structure*/
typedef struct{
	float ch11;
	float ch12;
	float ch21;
	float ch22;

}adc_smpl_t;

/** @brief Structure of FIFO*/
fifo_t fifo;

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void){


	adc_smpl_t Din[4]={\
			{1,2,3,4},\
			{5,6,7,8},\
			{9,10,11,12},\
			{13,14,15,16},\
	};


	for(uint8_t i=0;i<sizeof(Din)/sizeof(adc_smpl_t);i++)
		printf("Data for testing: N%u: %f %f %f %f\n",i,Din[i].ch11,Din[i].ch12,Din[i].ch21,Din[i].ch22);

	if(!(fifo_init(&fifo, 4, sizeof(adc_smpl_t)))){
		printf("mem err\n");
		return 0;
	}

	//printf("fifo st start: wr %u rd %u fs %u afs: %u e: %u f: %u\n",fifo.wr,fifo.rd,fifo.full_size,\
			fifo.almost_full_size,fifo_isEmpty(&fifo),fifo_isFull(&fifo));

	for(uint8_t j=0;j<1;j++){
		for(uint8_t i=0;i<4;i++){
			if(!fifo_isFull(&fifo))
				fifo_push(&fifo,(void*)&Din[i]);

			//printf("fifo wr%u: %u %u %u e: %u f: %u\n",i,fifo.wr,fifo.rd,fifo.full_size,\
					fifo_isEmpty(&fifo),fifo_isFull(&fifo));

		}

		adc_smpl_t d;

		while(!fifo_isEmpty(&fifo)){
			fifo_pop(&fifo,(void*)&d);

			//printf("fifo rd: %u %u %u e: %u f: %u\n",fifo.wr,fifo.rd,fifo.full_size,\
					fifo_isEmpty(&fifo),fifo_isFull(&fifo));

			printf("Data reading from FIFO: %f %f %f %f\n",d.ch11,d.ch12,d.ch21,d.ch22);
		}


		printf("=====================================================\n");
	}

	printf("Test passed!\n");

	fifo_clr(&fifo);

	return 0;
}
