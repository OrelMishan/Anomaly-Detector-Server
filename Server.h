/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>

struct sockAddress {
    uint8_t sin_len;
    sa_family_t family;
    in_port_t port;
    struct in_addr address;
    char sin_zero[8];
};

// edit your ClientHandler interface here:
class ClientHandler {
public:
    virtual void handle(int clientID) = 0;

};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler : public ClientHandler {
public:
    virtual void handle(int clientID) {

    }
};


// implement on Server.cpp
class Server {
    std::thread *t; // the thread to run the start() method in
    int fileDis;
    sockAddress server;
    sockAddress client;
    bool isStop = false;
    // you may add data members

public:
    Server(int port) throw(const char *);

    virtual ~Server();

    void start(ClientHandler &ch) throw(const char *);

    void stop();
};

#endif /* SERVER_H_ */
