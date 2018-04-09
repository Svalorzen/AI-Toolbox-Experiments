cmake_minimum_required (VERSION 3.0)

#######################################
##   Experiment Creation Functions   ##
#######################################

# These functions can be used below to easily add experiments to build. The
# only obligatory parameter is the name of the experiment (usually in the format
# experimentname_methodname). Each function can be used depending on which
# features of AIToolbox you need.
#
# If you need to link the experiment file against some additional libraries,
# you can add them as optional arguments after the name.

function (AddExperimentMDP name)
    set(MAKE_MDP 1 CACHE INTERNAL "")
    set(exename ${name}_main)
    add_executable(${exename} ${exename}.cpp)
    target_link_libraries(${exename} AIToolboxMDP ${Boost_LIBRARIES} ${GITHASH_LIBRARIES} ${ARGN})
endfunction (AddExperimentMDP)

function (AddExperimentPOMDP name)
    set(MAKE_POMDP 1 CACHE INTERNAL "")
    set(exename ${name}_main)
    add_executable(${exename} ${exename}.cpp)
    target_link_libraries(${exename} AIToolboxMDP AIToolboxPOMDP ${Boost_LIBRARIES} ${GITHASH_LIBRARIES} ${ARGN})
endfunction (AddExperimentPOMDP)

function (AddExperimentFMDP name)
    set(MAKE_FMDP 1 CACHE INTERNAL "")
    set(exename ${name}_main)
    add_executable(${exename} ${exename}.cpp)
    target_link_libraries(${exename} AIToolboxMDP AIToolboxFMDP ${Boost_LIBRARIES} ${GITHASH_LIBRARIES} ${ARGN})
endfunction (AddExperimentFMDP)

# Here we simply add a definition in case somebody is asking for logging.
if (${AI_LOGGING_ENABLED})
    add_definitions(-DAI_LOGGING_ENABLED)
endif()

############################
##   Experiment Library   ##
############################

# If you need other cpp files to compile for the experiment, enable the
# following library. Remember to add "ExperimentLibrary" as an additional
# parameter to the "AddExperimentXXX" functions (they'll link the
# ExperimentLibrary then through the ARGN parameter).

### EXAMPLE ###
# Create a library containing file1.cpp and file2.cpp:
#
#     add_library(ExperimentLibrary
#         ./file1.cpp
#         ./file2.cpp
#     )
#     target_link_libraries(ExperimentLibrary AIToolboxMDP AIToolboxFMDP ${Boost_LIBRARIES})

############################
## Experiment Declaration ##
############################

# Experiment source files should be in the format:
#
#     experimentname_methodname_main.cpp (e.g. mines_mauce_main.cpp)
#
# An experiment is then added here calling:
#
#     AddExperimentXXX(experimentname_methodname)
#
# where XXX depends on which features of AIToolbox you need.
#
### PYTHON ###
#
# If you need AIToolbox's Python binding, uncomment:
#
#     set(MAKE_PYTHON 1 CACHE INTERNAL "")
#
# Always uncomment the following:
#
#     find_package(PythonLibs 3 REQUIRED)
#     include_directories(SYSTEM ${PYTHON_INCLUDE_DIRS})
#
# Then you need to call AddExperimentXXX(name ${PYTHON_LIBRARIES})

##########################################################
##########################################################
#
# EXAMPLE EXPERIMENT
#
# The following line generates an executable for the example source file
# provided in the repository. Feel free to remove it if you do not need it.

AddExperimentMDP(example_rnd)
