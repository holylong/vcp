#ifndef _REGISTRATION_TOKEN_H_
#define _REGISTRATION_TOKEN_H_

#include <functional>
#include <vector>

namespace complex{
    class RegistrationToken{
        public:
            explicit RegistrationToken(std::function<void()> unregisterer);

            RegistrationToken(){}

            RegistrationToken(const RegistrationToken&) = delete;
            RegistrationToken& operator=(const RegistrationToken&) = delete;

            RegistrationToken(RegistrationToken&& rhs);
            RegistrationToken& operator=(RegistrationToken&& rhs);

            void Unregister();

            static RegistrationToken Combine(std::vector<RegistrationToken> tokens);

        private:
            std::function<void()> unregister_function_ = nullptr;
    };
}

#endif //_REGISTRATION_TOKEN_H_