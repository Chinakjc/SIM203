//
// Created by kjc on 2023/4/24.
//

#include "Prim.hpp"

Prim::Prim(int popMin) : cities(new ListOfCities(citiesReader(popMin))){

}

Prim::Prim(ListOfCities *cities): cities(cities){

}

pair<double,double> Prim::prim_f(bool text) const {
    clock_t t0 = clock();
    auto result = prim();
    clock_t t1 = clock();
    double networkSize = result.first;

    vector<pair<int,int>> connections = result.second;

    // Execution time
    cout << "Execution time: " << t1 - t0 << " ms"<< endl;

    // Output network size
    cout << "Network size: " << networkSize << " km"<< endl;

    if(text){
        // Print the generated tree
        cout << "Generated tree:" << endl;

        for (const pair<int, int>& connection : connections) {
            cout << "City " << cities->name[connection.first] << " connected to City " << cities->name[connection.second] << endl;
        }
    }


    // Save the coordinates and connections in a CSV file
    ofstream outputFile(output_file_name);
    if (outputFile.is_open()){
        outputFile << "city_name, lattiude, longitude, parent_city_name, parent_latitude, parent_longitude, population" << endl;
        for (const pair<int, int>& connection : connections){
            outputFile << cities->name[connection.first] << "," << cities->lat[connection.first] << "," << cities->lon[connection.first] << "," << cities->name[connection.second] << "," << cities->lat[connection.second] << "," << cities->lon[connection.second] << "," << cities->pop[connection.first] << endl;

        }
        outputFile.close();

    }

    return {t1 - t0, networkSize};

}