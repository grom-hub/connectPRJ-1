#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>



struct data
{
    int x;
    int y;
};


int main()
{
    int sock;
    struct sockaddr_in addr;
    char buf[1024];


    sock = socket(AF_INET, SOCK_STREAM, 0); // Префикс AF означает "address family" - "семейство адресов".
                                            // SOCK_STREAM - (TCP) способ передачи данных по сети.
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // INADDR_LOOPBACK - петля типа 127.0.0.1 (127.0.0.0/8).

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
   
    data dt;
    dt.x = 123;
    dt.y = 456;

    send(sock, &dt, sizeof(data), 0);
    //   const void *msg

    recv(sock, buf, 1024, 0);  
    std::cout << buf << std::endl;

    if(shutdown(sock, SHUT_RDWR) == 0)
        std::cout << "Shutdown - OK" << std::endl;
    if(close(sock) == 0)
        std::cout << "Close - OK" << std::endl;
    
    return 0;
}