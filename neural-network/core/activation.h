#pragma once

#include "common.h"
#include "layer.h"

namespace nnv2 {

//
// ReLU hidden layer activation
//
class ReLU : public Layer {
public:
    ReLU() : Layer() {}

    void forward() override;
    void backward() override;

    Array *get_grad() { return next->get_grad(); }
    Array *get_output() { return prev->get_output(); }
};

void relu_forward(Array *output, const Array *input);
void relu_backward(Array *input_grad, const Array *output_grad,
                   const Array *input);

//
// Sigmoid hidden layer activation
//
class Sigmoid : public Layer {
public:
    Sigmoid() : Layer() {}

    void forward() override;
    void backward() override;

    Array *get_grad() { return next->get_grad(); }
    Array *get_output() { return prev->get_output(); }
};

void sigmoid_forward(Array *output, const Array *input);
void sigmoid_backward(Array *input_grad, const Array *output_grad,
                      const Array *input);

//
// Tanh hidden layer activation
//
class Tanh : public Layer {
public:
    Tanh() : Layer() {}

    void forward() override;
    void backward() override;

    Array *get_grad() { return next->get_grad(); }
    Array *get_output() { return prev->get_output(); }
};

void tanh_forward(Array *output, const Array *input);
void tanh_backward(Array *input_grad, const Array *output_grad,
                   const Array *input);

//
// Softmax output activation
//
class Softmax : public Layer {
public:
    Softmax() : Layer() {}

    void forward() override;
    void backward() override;
};

void softmax_forward(Array *output, const Array *input);

//
// LogSoftmax output activation
//
class LogSoftmax : public Layer {
public:
    LogSoftmax() : Layer() {}

    void forward() override;
    void backward() override;
};

void log_softmax_forward(Array *output, const Array *input);
void log_softmax_backward(Array *input_grad, const Array *output_grad,
                          const Array *input);

} // namespace nnv2