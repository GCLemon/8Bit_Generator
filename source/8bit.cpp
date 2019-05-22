#include "../header/8bit.hpp"

int main(int argc, char** argv)
{
    text_reader reader("test.eb");
    wave_writer writer("test.wav");

    writer.write(reader.read());
}