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
    string line = "";
    vector<string> lines;
    vector<vector<string>> data;
    getline(file, line);
    if (file.is_open()) {
        while (getline(file, line)) {
            getline(file, line);
            lines.push_back(line);
            cout << lines.size() << endl;
            vector<double> locs;
            vector<string> dataToInsert;
            string sev;
            string temp = line.substr(0, 200);
            for (int j = 0; j < 7; j++) {
                temp = temp.substr(temp.find(',') + 1);
                if (j == 0)
                    sev = temp.substr(0, temp.find(','));
                else if (j > 2)
                    locs.push_back(stod(temp.substr(0, temp.find(','))));
            }
            dataToInsert.push_back(to_string((locs.at(0) + locs.at(2)) / 2));
            dataToInsert.push_back(to_string((locs.at(1) + locs.at(3)) / 2));
            dataToInsert.push_back(sev);
            data.push_back(dataToInsert);
        }
        file.close();
    }
    time_t ftr = time(NULL);
    cout << "Time taken to load file: " << ftr - itr << " seconds." << endl;
    time_t itw = time(NULL);
    fstream fileOut("dataOut.csv", std::ios_base::app | std::ios_base::in);
    if (fileOut.is_open()) {
        for (auto x : data) {
            string s = "";
            for (auto y : x) {
                s += y + ",";
            }
            fileOut << s.substr(0, s.length() - 1) << "\n";
        }
        fileOut.close();
    }
    time_t ftw = time(NULL);
    cout << "Time taken to output file: " << ftw - itw << " seconds." << endl;
}
