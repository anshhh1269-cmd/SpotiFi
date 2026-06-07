#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <JPEGDecoder.h>
#include <SpotifyEsp32.h>
#include <SPI.h>

// ============================================================================
// 1. HARDWARE PIN CONFIGURATIONS
// ============================================================================
#define BTN_NEXT  14  
#define BTN_PREV  12  
#define BTN_PLAY  13  
#define BTN_MODE  15  
#define BTN_SLEEP 16  

#define TFT_CS    5
#define TFT_RST   4
#define TFT_DC    2
#define TFT_SCLK  18
#define TFT_MOSI  23


const char* SSID          = "YOUR WIFI SSID";
const char* PASSWORD      = "YOUR WIFI PASSWORD";
const char* CLIENT_ID     = "YOUR_SPOTIFY_CLIENT_ID";
const char* CLIENT_SECRET = "YOUR_SPOTIFY_CLIENT_SECRET";


const uint16_t charFrame1[] PROGMEM = {
    0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000,
    0x0000, 0x07E0, 0xFFFF, 0x07E0, 0x07E0, 0xFFFF, 0x07E0, 0x0000,
    0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0,
    0x07E0, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x07E0,
    0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0,
    0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000,
    0x0000, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x0000,
    0x0000, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0x0000
};

const uint16_t charFrame2[] PROGMEM = {
    0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000,
    0x0000, 0x07E0, 0xFFFF, 0x07E0, 0x07E0, 0xFFFF, 0x07E0, 0x0000,
    0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0,
    0x07E0, 0x07E0, 0x0000, 0x07E0, 0x07E0, 0x0000, 0x07E0, 0x07E0,
    0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0,
    0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000,
    0x0000, 0x0000, 0x07E0, 0x0000, 0x0000, 0x07E0, 0x0000, 0x0000,
    0x0000, 0x0000, 0xF800, 0x0000, 0x0000, 0xF800, 0x0000, 0x0000
};


enum DisplayMode { BOOT_TEXT, ALBUM_ART_CHAR, ONLY_CHAR, OSCILLOSCOPE };
DisplayMode currentMode = BOOT_TEXT; 

bool screenSleep = false;
String lastTrackname = "";
String lastArtist = "";
String lastAlbumUrl = "";
unsigned long lastAnimationTime = 0;
unsigned long lastSpotifyUpdate = 0;
int animationFrame = 0;
float wavePhase = 0;

float realLoudness = -10.0; 
float realBPM = 120.0;       

Spotify sp(CLIENT_ID, CLIENT_SECRET);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Forward Declarations
int checkMultiClicks(int pin);
void drawSpotifyAlbumArt(String url);
void renderJPEG(int xpos, int ypos);
void drawTrackText(String track, String artist);
void fetchLiveAudioFeatures(String trackId);

void setup() {
    Serial.begin(115200);
    
    pinMode(BTN_NEXT, INPUT_PULLUP);
    pinMode(BTN_PREV, INPUT_PULLUP);
    pinMode(BTN_PLAY, INPUT_PULLUP);
    pinMode(BTN_MODE, INPUT_PULLUP);
    pinMode(BTN_SLEEP, INPUT_PULLUP);

    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1); 
    tft.fillScreen(ST77XX_BLACK);
    
    tft.setCursor(10, 20);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.print("Booting Connection...");

    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 20);
    tft.print("Syncing Spotify API...");

    sp.begin();
    while (!sp.is_auth()) {
        sp.handle_client();
        delay(10);
    }
    tft.fillScreen(ST77XX_BLACK);
    currentMode = ALBUM_ART_CHAR; 
}

