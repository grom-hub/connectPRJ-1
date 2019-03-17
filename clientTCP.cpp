#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <iostream>
#include <cstring> // std::memcpy()
//#include <cstdlib>
//#include <cstdio>

struct mData
{
    int id;
    int msg;
};


int main(int args, char *argv[])
{

	int sock;
	struct sockaddr_in addr;
	char buf[1024];
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
	else
		std::cout << "Connect - OK" << std::endl;

	while(1)
	{
		sleep(1);
		
		send(sock, &cd[myid], sizeof(mData), 0);
		
		recv(sock, buf, 1024, 0); 
		std::memcpy(&sd, &buf, sizeof(mData) * 5);
		// a = *((uData *)&buf);
		//system("clear");
        std::cout << "-----" << std::endl;
        for (int i = 0; i < 5; ++i)
        {
            std::cout << sd[i].id << " - " << sd[i].msg << std::endl;
        }
	}


	//shutdown(sock, SHUT_RDWR);
	//close(sock);
	
	// if(shutdown(sock, SHUT_RDWR) == 0)
	//     std::cout << "Shutdown - OK" << std::endl;
	if(close(sock) == 0)
	    std::cout << "Close - OK" << std::endl;

	return 0;
}