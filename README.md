This repository contains a set of modifications to [llvm-project](https://github.com/llvm/llvm-project) to enable additional checks for Clang Static Analyzer and Clang-Tidy. Specifically, Clang Static Analyzer is modified to report places where a program fails to handle out-of-memory conditions and implicitly assumes that dynamic memory allocation (of any kind) succeeds, and Clang-Tidy is modified to include a new check within a new module, facilitating future custom Clang-Tidy checks.

# Directory Structure

The `llvm-changes` directory mirrors the directory structure of the [llvm-project](https://github.com/llvm/llvm-project) repo, but it only contains new or modified files. The file `llvm-version.txt` contains a commit hash or tag name corresponding to the llvm-project version over which the `llvm-changes` directory masks. While a branch name might also work, branch tips are constantly updated and therefore don't serve the purpose of reproducability.

The bin directory contains several scripts. `save-changes` and `load-changes` are used to copy changes between `llvm-changes` and the llvm-project repo. `build-llvm` is used to compile the llvm-project repo. `clang-analyzer` and `clang-tidy-wrapper` run the locally compiled Clang Static Analyzer and Clang-Tidy, respectively.

# Environment Setup

## llvm-project Repo

If you haven't already, you should clone the [llvm-project](https://github.com/llvm/llvm-project) repo.

```sh
# Clone the full repository with all commits (more versatile)
git clone https://github.com/llvm/llvm-project.git <path to llvm-project>
# Clone only the necessary version (faster and smaller)
git init <path to llvm-project>
git -C <path to llvm-project> remote add origin https://github.com/llvm/llvm-project.git
git -C <path to llvm-project> fetch --depth=1 origin "$(cat llvm-version.txt)"
```

Then, you should switch to the right version.

```sh
git -C <path to llvm-project> checkout "$(cat llvm-version.txt)"
```

## llvm-project Symlink

Unless you chose to clone llvm-project into a directory called `llvm-project` in this repo's root, you will need to create a symbolic link called `llvm-project` in this repo's root that points to the llvm-project repo.

```sh
# Note: if a relative path is specified, it must be relative to the symlink, not the CWD
# (for simplicity, run this command from this repo's root)
ln -s <path to llvm-project> llvm-project
```

# Development

The `load-changes` and `save-changes` scripts copy changes from `llvm-changes` to `llvm-project` and from `llvm-project` to `llvm-changes`, respectively. Note that `save-changes` will discard any changes in `llvm-changes` that were reverted in `llvm-project`. **You should not stage or commit any changes in the llvm-project repo.** Use `load-changes` to copy the changes over to the `llvm-changes` directory in this repo and make your commits here.

The `build-llvm` script compiles the necessary parts of the llvm-project repo for the required executables. Currently, it will compile `clang` among other things by default (enough for the Clang Static Analyzer), and if `--clang-tidy` is specified, it will complile `clang-tidy` as well. It will try to use [Ninja](https://ninja-build.org/) by default, but it also supports Make, which is slower. View all options with `-h` or `--help`. The compiled binaries will be located in `llvm-build/bin`.

The `clang-analyzer` and `clang-tidy-wrapper` scripts set up the necessary parameters so that they can simply take a list of files to analyze. Since all of their arguments are passed to `clang`, you can use other flags as well. For example, you can use `clang-tidy-wrapper --list-checks` to view all Clang-Tidy checks enabled by the script. Note that, for the `clang-analyzer` script, `clang` is in its default GCC compatibility driver interface (not using `-cc1`).

# Limitations

Currently, there is not a way to indicate that a file from `llvm-project` should be deleted. If this is required in the future, maybe a file in this repository could be created that lists all the files/directories in `llvm-project` that need to be deleted.

As of 2024, CMake version 3.20.0 or higher is required to compile `llvm-project`. If the default CMake is too old, you can pass the path to a newer CMake binary to `build-llvm` using the `--cmake-exec` option.

When running `build-llvm`, you should try to be consistent in your choice of generator. `build-llvm` has not been tested with a mix of Ninja and Make (e.g. building with Ninja, making changes, and rebuilding with Make).

When running `clang-tidy` naively, you may get an error about a missing compile command database. For more information on this, see the [Clang-Tidy documentation](https://clang.llvm.org/extra/clang-tidy/).
