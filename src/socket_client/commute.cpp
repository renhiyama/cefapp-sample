// This communicates with the rust server via UNIX sockets, and is used to handle CEF events, all via Rust server.

//create unix socket client

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>

void connect(){
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "/tmp/rovel.sock");
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1){
        perror("oops: client1");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    std::cout << "char from server = " << ch << std::endl;
    close(sockfd);
}