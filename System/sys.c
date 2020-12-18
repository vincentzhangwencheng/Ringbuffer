/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-08-28 12:38:28
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-12-18 12:41:53
 */
#include "sys.h"

/**
 * @name: CheckSum8
 * @description: none
 * @param {*} uint8_t *buf, uint8_t len
 * @return {*} uint8_t checksum
 */
uint8_t CheckSum8(uint8_t *buf, uint8_t len)
{
    uint8_t i,checksum;
    uint16_t sum = 0;

    for (i = 0; i < len; i++)
    {
        sum += buf[i];
    }

    checksum = (uint8_t)(sum & 0xFF);

    return checksum;
}
