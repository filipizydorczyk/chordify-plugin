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
    Scale(Sound key, MusicVariant variant) {}
    ~Scale() {}
    std::vector<Sound> getChordByNote(Sound note) {}
};