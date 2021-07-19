#include <iostream>
#include <string>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

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
    string pimg;

    struct option options[7];

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

    options[6].flags      = GOPT_LAST;

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

    ASCII* img = new ASCII(pimg, tw, sv, iv, RGB_LIGHTNESS, mode);
    img->print(img->map(img->condense()));
    
    return 0;
}
