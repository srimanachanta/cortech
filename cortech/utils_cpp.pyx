from libcpp.vector cimport vector
import numpy as np
import numpy.typing as npt
cimport numpy as np

cdef extern from "utils_cpp_src.cpp":
    vector[int] map_values_from_source_to_target(vector[int],vector[int],vector[int]) except +

def map_values(source: npt.ArrayLike, target: npt.ArrayLike, values: npt.ArrayLike, ):

    cdef np.ndarray[int] source_ = np.ascontiguousarray(source, dtype=np.int32)
    cdef np.ndarray[int] target_ = np.ascontiguousarray(target, dtype=np.int32)
    cdef np.ndarray[int] values_ = np.ascontiguousarray(values, dtype=np.int32)
    out = map_values_from_source_to_target(source_, target_, values_)
    return np.array(out, dtype=int)
