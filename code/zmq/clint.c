#include <zmq.h>
#include <stdio.h>
#include <string.h>

static void s_send(void* socket, const char* ch);

int main()
{
    void* context = zmq_ctx_new();
    void* socket = zmq_socket(context, ZMQ_REQ);

    return 0;
}

