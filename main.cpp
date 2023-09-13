#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<cmath>
using namespace std;
float euclideanDistanceFunction(float x1,float y1,float x2,float y2)
{
    float range = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    return sqrt(range);
}
int main() {
    const int ROWS = 4000;
    const int COLS = 2; // two columns
    float** sheet = new float* [ROWS];
    for (int i = 0; i < 4000; i++) {
        sheet[i] = new float[COLS];
    }

    ifstream csvfile("driver-data.csv");
    string cord;
    int Hcell = 0;
    while (getline(csvfile, cord) && Hcell < ROWS) {
        stringstream converter(cord);
        int Vcell = 0;
        string value;
        while (getline(converter, value, ',') && Vcell < COLS + 1) {
            if (Vcell == 1 || Vcell == 2) { // store only the second and third columns
                sheet[Hcell][Vcell - 1] = stof(value);
            }
            ++Vcell;
        }
        ++Hcell;
    }
    csvfile.close();

    float* cluster = new float [4000];


    float centroid1[1][2];
    float centroid2[1][2];
    float centroid3[1][2];
    float centroid4[1][2];
    for (int i = 0; i < 1;i++) {
        for (int j = 0; j < 2; j++) {
            centroid1[i][j] = sheet[0][j];
            centroid2[i][j] = sheet[1][j];
            centroid3[i][j] = sheet[2][j];
            centroid4[i][j] = sheet[3][j];
        }
    }
    //--------------
    for (int i = 0; i < 4000; i++) {

        float dis1,dis2, dis3, dis4;
        dis1 = euclideanDistanceFunction(centroid1[0][0], centroid1[0][1], sheet[i][0], sheet[i][1]);
        dis2 = euclideanDistanceFunction(centroid2[0][0], centroid2[0][1], sheet[i][0], sheet[i][1]);
        dis3 = euclideanDistanceFunction(centroid3[0][0], centroid3[0][1], sheet[i][0], sheet[i][1]);
        dis4 = euclideanDistanceFunction(centroid4[0][0], centroid4[0][1], sheet[i][0], sheet[i][1]);
        float smallest = dis1;
        if (dis2 < smallest) {
            smallest = dis2;
        }
        if (dis3 < smallest) {
            smallest = dis3;
        }
        if (dis4 < smallest) {
            smallest = dis4;
        }

        if (dis1 == smallest) {
            cluster[i] = 1;
        }
        if (dis2 == smallest) {
            cluster[i] = 2;
        }
        if (dis3 == smallest) {
            cluster[i] = 3;
        }
        if (dis4 == smallest) {
            cluster[i] = 4;
        }

    }

    cout << "mean_dist_day\tmean_over_speed_perc\tcluster" << endl;
    for (int i = 0; i < 4000; i++) {
        for (int j = 0; j < 2; j++) {
            cout << sheet[i][j]<<"\t";
        }
        cout << cluster[i] << endl;
    }

    ofstream outCSV("output1.csv");
    outCSV << "mean_dist_day,mean_over_speed_perc,cluster" << endl;
    for (int i = 0; i < 4000; i++) {
        for (int j = 0; j < 2; j++) {
            outCSV << sheet[i][j] << ",";
        }
        outCSV << cluster[i] << endl;
    }
    outCSV.close();

    return 0;
}