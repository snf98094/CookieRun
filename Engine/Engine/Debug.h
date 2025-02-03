#include <iostream>
#include <fstream>
#include <cstring>

class Debug
{
public:
    static void Log(const char* log)
    {
        // Append the log message to the static text buffer
        strncat_s(text, sizeof(text), log, _TRUNCATE);
        strncat_s(text, sizeof(text), "\n", _TRUNCATE);

        // Write the log to the text file
        std::ofstream outFile;
        outFile.open("log.txt", std::ios::out); // Open the file in write mode (overwrite)
        if (outFile.is_open())
        {
            outFile << text;
            outFile.close();
        }
        else
        {
            std::cerr << "Failed to open log.txt for writing." << std::endl;
        }
    }

private:
    static char text[256];
};

char Debug::text[256] = ""; // Initialize the static member