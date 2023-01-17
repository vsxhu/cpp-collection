#pragma once
#include <memory>
#include <stdexcept>

class ValueNode : public std::enable_shared_from_this<ValueNode>{
   public:
    ValueNode(const ValueNode&)=delete;
    ValueNode& operator=(const ValueNode&)=delete;

    ~ValueNode(){
        WakeUpSuccessor();
    }

    template <class T>
    explicit ValueNode(const T& val)
    {
        value_holder = std::make_unique<ValueHolder<T>>(val);
    }

    template <class T>
    T& Get(){
        if (auto p = dynamic_cast<ValueHolder<T>*>(value_holder.get())){
            return p->val_;
        }
        throw std::logic_error("Bad value cast");
    }

    template <class T, class ... Args>
    void Emplace(Args&& ... args){
        if (auto p = dynamic_cast<ValueHolder<T>*>(value_holder.get())){
            p->Emplace(std::forward<Args>(args)...);
        }else{
            throw std::logic_error("Bad value cast when using emplace");
        }
    }

    void WakeUpSuccessor(){
    }

   private:
    class ValueHolderBase {
       public:
        virtual ~ValueHolderBase() = default;
    };

    template <class T>
    class ValueHolder : public ValueHolderBase {
       public:
        explicit ValueHolder(T val) : val_(val){};

        template <class ... Args>
        void Emplace(Args&& ... args){
            new(&val_) T(std::forward<Args>(args)...);
        }

        T val_;
    };

    std::unique_ptr<ValueHolderBase> value_holder;
};
