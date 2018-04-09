#include <iostream>
#include <fstream>
#include <random>

#include <CommandLineParsing.hpp>

#include <AIToolbox/Impl/Seeder.hpp>
#include <AIToolbox/Tools/Statistics.hpp>

#ifdef AI_LOGGING_ENABLED
#include <AIToolbox/Impl/Logging.hpp>
void logger(int severity, const char * message) {
    std::cout << '[' << severity << "] " << message << '\n';
}
#endif

int main(int argc, char** argv) {
#ifdef AI_LOGGING_ENABLED
    // Setup logger if needed
    AIToolbox::AILogger = logger;
#endif

    // Parameter variables.
    int seed;
    unsigned experiments;
    unsigned timesteps;
    std::string filename;

    Options options;

    // Adding options to parse.
    options.push_back(makeRequiredOption ("seed,s",         &seed,          "set the experiment's seed"));
    options.push_back(makeDefaultedOption("experiments,e",  &experiments,   "set the number of experiments",        1u));
    options.push_back(makeDefaultedOption("timesteps,t",    &timesteps,     "set the timesteps per experiment",     40000u));
    options.push_back(makeRequiredOption ("output,o",       &filename,      "set the final output file"));

    // Parse command line options
    if (!parseCommandLine(argc, argv, options))
        return 1;

    // Setup random engines/seeds
    AIToolbox::Impl::Seeder::setRootSeed(seed);
    std::default_random_engine engine(AIToolbox::Impl::Seeder::getSeed());

    // Setup Experiment...

    // Setup data recorder.
    AIToolbox::Statistics stats(timesteps);

    // Begin Experiment.
    for (unsigned e = 0; e < experiments; ++e) {
        std::cout << "Experiment " << e+1 << '\n';

        for (unsigned t = 0; t < timesteps; ++t) {
            std::cout << "Timestep " << t + 1 << '\n';

            // Record data.
            const double value = 0.0;
            stats.record(value, t);
        }
    }

    // Store data in output file.
    std::ofstream file(filename);
    file << stats;
}
