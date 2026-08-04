project('cgal', 'cpp', version: '6.2')

cpp = meson.get_compiler('cpp')

# CGAL 6.2 requires Boost >= 1.74 (cmake/modules/CGAL_SetupBoost.cmake)
boost_dep = dependency('boost', version: '>= 1.74')
eigen_dep = dependency('eigen3', version: '>= 3.3.4')

# Not every distribution ships gmp.pc/mpfr.pc (AlmaLinux 8 does not, AlmaLinux
# 9 does), so fall back to plain library lookup when pkg-config comes up empty
gmp_dep = dependency('gmp', required: false)
if gmp_dep.found()
    # mpfr.pc carries `-lgmp` in Libs but only puts its own libdir on the
    # linker search path. Homebrew installs every formula under a separate
    # Cellar prefix, so GMP does not sit next to MPFR and that `-lgmp` goes
    # unresolved unless GMP's libdir is added explicitly. MSVC's linker does
    # not understand -L, but there gmp and mpfr share a conda prefix anyway.
    gmp_libdir = gmp_dep.get_variable(pkgconfig: 'libdir', default_value: '')
    if gmp_libdir != '' and cpp.get_argument_syntax() != 'msvc'
        gmp_dep = declare_dependency(
            dependencies: gmp_dep,
            link_args: ['-L' + gmp_libdir],
        )
    endif
else
    assert(cpp.has_header('gmp.h'), 'GMP headers not found (install gmp-devel/libgmp-dev)')
    gmp_dep = cpp.find_library('gmp')
endif

mpfr_dep = dependency('mpfr', required: false)
if not mpfr_dep.found()
    assert(cpp.has_header('mpfr.h'), 'MPFR headers not found (install mpfr-devel/libmpfr-dev)')
    mpfr_dep = cpp.find_library('mpfr')
endif

cgal_dep = declare_dependency(
    include_directories: include_directories('include'),
    dependencies: [boost_dep, eigen_dep, gmp_dep, mpfr_dep],
)