void loop() {
    sp.handle_client();

    
    if (digitalRead(BTN_NEXT) == LOW) { sp.skip_to_next(); delay(300); }
    if (digitalRead(BTN_PREV) == LOW) { sp.skip_to_previous(); delay(300); }
    if (digitalRead(BTN_PLAY) == LOW) { sp.start_a_users_playback(); delay(300); }
    if (digitalRead(BTN_SLEEP) == LOW) {
        screenSleep = !screenSleep;
        if (screenSleep) tft.fillScreen(ST77XX_BLACK);
        else { lastAlbumUrl = ""; lastTrackname = ""; }
        delay(350);
    }

    if (screenSleep) return; 

    int clicks = checkMultiClicks(BTN_MODE);
    if (clicks == 1) { currentMode = ALBUM_ART_CHAR; tft.fillScreen(ST77XX_BLACK); lastAlbumUrl = ""; lastTrackname = ""; }
    else if (clicks == 2) { currentMode = ONLY_CHAR; tft.fillScreen(ST77XX_BLACK); }
    else if (clicks == 3) { currentMode = OSCILLOSCOPE; tft.fillScreen(ST77XX_BLACK); }

   
    static String currentTrack = "";
    static String currentArtist = "";
    static String currentAlbumUrl = "";
    static String lastTrackId = "";
    static bool isPlaying = false;

    if (millis() - lastSpotifyUpdate > 2000) {
        lastSpotifyUpdate = millis();
        currentTrack    = sp.current_track_name();
        currentArtist   = sp.current_artist_names();
        currentAlbumUrl = sp.get_current_album_image_url(2); 
        isPlaying       = sp.is_playing();
        
        String currentTrackId = sp.current_track_id(); 
        
        if (currentTrackId != lastTrackId && !currentTrackId.isEmpty()) {
            fetchLiveAudioFeatures(currentTrackId);
            lastTrackId = currentTrackId;
        }
    }

    
    switch (currentMode) {
        
        case ALBUM_ART_CHAR:
            if (currentTrack != lastTrackname) {
                drawTrackText(currentTrack, currentArtist);
                lastTrackname = currentTrack;
                lastArtist = currentArtist;
            }
            if (currentAlbumUrl != lastAlbumUrl && !currentAlbumUrl.isEmpty()) {
                tft.fillRect(10, 32, 64, 64, ST77XX_BLACK); 
                drawSpotifyAlbumArt(currentAlbumUrl); 
                lastAlbumUrl = currentAlbumUrl;
            }
            if (millis() - lastAnimationTime > 400) {
                lastAnimationTime = millis();
                tft.fillRect(120, 56, 16, 16, ST77XX_BLACK); 
                if (isPlaying) animationFrame = (animationFrame == 0) ? 1 : 0;
                
                int startX = 120;
                int startY = 56;
                int scale = 2;
                const uint16_t* currentFrame = (animationFrame == 0) ? charFrame1 : charFrame2;
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        uint16_t color = pgm_read_word(&(currentFrame[row * 8 + col]));
                        if(color != 0x0000) { 
                            tft.fillRect(startX + (col * scale), startY + (row * scale), scale, scale, color);
                        }
                    }
                }
            }
            break;

        case ONLY_CHAR:
            if (millis() - lastAnimationTime > 200) {
                lastAnimationTime = millis();
                tft.fillRect(48, 32, 64, 64, ST77XX_BLACK); 
                if (isPlaying) animationFrame = (animationFrame == 0) ? 1 : 0;
                
                int startX = 48;
                int startY = 32;
                int scale = 8;
                const uint16_t* currentFrame = (animationFrame == 0) ? charFrame1 : charFrame2;
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        uint16_t color = pgm_read_word(&(currentFrame[row * 8 + col]));
                        if(color != 0x0000) {
                            tft.fillRect(startX + (col * scale), startY + (row * scale), scale, scale, color);
                        }
                    }
                }
            }
            break;

        case OSCILLOSCOPE:
            tft.fillRect(0, 40, 160, 50, ST77XX_BLACK); 
            if (isPlaying) {
                // Map real decibel loudness (typically ranges around -20dB to -3dB) to visual amplitude bounds
                int amplitude = map(constrain((int)realLoudness, -25, -2), -25, -2, 4, 23);
                
                float speedFactor = (realBPM / 120.0) * 5.0;
                wavePhase += speedFactor; 

                for (int x = 0; x < 160; x++) {
                    int y = 64 + (amplitude * sin((x + wavePhase) * 0.09));
                    tft.drawPixel(x, y, ST77XX_CYAN); 
                }
            } else {
                tft.drawFastHLine(0, 64, 160, ST77XX_RED); 
            }
            delay(15); 
            break;
            
        default:
            break;
    }
}


