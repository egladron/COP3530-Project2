

#ifndef COP3530_PROJECT2_DATASET_H
#define COP3530_PROJECT2_DATASET_H

#include <string>
using namespace std;


class datasetDownloader {
    //  Returns where the program is running from in the form of a string
    string fileDirectory;

    /*  Downloads the zip file containing the dataset using cURL. This should work on most platforms except older
     *  versions of windows or platforms that do not have cURL already installed. Consult the readme for alternatives
     */
    bool downloadFile();

    //  Extracts the file. Checks for operating system in order to determine how
    bool extractFile();

    //  Returns true if the dataset is in the same directory as the executable
    bool isDownloaded() const;

public:
    datasetDownloader();

    //  Checks to see if the file exists, if not it downloads the file and extracts it
    bool checkAvailability();

    //  Sets fileDirectory to the directory of the executable
    string filePath();
};


#endif //COP3530_PROJECT2_DATASET_H