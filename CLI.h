#ifndef CLI_H_
#define CLI_H_

#include <string>
#include "commands.h"


class CLI {
    DefaultIO *dio;
    Command* arrayCommand[6];
    vector<AnomalyReport> *anomalyReport;
    int *linesNumber;


public:
    CLI(DefaultIO *dio);

    void start();

    virtual ~CLI();
};

#endif /* CLI_H_ */
