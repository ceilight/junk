#include <functional>
#include <numeric>

#include "flatten.h"

namespace nnv2 {

void Flatten::forward() {
    Array *input = prev->get_output();
    in_shape = input->get_shape();

    int out_feats = std::accumulate(in_shape.begin() + 1, in_shape.end(), 1,
                                    std::multiplies<int>());
    input->reshape({in_shape[0], out_feats});
}

void Flatten::backward() {
    Array *output_grad = next->get_grad();
    output_grad->reshape(in_shape);
}

} // namespace nnv2