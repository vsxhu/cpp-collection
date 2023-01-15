#include <chrono>
#include <iostream>
#include <thread>

#include "async-graph/core/executor.h"
#include "async-graph/core/func_register.h"
#include "async-graph/core/value_node.h"

void Kernel1(KernelContext* frame) {
    auto val = frame->GetInput<int>(0);
    std::cout << "Kernel1 val: " << val << std::endl;
    frame->AddOutput(val);
}

void Kernel2(KernelContext* frame) {
    auto val = frame->GetInput<int>(0);
    std::cout << "Kernel2 val: " << val << std::endl;
    frame->AddOutput(val);
}

void Kernel3(KernelContext* frame) {
    auto val0 = frame->GetInput<int>(0);
    auto val1 = frame->GetInput<int>(1);
    std::cout << "Kernel3 val: " << val0 + val1 << std::endl;
    frame->AddOutput(val0 + val1);
}

int main() {
    Graph graph;
    auto ptr1 = new TaskNode{&Kernel1, "Kernel1"};
    auto ptr2 = new TaskNode{&Kernel2, "Kernel2"};
    auto ptr3 = new TaskNode{&Kernel3, "Kernel3"};
    ptr1->AddSuccessor(ptr3);
    ptr2->AddSuccessor(ptr3);
    ptr1->GetContext()->AddInput(3);
    ptr2->GetContext()->AddInput(4);
    graph.AddNode(ptr1);
    graph.AddNode(ptr2);
    graph.AddNode(ptr3);
    graph.Build();
    graph.Run();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << graph.GetNode("Kernel3")->GetContext()->GetOutput<int>(0) << std::endl;
    ValueNode val{1};
    std::cout << val.Get<int>() << std::endl;
}