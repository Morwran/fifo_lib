/*
  **********************************************************************************************************
  * @file   : fifo.c
  * @brief  : Library containing functions for working with FIFO (First In First Out).
  * This library has been successfully tested on x86 PC and MCU boards such as STM32 (Cortex M3 and M7 core)
  * and Xilinx Spartan6 (Microblaze core).
  **********************************************************************************************************
 *  Created on: 24.07.2020
 *      Author: kvb
 *      mail: mat3x@mail.ru
 */

#include "fifo.h"
#include "string.h"
#include "stdlib.h"


/**
  * @brief Calculating and aligning FIFO depth
  * @param void* d - Pointer to the actual size of the data.
  * @retval int - FIFO aligned depth.
  */
static int FifoMemSizeClc(const void* d, size_t size)
{
	int cnt_id=0;
	int d_out=1;
	for(int i=0;i<(size*8);i++)
		if((*(int*)d>>i)&0x1)cnt_id=i;

	//if(cnt_id)
	d_out<<=(cnt_id+1);

	return (d_out-1);

}

/**
  * @brief FIFO structure initialization
  * @param fifo_t * buf - Pointer to the FIFO structure.
  * @param uint16_t num_blocks - number of data blocks
  * @param uint16_t block_size - size of one data block
  * @retval _Bool - True/False (1,0). True if FIFO initialization was successful.
  */
_Bool fifo_init(fifo_t * buf, uint16_t num_blocks, uint8_t block_size)
{

	uint16_t full_size = (num_blocks*block_size);

	if(!full_size)
		return 0;

	buf->almost_full_size = full_size;

	full_size=FifoMemSizeClc(&full_size,sizeof(uint16_t));

	buf->head =NULL;
	if(!(buf->head = (uint8_t*)malloc(full_size))){
		return 0;
	}
	buf->wr = 0;
	buf->rd = 0;
	buf->sp = 0;

	buf->block_size = block_size;
	buf->full_size = full_size;


	return 1;
}
/**
  * @brief Push one block of data into FIFO
  * @param fifo_t * buf - Pointer to the FIFO structure.
  * @param void* data - Pointer to input data
  * @retval None.
  */
void fifo_push(fifo_t * buf, void* data)
{

	memcpy(&buf->head[buf->wr],data,buf->block_size);
	buf->wr+=buf->block_size;
	buf->wr &= buf->full_size;

}

/**
  * @brief Pop one block of data from FIFO
  * @param fifo_t * buf - Pointer to the FIFO structure.
  * @param void* data - Pointer to output data
  * @retval None.
  */
void fifo_pop(fifo_t * buf,void* data)
{

	memcpy(data,&buf->head[buf->rd],buf->block_size);
	buf->rd+=buf->block_size;
	buf->rd &= buf->full_size;

}
/**
  * @brief Clear FIFO memory
  * @param fifo_t * buf - Pointer to the FIFO structure.
  * @retval None.
  */
void fifo_clr(fifo_t * buf)
{
	free(buf->head);
	buf->wr = 0;
	buf->rd = 0;
	buf->full_size = 0;
}

/**
  * @brief Checking if FIFO is empty or not
  * @param fifo_t * buf - Pointer to the FIFO structure.
  * @retval _Bool - True/False (1,0). True if FIFO is empty.
  */
_Bool fifo_isEmpty(fifo_t * buf)
{
	if(buf->wr == buf->rd)
		return 1;

	return 0;
}

uint16_t fifo_cnt(fifo_t * buf)
{
	uint16_t delta = (((int)buf->wr<(int)buf->rd)?(buf->full_size+1-buf->rd+buf->wr):\
			(buf->wr-buf->rd));

	return (delta/buf->block_size);
}

/**
  * @brief Checking if FIFO is full or not
  * @param fifo_t * buf - Pointer to the FIFO structure.
  * @retval _Bool - True/False (1,0). True if FIFO is full.
  */
_Bool fifo_isFull(fifo_t * buf)
{
	uint16_t delta = (((int)buf->wr<(int)buf->rd)?(buf->full_size+1-buf->rd+buf->wr):\
			(buf->wr-buf->rd));


	if((delta == buf->full_size) || (delta == buf->almost_full_size) ||\
			(buf->full_size - delta) < buf->block_size ||\
			(buf->almost_full_size - delta) < buf->block_size)
		return 1;

	return 0;
}
















