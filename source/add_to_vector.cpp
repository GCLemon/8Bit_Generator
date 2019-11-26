#include "../header/score_builder.hpp"

using namespace retro_sound;

void score_builder::add_note (smatch submatches)
{
    #ifdef RATIONAL
    note note = { position, { 1, length }, 1.0, octave * 12, volume, octave * 12, volume, sound };
    #else
    note note = { position, 1.0 / length, 1.0, octave * 12, volume, octave * 12, volume, sound };
    #endif
    string match = "";
    int reset_scale = 0;

    match = submatches[1].str();
    if(match != "")
        switch(match[0])
        {
            case 'a':
                note.start_scale += a + key[0];
                reset_scale = octave * 12 + a;
                break;
            case 'b':
                note.start_scale += b + key[1];
                reset_scale = octave * 12 + b;
                break;
            case 'c':
                note.start_scale += c + key[2];
                reset_scale = octave * 12 + c;
                break;
            case 'd':
                note.start_scale += d + key[3];
                reset_scale = octave * 12 + d;
                break;
            case 'e':
                note.start_scale += e + key[4];
                reset_scale = octave * 12 + e;
                break;
            case 'f':
                note.start_scale += f + key[5];
                reset_scale = octave * 12 + f;
                break;
            case 'g': 
                note.start_scale += g + key[6];
                reset_scale = octave * 12 + g;
                break;
        }

    match = submatches[2].str();
    if(match != "")
        for(char c : match)
            switch(c)
            {
                case '+': ++note.start_scale; break;
                case '-': --note.start_scale; break;
                case '=':
                    note.start_scale = reset_scale;
                    break;
                case '^':
                    note.start_scale += 12;
                    reset_scale += 12;
                    break;
                case 'v':
                    note.start_scale -= 12;
                    reset_scale -= 12;
                    break;
            }

    match = submatches[3].str();
    if(match != "")
    {
        #ifdef RATIONAL
        note.length = { 0, 4 };
        #else
        note.length = 0;
        #endif
        string value = "";
        bool   plus  = true;

        for(char c : match)
            switch (c)
            {
                case '+':
                    #ifdef RATIONAL
                    note.length += { plus ? 1 : -1, stoi(value) };
                    #else
                    note.length += (plus ? 1.0 : -1.0) / stod(value) ;
                    #endif
                    value = "";
                    plus = true;
                    break;
                case '-':
                    #ifdef RATIONAL
                    note.length += { plus ? 1 : -1, stoi(value) };
                    #else
                    note.length += (plus ? 1.0 : -1.0) / stod(value) ;
                    #endif
                    value = "";
                    plus = false;
                    break;
                default:
                    value += c; break;
            }

        #ifdef RATIONAL
        note.length += { plus ? 1 : -1, stoi(value) };
        #else
        note.length += (plus ? 1.0 : -1.0) / stod(value) ;
        #endif
    }

    match = submatches[5].str();
    if(match != "")
        note.length_time = stod(submatches[6]);

    match = submatches[8].str();
    if(match != "")
        for(char c : match)
            switch(c)
            {
                case '_': note.length *= 2; break;
                case '/': note.length /= 2; break;
                case '.':
                    #ifdef RATIONAL
                    note.length *= { 3, 2 }; break;
                    #else
                    note.length *= 1.5; break;
                    #endif
            }

    match = submatches[9].str();
    if(match != "")
    {
        string value = submatches[11].str();
        switch(submatches[10].str()[0])
        {
            case '+': note.start_volume += stoi(value); break;
            case '-': note.start_volume -= stoi(value); break;
            default : note.start_volume  = stoi(value); break;
        }
    }

    if(submatches[12].str()[0] == '&')
    {
        if(note_holding)
        {
            // ホールドしている音符を追加
            note_hold.end_scale = note.start_scale;
            note_hold.end_volume = note.start_volume;
            
            score.push(note_hold);
        }

        note_hold = note;
        note_holding = true;
    }
    else
    {
        if(note_holding)
        {
            // ホールドしている音符を追加
            note_hold.end_scale = note.start_scale;
            note_hold.end_volume = note.start_volume;
            score.push(note_hold);
        }

        // 作成した音符を追加
        note.end_scale = note.start_scale;
        note.end_volume = note.start_volume;
        score.push(note);

        note_holding = false;
    }

    position += note.length;
}

void score_builder::add_rest (smatch submatches)
{
    #ifdef RATIONAL
    note note = { position, { 1, length }, 0, 0, 0, 0, 0, sound };
    #else
    note note = { position, 1.0 / length, 1.0, 0, 0, 0, 0, sound };
    #endif
    string match = "";

    match = submatches[1].str();
    if(match != "")
    {
        #ifdef RATIONAL
        note.length = { 0, 4 };
        #else
        note.length = 0;
        #endif
        string value = "";
        bool plus = true;

        for(char c : match)
            switch (c)
            {
                case '+':
                    #ifdef RATIONAL
                    note.length += { plus ? 1 : -1, stoi(value) };
                    #else
                    note.length += (plus ? 1.0 : -1.0) / stod(value) ;
                    #endif
                    value = "";
                    plus = true;
                    break;
                case '-':
                    #ifdef RATIONAL
                    note.length += { plus ? 1 : -1, stoi(value) };
                    #else
                    note.length += (plus ? 1.0 : -1.0) / stod(value) ;
                    #endif
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
                case '.':
                    #ifdef RATIONAL
                    note.length *= { 3, 2 }; break;
                    #else
                    note.length *= 1.5; break;
                    #endif
            }
            
    score.push(note);
    position += note.length;
}