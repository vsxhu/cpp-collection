#pragma once
#include <exception>
#include <memory>
#include <stdexcept>

class Any{
   public:
    Any() = delete;
    template <class T>
    explicit Any(T t){
        value_holder_ = std::make_unique<ValueHolder<T>>(t);
    }

    Any& operator=(const Any& rhs){
        value_holder_ = rhs.value_holder_->clone();
        return *this;
    }

    Any& operator=(Any&& rhs) noexcept {
        value_holder_ = std::move(rhs.value_holder_);
        return *this;
    }

    Any(const Any& rhs){
        *this = rhs;
    }

    template <class T>
    T& Value(){
        if (auto p = dynamic_cast<ValueHolder<T>*>(value_holder_.get())){
            return p->t_;
        }
        throw std::logic_error("bad value cast");
    }

    private:
    struct AbstractValueHolder{
        virtual ~AbstractValueHolder() = default;
        [[maybe_unused]] virtual std::unique_ptr<AbstractValueHolder> clone() = 0;
    };

    template <class T>
    struct ValueHolder : AbstractValueHolder{
        T t_;
        explicit ValueHolder(T t):t_(t){};
        std::unique_ptr<AbstractValueHolder> clone() override {
            return std::make_unique<ValueHolder<T>>(t_);
        }
    };
    std::unique_ptr<AbstractValueHolder> value_holder_;
};