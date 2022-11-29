#include "./cn.h"
#include <gmp.h>

struct encryptmsg{
    char m[BUFFSIZE];
};

int main() {

    int sfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    init_socket_address(&server_addr,LOCAL_HOST,PORT);

    if((sfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
        error("socket error");
    
    char buff[BUFFSIZE] = {'\0'};

    mpz_t m;
    mpz_inits(m, NULL);
    mpz_set_ui(m, 50);

    char *m1 = mpz_get_str(NULL, 16, m); 

    struct encryptmsg msg;
    strcpy(msg.m, m1);

    // cout<<"Enter message : ";
    // cin.getline(buff, BUFFSIZE);

    if(sendto(sfd, &msg, BUFFSIZE, 0, (struct sockaddr*)&server_addr, len) < 0)
        error("sendto error");
    
    cout<<"message sent ..."<<endl;

    // if(recvfrom(sfd, buff, BUFFSIZE, 0, (struct sockaddr*)&server_addr, &len) < 0)
    //     error("recvfrom error");
    // cout<<"message received ..."<<endl;

    // cout<<buff<<endl;
}