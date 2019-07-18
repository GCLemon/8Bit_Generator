#include "../header/wave_writer.hpp"

using namespace retro_sound;

uint wave_writer::point_max;

wave_writer::wave_writer(string path)
{
    writer = ofstream(path, ios::binary);
    (*this).path = path;

    if(writer.fail())
    {
        cerr << "File open failed." << endl;
        exit(-1);
    }
}

wave_writer::~wave_writer()
{
    writer.close();
}