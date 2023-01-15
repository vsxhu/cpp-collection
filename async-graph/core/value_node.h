#pragma once
#include <memory>
#include <stdexcept>

class ValueNode : public std::enable_shared_from_this<ValueNode>{
   public:
    ~ValueNode() = default;

    template <class T>
    explicit ValueNode(const T& val)
    {
        value_holder = std::make_unique<ValueHolder<T>>(val);
    }

    ValueNode& operator=(const ValueNode& rhs) {
        value_holder = rhs.value_holder->Clone();
        return *this;
    }

    ValueNode(const ValueNode& rhs){
        *this = rhs;
    }

    template <class T>
    T& Get(){
        if (auto p = dynamic_cast<ValueHolder<T>*>(value_holder.get())){
            return p->val_;
        }
        throw std::logic_error("bad value cast");
    }

   private:
    class ValueHolderBase {
       public:
        virtual ~ValueHolderBase() = default;
        virtual std::unique_ptr<ValueHolderBase> Clone() = 0;
    };

    template <class T>
    class ValueHolder : public ValueHolderBase {
       public:
        explicit ValueHolder(T val) : val_(val){};

        std::unique_ptr<ValueHolderBase> Clone() override {
            // if constexpr (std::is_copy_constructible_v<T>){
            return std::make_unique<ValueHolder<T>>(val_);
        }

        T val_;
    };

    std::unique_ptr<ValueHolderBase> value_holder;
};
