/******************************************************************************
 * File        : message.h
 * Module      : Common
 * Description : Generic message exchanged between Transport and Kernel.
 ******************************************************************************/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stddef.h>
#include <stdint.h>

#define MESSAGE_MAX_SIZE 256

typedef struct
{
    uint8_t data[MESSAGE_MAX_SIZE];
    size_t length;

} Message;

#endif