

#include "dataset.h"
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <iostream>

static const string downloadUrl = "https://www.kaggle.com/api/v1/datasets/download/wilmerarltstrmberg/recipe-dataset-over-2m";
static const string fileZip = "recipe.zip";
static const string filename = "recipes_data.csv";

bool datasetDownloader::downloadFile() {
    string command = "curl -L -o " + fileZip + " " + downloadUrl;

    int result = system(command.c_str());

    if (result != 0) {
        return false;
    }

    return true;
}

bool datasetDownloader::extractFile() {
    cout << "Extracting..." << endl;

    #ifdef _WIN32
        string winExtract = "powershell -Command \"Expand-Archive -Path " + fileZip + " -DestinationPath . -Force\"";
        if (system(winExtract.c_str()) == 0) {
            return true;
        }
    #else
        string extract = "unzip -q -o " + fileZip;
        int result = system(extract.c_str());

        if (result != 0) {
            return false;
        }
    #endif

    return true;
 }

bool datasetDownloader::isDownloaded() const {
    return filesystem::exists(filename) && filesystem::file_size(filename) > 0;
}

datasetDownloader::datasetDownloader() {

}

bool datasetDownloader::checkAvailability() {
    if (isDownloaded()) {
        return true;
    }

    if (!downloadFile()) {
        return false;
    }

    if (!filesystem::exists(fileZip) || filesystem::file_size(fileZip) == 0) {
        return false;
    }

    if (!extractFile()) {
        return false;
    }

    filesystem::remove(fileZip);

    if (!isDownloaded()) {
        return false;
    }

    return true;
}

string datasetDownloader::filePath() {
    return filesystem::current_path().string();
}
