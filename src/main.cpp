#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

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

size_t get_max_alias_size(const MapAlias& map_alias)
{
    size_t size = 0;

    for (auto it : map_alias)
        if (it.first.size() > size)
            size = it.first.size();

    return size;
}


void list(const MapAlias& map_alias)
{
    size_t max_columns = get_max_alias_size(map_alias);
    std::cout.flags(std::ios::left);
    std::cout.width(max_columns);

    for (const auto& it : map_alias)
        std::cout << it.first << " -> " << it.second << std::endl;
}


 template<class T>
 std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
 {
     std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " ")); 
     return os;
 }

 int main(int argc, char *argv[])
{
	MapAlias map_alias;

	try
	{
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
			("add,a", po::value<std::string>(), "create a new alias")
			("alias", po::value<std::string>(), "")
			("remove,r", po::value<std::string>(), "remove an alias")
            ("list,l", "")
            //("optimization", po::value<int>(&opt)->default_value(10), "optimization level")
            //("verbose,v", po::value<int>()->implicit_value(1), "enable verbosity (optionally specify level)")
            //("listen,l", po::value<int>(&portnum)->implicit_value(1001)->default_value(0,"no"), "listen on a port.")
            //("include-path,I", po::value< std::vector<std::string> >(), "include path")
            //("input-file", po::value< std::vector<std::string> >(), "input file")
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
            }
            else
                throw(std::runtime_error("an alias should be specified"));
        }
		else if (vm.count("remove"))
		{
			std::cout << "REMOVE: " << vm["remove"].as<std::string>() << "\n";
		}
        else if (vm.count("list"))
		{
            std::cout << "list" << "\n";
			//std::cout << "REMOVE: " << vm["remove"].as<std::string>() << "\n";
		}
        else if (vm.count("alias"))
        {
            std::cout << "Input files are: " << vm["alias"].as< std::string>() << "\n";
        }

        //if (vm.count("verbose")) {
        //    std::cout << "Verbosity enabled.  Level is " << vm["verbose"].as<int>()
        //         << "\n";
        //}

        //std::cout << "Optimization level is " << opt << "\n";                
        //std::cout << "Listen port is " << portnum << "\n";

        list(map_alias);
	}
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }
    //MapAlias map_alias;

    //map_alias.insert(std::make_pair("hello", "C:\\Users\\Hugo\\Desenvolvimento\\GitHub\\kd\\Build"));
    //map_alias.insert(std::make_pair("h", "C:\\Users\\Hugo\\Desenvolvimento\\GitHub\\kd\\Build"));

    //list(map_alias);

    return 0;
}
//#include <boost/program_options.hpp>
//
//using namespace boost;
//namespace po = boost::program_options;
//
//#include <iostream>
//#include <algorithm>
//#include <iterator>
//using namespace std;
//
//
//// A helper function to simplify the main part.
//template<class T>
//ostream& operator<<(ostream& os, const vector<T>& v)
//{
//    copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); 
//    return os;
//}
//
//int main(int ac, char* av[])
//{
//    try {
//        int opt;
//        int portnum;
//        po::options_description desc("Allowed options");
//        desc.add_options()
//            ("help", "produce help message")
//            ("optimization", po::value<int>(&opt)->default_value(10), 
//                  "optimization level")
//            ("verbose,v", po::value<int>()->implicit_value(1),
//                  "enable verbosity (optionally specify level)")
//            ("listen,l", po::value<int>(&portnum)->implicit_value(1001)
//                  ->default_value(0,"no"),
//                  "listen on a port.")
//            ("include-path,I", po::value< vector<string> >(), 
//                  "include path")
//            ("input-file", po::value< vector<string> >(), "input file")
//        ;
//
//        po::positional_options_description p;
//        p.add("input-file", -1);
//        
//        po::variables_map vm;
//        po::store(po::command_line_parser(ac, av).
//                  options(desc).positional(p).run(), vm);
//        po::notify(vm);
//    
//        if (vm.count("help")) {
//            cout << "Usage: options_description [options]\n";
//            cout << desc;
//            return 0;
//        }
//
//        if (vm.count("include-path"))
//        {
//            cout << "Include paths are: " 
//                 << vm["include-path"].as< vector<string> >() << "\n";
//        }
//
//        if (vm.count("input-file"))
//        {
//            cout << "Input files are: " 
//                 << vm["input-file"].as< vector<string> >() << "\n";
//        }
//
//        if (vm.count("verbose")) {
//            cout << "Verbosity enabled.  Level is " << vm["verbose"].as<int>()
//                 << "\n";
//        }
//
//        cout << "Optimization level is " << opt << "\n";                
//
//        cout << "Listen port is " << portnum << "\n";                
//    }
//    catch(std::exception& e)
//    {
//        cout << e.what() << "x\n";
//        return 1;
//    }    
//    return 0;
//}