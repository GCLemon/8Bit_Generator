#include "../header/8bit.hpp"

int main(int argc, char** argv)
{
    string path = argv[1];
    text_reader reader(path);
    path = path.replace(path.length() - 4, 4, ".wav");
    wave_writer writer("test.wav");

    writer.write(reader.read());
}