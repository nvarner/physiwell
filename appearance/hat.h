#include <string>

enum HatHeight {
    Tall,
    Short,
};

class Hat {
public:
    Hat(const HatHeight height, const std::string color);

    const HatHeight & get_height() const;
    const std::string & get_color() const;
    std::string get_description() const;
private:
    const HatHeight height;
    const std::string color;
};