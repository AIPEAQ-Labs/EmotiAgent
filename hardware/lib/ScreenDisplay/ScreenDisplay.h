#pragma once
#include <AnimatedGIF.h>
#include "GIFDraw.h"
#include <Audio.h>

// Happy emotions
#include "images/awe.h"
#include "images/glee.h"
#include "images/happy.h"

// Neutral emotions
#include "images/sleepy_eyes.h"
#include "images/blink_high.h"
#include "images/blink_low.h"
#include "images/focused_detrmnined.h"
#include "images/neutral.h"
#include "images/skeptic.h"
#include "images/surprised.h"
#include "images/suspicious.h"

// Sad emotions
#include "images/sad_loocking_high.h"
#include "images/sad_loocking_down.h"
#include "images/unnipressed.h"
#include "images/worrised.h"

// Angry emotions
#include "images/angry.h"
#include "images/annoyed.h"
#include "images/frustrated.h"
#include "images/furious.h"

// Scared emotions
#include "images/scared.h"

class ScreenDisplay {
    private:
        AnimatedGIF gif;
        Audio audio;
        unsigned short currentGif = 0;
        unsigned long lastGifTime = 0;

        // Emotion grouping
        enum EmotionGroup {
            HAPPY,
            NEUTRAL,
            SAD,
            ANGRY,
            SCARED,
            OTHER
        };

        // Structure to hold GIF data with emotion group
        struct GifData {
            const uint8_t* data;
            const int size;
            EmotionGroup emotion;
        };

        // Array of GIF data with emotion grouping
        const GifData gifs[20] = {
            // HAPPY emotions
            // {awe, sizeof(awe), HAPPY},
            {glee, sizeof(glee), HAPPY},
            {happy, sizeof(happy), HAPPY},

            // NEUTRAL emotions
            {sleepy_eyes, sizeof(sleepy_eyes), NEUTRAL},
            {blink_high, sizeof(blink_high), NEUTRAL},
            {blink_low, sizeof(blink_low), NEUTRAL},
            {focused_detrmnined, sizeof(focused_detrmnined), NEUTRAL},
            {neutral, sizeof(neutral), NEUTRAL},
            {skeptic, sizeof(skeptic), NEUTRAL},
            {surprised, sizeof(surprised), NEUTRAL},
            {suspicious, sizeof(suspicious), NEUTRAL},

            // SAD emotions
            {sad_loocking_high, sizeof(sad_loocking_high), SAD},
            {sad_loocking_down, sizeof(sad_loocking_down), SAD},
            {unnipressed, sizeof(unnipressed), SAD},

            // ANGRY emotions
            {angry, sizeof(angry), ANGRY},
            {annoyed, sizeof(annoyed), ANGRY},
            {frustrated, sizeof(frustrated), ANGRY},
            {furious, sizeof(furious), ANGRY},

            // SCARED emotions
            {scared, sizeof(scared), SCARED},
            {worrised, sizeof(worrised), SCARED}
        };

        int getRandomGifFromEmotion(EmotionGroup emotion) {
            int count = 0;
            int indices[20];
            
            for (int i = 0; i < sizeof(gifs)/sizeof(gifs[0]); i++) {
                if (gifs[i].emotion == emotion) {
                    indices[count] = i;
                    count++;
                }
            }
            
            return count > 0 ? indices[random(count)] : 0;
        }

        void setRandomGif(float happinessRate) {
            EmotionGroup targetEmotion;
            
            if (happinessRate >= 80) {
                targetEmotion = HAPPY;
            } else if (happinessRate >= 60) {
                targetEmotion = (random(2) == 0) ? HAPPY : NEUTRAL;
            } else if (happinessRate >= 40) {
                targetEmotion = NEUTRAL;
            } else if (happinessRate >= 20) {
                targetEmotion = (random(2) == 0) ? SAD : NEUTRAL;
            } else {
                targetEmotion = (random(2) == 0) ? SAD : ANGRY;
            }
            
            currentGif = getRandomGifFromEmotion(targetEmotion);
        }

        void drawGif(uint8_t *gifFile, int size) {
            if (gif.open((uint8_t *)gifFile, size, GIFDraw)) {
                
                tft.startWrite();
                while (gif.playFrame(true, NULL)) {
                    yield();
                }
                gif.close();
                tft.endWrite();
            }
        }

    public:
        void setup() {
            tft.init();
            tft.setRotation(1);
            tft.fillScreen(TFT_BLACK);
            gif.begin(BIG_ENDIAN_PIXELS);

            // audio.setPinout(I2S_AUDIO_BCLK, I2S_AUDIO_LRC, I2S_AUDIO_DOUT);
            // audio.connecttoFS(SPIFFS, "/happy_sfx.wav");
            // audio.setFileLoop(true);
            // audio.setVolume(21); // default 0...21
        }

        void loop(float happinessRate) {
            if (millis() - lastGifTime > 2000) {
                setRandomGif(happinessRate);
                lastGifTime = millis();
            }

            drawGif((uint8_t*)gifs[currentGif].data, gifs[currentGif].size);
            // audio.loop();
        }

        TFT_eSPI* getTft() {
            return &tft;
        }
};