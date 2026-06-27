

#ifndef COP3530_PROJECT2_DATASET_H
#define COP3530_PROJECT2_DATASET_H

#include <string>
using namespace std;


class datasetDownloader {
    string fileDirectory;
    bool downloadFile();
    bool extractFile();
    bool isDownloaded() const;

public:
    datasetDownloader();
    bool checkAvailability();
    string filePath();
};


#endif //COP3530_PROJECT2_DATASET_H