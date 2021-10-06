#include <vector>
#include <algorithm>

enum MusicVariant : uint8_t
{
    MAJOR = 0,
    MINOR = 1
};

enum Sound : uint8_t
{
    C = 0,
    CIS = 1,
    D = 2,
    DIS = 3,
    E = 4,
    F = 5,
    FIS = 6,
    G = 7,
    GIS = 8,
    A = 9,
    AIS = 10,
    B = 11,
};

static int8_t get_index(std::vector<Sound> v, Sound K)
{
    auto it = std::find(v.begin(), v.end(), K);

    if (it != v.end())
    {
        int8_t index = it - v.begin();
        return index;
    }
    return 0;
}

class Scale
{
public:
    Scale(Sound key, MusicVariant variant)
    {
        if (variant == MusicVariant::MAJOR)
        {
            this->m_Sounds = {
                key,
                static_cast<Sound>(key + 2),
                static_cast<Sound>(key + 4),
                static_cast<Sound>(key + 5),
                static_cast<Sound>(key + 7),
                static_cast<Sound>(key + 9),
                static_cast<Sound>(key + 11)};
        }
    }
    ~Scale() {}

    std::vector<int8_t> get_chord_by_note(Sound note, int8_t octave)
    {

        int8_t index = get_index(m_Sounds, note);

        return {
            //I am actually not sure if plain int wasn't better
            static_cast<int8_t>(m_Sounds.at(index % 7) + (octave + 1) * 12),
            static_cast<int8_t>(m_Sounds.at((index + 2) % 7) + (octave + 1) * 12),
            static_cast<int8_t>(m_Sounds.at((index + 4) % 7) + (octave + 1) * 12)};
    }

private:
    std::vector<Sound> m_Sounds;
};
