#include <iostream>
#include <string>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>

#include "gopt.h"
#include "ASCII.h"

using namespace std;

#define RGB_AVERAGE 1
#define RGB_LIGHTNESS 2
#define RGB_LUMINOSITY 3

/**
 * @brief Reads and converts ASCII.
 *
 * @return Returns 0 when execution completes successfully.
 */

int main(int argc, char** argv) {


    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    double th           = w.ws_row;
    double tw           = w.ws_col;

    int sv              = 1;
    int iv              = 0;
    int mode            = RGB_LIGHTNESS;
    int html            = 0;
    string pimg;
    string fileName = "";

    struct option options[8];

    options[0].long_name  = "help";
    options[0].short_name = 'h';
    options[0].flags      = GOPT_ARGUMENT_FORBIDDEN;

    options[1].long_name  = "version";
    options[1].short_name = 'V';
    options[1].flags      = GOPT_ARGUMENT_FORBIDDEN;

    options[2].long_name  = "stretch";
    options[2].short_name = 's';
    options[2].flags      = GOPT_ARGUMENT_REQUIRED;

    options[3].long_name  = "invert";
    options[3].short_name = 'i';
    options[3].flags      = GOPT_ARGUMENT_REQUIRED;

    options[4].long_name  = "path";
    options[4].short_name = 'f';
    options[4].flags      = GOPT_ARGUMENT_REQUIRED;

    options[5].long_name  = "ascii";
    options[5].short_name = 'a';
    options[5].flags      = GOPT_ARGUMENT_REQUIRED;

    options[6].long_name  = "output";
    options[6].short_name = 'o';
    options[6].flags      = GOPT_ARGUMENT_REQUIRED;

    options[7].long_name  = "html";
    options[7].short_name = 'h';
    options[7].flags      = GOPT_ARGUMENT_REQUIRED;

    options[7].flags      = GOPT_LAST;

    argc = gopt(argv, options);
    gopt_errors(argv[0], options);

    FILE *fout;
    int i;

    if (options[0].count)
    {
        cout << "Read the manual." << endl;
        exit (EXIT_SUCCESS);
    }

    if (options[1].count)
    {
        cout << "0.1.0" << endl;
        exit (EXIT_SUCCESS);
    }

    if (options[2].count)
    {
        cout << options[2].argument << endl;
        sv = atoi(options[2].argument);
    }

    if (options[3].count)
    {
        cout << options[3].argument << endl;
        iv = atoi(options[3].argument);
    }

    if (options[4].count)
    {
        cout << options[4].argument << endl;
        pimg = options[4].argument;
    }
    else {
        cout << "Insufficient argument(s). Please add an image path." << endl;
        exit(EXIT_FAILURE);
    }

    if (options[5].count)
    {
        cout << options[5].argument << endl;
        mode = double(atoi(options[5].argument));
    }

    if (options[6].count)
    {
        cout << options[6].argument << endl;
        fileName = options[6].argument;
    }    
    
    if (options[7].count)
    {
        cout << options[7].argument << endl;
        html = options[7].argument;
    }



    ASCII* img = new ASCII(pimg, tw, sv, iv, RGB_LIGHTNESS, mode, html);

    if (fileName != "") {
        ofstream fileOut;
        fileOut.open(fileName);
        fileOut << img->print(img->map(img->condense()));
        fileOut.close();
        return 0;
    }
    
    cout << img->print(img->map(img->condense())) << endl;
    
    return 0;
}
