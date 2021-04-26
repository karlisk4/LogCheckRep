
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
    string regTrg = ":flag";
    string regLine;
    string curLine;
    std::vector<std::string> regLst{};
    std::vector<std::string> drsLst{};

    ifstream RegFile("C:\\Users\\karlis\\Documents\\reg.txt");

    while (getline(RegFile, regLine)) {
        if (regLine.find(regTrg) != string::npos) {

            unsigned first = findLastIndex(regLine, ':');
            unsigned last = regLine.length()-5;
            string rgName = regLine.substr(first + 2, last - first-1);
            regLst.push_back(rgName);
        }
    }
    ifstream ReadFile("C:\\Users\\karlis\\Documents\\output_2021-04-24_19-13-47.log");

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
        if (curLine.find(drsPen) != string::npos) {
            unsigned first = curLine.find("(");
            unsigned last = curLine.find(")");
            string rnName = curLine.substr(first + 1, last - first - 1);
            cout << rnName;
            cout << " pen \n";
        }
        
    }
    bool found;
    for (int i = 0; i < regLst.size(); i) {
        found = false;
        //cout << "First ";
        //cout << drsLst.at(0);
        //cout << "\n";
        //cout << regLst.at(5);
        for (int j = 0; j < drsLst.size(); j++) {
            string drsD = drsLst.at(j);
            string regD = regLst.at(i);
            
            /*string drsD = drsLst.at(0);
            //cout << drsLst.at(j);
            cout << "drs \n";
            string regD = regLst.at(5);
            cout << drsD.length();
            cout << " reg \n";
           cout << regD.length();*/
            if (drsD == regD) {
                found = true;
                i++;
                //cout << "Match!";
            }
        }
        string name = regLst.at(i);
        if (found == false) {
            //cout << "Naughty!";
            cout << name;
            cout << "drs \n";
            i++;
        }
        //cout << "\n";
    }

    // Close the file
    ReadFile.close();
}

