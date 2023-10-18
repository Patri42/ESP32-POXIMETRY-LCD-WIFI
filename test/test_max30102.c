#include "unity.h"
#include "max30102.h"
#include "i2c-driver.h"  

TEST_CASE("MAX30102 Initialization", "[max30102]")
{
    max30102_init();
    
    uint8_t data;

    // Example: Read from one of the registers that was written during init to see if the value is as expected.
    i2c_read(I2C_ADDR_MAX30102, 0x08, &data);
    TEST_ASSERT_EQUAL_UINT8(0x40, data);  // Expecting the value (0x2 << 5)

    // Add more reads and asserts for other registers if needed.
}


bool get_sensor_reading(SensorData *outputData) {
    SensorData sensorData;
    
    // HealthMetrics metrics;
    int cnt, samp, tcnt = 0;
    uint8_t rptr, wptr;
    uint8_t data;
    uint8_t regdata[256];
    //int irmeas, redmeas;
    float firxv[5], firyv[5], fredxv[5], fredyv[5];
    float lastmeastime = 0;
    float hrarray[5] = {0, 0, 0, 0, 0};
    float spo2array[5] = {0, 0, 0, 0, 0};
    int hrarraycnt = 0;
    //char buffer[16];
    sensorData.heartrate = 99.2;
    sensorData.pctspo2 = 99.2;

    while(1){
        // Update LED pulse amplitude if needed
        if(lirpower!=irpower){
            data = (uint8_t) irpower;
            i2c_write(I2C_ADDR_MAX30102, 0x0d,  data); 
            lirpower=irpower;
        }
        if(lrpower!=rpower){
            data = (uint8_t) rpower;
            i2c_write(I2C_ADDR_MAX30102, 0x0c,  data); 
            lrpower=rpower;
        }

        // Reading FIFO data pointers
        i2c_read(I2C_ADDR_MAX30102, 0x04, &wptr, 1);
        i2c_read(I2C_ADDR_MAX30102, 0x06, &rptr, 1);
        
        samp = ((32+wptr)-rptr)%32;
        i2c_read(I2C_ADDR_MAX30102, 0x07, regdata, 6*samp);
        //ESP_LOGI("samp","----  %d %d %d %d",  adc_read_ptr,samp,wptr,rptr);

        for(cnt = 0; cnt < samp; cnt++){
            meastime =  0.01 * tcnt++;
            firxv[0] = firxv[1]; firxv[1] = firxv[2]; firxv[2] = firxv[3]; firxv[3] = firxv[4];
            firxv[4] = (1/3.48311) * (256*256*(regdata[6*cnt+3]%4)+ 256*regdata[6*cnt+4]+regdata[6*cnt+5]);
            firyv[0] = firyv[1]; firyv[1] = firyv[2]; firyv[2] = firyv[3]; firyv[3] = firyv[4];
            firyv[4] = (firxv[0] + firxv[4]) - 2 * firxv[2]
                    + ( -0.1718123813 * firyv[0]) + (  0.3686645260 * firyv[1])
                    + ( -1.1718123813 * firyv[2]) + (  1.9738037992 * firyv[3]);

            fredxv[0] = fredxv[1]; fredxv[1] = fredxv[2]; fredxv[2] = fredxv[3]; fredxv[3] = fredxv[4];
            fredxv[4] = (1/3.48311) * (256*256*(regdata[6*cnt+0]%4)+ 256*regdata[6*cnt+1]+regdata[6*cnt+2]);
            fredyv[0] = fredyv[1]; fredyv[1] = fredyv[2]; fredyv[2] = fredyv[3]; fredyv[3] = fredyv[4];
            fredyv[4] = (fredxv[0] + fredxv[4]) - 2 * fredxv[2]
                    + ( -0.1718123813 * fredyv[0]) + (  0.3686645260 * fredyv[1])
                    + ( -1.1718123813 * fredyv[2]) + (  1.9738037992 * fredyv[3]);

            //if (-1.0 * firyv[4] >= 100 && -1.0 * firyv[3] < 100){
            //   heartrate = 60 / (meastime - lastmeastime);
            //   pctspo2 = 110 - 25 * ((fredyv[4]/fredxv[4]) / (firyv[4]/firxv[4]));
            //   printf ("%6.2f  %4.2f     hr= %5.1f     spo2= %5.1f\n", meastime, meastime - lastmeastime, heartrate, pctspo2);
            //   lastmeastime = meastime;
            //}

            //printf("%8.1f %8.1f %8.1f %8.3f\n", -1.0 * firyv[0], -1.0 * firyv[2], -1.0 * firyv[4], meastime-lastmeastime); 

            // Compute and display heart rate and SpO2 using detected peaks
            if (-1.0 * firyv[4] >= 100 && -1.0 * firyv[2] > -1*firyv[0] && -1.0 * firyv[2] > -1*firyv[4] && meastime-lastmeastime > 0.5){
                printf("Condition met, calculating values...\n");
                hrarray[hrarraycnt % 5] = 60 / (meastime - lastmeastime);
                spo2array[hrarraycnt % 5] = 110 - 25 * ((fredyv[4]/fredxv[4]) / (firyv[4]/firxv[4]));

                // Limit SpO2 to 100
                if(spo2array[hrarraycnt % 5] > 100)spo2array[hrarraycnt % 5]=99.9;

                // Displaying the intermediate result
                printf ("%6.2f  %4.2f     hr= %5.1f     spo2= %5.1f\n", meastime, meastime - lastmeastime, sensorData.heartrate, sensorData.pctspo2);
                lastmeastime = meastime;
                hrarraycnt++;

                // Averaging recent 5 HR and SpO2 values and ensuring they are within plausible range
	            sensorData.heartrate = (hrarray[0]+hrarray[1]+hrarray[2]+hrarray[3]+hrarray[4]) / 5;              
	            if (sensorData.heartrate < 40 || sensorData.heartrate > 150) 
                    sensorData.heartrate = 0;

	            sensorData.pctspo2 = (spo2array[0]+spo2array[1]+spo2array[2]+spo2array[3]+spo2array[4]) / 5;
	            if (sensorData.pctspo2 < 50 || sensorData.pctspo2 > 101) 
                    sensorData.pctspo2 = 0;

    if (xQueueSend(sensorDataQueue, &sensorData, 0) == pdTRUE) {
        printf(("Sent data to queue: [Pulse: %lf , Oximetry: %lf]"), sensorData.heartrate, sensorData.pctspo2);
        if (outputData) {
            // if a pointer to SensorData was provided, store the results there
            *outputData = sensorData;
        }
        return true;
    } else {
        printf("Failed to send data to queue");
        return false;
    }
    if (sensorData.heartrate > 0 && sensorData.pctspo2 > 0) {
        if (outputData) {
            // Copy the sensorData to the outputData if a valid pointer is provided
            *outputData = sensorData;
        }
        return true;
    }
    return false;
}

TEST_CASE("Test get_sensor_reading function", "[max30102]") {
    SensorData data;
    bool result = get_sensor_reading(&data);
    TEST_ASSERT_TRUE_MESSAGE(result, "Failed to get sensor reading");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(1.0, 99.2, data.heartrate, "Unexpected heartrate value");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(1.0, 99.2, data.pctspo2, "Unexpected pctspo2 value");
}