#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;

vector<vector<int>> dataGenerator(){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> col1Dist(0, 15);
    std::uniform_int_distribution<> col2Dist(0, 10);
    std::uniform_int_distribution<> col3Dist(0, 100);
    std::uniform_int_distribution<> col4Dist(0, 365);

    std::vector<std::vector<int>> data(100, std::vector<int>(5));

    for (int i = 0; i < 100; ++i) {
        data[i][0] = col1Dist(gen);
        data[i][1] = col2Dist(gen);
        data[i][2] = col3Dist(gen);
        data[i][3] = col4Dist(gen);
        data[i][4] = i;
    }

    // Printing the generated 2D vector
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    return data;
}

bool myCmp(vector<int> a, vector<int> b){
    return a[3] > b[3];
}
vector<char> GroupAndAssign(vector<vector<int>>&vect){
    //(*vect)[0]
    int numPerCat = vect.size()/16 + 1; //16 because hexadecimal
    short int currentCat = 0;
    short int counter = 0;
    sort(vect.begin() , vect.end() , myCmp);
    vector<char> res;
    char temp;
    stringstream ss ;
    for(int i = 0 ; i < vect.size() ; i++){
         ss << hex << currentCat;
         temp = ss.str()[0];
         ss.str("");
         res.push_back(temp);
         counter++;
         if(counter == numPerCat){
            counter = 0;
            currentCat++;
         }
    }
    // for(int i = 0 ;i < 100 ;i++){
    //     cout << res[i] << " ";
    // }
    return res;
    // for (int i = 0; i < 100; ++i) {
    //     for (int j = 0; j < 5; ++j) {
    //         std::cout << vect[i][j] << "\t";
    //     }
    //     std::cout << std::endl;
    // }
}

bool mySorter(pair<string , int> a, pair<string , int>b){
    return a.first > b.first;
}
int main(){
    vector<vector<int>>data = {} ;
    cout << "Genrating sample data";
    // data = dataGenerator();
    data = {{2 , 1 , 60 , 50 , 1},
            {3 , 5 , 70 , 40 , 2},
            {2 , 2 , 30 , 30 , 3},
            {2 , 2 , 30 , 10 , 4},
            {1 , 3 , 80 , 20 , 5},
           };
    vector<vector<int>> deepCopy(data.begin() , data.end());
    
    stringstream ss;
    ss << hex << 15;
    cout << ss.str() << endl;
    vector<char> hexaVals= GroupAndAssign(data); //sorts based on date and returns hexa values
    vector<pair<string , int>> finalData;
    stringstream ssTemp;
    for(int i = 0 ; i < data.size() ; i++){
        for(int j = 0 ; j < 3 ; j++){
            // cout << hex << data[i][j] << " ";
            // cout << data[i][j];
            
            // cout << endl;
            if(j == 2) data[i][j] /= 7;
            ssTemp << hex << data[i][j];
        }
        ssTemp << hex << hexaVals[i];
        finalData.push_back({ssTemp.str(), data[i][4]});
        ssTemp.str("");
    }
    sort(finalData.begin() , finalData.end(), mySorter);
    for (int i = 0; i < finalData.size(); ++i) {
        cout << finalData[i].first << " " << finalData[i].second << endl;
    }
    cout << "Disease priority " << "  severity \t" << "age \t" << "appointment Date \t" << "Id \t \n";
    for(int i = 0 ; i < deepCopy.size() ; i++){
        for(int j = 0 ; j < 5 ; j++){
            cout << deepCopy[finalData[i].second-1][j] << "\t";
        }
        cout << endl;
    }
    // cout << data[4][0];
    return 0;
}