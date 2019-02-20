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
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // 0 - система сама выберет произвольный неиспользуемый в данный момент номер порта.
                                // 1-1023 - привелигированные порты. 1024-41951 регестрируются в IANA.
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY - соединяться с клиентами через любой интерфейс.


    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) // Привязка сокета к адресу.
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1); // Cокет переводится в режим ожидания запросов со стороны клиентов и создается очередь запросов на соединение.

    while(1)
    {
        std::cout << "Wait for accept...\n";

        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        std::cout << "accept!\n";

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);

            std::cout << "bytes_read = " <<bytes_read << std::endl;

            if(bytes_read <= 0) break;

            data dt = *((data *)&buf);
            std::cout << "Message form client: " << dt.x  << " - " << dt.y << std::endl; // Мой вывод.
            
            char a[] = "OTVET";
            send(sock, &a, 5, 0);
        }

        if(shutdown(sock, SHUT_RDWR) == 0) // Разрывает соединение.
            std::cout << "Shutdown - OK" << std::endl;
        if(close(sock) == 0)
            std::cout << "Close - OK" << std::endl;
        
    }
    
    return 0;
}