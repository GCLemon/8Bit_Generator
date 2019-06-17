#include "../header/8bit.hpp"

int main(int argc, char** argv)
{
    string path = argv[1];
    text_reader reader(path);
    path = path.replace(path.length() - 4, 4, ".wav");
    wave_writer writer(path);

    reader.read();
    score s = reader.get_score();
    writer.write(s);
}