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
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listener, (struct sockaddr *)&addr, sizeof(addr));

    listen(listener, 1);

    while(1)
    {
        std::cout << "Wait for accept...\n";

        sock = accept(listener, NULL, NULL);

        std::cout << "accept!\n";

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);

            std::cout << "bytes_read = " <<bytes_read << std::endl;

            if(bytes_read <= 0) break;

            data dt = *((data *)&buf);
            std::cout << "Message form client: " << dt.x  << " - " << dt.y << std::endl; // Мой вывод.
            
            char a[] = "OK";
            send(sock, &a, sizeof(2), 0);
        }
    
        close(sock);
    }
    
    return 0;
}