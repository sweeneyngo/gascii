#include "ASCII.h"
#include <opencv2/opencv.hpp>
#include <math.h>  
#include <vector>

#define RGB_AVERAGE 1
#define RGB_LIGHTNESS 2
#define RGB_LUMINOSITY 3

using namespace cv;
using namespace std;
const std::string ASCII_BRIGHTNESS_COMPLEX = " .\'`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
const std::string ASCII_BRIGHTNESS_SIMPLE = " .:-=+*#%@";


/*
 * @params
 * std::string path = Image path for ASCII generation.
 * double tw = Terminal window width.
 * int sv = Stretch value (number of reps per char).
 * int iv = Inversion value (0,1).
 * int mode = Filtering mode (average, lightness, luminosity).
 * int set = ASCII string set.
 */

ASCII::ASCII(std::string path, double tw, int sv, int iv, int mode, int set) {
    
    m_path = path;
    m_tw = tw;
    m_sv = sv;
    m_iv = iv;
    m_mode = mode;
    m_set = set ? ASCII_BRIGHTNESS_COMPLEX : ASCII_BRIGHTNESS_SIMPLE;

    Mat3b image, dst;
    cout << m_path << endl;
    image = imread(m_path, 1);
    if ( !image.data ) 
        cout << "No image data." << endl;
    else {
        double p = (m_tw/image.cols)/m_sv;
        resize(image, dst, Size(), p, p);
        m_image = dst;
    }
}

vector<vector<int>> ASCII::condense() {

    vector<vector<int>> res = vector<vector<int>>(m_image.rows, vector<int>(m_image.cols, 0));
    for (int r = 0; r < m_image.rows; ++r) {
        for (int c = 0; c < m_image.cols; ++c) {
            Vec3b pixel = m_image(r, c);    
            uchar blue = pixel[0];
            uchar green = pixel[1];
            uchar red = pixel[2];

            switch(m_mode) {
            case RGB_AVERAGE:
                res[r][c] = (blue + green + red) / 3;
                break;
            case RGB_LIGHTNESS:
                res[r][c] = (maximum(blue, green, red) + minimum(blue, green, red)) / 2;
                break;
            case RGB_LUMINOSITY:
                res[r][c] = (0.07*blue + 0.72*green + 0.21*red);
                break;
            default:
                res[r][c] = 0;
                break;
            }

            res[r][c] = m_iv ? 255 - res[r][c] : res[r][c];

        }
    }

    return res;
}

vector<vector<uchar>> ASCII::map(vector<vector<int>> v) {

    double BRIGHTNESS = 255.0 / m_set.size();

    vector<vector<uchar>> res = vector<vector<uchar>>(m_image.rows, vector<uchar>(m_image.cols, 0));
    for (int r = 0; r < m_image.rows; ++r)
        for (int c = 0; c < m_image.cols; ++c) 
            res[r][c] = m_set[int(round(v[r][c] / BRIGHTNESS))];

    return res;
}

void ASCII::print(vector<vector<uchar>> v) {
    for (int r = 0; r < v.size(); ++r) {
        for (int c = 0; c < v[r].size(); ++c)
            for (int j = 0; j < 1; ++j)
                cout << v[r][c];
        cout << endl;
    }
}

void ASCII::printSize() {
    cout << "Image size: " << m_image.cols << " x " << m_image.rows << endl;
}

void ASCII::displayImage() {
    namedWindow("cv2 - gascii", WINDOW_AUTOSIZE);
    imshow("Display Image", m_image);
    waitKey(0);
}