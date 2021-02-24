#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <iostream> 

#define PORT 8080 

using namespace std;

void socket_Create_and_Conect(int &server_fd, int &new_socket);
int fib(int n);

int main(void) 
{ 
    int server_fd, new_socket, buffer, r;
    
    socket_Create_and_Conect(server_fd, new_socket); 

       
    read( new_socket , &buffer, sizeof(buffer)); 

    for (int i = 0; i < buffer; i++){
        r = fib(i);
        send(new_socket, &r, sizeof(r), 0);
    }
     
    return 0; 
} 


void socket_Create_and_Conect(int &server_fd, int &new_socket){
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
}

int fib(int n) {
    if (n < 2) return n;
    else return fib(n - 1) + fib(n - 2);
}
