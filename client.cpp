#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <iostream>

#define PORT 8080

using namespace std;

int socket_Create_and_Conect();
   
int main(void) 
{ 
    int sock = socket_Create_and_Conect();
    
    if (sock == -1){
        return 0;
    } 
    
    int n, buffer;

    cout << "Insira n de Fibo(n) : ";
    cin >> n;
 

    send(sock, &n, sizeof(n), 0);

    cout << endl << "Fibo(n) = ";
    
    for (int i = 0; i < n; i++){
        read( sock , &buffer, sizeof(buffer));
        cout << " " << buffer << " ";
    }

    return 0; 
}

int socket_Create_and_Conect()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }

    return sock;  
}
