#include "../header/score_builder.hpp"

using namespace retro_sound;

void score_builder::add_note (smatch submatches)
{
    note note = { position, { 1, length }, octave * 12, volume, sound };
    string match = "";

    match = submatches[1].str();
    if(match != "")
        switch(match[0])
        {
            case 'a': note.scale += a; break;
            case 'b': note.scale += b; break;
            case 'c': note.scale += c; break;
            case 'd': note.scale += d; break;
            case 'e': note.scale += e; break;
            case 'f': note.scale += f; break;
            case 'g': note.scale += g; break;
        }

    match = submatches[2].str();
    if(match != "")
        for(char c : match)
            switch(c)
            {
                case '+': ++note.scale;     break;
                case '-': --note.scale;     break;
                case '^': note.scale += 12; break;
                case 'v': note.scale -= 12; break;
            }

    match = submatches[3].str();
    if(match != "")
    {
        note.length = { 0, 4 };
        string value = "";
        bool   plus  = true;

        for(char c : match)
            switch (c)
            {
                case '+':
                    note.length += { plus ? 1 : -1, stoi(value) };
                    value = "";
                    plus = true;
                    break;
                case '-':
                    note.length += { plus ? 1 : -1, stoi(value) };
                    value = "";
                    plus = false;
                    break;
                default:
                    value += c; break;
            }

        note.length += { plus ? 1 : -1, stoi(value) };
    }

    match = submatches[5].str();
    if(match != "")
        for(char c : match)
            switch(c)
            {
                case '_': note.length *= 2; break;
                case '/': note.length /= 2; break;
                case '.': note.length *= { 3, 2 }; break;
            }

    match = submatches[6].str();
    if(match != "")
    {
        string value = submatches[8].str();
        switch(submatches[7].str()[0])
        {
            case '+': note.volume += stoi(value); break;
            case '-': note.volume -= stoi(value); break;
            default : note.volume  = stoi(value); break;
        }
    }
    score.push(note);
    position += note.length;
}

void score_builder::add_rest (smatch submatches)
{
    note note = { position, { 1, length }, 0, 0, sound };
    string match = "";

    match = submatches[1].str();
    if(match != "")
    {
        if(submatches[1].str()[0] == '+'
        || submatches[1].str()[0] == '-')
        {
            cerr << "エラー : 休符に半音記号は使えません." << endl;
            exit(-1);
        }

        note.length = { 0, 4 };
        string value = "";
        bool plus = true;

        for(char c : match)
            switch (c)
            {
                case '+':
                    note.length += { plus ? 1 : -1, stoi(value) };
                    value = "";
                    plus = true;
                    break;
                case '-':
                    note.length += { plus ? 1 : -1, stoi(value) };
                    value = "";
                    plus = false;
                    break;
                default:
                    value += c; break;
            }
    }

    match = submatches[3].str();
    if(match != "")
        for(char c : match)
            switch(c)
            {
                case '_': note.length *= 2; break;
                case '/': note.length /= 2; break;
                case '.': note.length *= { 3, 2 }; break;
            }
            
    score.push(note);
    position += note.length;
}