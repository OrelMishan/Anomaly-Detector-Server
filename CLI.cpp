#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    HybridAnomalyDetector sad;
    arrayCommand[0] = new uploadCommand(dio,&sad,anomalyReport);
}

void CLI::start(){
    arrayCommand[0];

    while(true) {
        dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:");
        for (Command *command: arrayCommand) {
            dio->write(command->getDescription() + "\n");
        }
        float choose;
        dio->read(&choose);
        arrayCommand[(int) choose - 1]->execute();
    }

}


CLI::~CLI() {
}

