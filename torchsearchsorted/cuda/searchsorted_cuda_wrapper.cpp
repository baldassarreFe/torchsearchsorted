#include <torch/extension.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "searchsorted_cuda_kernel.h"

// C++ interface

#define CHECK_CUDA(x) AT_ASSERTM(x.type().is_cuda(), #x " must be a CUDA tensor")
#define CHECK_CONTIGUOUS(x) AT_ASSERTM(x.is_contiguous(), #x " must be contiguous")
#define CHECK_INPUT(x) CHECK_CUDA(x); CHECK_CONTIGUOUS(x)


void searchsorted_cuda_wrapper(
  at::Tensor a,
  at::Tensor v,
  at::Tensor res
){
    CHECK_INPUT(a);
    CHECK_INPUT(v);
    CHECK_INPUT(res);

    searchsorted_cuda(a, v, res);
    return;
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("searchsorted_cuda_wrapper", &searchsorted_cuda_wrapper, "searchsorted (CUDA)");
}
