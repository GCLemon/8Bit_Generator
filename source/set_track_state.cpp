#include "../header/score_builder.hpp"

using namespace retro_sound;

void score_builder::set_octave(smatch submatches)
{
    switch(submatches[0].str()[0])
    {
        case '<' :
            ++octave; break;
        case '>' :
            --octave; break;
        case 'o' : 
            string match = submatches[1].str();
            if(match != "") octave = stoi(match);
            break;
    }
}

void score_builder::set_length(smatch submatches)
{
    length = stoi(submatches[1].str());
}

void score_builder::set_volume(smatch submatches)
{
    volume = stoi(submatches[1].str());
}

void score_builder::set_sound(smatch submatches)
{
    switch(stoi(submatches[1].str()))
    {
        case 0: sound = wave_square_2; break;
        case 1: sound = wave_square_4; break;
        case 2: sound = wave_square_8; break;
        case 3: sound = wave_triangle; break;
        case 4: sound = wave_noise;    break;
    }
}

vector<tempo_change> score_builder::change;

void score_builder::set_tempo(smatch submatches)
{
    double tempo = stod(submatches[1].str());
    change.push_back({ position, tempo });
}