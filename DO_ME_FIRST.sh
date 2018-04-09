#!/bin/bash

# REMEMBER TO REMOVE THE ORIGINAL REMOTE OF THE REPO BEFORE PUSHING!
#
# To use AI-Toolbox at the current version, you must run the initial submodule
# commands yourself.
#
# So what you need to do is:
#
# - `git submodule init`
# - `git submodule add https://github.com/Svalorzen/AI-Toolbox.git deps/AI-Toolbox`
# - Delete this file.
# - `git ci -m "Added AI-Toolbox"`
#
# Or you can just call this script.

set -ex

# Detach this repo from its original remote
git remote rm origin

# Init submodules and get AI-Toolbox
git submodule init
git submodule add https://github.com/Svalorzen/AI-Toolbox.git deps/AI-Toolbox

# Remove this file from repo and commit changes.
rm -- "$0"
git add "$0"
git ci -m "Added AI-Toolbox"
