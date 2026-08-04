project('cgal', 'cpp', version: '6.2')

cpp = meson.get_compiler('cpp')

# CGAL 6.2 requires Boost >= 1.74 (cmake/modules/CGAL_SetupBoost.cmake)
boost_dep = dependency('boost', version: '>= 1.74')
eigen_dep = dependency('eigen3', version: '>= 3.3.4')

# Not every distribution ships gmp.pc/mpfr.pc (AlmaLinux 8 does not, AlmaLinux
# 9 does), so fall back to plain library lookup when pkg-config comes up empty
gmp_dep = dependency('gmp', required: false)
if not gmp_dep.found()
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
