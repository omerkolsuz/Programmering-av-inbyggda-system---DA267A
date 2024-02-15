#include "math.h"
#include "i2C.h"

// Define MPU6050 register addresses
#define ACCEL_X_HIGH_REG 0x3B
#define ACCEL_X_LOW_REG 0x3C
#define ACCEL_Y_HIGH_REG 0x3D
#define ACCEL_Y_LOW_REG 0x3E
#define ACCEL_Z_HIGH_REG 0x3F
#define ACCEL_Z_LOW_REG 0x40
#define SMPLRT_DIV_REG 0x19
#define MPU6050_ADDRESS 0x68
#define PWR_MGMT_1_REG 0x6B

i2c_cmd_handle_t cmd;
esp_err_t res;


/*
This function initializes the I2C communication and configures the MPU6050 sensor.
It sets up the I2C communication parameters for the master mode.
Initializes the I2C driver and configures the sensor's power management and sample rate settings
*/
void init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 33,  
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = 32,  
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed =
            100000,  
    
    };

    esp_err_t res = i2c_param_config(I2C_NUM_0, &conf);
    ESP_ERROR_CHECK(res);
    res = i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0);
    ESP_ERROR_CHECK(res);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);

    res = i2c_master_write_byte(cmd, MPU6050_ADDRESS << 1 | I2C_MASTER_WRITE, 1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_write_byte(cmd, PWR_MGMT_1_REG, 1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_write_byte(cmd, 0x00, 1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);

    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(res);

    i2c_cmd_link_delete(cmd);

    cmd = i2c_cmd_link_create();
    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, MPU6050_ADDRESS << 1 | I2C_MASTER_WRITE,
                                1);  
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, SMPLRT_DIV_REG,
                                1);  
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, 250, 1);  
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);

    i2c_cmd_link_delete(cmd);
}
/*
Reads accelerometer data from the MPU6050 sensor's specified registers.
The function sends I2C commands to read the data from the specified registers
and combines the high and low bytes into a 16-bit signed integer.
*/
int16_t readAccelerometer(uint16_t registerHigh, uint16_t registerLow) {
    int16_t tempRaw = 0;
    uint8_t buffer;

    cmd = i2c_cmd_link_create();
    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, MPU6050_ADDRESS << 1 | I2C_MASTER_WRITE,
                                1); 
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, registerLow,
                                1); 
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);

    cmd = i2c_cmd_link_create();
    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, MPU6050_ADDRESS << 1 | I2C_MASTER_READ,
                                1);  
    ESP_ERROR_CHECK(res);
    res = i2c_master_read(cmd, &buffer, 1, I2C_MASTER_NACK);
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);
    tempRaw = buffer;

    cmd = i2c_cmd_link_create();
    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, MPU6050_ADDRESS << 1 | I2C_MASTER_WRITE,
                                1);  
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, registerHigh, 1); 
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    cmd = i2c_cmd_link_create();
    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, MPU6050_ADDRESS << 1 | I2C_MASTER_READ,
                                1);
    ESP_ERROR_CHECK(res);
    res = i2c_master_read(cmd, &buffer, 1, I2C_MASTER_NACK);
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);
    tempRaw |= ((int16_t)buffer) << 8;

    return tempRaw;
}
/*
This function calculates the magnitude of acceleration from the X, Y, and Z axes.
It calls the readAccelerometer function three times to obtain the accelerometer data for each axis.
*/
u_int32_t getMagnitude() {
    double Xaccel = readAccelerometer(ACCEL_X_HIGH_REG, ACCEL_X_LOW_REG);
    double Yaccel = readAccelerometer(ACCEL_Y_HIGH_REG, ACCEL_Y_LOW_REG);
    double Zaccel = readAccelerometer(ACCEL_Z_HIGH_REG, ACCEL_Z_LOW_REG);

    return (u_int32_t)sqrt(pow(Xaccel, 2) + pow(Yaccel, 2) + pow(Zaccel, 2));
}