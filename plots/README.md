How to Run the Experiments
==========================

Requirements
------------

Using these facilities assumes that the source files of the experiments were in
the form `{environment_name}_{method_name}_main.cpp`.

Running Experiments
-------------------

The list of experiments to run needs to be contained inside a `.json` file. An
example one already exists: the file `experiments.json` in the `experiments`
folder. It contains a list of executables and the parameters with which they
must be run.

The file can be given as input to the `runExperiments.py` script, as
```
./runExperiments.py experiments/experiments.json
```
In case you do not want to run all experiments contained in the JSON file, the
script contains some rudimentary filtering abilities. For example, you can do
```
./runExperiments.py experiments/experiments.json -e some_environment -a some_algorithm -p epsilon=0.9
```
to only run the experiments in `some_environment` using `some_algorithm`, and
with the parameter `epsilon` set to `0.9`. Calling
```
./runExperiments.py --help
```
will give a brief help of the available flags.

The script will generate automatically, based on the information contained in the `json`
file, a series of folders - one per each separate experiment, and inside one per
each method. Each folder will contain:

- A `log` folder containing all outputs to `stdout` and `stderr` of all the runs
  - one for each set of parameters.
- A `statistics` folder containing, for each run, a file with the number of
  seconds that the particular run took to complete.

In particular, the executables for the experiments themselves create a file
containing the average rewards over all episodes/timestep.

Note that an experiment will be run ONLY IF the output file of the experiments
does not exist, or the executable of the experiment has been updated more
recently than the last generated output for it. This avoids duplicating work
when unneeded.

Plotting
--------

*The plotting scripts assume that the files have been outputted using the
`AIToolbox::Statistics` class!*, or using its same output format (check its
documentation).

The output files can be given to the `Scripts/plotResult.py` script, which will create
an appropriate plot of the input files using an intermediate GnuPlot script.

The script has a *bunch* of options, which you can check by calling it without
any arguments. An example call might be:
```
./Scripts/plotResults.py --output=out.pdf --xtics=50 --xrange=200 --yrange="-25:25" --ytics=10  experiments/results/ some_environment algo1 skip algo3
```
This generates a PDF output `out.pdf` using the result files contained in the
`experiments/results` folder. In particular, it uses the ones related to the
`some_environment` environment, and it will plot the results for `algo1` and
`algo3`. The `skip` parameter is used as the line colors in the plot are
position dependent, `skip` is just used to "skip" a line color to maintain
consistency across multiple plots.

Additional Utilities
--------------------

Some additional scripts are provided, but you won't generally need them.

The `statistics.py` script can be used to generate statistics on the execution
time of experiments run using the `runExperiments.py` script. Additionally it
can be used to generate an `experiment.json` file made of partitions, where each
partition should take an approximately equal time to complete (in case the
various algorithms being tested have different compute requirements).

The `transform.py` script can be used to add, subtract or otherwise manipulate
different experiment files. This can be useful for example if a run has been
split into multiple separate processes for speed, and now one needs to combine
the results together.

The `convert.py` script is used to automatically call `transform.py` on a folder
containing multiple results. This script should probably be modified by hand
before being used.
