
#include <unistd.h>
#include "Server.h"

Server::Server(int port) throw(const char *) {
    fileDis = socket(AF_INET, SOCK_STREAM, 0);
    if (fileDis < 0) {
        throw "can't open socket";
    }
    server.family = AF_INET;
    server.address.s_addr = INADDR_ANY;
    server.port = htons(port);
    int checkBind = bind(fileDis, (struct sockaddr *) &server, sizeof(server));
    if (checkBind < 0) {
        throw "can't bind";
    }
    int checkListen = listen(fileDis, 5);
    if (checkListen < 0)
        throw "can't listen";
}

void Server::start(ClientHandler &ch) throw(const char *) {
    t = new thread([&ch, this]() {
    //add time out to accept
        while (!isStop) {
            socklen_t clintSize = sizeof(client);
            int clientNum = accept(fileDis, (struct sockaddr *) &client, &clintSize);
            if (clientNum < 0)
                throw "can't accept";
            ch.handle(clientNum);
            close(clientNum);
        }
    });
    close(fileDis);
}

void Server::stop() {
    isStop = true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

