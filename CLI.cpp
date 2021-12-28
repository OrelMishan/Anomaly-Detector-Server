#include "CLI.h"

CLI::CLI(DefaultIO *dio) {
    HybridAnomalyDetector sad;
    arrayCommand[0] = new uploadCommand(dio, &sad, anomalyReport, linesNumber);
    arrayCommand[1] = new settingsCommand(dio, &sad, anomalyReport, linesNumber);
    arrayCommand[2] = new detectCommand(dio, &sad, anomalyReport, linesNumber);
    arrayCommand[3] = new resultsCommand(dio, &sad, anomalyReport, linesNumber);
    arrayCommand[4] = new analyzeCommand(dio, &sad, anomalyReport, linesNumber);
    arrayCommand[5] = new exitCommand(dio, &sad, anomalyReport, linesNumber);

}

void CLI::start() {
    float choose;
    while (true) {
        dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        for (Command *command: arrayCommand) {
            dio->write(command->getDescription() + "\n");
        }

        dio->read(&choose);
        arrayCommand[(int) choose - 1]->execute();
        if (choose == 0) {
            break;
        }
    }

}


CLI::~CLI() {
}

