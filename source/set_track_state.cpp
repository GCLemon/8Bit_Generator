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

void score_builder::set_key(smatch submatches)
{
    string k = submatches[1].str();
    string h = submatches[2].str();
    string m = submatches[3].str();
    if(h == "")
    {
        switch(k[0])
        {
            case 'c':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                break;
            case 'd':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                break;
            case 'e':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::natural;
                }
                break;
            case 'f':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                break;
            case 'g':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                break;
            case 'a':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                break;
            case 'b':
                if(m == "maj")
                {
                    key[0] = half::sharp;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::natural;
                }
                break;
        }
    }
    if(h == "+")
    {
        switch(k[0])
        {
            case 'c':
                if(m == "maj")
                {
                    key[0] = half::sharp;
                    key[1] = half::sharp;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::sharp;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                break;
            case 'd':
                if(m == "maj")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::sharp;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::sharp;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                break;
            case 'e':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::natural;
                    key[6] = half::flat;
                }
                if(m == "min")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                break;
            case 'f':
                if(m == "maj")
                {
                    key[0] = half::sharp;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::sharp;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                break;
            case 'g':
                if(m == "maj")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::sharp;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                break;
            case 'a':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::sharp;
                    key[1] = half::sharp;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::sharp;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                break;
            case 'b':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                break;
        }
    }
    if(h == "-")
    {
        switch(k[0])
        {
            case 'c':
                if(m == "maj")
                {
                    key[0] = half::sharp;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::natural;
                }
                break;
            case 'd':
                if(m == "maj")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::flat;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                break;
            case 'e':
                if(m == "maj")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::flat;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::flat;
                }
                break;
            case 'f':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::sharp;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::natural;
                }
                break;
            case 'g':
                if(m == "maj")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::flat;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::flat;
                }
                if(m == "min")
                {
                    key[0] = half::natural;
                    key[1] = half::natural;
                    key[2] = half::sharp;
                    key[3] = half::natural;
                    key[4] = half::natural;
                    key[5] = half::sharp;
                    key[6] = half::sharp;
                }
                break;
            case 'a':
                if(m == "maj")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::flat;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::flat;
                    key[6] = half::flat;
                }
                break;
            case 'b':
                if(m == "maj")
                {
                    key[0] = half::natural;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::natural;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::natural;
                }
                if(m == "min")
                {
                    key[0] = half::flat;
                    key[1] = half::flat;
                    key[2] = half::natural;
                    key[3] = half::flat;
                    key[4] = half::flat;
                    key[5] = half::natural;
                    key[6] = half::flat;
                }
                break;
        }
    }
}