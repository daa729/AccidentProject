#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

int main()
{
    fstream file;
    file.open("dataOut.csv");
    string line = "";
    double lati;
    double loni;
    cout << "Please input the latitude and longitude in the form of: \"lat,lon\" without quotation marks." << endl;
    cin >> line;
    lati = stod(line.substr(0, line.find(',')));
    loni = stod(line.substr(line.find(',') + 1));
    time_t itr = time(NULL);
    if (file.is_open()) {
        while (getline(file, line)) {
            double latf = stod(line.substr(0, line.find(',')));
            line = line.substr(line.find(',') + 1);
            double lonf = stod(line.substr(0, line.find(',')));
            line = line.substr(line.find(',') + 1);
            int sev = stoi(line.substr(0, line.find(',')));
            double dist = sqrt(pow(latf - lati, 2) + pow(lonf - loni, 2));
        }
        file.close();
    }
    time_t ftr = time(NULL);
    cout << "Time taken to load file: " << ftr - itr << " seconds." << endl;
}