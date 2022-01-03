//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092
#include <unistd.h>
#include <csignal>
#include "Server.h"

Server::Server(int port) throw(const char *) {
    fileDis = socket(AF_INET, SOCK_STREAM, 0);
    if (fileDis < 0) {
        throw "can't open socket";
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    //int checkBind = bind(fileDis, (struct sockaddr *) &server, sizeof server);
    if (bind(fileDis, (struct sockaddr *) &server, sizeof server) < 0) {
        throw "can't bind";
    }
    int checkListen = listen(fileDis, 3);
    if (checkListen < 0)
        throw "can't listen";
}

void sigHandler(int sigNum) {
    cout<<"sidH"<<endl;
}

void Server::start(ClientHandler &ch) throw(const char *) {
    t = new std::thread([&ch, this]() {
        //add time out to accept
        signal(SIGALRM, sigHandler);
        while (!isStop) {
            alarm(5);
            socklen_t clintSize = sizeof client;
            int clientNum = accept(fileDis, (struct sockaddr *) &client, &clintSize);
            if (clientNum < 0)
                throw "can't accept";
            ch.handle(clientNum);
            close(clientNum);
        }
        close(fileDis);
    });
}

void Server::stop() {
    isStop = true;
    t->join(); // do not delete this!
}

Server::~Server() {
    delete t;
}



