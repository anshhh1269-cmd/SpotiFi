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

<img width="1350" height="737" alt="image" src="https://github.com/user-attachments/assets/5c7360f4-011d-4415-b2c5-eb6379cba8a4" />


<img width="1177" height="780" alt="Screenshot 2026-06-05 230702" src="https://github.com/user-attachments/assets/fc1be34f-57b9-4e49-bd49-e4947e286b7b" />

<img width="701" height="562" alt="Screenshot 2026-06-05 230719" src="https://github.com/user-attachments/assets/1418a54f-a18c-4c00-b40f-91352845d692" />

<img width="1463" height="767" alt="Screenshot 2026-06-05 230743" src="https://github.com/user-attachments/assets/3d4b17c4-9c99-488c-b27b-d18fad9a4fab" />

<img width="1187" height="702" alt="image" src="https://github.com/user-attachments/assets/8d2a4d1a-e517-445b-b061-103d02019563" />


**Public Link: https://a360.co/4dSKmTr**

# The Wiring

<img width="1169" height="827" alt="Schematic_SpotiFi_2026-06-15" src="https://github.com/user-attachments/assets/ea48272f-68fe-46dd-a757-3b10fa912283" />

EasyEDA Link: https://easyeda.com/editor#project_id=699845724ab2404091f892d3d4bc927d

## 📊 Bill of Materials (BOM)

