/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-12-08 15:48:43
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-12-18 12:22:04
 */
#ifndef __QUEUE_H
#define __QUEUE_H

#include "sys.h" 

#define RING_QUEUE_SIZE  90

typedef enum
{
  RING_QUEUE_EMPTY = 0,
  RING_QUEUE_FULL = 1,
  RING_QUEUE_OK = 2,
} ring_queue_status_t;

typedef struct
{  
  uint8_t head;
  uint8_t tail;
  uint8_t size;
  uint8_t data[RING_QUEUE_SIZE];
} ring_queue_t;
 
extern ring_queue_t Rxbuffer;
 
void RingQueueInit(ring_queue_t *q);
uint8_t RingQueuePop(ring_queue_t *q, uint8_t *data);
uint8_t RingQueuePush(ring_queue_t *q, uint8_t data);

#endif
