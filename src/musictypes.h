#include <vector>

enum MusicVariant
{
    MAJOR = 0,
    MINOR = 1
};

enum Sound
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

class Scale
{
public:
    Scale(Sound key, MusicVariant variant)
    {
        if (variant == MusicVariant::MAJOR)
        {
            this->sounds = {
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
    std::vector<Sound> get_chord_by_note(Sound note)
    {
        return {sounds.at(0), sounds.at(2), sounds.at(4)};
    }

private:
    std::vector<Sound> sounds;
};