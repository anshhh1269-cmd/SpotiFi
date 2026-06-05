# SpotiFi

An ESP32-powered desktop toy that interfaces with the Spotify Web API to display live track metadata, custom retro animations, and interactive player visualizations on an ILI9341 TFT display. This display is a hardware-software hybrid where physical screens meet APIs and WiFi connections.

# The Reason

Now, why did I choose this project over all amazing starter projects?
First obvi it looks more on the easier side compared to the rest of them and my main objective was to learn Fusion360 through it to master my skillset in CAD and 3D Printing. Second this display looked like something I could actually use or someone else could if they like keeping their surroundings more towards the side of a cosy vibe. 

# The Functionality

Firstly, hardware:
SpotiFi contains a TFT display, an ESP32, and five switches..each of the switches have a functionality; 

First Button: Forward
Second Button: Pause/Play
Third button: Backwards
Fourth button: 3 modes ( an inspiration from my sister); one of the modes is where the screen would show the cover image of the song/album and a character on the side which moves/vibes, others include a live oscilloscope and a character-only mode.

The ESP32 device will connect to the local Wi-Fi network of your home and use the OAuth 2.0 authentication to create a secure connection between the ESP32 and the Spotify Web API. It will send a series of background HTTP requests to the API at regular intervals in order to retrieve a real-time JSON payload containing track information such as track title, artist name, and playback state.

Then, the processed data will be transferred to the ILI9341 display controller in order to update the text and graphics on the screen. When you press any of the physical buttons, a reverse command will be sent to the Spotify server through the corresponding GPIO input.

# The 3D Model

<img width="1177" height="780" alt="Screenshot 2026-06-05 230702" src="https://github.com/user-attachments/assets/fc1be34f-57b9-4e49-bd49-e4947e286b7b" />

<img width="701" height="562" alt="Screenshot 2026-06-05 230719" src="https://github.com/user-attachments/assets/1418a54f-a18c-4c00-b40f-91352845d692" />

<img width="1463" height="767" alt="Screenshot 2026-06-05 230743" src="https://github.com/user-attachments/assets/3d4b17c4-9c99-488c-b27b-d18fad9a4fab" />

**Public Link: https://a360.co/4dSKmTr**

# The Wiring


