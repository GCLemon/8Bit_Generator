#include "../header/score_builder.hpp"

using namespace retro_sound;

queue<note> score_builder::convert(queue<string> note_str)
{
    smatch submatches;

    while(!note_str.empty())
    {
        string token_str = note_str.front();

        if(regex_match(token_str, submatches, regex(n_str)))
            add_note(submatches);

        if(regex_match(token_str, submatches, regex(r_str)))
            add_rest(submatches);
            
        if(regex_match(token_str, submatches, regex(o_str)))
            set_octave(submatches);

        if(regex_match(token_str, submatches, regex(l_str)))
            set_length(submatches);

        if(regex_match(token_str, submatches, regex(v_str)))
            set_volume(submatches);

        if(regex_match(token_str, submatches, regex(at_k_str)))
            set_key(submatches);

        if(regex_match(token_str, submatches, regex(at_i_str)))
            set_sound(submatches);

        if(regex_match(token_str, submatches, regex(at_m_str)))
            set_tempo(submatches);

        note_str.pop();
    }

    return score;
}

queue<tempo_change> score_builder::get_tempo_change()
{
    queue<tempo_change> que;
    for(auto c : change) que.push(c);
    return que;
}