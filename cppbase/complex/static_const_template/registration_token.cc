#include "registration_token.h"

#include <utility>


namespace complex{
    RegistrationToken::RegistrationToken(std::function<void()> unregisterer)
    :unregister_function_(std::move(unregisterer)){}

    RegistrationToken::RegistrationToken(RegistrationToken&& rhs)
    :unregister_function_(std::move(rhs.unregister_function_)){
        rhs.unregister_function_ = nullptr;
    }

    RegistrationToken& RegistrationToken::operator=(RegistrationToken&& rhs)
    {
        if(&rhs != this){
            unregister_function_ = std::move(rhs.unregister_function_);
            rhs.unregister_function_ = nullptr;
        }

        return *this;
    }

    void RegistrationToken::Unregister(){
        if (unregister_function_ != nullptr){
            unregister_function_();
            unregister_function_ = nullptr;
        }
    }

    namespace {
        struct CombinedToken
        {
            void operator()(){
                for (auto& f:functions){
                    f();
                }
            }

            std::vector<std::function<void()>> functions;
        };
        
    }

    RegistrationToken RegistrationToken::Combine(std::vector<RegistrationToken> tokens){
        CombinedToken combined;

        combined.functions.reserve(tokens.size());

        for (RegistrationToken& token : tokens){
            combined.functions.push_back(std::move(token.unregister_function_));
        }

        return RegistrationToken(std::move(combined));
    }

}