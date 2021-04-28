
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#include <cstddef>
#include <vector>

int findLastIndex(string& str, char x)
{
    // Traverse from right
    for (int i = str.length() - 1; i >= 0; i--)
        if (str[i] == x)
            return i;

    return -1;
}
int main()
{   
    string drsPen = "ACRLRD_DRS: Penalty";
    string drsRun = "ACRLRD_DRS is running";
    string pstRac = "UNSERVED";
    string regTrg = ":flag";
    string regLine;
    string curLine;
    std::vector<std::string> regLst{};
    std::vector<std::string> drsLst{};
    std::vector<std::string> delLst{};

    ifstream RegFile("C:\\Users\\karli\\Documents\\reg.txt");

    while (getline(RegFile, regLine)) {
        if (regLine.find(regTrg) != string::npos) {

            unsigned first = findLastIndex(regLine, ':');
            unsigned last = regLine.length()-5;
            string rgName = regLine.substr(first + 2, last - first-1);
            regLst.push_back(rgName);
            delLst.push_back(rgName);
        }
    }
    ifstream ReadFile("C:\\Users\\karli\\Documents\\output_2021-04-24_19-13-47.log");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(ReadFile, curLine)) {
        //cout << drsRun;
        if (curLine.find(drsRun) != string::npos) {
            unsigned first = curLine.find("(");
            unsigned last = curLine.find(")");
            string rnName = curLine.substr(first+1, last - first -1);
            drsLst.push_back(rnName);
            //cout << rnName;
            //cout << "\n";
        }
        if (curLine.find(drsPen) != string::npos) { //rewrite whole section to include tires and refuel
            if (curLine.find(pstRac) != string::npos) {

            } else {
                unsigned first = curLine.find("(");
                unsigned last = curLine.find(")");
                string rnName = curLine.substr(first + 1, last - first - 1);
                cout << rnName;
                cout << " Illegal DRS penalty \n";
            }
        }
        
    }
    for (int i = 0; i < regLst.size(); i++) {
        for (int j = 0; j < drsLst.size(); j++) {
            if (regLst.at(i)==drsLst.at(j)) {
                delLst.at(i) = "";
            }
        }
    }
    for (int i = 0; i < delLst.size(); i++) {
        if (delLst.at(i) != "") {
            cout << delLst.at(i);
            cout << " DRS app not detected \n";
        }
        
    }

    // Close the file
    ReadFile.close();
}

