#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

class Novastore_Probeaufgabe
{
public:
	int Run(int argc, char **argv)
	{
		using namespace std::string_view_literals;
		namespace po = boost::program_options;

		unsigned int cpus = std::thread::hardware_concurrency();
		bool help = false;
		std::vector<std::string> paths;
		// Declare the supported options.
		po::options_description desc("Options");
		desc.add_options()
			("help,h", "this help message")
			("threads,t", po::value(&cpus)->default_value(cpus), "set number of threads to use");
		po::options_description hidden("hidden options");
		hidden.add_options()
			("path", po::value(&paths), "path to search");

		po::positional_options_description posOpts;
		posOpts.add("path", -1);

		po::options_description cmdLineOptions;
		cmdLineOptions.add(desc).add(hidden);

		po::variables_map vm;
		po::command_line_parser parser(argc, argv);
		parser.options(cmdLineOptions)
			.positional(posOpts);
		po::store(parser.run(), vm);
		po::notify(vm);

		if (vm.count("help") > 0)
		{
			std::filesystem::path path(argv[0]);
			std::cout << "Synopsis: "sv << path.filename() << " [Options] [paths]\n"sv << std::endl;
			std::cout << desc << "\n";
			return EXIT_SUCCESS;
		}

		std::cout << "Using " << cpus << " threads" << std::endl;
		for (const auto& p : paths)
		{
			std::cout << "path: " << p << std::endl;
		}

		return EXIT_SUCCESS;
	}
};

int main(int argc, char **argv)
{
	Novastore_Probeaufgabe app;
	return app.Run(argc, argv);
}
