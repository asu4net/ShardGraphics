#pragma once
#include <functional>

namespace Shard
{
    template<typename T>
    class Delegate;
    
    template<typename TReturn, typename ...TArgs>
    class Delegate<TReturn(TArgs...)>
    {
    public:
        Delegate() = default;
        
        Delegate(const std::function<TReturn(TArgs...)>& func)
            : m_function(func)
        {}
        
        template<typename TSubscriber>
        void Bind(TSubscriber* obj, TReturn(TSubscriber::*funcPtr)(TArgs...))
        {
            m_function = std::bind(funcPtr, obj);
        }
        
        template<typename ...Args>
        TReturn operator()(Args&&... args)
        {
            if (!m_function)
                return TReturn();
            return m_function(std::forward<Args>(args)...);
        }
        
        bool operator==(const Delegate& other) const
        {
            return m_function == other.m_function;
        }
        
        void Clear() { m_function = nullptr; }
    
    private:
        std::function<TReturn(TArgs...)> m_function;
    };
}