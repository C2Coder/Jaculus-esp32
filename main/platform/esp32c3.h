#pragma once

#include <jac/machine/machine.h>
#include <set>
#include <unordered_map>
#include <string>

#include "hal/adc_types.h"
#include "soc/adc_channel.h"


template<class Next>
class PlatformInfoFeature : public Next {
public:
    struct PlatformInfo {
        static inline const std::string NAME = "ESP32-C3";

        struct PinConfig {
            static inline const std::set<int> DIGITAL_PINS = {
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 20, 21
            };
            static inline const std::unordered_map<int, std::pair<int, int>> ANALOG_PINS = {
                { 0, { 1, ADC1_GPIO0_CHANNEL }},
                { 1, { 1, ADC1_GPIO1_CHANNEL }},
                { 2, { 1, ADC1_GPIO2_CHANNEL }},
                { 3, { 1, ADC1_GPIO3_CHANNEL }},
                { 4, { 1, ADC1_GPIO4_CHANNEL }}
            };
            static inline const std::set<int> INTERRUPT_PINS = DIGITAL_PINS;
            static inline const int DEFAULT_I2C_SDA_PIN = 0;
            static inline const int DEFAULT_I2C_SCL_PIN = 1;
        };
    };

    void initialize() {
        Next::initialize();

        jac::ContextRef ctx = this->context();

        jac::Object platformInfo = jac::Object::create(ctx);
        platformInfo.defineProperty("name", jac::Value::from(ctx, PlatformInfo::NAME), jac::PropFlags::Enumerable);

        ctx.getGlobalObject().defineProperty("PlatformInfo", platformInfo, jac::PropFlags::Enumerable);
    }
};
