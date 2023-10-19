#include <iostream>
#include <string>

class Variabel
{       // The class
public: // Access specifier
    struct Mpos
    {
        float x, y, z;
    };
    struct FS
    {
        float f, s;
    };
    struct WCO
    {
        float x, y, z;
    };
    struct PN
    {
        char x, y, z;
    };
    struct OV
    {
        float o, v;
    };
    struct OS
    {
        float o, s;
    };
    static std::string status;
    static Mpos mpos;
    static FS fs;
    static WCO wco;
    static PN pn;
    static OV ov;
    static OS os;
};

std::string Variabel::status;
Variabel::Mpos Variabel::mpos;
Variabel::FS Variabel::fs;
Variabel::WCO Variabel::wco;
Variabel::PN Variabel::pn;
Variabel::OV Variabel::ov;
Variabel::OS Variabel::os;