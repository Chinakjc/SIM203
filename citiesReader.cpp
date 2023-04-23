#include "citiesReader.hpp"

ListOfCities citiesReader(int popMin){
    
    ListOfCities cities;
    
    //--------------------------------------------------------------------
    //--- READING cities with population greater than or equal to 'popMin'
    //--------------------------------------------------------------------
    
    cout << "== Reading cities with population >= " << popMin << " from 'citiesList.csv' ==" << endl;
    
    cities.number = 0;
    
    ifstream inputFile("citiesList.csv");
    string myLine, myWord, myName;
    int myPop;
    int myDepartment;
    float myLon, myLat;
    if (inputFile.is_open()){
        while (getline(inputFile, myLine)) {
            stringstream str(myLine);
            getline(str, myWord, ',');
            getline(str, myWord, ',');myDepartment = stoi(myWord);
            getline(str, myWord, ',');
            getline(str, myWord, ','); myName = myWord;
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ','); myPop = stoi(myWord);
            getline(str, myWord, ',');
            getline(str, myWord, ',');
            getline(str, myWord, ','); myLon = stof(myWord);
            getline(str, myWord, ','); myLat = stof(myWord);
            if(myPop >= popMin){
                cities.name.push_back(myName);
                cities.pop.push_back(myPop);
                cities.lon.push_back(myLon);
                cities.lat.push_back(myLat);
                cities.depart.push_back(myDepartment);
                cities.number++;
            }
        }
    }
    inputFile.close();
    
    //--------------------------------------------------------------------
    //--- WRITING cities with population greater than or equal to 'popMin'
    //--------------------------------------------------------------------
    
    cout << "== Writing cities with population >= " << popMin << " in 'resuCities.dat' ==" << endl;
    
    ofstream outputFile("resuCities.dat");
    if (outputFile.is_open()){
        for(int i=0; i<cities.number; i++){
            outputFile << cities.pop[i] << " " << cities.lon[i] << " " << cities.lat[i] << endl;
        }
        outputFile.close();
    }
    
    return cities;
}