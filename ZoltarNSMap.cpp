#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include "SortAlgorithms.cpp"

using namespace std;

struct JobData {
    string areaTitle;
    string primState;
    string naics;
    string naicsTitle;
    string occTitle;
    string totEmp;
    string hMean;
    string aMean;
    string aPct10;
    string aPct25;
    string aMedian;
    string aPct75;
    string aPct90;
};



void inCSV(const string& filename, map<string, int>& jobMap, string industry, string state) {
    ifstream file(filename);
    string line;
    vector<string> tokens;
    JobData job;

    if (!file){
        cout << "File not found" << endl;
        return;
    }

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        while (getline(ss, token, '/')) {
            tokens.push_back(token);
        }

        string region = tokens[0];
        string naics = tokens[1];
        string occupationTitle = tokens[2];
        string salary = tokens[3];

        if (tokens[1].substr(0, 2) == industry && tokens[0] == state) {
            JobData job;
            job.occTitle = tokens[2];
            job.aMean = tokens[3];

            bool processEntry = true;
            for (auto c : job.aMean) {
                if (!isdigit(c) && c != ',') {
                    processEntry = false; 
                }
            }
            if (processEntry) {
                jobMap.insert(make_pair(job.occTitle, stoi(job.aMean)));
                tokens.clear();
            }
        }

        tokens.clear();
    }
}

void printResults(vector<Job>& results) {
    for (int i = 0; i < 10; i++) {
        cout << results.at(i).jobTitle << ": $" << results.at(i).salary << ",000\n";
    }
}

int main() {
    map<string, int> jobMap;
    vector<string> name, salary;

    int minSalary, maxSalary;
    string industry, state;

    cout << "Enter occupation category based on the following codes:\n"
        << "11: Management Occupations\n"
        << "13: Business and Financial Operations Occupations\n"
        << "15: Computer and mathematical occupations\n"
        << "17: Architecture and Engineering Occupations\n"
        << "19: Life, Physical, and Social Science Occupations\n"
        << "21: Community and Social Service Occupations\n"
        << "23: Legal Occupations\n"
        << "25: Education, Training, and Library Occupations\n"
        << "27: Arts, Design, Entertainment, Sports, and Media Occupations\n"
        << "29: Healthcare Practitioners and Technical Occupations\n"
        << "31: Healthcare Support Occupations\n"
        << "33: Protective Service Occupations\n"
        << "35: Food Preparation and Serving Related Occupations\n"
        << "37: Building and Grounds Cleaning and Maintenance Occupations\n"
        << "39: Personal Care and Service Occupations\n"
        << "41: Sales and Related Occupations\n"
        << "43: Office and Administrative Support Occupations\n"
        << "45: Farming, Fishing, and Forestry Occupations\n"
        << "47: Construction and Extraction Occupations\n"
        << "49: Installation, Maintenance, and Repair Occupations\n"
        << "51: Production Occupations\n"
        << "53: Transportation and Material Moving Occupations\n"
        << "55: Military Specific Occupations\n";
    cin >> industry;

    cout << "Enter State (e.g., FL, KY, WA): ";
    cin >> state;

    inCSV("2022LaborData.csv", jobMap, industry, state);

    sortedSalaries ss = sortJobSalaries(jobMap);
    vector<Job> ascending = ss.ascending;
    vector<Job> descending = ss.descending;

    cout << "\n\nTop 10 Occupations by Salary:\n";
    printResults(descending);

    cout << "\nBottom 10 Occupations by Salary:\n";
    printResults(ascending);

    return 0;
}
