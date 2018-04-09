// ########################################################################
// #
// # EXAMPLE EXECUTABLE FILE
// #
// # This file only exists es an example project, to possibly copy-paste to
// # speed you up.
// #
// # Please read the comments throughout as they explain how to setup/use
// # features of AI-Toolbox in your project.
// #
// # Feel free to delete it if you do not need it.
// #
// ########################################################################

// Used for handling interrupt signals
#include <csignal>
// Used for input/output
#include <iostream>
#include <fstream>
// Used to generate random numbers
#include <random>

// Used to obtain an unique identifier of the git commit that is being
// compiled.
#include <GitHash.hpp>
// Used to handle simple command line arguments.
#include <CommandLineParsing.hpp>

// AI-Toolbox basic seed generator for random engines.
#include <AIToolbox/Seeder.hpp>
// AI-Toolbox basic utility to generate mean and variance for data.
#include <AIToolbox/Tools/Statistics.hpp>

// ########################################################################
// #
// # LOGGING
// #
// # The code below is used in case AI-Toolbox has been compiled with logging
// # enabled. In this case, we create a simple printing function that will output
// # debug messages from AI-Toolbox.
// #
// ########################################################################
#ifdef AI_LOGGING_ENABLED
#include <AIToolbox/Logging.hpp>
void logger(int severity, const char * message) {
    std::cout << '[' << severity << "] " << message << '\n';
}
#endif

// ########################################################################
// #
// # OUTPUT HANDLING AND SIGNALS
// #
// # It generally happens that you might want to save the data you generate
// # from your AI-Toolbox experiments to a file.
// #
// # You might also want to still output results in case the program crashes or
// # is interrupted.
// #
// # Here we declare two functions, one to output data to a file, and the
// # second that will catch signals. They are defined at the bottom of this file.
// #
// ########################################################################
void outputData(std::ofstream & file, const AIToolbox::Statistics & stats);
void signal_callback_handler(int /* signum */);

// Because the signal handler is not called from the "common" execution path,
// we must store anything we might need in case of a signal being received in a
// global place where we can reach it. This struct is that global place.
//
// In these case, each of these fields is something we want to log to a file in
// case a signal is catched.
struct {
    // Experiment parameters.
    int seed;
    std::string filename;

    unsigned experimentsNum;
    unsigned timestepsNum;

    // Additional info to print.
    unsigned currentExperiment;
    unsigned currentTimestep;

    // Statistics object to compute data statistics.
    //
    // This field is a pointer because AIToolbox::Statistics's constructor
    // requires a timestep parameter that we do not yet have (it is user
    // input). We setup the Statistics object as soon as we can in the main
    // code.
    AIToolbox::Statistics * statPointer;
} info;

// ########################################################################
// #
// # ENTRY POINT OF THE EXECUTABLE
// #
// ########################################################################
int main(int argc, char** argv) {
    // If logging is needed, this code provides the logging function we have
    // defined earlier to AI-Toolbox so that it can actually output its
    // debugging messages.
#ifdef AI_LOGGING_ENABLED
    AIToolbox::AILogger = logger;
#endif

    // If catching signals is needed, this line registers our
    // signal_callback_handler to be called in case of SIGINT interrupts
    // (usually CTRL-C). Additional signals can be catched if desired.
    signal(SIGINT, signal_callback_handler);

    // ####################################################################
    // #
    // # ARGUMENT PARSING
    // #
    // # This code uses a custom wrapping of Boost's argument parsing library.
    // # The wrappers are found in the `include/CommandLineParsing.hpp` file of
    // # this project.
    // #
    // ####################################################################
    Options options;

    // Adding options to parse.
    options.push_back(makeRequiredOption ("seed,s",         &info.seed,             "set the experiment's seed"                 ));
    options.push_back(makeDefaultedOption("experiments,e",  &info.experimentsNum,   "set the number of experiments",        1u  ));
    options.push_back(makeDefaultedOption("timesteps,t",    &info.timestepsNum,     "set the timesteps per experiment", 40000u  ));
    options.push_back(makeRequiredOption ("output,o",       &info.filename,         "set the final output file"                 ));

    // Parse command line options
    if (!parseCommandLine(argc, argv, options))
        return 1;

    // ####################################################################
    // #
    // # REMAINING GENERAL SETUP
    // #
    // # Here we can setup anything else we need.
    // #
    // # In this case we're setting up the random seed generator for
    // # AI-Toolbox, and a C++ random engine to generate random numbers.
    // #
    // # We are also setting up the AI-Toolbox's Statistics object so we can
    // # save data and later compute its mean and variance.
    // #
    // # Remember that the documentation for these classes is always available
    // # on AI-Toolbox's docs page.
    // #
    // ####################################################################
    AIToolbox::Seeder::setRootSeed(info.seed);
    std::default_random_engine engine(AIToolbox::Seeder::getSeed());

    // Setup data recorder.
    AIToolbox::Statistics stats(info.timestepsNum);
    // Set signal catcher Statistics pointer to the newly created Statistics
    // object.
    info.statPointer = &stats;

    // ####################################################################
    // #
    // # ACTUAL EXPERIMENT
    // #
    // # The way I generally use AI-Toolbox is to run a set of experiments,
    // # each with a set of timesteps. This is what these for loops do.
    // #
    // # If you need something else you can completely replace this part.
    // #
    // ####################################################################
    for (info.currentExperiment = 0; info.currentExperiment < info.experimentsNum; ++info.currentExperiment) {
        for (info.currentTimestep = 0; info.currentTimestep < info.timestepsNum; ++info.currentTimestep) {
            std::cout << '[' << info.currentExperiment << "] Timestep " << info.currentTimestep << '\n';

            // Record data.
            const double value = 0.0;
            stats.record(value, info.currentTimestep);
        }
    }

    // ####################################################################
    // #
    // # DATA OUTPUT
    // #
    // # Finally, we simply create an output file, and dump the statistics data
    // # into it.
    // #
    // ####################################################################
    std::ofstream file(info.filename);
    outputData(file, stats);
}

void signal_callback_handler(int /* signum */) {
    std::ofstream file(info.filename);

    // Add to the output a warning that this was generated after an interrupt.
    file << "#########################\n";
    file << "# RUN ENDED WITH SIGINT\n";
    file << "# AT EXPERIMENT: " << info.currentExperiment << '\n';
    file << "# AT TIMESTEP:   " << info.currentTimestep << '\n';
    file << "#########################\n";

    // Actually output the data.
    outputData(file, *info.statPointer);

    // Since we received a signal, the program is supposed to stop. Thus, we
    // abort.
    std::abort();
}

void outputData(std::ofstream & file, const AIToolbox::Statistics & stats) {
    // GitHash is a custom system that allows you to retrieve `git` information
    // in your code. This allows you, for example, to add to your output the
    // hash of the commit of the code that is being run.
    //
    // This can be really useful if you often modify code and risk mixing
    // result files from slightly different branches.
    file << "# OUTPUT PRODUCED WITH HASH: " << GitHash::sha1 << (GitHash::dirty ? "-dirty" : "") << '\n';

    file << stats << std::flush;
}
