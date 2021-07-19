#ifndef ASCII_H
#define ASCII_H

#include <opencv2/opencv.hpp>
#include <string>

class ASCII {
public:
    ASCII(std::string path, double tw, int sv, int iv, int mode, int set);
    std::vector<std::vector<int>> condense();
    std::vector<std::vector<uchar>> map(std::vector<std::vector<int>> v);
    void print(std::vector<std::vector<uchar>> v);
    void printSize();
    void displayImage();
private:
    std::string m_path;
    cv::Mat3b m_image;
    double m_tw;
    int m_sv;
    int m_iv;
    int m_mode;
    std::string m_set;

    // helper functions
    int maximum(int a, int b, int c) {
        int max = ( a < b) ? b : a;
        return ( ( max < c ) ? c : max);
    }

    int minimum(int a, int b, int c) {
        int min = ( a > b) ? b : a;
        return ( ( min > c ) ? c : min);
    }
};

#endif // ASCII_H