void fetchLiveAudioFeatures(String trackId) {
    WiFiClientSecure client;
    client.setInsecure(); 
    HTTPClient http;
    
    String url = "https://api.spotify.com/v1/audio-features/" + trackId;
    
    if (http.begin(client, url)) {
        // FIXED: Using wrapper's core token getter structure variables
        String headerAuth = "Bearer " + String(sp.get_access_token()); 
        http.addHeader("Authorization", headerAuth);
        
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String response = http.getString();
            JsonDocument doc;
            deserializeJson(doc, response);
            
            if (doc.containsKey("loudness")) realLoudness = doc["loudness"].as<float>();
            if (doc.containsKey("tempo")) realBPM = doc["tempo"].as<float>();
            
            Serial.print("REAL TRACK SYNC -> Loudness: "); Serial.print(realLoudness);
            Serial.print(" dB | Tempo: "); Serial.print(realBPM); Serial.println(" BPM");
        }
        http.end();
    }
}



void drawTrackText(String track, String artist) {
    tft.fillRect(0, 0, 160, 28, ST77XX_BLACK);
    tft.setTextWrap(false);
    tft.setTextColor(ST77XX_GREEN); 
    tft.setTextSize(1);
    tft.setCursor(10, 4);
    tft.print(track.substring(0, 24).c_str()); 

    tft.setCursor(10, 16);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(artist.substring(0, 26).c_str());
}

void drawSpotifyAlbumArt(String url) {
    WiFiClientSecure client;
    client.setInsecure(); 
    HTTPClient http;
    if (http.begin(client, url)) {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            int totalBytes = http.getSize();
            
            // FIXED: Allocate an explicit heap array storage buffer to decode arrays safely without stream pointer casts
            uint8_t* artBuffer = (uint8_t*)malloc(totalBytes);
            if (artBuffer != NULL) {
                WiFiClient* stream = http.getStreamPtr();
                stream->readBytes(artBuffer, totalBytes);
                
                // Decode using the verified array parser matching your JPEGDecoder footprint
                if (JpegDec.decodeArray(artBuffer, totalBytes)) {
                    renderJPEG(10, 32); 
                }
                free(artBuffer); 
            }
        }
        http.end();
    }
}

void renderJPEG(int xpos, int ypos) {
    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    while (JpegDec.read()) {
        pImg = JpegDec.pImage;
        int mcu_x = JpegDec.MCUx * mcu_w + xpos;
        int mcu_y = JpegDec.MCUy * mcu_h + ypos;
        if ((mcu_x + mcu_w <= tft.width()) && (mcu_y + mcu_h <= tft.height())) {
            tft.drawRGBBitmap(mcu_x, mcu_y, pImg, mcu_w, mcu_h);
        }
    }
}

int checkMultiClicks(int pin) {
    static bool lastButtonState = HIGH;
    static unsigned long firstClickTime = 0;
    static int clickCounter = 0;
    bool currentButtonState = digitalRead(pin);
    int resultClicks = 0;

    if (currentButtonState == LOW && lastButtonState == HIGH) {
        delay(20); 
        if (clickCounter == 0) firstClickTime = millis();
        clickCounter++;
    }
    lastButtonState = currentButtonState;

    if (clickCounter > 0 && (millis() - firstClickTime > 400)) {
        resultClicks = clickCounter;
        clickCounter = 0; 
        if (resultClicks > 3) resultClicks = 3; 
    }
    return resultClicks;
}