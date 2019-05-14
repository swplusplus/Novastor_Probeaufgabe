#include "workerPool/WorkerPool.h"

#include <boost/program_options.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

namespace program_options = boost::program_options;

class program_option_exception : public std::runtime_error { using std::runtime_error::runtime_error; };
class missing_argument : public program_option_exception { using program_option_exception::program_option_exception; };
class show_help : public std::exception { using std::exception::exception; };

class Novastore_Probeaufgabe
{
public:

	Novastore_Probeaufgabe()
		: m_desc("Options")
		, m_hidden("hidden options")
	{
		using program_options::value;

		// Declare the supported options.
		m_desc.add_options()
			("help,h", "this help message")
			("output,o", value(&outputFile), "name of output file")
			("threads,t", value(&threads)->default_value(threads), "set number of threads to use");
		m_hidden.add_options()
			("path", value(&pathList), "path to search");
		m_posOpts.add("path", -1);
		m_cmdLineOptions.add(m_desc).add(m_hidden);
	}

	int Run(int argc, char **argv)
	{
		ParseOptions(argc, argv);

		std::ofstream output(outputFile);
		if (!output)
		{
			throw std::runtime_error("Failed to open output file.");
		}

		std::cout << "Using " << threads << " threads" << std::endl;

		for (const auto& p : pathList)
		{
			std::cout << "path: " << p << std::endl;
		}

		std::vector<std::filesystem::path> paths{ pathList.begin(), pathList.end() };
		WorkerPool workerPool(threads, paths, &output);
		workerPool.Join();

		return EXIT_SUCCESS;
	}

	void Help(std::ostream& out, char* argv0)
	{
		using namespace std::string_view_literals;
		std::filesystem::path path(argv0);
		out << "Synopsis: "sv << path.filename() << " [Options] [paths]\n"sv << std::endl;
		out << m_desc << "\n";
	}

private:
	void ParseOptions(int argc, char** argv)
	{
		namespace po = program_options;
		po::variables_map vm;
		po::command_line_parser parser(argc, argv);
		parser.options(m_cmdLineOptions)
			.positional(m_posOpts);
		po::store(parser.run(), vm);
		po::notify(vm);
		if (vm.count("help") > 0)
		{
			throw show_help{};
		}
		if (outputFile.empty())
		{
			throw missing_argument("No output file given.");
		}
		if (pathList.empty())
		{
			throw missing_argument("No input paths given.");
		}
	}


private:
	program_options::options_description m_desc;
	program_options::options_description m_hidden;
	program_options::options_description m_cmdLineOptions;
	program_options::positional_options_description m_posOpts;

	std::string outputFile;
	std::vector<std::string> pathList;
	unsigned int threads = std::thread::hardware_concurrency();
};

int main(int argc, char **argv)
{
	Novastore_Probeaufgabe app;
	try
	{
		return app.Run(argc, argv);
	}
	catch (const show_help&)
	{
		app.Help(std::cout, argv[0]);
		return EXIT_SUCCESS;
	}
	catch (const std::runtime_error& e)
	{
		app.Help(std::cerr, argv[0]);
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
