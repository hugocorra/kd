#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/map.hpp>

#include <boost/config/select_platform_config.hpp>

namespace po = boost::program_options;

typedef std::map<std::string, std::string> MapAlias;

std::string getStorageFile()
{
    boost::filesystem::path path;
    path = std::getenv(BOOST_WINDOWS ? "HOMEPATH" :  "HOME");
    path /= ".kd_database";
    return path.string();
}

// add a new alias or throw in case it already exists.
void add(const std::string& alias, const std::string& path, MapAlias& map_alias)
{
    auto it = map_alias.find(alias);

    if (it != map_alias.end())
        throw(std::runtime_error("alias already exists!"));

    map_alias[alias] = path;
}

// remove an alias or throw in the case it doesn't exist.
void remove(const std::string& alias, MapAlias& map_alias)
{
    auto it = map_alias.find(alias);

    if (it != map_alias.end())
        map_alias.erase(it);
        return;

    throw(std::runtime_error("alias doesn't exists!"));
}

// return how many characters the greatest alias has...
size_t get_max_alias_size(const MapAlias& map_alias)
{
    size_t size = 0;

    for (auto it : map_alias)
        if (it.first.size() > size)
            size = it.first.size();

    return size;
}

// list all aliases.
void list(const MapAlias& map_alias)
{
    size_t max_columns = get_max_alias_size(map_alias);
    std::cout.flags(std::ios::left);
    std::cout.width(max_columns);

    for (const auto& it : map_alias)
        std::cout << it.first << " -> " << it.second << std::endl;
}

// serialize the map of aliases.
void save(const MapAlias& map_alias)
{
    std::ofstream ofs(getStorageFile());

    if (ofs.is_open())
    {
        boost::archive::text_oarchive output(ofs);
        output << map_alias;
    }
}

// deserialize the map of aliases.
void load(MapAlias& map_alias)
{
    std::ifstream ifs(getStorageFile());

    if (ifs.is_open())
    {
        boost::archive::text_iarchive input(ifs);
        input >> map_alias;
    }
}

// serialization for a vetor of T.
 template<class T>
 std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
 {
     std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " ")); 
     return os;
 }

 int main(int argc, char *argv[])
{
    getStorageFile();

    MapAlias map_alias;

    load(map_alias);

    try
    {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("add,a", po::value<std::string>(), "create a new alias")
            ("alias", po::value<std::string>(), "")
            ("remove,r", po::value<std::string>(), "remove an alias")
            ("list,l", "")
        ;

        po::positional_options_description p;
        p.add("alias", -1);
        
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);
    
        if (vm.count("help")) {
            std::cout << "Usage: options_description [options]\n";
            std::cout << desc;
            return 0;
        }

        if (vm.count("add"))
        {
            if (vm.count("alias"))
            {
                add(vm["alias"].as<std::string>(), vm["add"].as<std::string>(), map_alias);
                save(map_alias);
            }
            else
                throw(std::runtime_error("an alias should be specified"));
        }
        else if (vm.count("remove"))
        {
            remove(vm["remove"].as<std::string>(), map_alias);
            save(map_alias);
        }
        else if (vm.count("list"))
        {
            list(map_alias);
        }
        else if (vm.count("alias"))
        {
            auto it = map_alias.find(vm["alias"].as<std::string>());
            if (it != map_alias.end())
                std::cout << it->second;
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }

    return 0;
}
