#include <iostream>
#include <istream>
#include <streambuf>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

void readHandData(std::vector<std::vector<double>> &hand_data){
    std::ifstream csv_data("/home/xgy/ws_xgy/ws_data/xgy_0702_data/csv/hand_01.csv", std::ios::in);
    std::string line;

    if (!csv_data.is_open())
    {
        std::cout << "Error: opening hand file fail" << std::endl;
        std::exit(1);
    }

    std::istringstream sin;         //将整行字符串line读入到字符串istringstream中
    std::vector<std::string> words; //声明一个字符串向量
    std::string word;
    std::vector<double> hand_data_line;

    // 读取数据
    while (std::getline(csv_data, line))
    {
        sin.clear();
        sin.str(line);
        hand_data_line.clear();
        while (std::getline(sin, word, ',')) //将字符串流sin中的字符读到field字符串中，以逗号为分隔符
        {
            hand_data_line.push_back(stod(word));
//           std::cout << std::stod(word.c_str())<<"\t";
        }
        hand_data.push_back(hand_data_line);
        // do something。。。
    }
    csv_data.close();
}

void readGelsightData(std::vector<double> &gelsight_data){
    std::ifstream csv_data("/home/xgy/ws_xgy/ws_data/xgy_0702_data/csv/gelsight_01.csv", std::ios::in);
    std::string line;

    if (!csv_data.is_open())
    {
        std::cout << "Error: opening gelsight file fail" << std::endl;
        std::exit(1);
    }

    std::istringstream sin;         //将整行字符串line读入到字符串istringstream中
    std::vector<std::string> words; //声明一个字符串向量
    std::string word;

    // 读取数据
    while (std::getline(csv_data, line))
    {
        sin.clear();
        sin.str(line);
        while (std::getline(sin, word, ',')) //将字符串流sin中的字符读到field字符串中，以逗号为分隔符
        {
            gelsight_data.push_back(stod(word));
//           std::cout << std::stod(word.c_str())<<"\t";
        }
        // do something。。。
    }
    csv_data.close();


}


int main()
{
    std::vector<std::vector<double>> hand_data; //定义机械手信息
    readHandData(hand_data);                    //读取机械手信息
    std::vector<double> gelsight_data;          //定义GelSight信息
    readGelsightData(gelsight_data);            //读取GelSight信息

    std::ofstream ofs;
    ofs.open("/home/xgy/ws_xgy/ws_data/xgy_0702_data/csv/sync_01.csv",std::ios::out|std::ios::app);

    double Y0[36];
    double Y1[36];
    double Y[36];
    double x0, x1, x, y0, y1, y;
    for (unsigned int i = 0; i < gelsight_data.size(); i++){
        for (unsigned int j = 0; j < hand_data.size(); j++){
            if (hand_data[j][0] > gelsight_data[i]){
                x0 = hand_data[j-1][0];
                x1 = hand_data[j][0];
                x = gelsight_data[i];
                y0 = hand_data[j-1][1];
                y1 = hand_data[j][1];
                for (int k=0;k<36;k++) {
                  Y0[k] = hand_data[j-1][k+1];
                  Y1[k] = hand_data[j][k+1];
                }
                break;
            }
        }
//        y = (x1-x)/(x1-x0)*y0+(x-x0)/(x1-x0)*y1;
        ofs << std::to_string(gelsight_data[i]);
        for (int k=0;k<36;k++) {
          Y[k] = (x1-gelsight_data[i])/(x1-x0)*Y0[k]+(gelsight_data[i]-x0)/(x1-x0)*Y1[k];
          ofs<<"," << Y[k];
        }
        ofs<< std::endl;
    }
    ofs.close();
    std::cout << "sync is ok" <<std::endl;
    return 0;
}
