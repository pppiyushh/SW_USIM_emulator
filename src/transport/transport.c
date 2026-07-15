#include <stdio.h>
#include <string.h>

#include "transport.h"

void transport_wait_for_message(Message *msg)
{
    char input[512];

    printf("\nUSIM> ");
    fflush(stdout);

    /*
     * fgets() is a BLOCKING call.
     *
     * The thread sleeps here until the user presses Enter.
     */
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        msg->length = 0;
        return;
    }

    size_t len = strlen(input);

    if (len && input[len - 1] == '\n')
    {
        input[--len] = '\0';
    }

    memcpy(msg->data, input, len);
    msg->length = len;
}