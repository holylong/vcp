#ifndef _OPTIONS_REGISTRY_H_
#define _OPTIONS_REGISTRY_H_

#include "registration_token.h"
#include <iostream>

typedef struct {
    uint8_t i;
    uint8_t j;
    uint8_t k;
}FieldData;


class LargeField{

};

class MyMessage {};

namespace complex{
    namespace tool{
        class OptionsRegistry{
            public:
                static RegistrationToken Register(const FieldData& file_descriptor_set){
                    return RegistrationToken([](){});
                }

                static LargeField makeMessage(){
                    return LargeField();
                }

                template<typename MessageT>
                static const RegistrationToken registration_token;

                template<typename MessageT>
                static const FieldData field_data;

                template<typename MessageT>
                static const LargeField large_field;
        };
    }
}

#endif //_OPTIONS_REGISTRY_H_