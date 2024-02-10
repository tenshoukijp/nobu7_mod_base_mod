#include <windows.h>
#include <string>

bool isFileExists(const std::string& filename) {
    if (filename == "") {
        return false;
    }
    return GetFileAttributesA(filename.c_str()) != INVALID_FILE_ATTRIBUTES;
}
