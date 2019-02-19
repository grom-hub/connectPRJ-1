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

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
   
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