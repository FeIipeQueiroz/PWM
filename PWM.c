#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define LED_PIN 12
#define PWM_FREQ 50
#define WRAP_VALUE 25000

void setServoPulse(uint slice_num, uint channel, uint16_t pulse_width) {
    pwm_set_chan_level(slice_num, channel, pulse_width);
}

int main() {
    //stdio_init_all();
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);
    pwm_set_wrap(slice_num, WRAP_VALUE);
    pwm_set_clkdiv(slice_num, 125.0f);
    pwm_set_enabled(slice_num, true);

    setServoPulse(slice_num, channel, 2400);
    sleep_ms(5000);
    setServoPulse(slice_num, channel, 1470);
    sleep_ms(5000);
    setServoPulse(slice_num, channel, 500);
    sleep_ms(5000);

    while (true) {
        for (uint16_t pulse = 500; pulse <= 2400; pulse += 5) {
            setServoPulse(slice_num, channel, pulse);
            sleep_ms(10);
        }
        for (uint16_t pulse = 2400; pulse >= 500; pulse -= 5) {
            setServoPulse(slice_num, channel, pulse);
            sleep_ms(10);
        }
    }
}