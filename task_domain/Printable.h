#pragma once
#include <string>
#include <ostream>

class Printable {
public:
    virtual std::string to_string() const final;
    virtual std::wstring to_wstring() const final;
    friend std::ostream& operator<<(std::ostream& stream, const Printable& position);
    friend std::wostream& operator<<(std::wostream& stream, const Printable& position);

    inline virtual ~Printable() = default;

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const = 0;
    virtual std::wostream& add_to_stream(std::wostream& stream) const = 0;
};
