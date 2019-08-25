// MIT License

// Copyright (c) 2019 ShellAddicted

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "WemosMotorShieldESP32.h"

static const char *WMS_LOG = "WemosMS";
extern "C" void app_main(void) {
    // Setup I²C
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_NUM_21;
    conf.scl_io_num = GPIO_NUM_22;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    i2c_set_timeout(I2C_NUM_0, 30000);

    // Setup Motor Shield (Use of I²C Motor Standby is strongly recommended)
    ESP_LOGE(WMS_LOG, "Shield init");
    WemosMotorShield wemosMS(I2C_NUM_0);
    // WemosMotorShield wemosMS2(I2C_NUM_0, 0x2D); // Support for multiple shield

    // Do something with the motors
    while (1) {
        ESP_LOGI(WMS_LOG, "MotorA: Forward");
        wemosMS.setMotor(MotorNum::MOTOR_A, MotorDirection::FORWARD, 100.0);
        ESP_LOGI(WMS_LOG, "MotorB: Backward");
        wemosMS.setMotor(MotorNum::MOTOR_B, MotorDirection::BACKWARD, 100.0);
        ESP_LOGI(WMS_LOG, "Waiting for 5s");
        vTaskDelay(5000 / portTICK_PERIOD_MS);

        ESP_LOGI(WMS_LOG, "MotorA: Backward");
        wemosMS.setMotor(MotorNum::MOTOR_A, MotorDirection::BACKWARD, 100.0);
        ESP_LOGI(WMS_LOG, "MotorB: Forward");
        wemosMS.setMotor(MotorNum::MOTOR_B, MotorDirection::FORWARD, 100.0);
        ESP_LOGI(WMS_LOG, "Waiting for 5s");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
