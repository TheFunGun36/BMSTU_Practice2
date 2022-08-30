#include "Printable.h"
#include <sstream>

std::string Printable::to_string() const {
    std::stringstream sstr;
    add_to_stream(sstr) << '\0';
    return sstr.str();
}

std::wstring Printable::to_wstring() const {
    std::wstringstream sstr;
    add_to_stream(sstr) << L'\0';
    return sstr.str();
}

std::ostream& operator<<(std::ostream& stream, const Printable& printable) {
    return printable.add_to_stream(stream);
}

std::wostream& operator<<(std::wostream& stream, const Printable& printable) {
    return printable.add_to_stream(stream);
}