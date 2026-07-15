#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "../message/message.h"

void transport_wait_for_message(Message *msg);

void transport_send_message(const Message *msg);

#endif