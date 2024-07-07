#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


int main()
{
    void* contex = zmq_ctx_new();
    void* socket = zmq_socket(contex, ZMQ_REP);
    zmq_connect(socket, "tcp://locolhost:5555");
    
    char buff[10];
    while(1)
    {
        int bytes = zmq_recv(socket, buff, 10, 0);
        printf("收到了: %s\n", buff);

        sleep(10);

        const char* ch = "got it";
        zmq_send(socket, ch, strlen(ch), 0);
    }

    zmq_close(socket);
    zmq_ctx_destroy(contex);

    return 0;
}

