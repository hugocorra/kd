#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

typedef std::map<std::string, std::string> MapAlias;

void add(const std::string& alias, const std::string& path, MapAlias& map_alias)
{
    auto it = map_alias.find(alias);

    if (it != map_alias.end())
        throw(std::runtime_error("alias already exists!"));

    map_alias[alias] = path;
}

void remove(const std::string& alias, MapAlias& map_alias)
{
    auto it = map_alias.find(alias);

    if (it != map_alias.end())
        map_alias.erase(it);
        return;

    throw(std::runtime_error("alias doesn't exists!"));
}

int get_max_alias_size(const MapAlias& map_alias)
{
    int size = 0;

    for (auto it : map_alias)
        if (it.first.size() > size)
            size = it.first.size();

    return size;
}


void list(const MapAlias& map_alias)
{
    int max_columns = get_max_alias_size(map_alias);
    std::cout.flags(std::ios::left);
    std::cout.width(max_columns);

    for (const auto& it : map_alias)
        std::cout << it.first << " -> " << it.second << std::endl;
}


int main(int argc, char const *argv[])
{
    MapAlias map_alias;

    map_alias.insert(std::make_pair("hello", "C:\\Users\\Hugo\\Desenvolvimento\\GitHub\\kd\\Build"));
    map_alias.insert(std::make_pair("h", "C:\\Users\\Hugo\\Desenvolvimento\\GitHub\\kd\\Build"));

    list(map_alias);

    return 0;
}