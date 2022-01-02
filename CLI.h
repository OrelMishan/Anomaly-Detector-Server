//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092
#ifndef CLI_H_
#define CLI_H_

#include <string>
#include "commands.h"


class CLI {
    DefaultIO *dio;
    Command* arrayCommand[6];
    HybridAnomalyDetector* sad;
    vector<AnomalyReport> *anomalyReport;
    int *linesNumber;


public:
    CLI(DefaultIO *dio);

    void start();

    virtual ~CLI();
};

#endif /* CLI_H_ */
