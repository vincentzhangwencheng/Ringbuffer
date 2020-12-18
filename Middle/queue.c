/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-12-08 15:48:57
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-12-10 10:58:34
 */
#include "queue.h"

ring_queue_t Rxbuffer;

//环形队列初始化
void RingQueueInit(ring_queue_t *q)
{
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}
 
//入队
uint8_t RingQueuePush(ring_queue_t *q, uint8_t data)
{
    if (((q->tail % RING_QUEUE_SIZE) == q->head) && ((q->size == RING_QUEUE_SIZE)))
    {
        //printf("--------------RING_QUEUE_FULL------------------");
        return RING_QUEUE_FULL;
    }
    
    q->data[q->tail] = data;
    q->tail = (q->tail + 1) % RING_QUEUE_SIZE;
    q->size++;
 
    return RING_QUEUE_OK;
}

//出队
uint8_t RingQueuePop(ring_queue_t *q, uint8_t *data)
{
    if ((q->head == q->tail) && (q->size == 0))
    {
        //printf("--------------RING_QUEUE_EMPTY-------------------");
        return RING_QUEUE_EMPTY;
    }
 
    *data = q->data[q->head];
    q->head = (q->head + 1) % RING_QUEUE_SIZE;
    q->size--;
 
    return RING_QUEUE_OK;
}
