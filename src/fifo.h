/*
 *******************************************************************************
  * @file           : fifo.h
  * @brief         Header of fifo.c
  ******************************************************************************
 *  Created on: 24.07.2020
 *      Author: kvb
 *      mail: mat3x@mail.ru
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdint.h"

/** @brief Structure of FIFO*/
typedef struct{
	uint8_t *head;
	uint16_t wr;
	uint16_t rd;
	uint16_t sp;
	uint16_t full_size;
	uint16_t almost_full_size;
	uint16_t block_size;
}fifo_t;

_Bool fifo_init(fifo_t * buf, uint16_t num_blocks, uint8_t block_size);
void fifo_push(fifo_t * buf, void* data);
void fifo_pop(fifo_t * buf,void* data);
void fifo_clr(fifo_t * buf);
_Bool fifo_isEmpty(fifo_t * buf);
_Bool fifo_isFull(fifo_t * buf);
uint16_t fifo_cnt(fifo_t * buf);
#endif /* FIFO_H_ */
