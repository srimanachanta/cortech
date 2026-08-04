# cortech
A suite of tools for cortical layer placement and analysis.

Supports CPython 3.11, 3.12, 3.13, and 3.14.

## Installation From Source

This package compiles some CGAL functions. CGAL itself is fetched and built automatically by meson (as a header-only [wrap](subprojects/cgal.wrap)), so no separate step is needed. CGAL's own dependencies must be available on your system beforehand: Boost >= 1.74, Eigen >= 3.3.4, GMP, and MPFR. Boost is located by meson's built-in Boost detection and Eigen via pkg-config. GMP and MPFR are looked up via pkg-config first, falling back to plain library lookup on systems that ship no `gmp.pc` or `mpfr.pc`. The build fails immediately with a clear error naming whichever of these isn't found.

### macOS

    brew install boost eigen gmp mpfr pkg-config
    pip install .

### Linux (Debian/Ubuntu)

    sudo apt install libboost-dev libeigen3-dev libgmp-dev libmpfr-dev pkg-config
    pip install .

### Windows, or any OS via conda-forge

Boost, GMP, and MPFR don't build cleanly under plain MSVC, so conda-forge is the simplest route on Windows (and works identically on any OS):

    conda install -c conda-forge boost eigen gmp mpfr pkg-config
    pip install .

For an editable (developer) install, add `-e` and drop build isolation once the above dependencies are installed:

    pip install --no-build-isolation --no-deps -e .
