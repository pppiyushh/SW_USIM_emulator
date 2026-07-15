#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdint.h>

/**
 * Reads a hexadecimal string from stdin and converts it into bytes.
 *
 * Returns:
 *      Number of bytes received.
 */
size_t io_receive(uint8_t *buffer, size_t max_len);

/**
 * Sends raw bytes to stdout in hexadecimal format.
 */
void io_send(const uint8_t *buffer, size_t len);

void io_init(void);

#endif