#pragma once
#include <driver/i2s.h>

class InterICSound {
    private:
        int16_t *samples;
        int numSamples;
        i2s_port_t i2sPort;
        int i2sWS;
        int i2sSD;
        int i2sSCK;
        
        float calculateRMS(int16_t* samples, int numSamples) {
            float sum = 0;
            for (int i = 0; i < numSamples; i++) {
                sum += (float)samples[i] * samples[i];
            }
            return sqrt(sum / numSamples);
        }

    public:
        InterICSound(i2s_port_t port = I2S_NUM_0, int ws = 15, int sd = 18, int sck = 2, int bufferLen = 64) 
            : i2sPort(port), i2sWS(ws), i2sSD(sd), i2sSCK(sck) {
            samples = new int16_t[bufferLen];
            numSamples = bufferLen;
        }

        ~InterICSound() {
            if (samples) {
                delete[] samples;
            }
            i2s_driver_uninstall(i2sPort);
        }

        void setup() {
            const i2s_config_t i2s_config = {
                .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
                .sample_rate = 44100,
                .bits_per_sample = i2s_bits_per_sample_t(16),
                .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
                .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
                .intr_alloc_flags = 0,
                .dma_buf_count = 8,
                .dma_buf_len = numSamples,
                .use_apll = false
            };

            i2s_driver_install(i2sPort, &i2s_config, 0, NULL);

            const i2s_pin_config_t pin_config = {
                .bck_io_num = i2sSCK,
                .ws_io_num = i2sWS,
                .data_out_num = -1,
                .data_in_num = i2sSD
            };

            i2s_set_pin(i2sPort, &pin_config);
            i2s_start(i2sPort);
        }

        float readRMS() {
            size_t bytesIn = 0;
            esp_err_t result = i2s_read(i2sPort, samples, numSamples * sizeof(int16_t), &bytesIn, portMAX_DELAY);
            
            if (result == ESP_OK) {
                int samplesRead = bytesIn / 8;
                if (samplesRead > 0) {
                    return calculateRMS(samples, samplesRead);
                }
            }
            return -1.0f;
        }
};