| Item | Quantity | Use | Cost (THB) + Shipping | Link |
| :--- | :---: | :--- | :---: | :--- |
| **Stranded Silicone Wires** | 4-5 meters | wire components together by solder | 630 | https://shopee.co.th/1-5-10-Meter-Number-6-30AWG-0.08mm-UL-Stranded-Silicone-Flexible-Cable-600V-200%C2%B0C-i.1096643478.27219985090?is_from_login=true |
| **ESP-32 30-pin** | 1 | microcontroller | 230 | https://shopee.co.th/ESP32-ESP-32-DOIT-DEVKIT-V1-Layout-Development-Board-30-Pin-i.128765755.4216421644?extraParams=%7B%22display_model_id%22%3A205873168602%2C%22model_selection_logic%22%3A3%7D&sp_atk=bbc53ea4-5011-4bb9-9671-540ca8dcf233&xptdk=bbc53ea4-5011-4bb9-9671-540ca8dcf233 |
| **LCD TFT Screen** | 2 | The screen is used to display the output from Spotify API | 300 | https://shopee.co.th/%E0%B8%82%E0%B8%AD-LCD-TFT-1.8%E0%B8%99%E0%B8%B4%E0%B9%89%E0%B8%A5-RGB-128x160px-SPI-SNP-00086-i.1272136510.26451852926?extraParams=%7B%22display_model_id%22%3A245961807170%2C%22model_selection_logic%22%3A3%7D&sp_atk=58c967bb-f13b-4bf2-b8dd-e695ec0ac357&xptdk=58c967bb-f13b-4bf2-b8dd-e695ec0ac357 |
| **Tactical Switches** | 5 | Switches usedto control the output executed | 63 | https://shopee.co.th/Outemu-Switch-Red-Switch-Blue-Switch-%E0%B8%9B%E0%B8%B5%E0%B9%88%E0%B8%A1%E0%B8%AA%E0%B8%A7%E0%B8%B4%E0%B8%95%E0%B8%8A%E0%B9%8C-Mechanical-Keyboard-(Switch%E0%B9%81%E0%B8%ACCherry-Mx)-2-%E0%B8%82%E0%B8%B2-i.114602778.11226353225?extraParams=%7B%22display_model_id%22%3A68174988955%2C%22model_selection_logic%22%3A3%7D&sp_atk=8a9c0300-f607-44dd-a667-facdf7ef0c61&xptdk=8a9c0300-f607-44dd-a667-facdf7ef0c61 |
| **Soldering iron** | 1 | needed to solder parts together | 179 | https://shopee.co.th/%E0%B8%8A%E0%B8%B5%E0%B8%AB%E0%B8%B5%E0%B8%A3%E0%B9%82%E0%B8%9F%E0%B8%9F%E0%B9%8A%E0%B8%B2-15-%E0%B8%8A%E0%B8%B4%E0%B8%A3-%E0%B8%A1%E0%B8%A3%E0%B8%B3%E0%B8%AD%E0%B8%A1%E0%B8%88%E0%B8%B5%E0%B9%81%E0%B8%AA%E0%B8%94%E0%B8%81%E0%B8%9C%E0%B8%A5%E0%B8%94%E0%B8%B4%E0%B8%88%E0%B8%B4%E0%B8%A5%E0%B8%AD%E0%B8%A5-i.1198267900.25324123792?extraParams=%7B%22display_model_id%22%3A250635337009%2C%22model_selection_logic%22%3A3%7D&rModelId=250635337009&sp_atk=48ac7c46-89c0-4e79-a02a-c1a16f42ead9&vItemId=27690169019&vModelId=243767613376&vShopId=1449018616&xptdk=48ac7c46-89c0-4e79-a02a-c1a16f42ead9 |
| **Hot glue gun sticks** | 1 pack | needed for my hot glue gun | 109 | https://shopee.co.th/50-%E0%B8%8A%E0%B8%B4%E0%B9%83%E0%B8%A3-7-%E0%B8%A1%E0%B8%B4%E0%B8%A5%E0%B8%A5%E0%B8%B4%E0%B9%80%E0%B8%A1%E0%B8%95%E0%B8%A3-100-%E0%B8%A1%E0%B8%B4%E0%B8%A5%E0%B8%A5%E0%B8%B4%E0%B9%80%E0%B8%A1%E0%B8%95%E0%B8%A3%E0%B9%82%E0%B8%9B%E0%B8%A3%E0%B9%86%E0%B9%83%E0%B8%AA-Hot-Melt-%E0%B8%81%E0%B8%B2%E0%B8%A7-Sticks-%E0%B8%AA%E0%B9%83%E0%B8%B2%E0%B8%AB%E0%B8%A3%E0%B8%B1%E0%B8%91%E0%B8%84%E0%B8%A7%E0%B8%B2%E0%B8%A1%E0%B8%A3%E0%B9%83%E0%B8%AD%E0%B8%99%E0%B8%9B%E0%B8%B7%E0%B8%99%E0%B8%9E%E0%B8%81%E0%B8%9B%E0%B8%B7%E0%B8%99%E0%B8%81%E0%B8%B2%E0%B8%A7%E0%B9%84%E0%B8%9F%E0%B8%9F%E0%B9%8A%E0%B8%B2%E0%B8%9B%E0%B8%B7%E0%B8%99%E0%B8%AB%E0%B8%B1%E0%B8%95%E0%B8%96%E0%B8%81%E0%B8%A3%E0%B8%A3%E0%B8%A1%E0%B8%8B%E0%B9%88%E0%B8%AD%E0%B8%A1%E0%B8%97%E0%B8%B1%E0%B9%88%E0%B8%A7%E0%B9%84%E0%B8%9B%E0%B8%A1%E0%B8%B2%E0%B8%A7-DIY-%E0%B9%80%E0%B8%84%E0%B8%A3%E0%B8%B7%E0%B9%88%E0%B8%AD%E0%B8%81%E0%B8%A1%E0%B8%B7%E0%B8%AD-i.102282123.25481407599?extraParams=%7B%22display_model_id%22%3A222841142091%2C%22model_selection_logic%22%3A3%7D&sp_atk=8ebf9c46-6013-42ce-93b3-87f9d9e26f0b&xptdk=8ebf9c46-6013-42ce-93b3-87f9d9e26f0b |
| **Solder Wire** | 1 | needed for the soldering iron | 630 | https://shopee.co.th/63-37-Tin-Rosin-Core-20g-0.8-%E0%B8%A1%E0%B8%A1.%E0%B8%A5%E0%B8%A7%E0%B8%94%E0%B8%9A%E0%B8%B1%E0%B8%94%E0%B8%81%E0%B8%A3%E0%B8%B5%E0%B8%9E%E0%B8%A3%E0%B9%83%E0%B8%AD%E0%B8%A1%E0%B8%9F%E0%B8%A5%E0%B8%B1%E0%B8%81%E0%B8%8B%E0%B9%8C%E0%B8%AA%E0%B9%83%E0%B8%B2%E0%B8%AB%E0%B8%A3%E0%B8%B1%E0%B8%91%E0%B8%9A%E0%B8%B1%E0%B8%94%E0%B8%81%E0%B8%A3%E0%B8%B5%E0%B9%84%E0%B8%9F%E0%B8%9F%E0%B9%8A%E0%B8%B2%E0%B8%8B%E0%B9%88%E0%B8%AD%E0%B8%A1-i.1842448496.51861476793?extraParams=%7B%22display_model_id%22%3A375998075389%2C%22model_selection_logic%22%3A3%7D&sp_atk=c3e4871c-22dc-4a27-8346-67d5d2387692&xptdk=c3e4871c-22dc-4a27-8346-67d5d2387692 |
| **M2 Screws** | 1 | needed to screw ESP32 and TFT Screen to the 3D Printed SpotiFi | 167 | https://shopee.co.th/%E0%B8%8A%E0%B8%B5%E0%B8%94%E0%B9%80%E0%B8%AA%E0%B8%B2%E0%B8%97%E0%B8%AD%E0%B8%81%E0%B9%80%E0%B8%AB%E0%B8%A5%E0%B8%B7%E0%B8%AD%E0%B8%81-%E0%B9%80%E0%B8%AA%E0%B8%B2%E0%B9%84%E0%B8%A3%E0%B8%A5%E0%B8%AD%E0%B8%99-%E0%B8%94%E0%B8%AD%E0%B8%95-%E0%B8%AA%E0%B8%81%E0%B8%A3%E0%B8%B9-M2-M3-120-180-910%E0%B8%8A%E0%B8%B4%E0%B9%83%E0%B8%99-M2-M3-Hex-Brass-Nylon-Standoff-Nut-Screw-kit-%E0%B9%80%E0%B8%AA%E0%B8%B2%E0%B8%A2%E0%B8%B6%E0%B8%94%E0%B9%81%E0%B8%9C%E0%B9%81%E0%B8%94%E0%B8%9B%E0%B8%A3...-i.944231623.40607511905?extraParams=%7B%22display_model_id%22%3A208588712774%2C%22model_selection_logic%22%3A3%7D&sp_atk=6c7eca2d-ecc2-40df-9c8d-caf153cace20&xptdk=6c7eca2d-ecc2-40df-9c8d-caf153cace20 |


