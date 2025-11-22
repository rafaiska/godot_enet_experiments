# 2025-11-22

Just started writing these logs. There already have been many challenges along the way, but one technical issue I had that still puzzles me is this one.

When I was sending packets from the server application, I had to add 16 bytes of characters to the payload. Otherwise, it was getting replaced with some kind of random data. I started tcpdump and checked the UDP packet being sent to confirm it. I didn't investigate at the time, but it was like it was replacing these bytes with part of the headers of the underlying network stack layers or something.

If I used this function in main.cpp:

```C++
void send_map_data(const ENetEvent &event, const rapinae::SMap &map);
  ```

I had to send the map data payload like this:

```json
 0000000000000000{"mapdata":"(500|500)"} 
 ```

So I could read it in the client without compromising any data. The first 16 zeroes (ASCII 48) were being replaced with unprintable bytes.

THE PROBLEM FIXED ITSELF ON ITS OWN as I added more lines of code to the project. I can't pinpoint exactly which change made it happen. This is quite frustrating, as I was yearning to find out what was happening here.
