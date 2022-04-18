#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

int main()
{
    time_t itr = time(NULL);
    fstream file;
    file.open("data.csv");
    fstream fileOut("dataOut.csv", std::ios_base::app | std::ios_base::in);
    string line = "";
    getline(file, line);
    if (file.is_open() && fileOut.is_open()) {
        while (getline(file, line)) {
            vector<double> locs;
            string s = "";
            string sev;
            string temp = line.substr(0, 200);
            for (int j = 0; j < 7; j++) {
                temp = temp.substr(temp.find(',') + 1);
                if (j == 0)
                    sev = temp.substr(0, temp.find(','));
                else if (j > 2)
                    locs.push_back(stod(temp.substr(0, temp.find(','))));
            }
            s += to_string((locs.at(0) + locs.at(2)) / 2) + "," + to_string((locs.at(1) + locs.at(3)) / 2) + "," + sev;
            fileOut << s << "\n";
        }
        file.close();
        fileOut.close();
    }
    time_t ftr = time(NULL);
    cout << "Time taken to load, read, and write file: " << ftr - itr << " seconds." << endl;
}
