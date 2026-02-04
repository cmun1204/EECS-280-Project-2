#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Image.hpp"
#include "processing.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
    }

    const string in_filename = argv[1];
    const string out_filename = argv[2];

    ifstream infile(in_filename);
    if (!infile.is_open()) {
        cout << "Error opening file: " << in_filename << endl;
    return 1;
    }

    Image img;
    Image_init(&img, infile);
    int new_width = atoi(argv[3]);
    int new_height = Image_height(&img);
    if (argc == 5) new_height = atoi(argv[4]);
    

    if (new_width <= 0 || new_width > Image_width(&img) || new_height <= 0
     || new_height > Image_height(&img)) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
    }

   seam_carve(&img, new_width, new_height);

    ofstream outfile(out_filename);
    if (!outfile.is_open()) {
        cout << "Error opening file: " << out_filename << endl;
    return 1;
    }

    Image_print(&img, outfile);

    return 0;
}


