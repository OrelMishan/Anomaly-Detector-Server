//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092
#include "CLI.h"

CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    sad = new HybridAnomalyDetector;
    anomalyReport = new std::vector<AnomalyReport>;
    linesNumber = new int;
    arrayCommand[0] = new uploadCommand(dio, sad, anomalyReport, linesNumber);
    arrayCommand[1] = new settingsCommand(dio, sad, anomalyReport, linesNumber);
    arrayCommand[2] = new detectCommand(dio, sad, anomalyReport, linesNumber);
    arrayCommand[3] = new resultsCommand(dio, sad, anomalyReport, linesNumber);
    arrayCommand[4] = new analyzeCommand(dio, sad, anomalyReport, linesNumber);
    arrayCommand[5] = new exitCommand(dio, sad, anomalyReport, linesNumber);

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
        if (choose == 6) {
            break;
        }
    }

}


CLI::~CLI() {
    delete sad;
    delete anomalyReport;
    delete linesNumber;
    for (Command *c :arrayCommand){
        delete c;
    }
    delete this;
}

