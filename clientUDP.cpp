#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <vector>
//#include <cstring> // std::memcpy()


//char msg[] = "Test\n";
struct mData
{
    int id;
    int msg;
};

// typedef std::vector<cData> DataVector;



int main(int args, char *argv[])
{
    //std::vector<cData> data_vector;
    //DataVector data_vector(10);
   // data_vector.push_back(cData());
    //data_vector[i].id;

//for (int i = 0; i < data_vector.size(); i++)

    int sock;
    struct sockaddr_in addr;
    int myid = atoi(argv[1]);
    int command = atoi(argv[2]);

    mData cd[5];
    mData sd[5];

    for (int i = 0; i < 5; ++i)
    {
        cd[i].id = i;
        cd[i].msg = 0;
        sd[i].id = i;
        sd[i].msg = 0;
    }

    cd[myid].msg = command;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
//----------------------------------------------------

    while(1)
    {
        sleep(1);
 
        sendto(sock, &cd[myid], sizeof(mData), 0,
               (struct sockaddr *)&addr, sizeof(addr));

    }


    return 0;
}