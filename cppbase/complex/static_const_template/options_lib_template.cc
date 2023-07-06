#include "options_registry.h"



namespace complex{
    // template<>
    // const RegistrationToken tool::OptionsRegistry::registration_token<FieldData> = tool::OptionsRegistry::Register(FieldData());

    

    template<>
    const complex::RegistrationToken complex::tool::OptionsRegistry::registration_token<MyMessage> =
        complex::tool::OptionsRegistry::Register(complex::tool::OptionsRegistry::field_data<MyMessage>);

    template<typename MessageT>
    const FieldData tool::OptionsRegistry::field_data = FieldData();

    // template<typename MessageT>
    // const LargeField tool::OptionsRegistry::large_field = LargeField();

    template<>
    const LargeField tool::OptionsRegistry::large_field<MyMessage> = tool::OptionsRegistry::makeMessage();
}