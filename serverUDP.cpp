#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <cstring> // std::memcpy()

struct mData
{
    int id;
    int msg;
};


int main()
{
    int sock;
    struct sockaddr_in addr;
    char buf[1024];
    //int bytes_read;


    mData cd;
    mData sd[5];

    for (int i = 0; i < 5; ++i)
    {
        sd[i].id = i;
        sd[i].msg = 0;
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    // while(1)
    // {
    //     bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
    //     buf[bytes_read] = '\0';
    //     printf(buf);
    // }
//----------------------------------------------------------
    while(1)
    {
        recvfrom(sock, buf, 1024, 0, NULL, NULL);

        std::memcpy(&cd, &buf, sizeof(mData));
        //cd = *((cData *)&buf);
        //std::cout << msg << std::endl;

        // cd[msg].id = msg;
        // cd[msg].data++;

        sd[cd.id].msg += cd.msg;

        system("clear");
        std::cout << "-----" << std::endl;

        for (int i = 0; i < 5; ++i)
        {
            std::cout << sd[i].id << " - " << sd[i].msg << std::endl;
        }
    //---------------

        sendto(sock, &sd, sizeof(mData) * 5, 0,
               (struct sockaddr *)&addr, sizeof(addr));
        
    }

    return 0;
}