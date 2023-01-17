#pragma once
#include "value_node.h"

class ValueNodeRef{
   public:
    ValueNodeRef(const ValueNode& value_node){
        const_cast<ValueNode&>(value_node).AddRef();
    };
    ~ValueNodeRef(){

    };
};