# godot_enet_experiments

Experimental environment involving an ENet Connection between a game client made in Godot and a C++ server. The goal is to make a multiplayer version of the classic [Asteroids](https://en.wikipedia.org/wiki/Asteroids_(video_game)) game using ENet as the main network protocol.

# Purpose of this repo

I just started contributing to [Godot Engine's unit testing](https://github.com/godotengine/godot/issues/43440), and ENetConnection seems to be one of the modules that still have no unit testing available. As I was writing those tests, I found out that I lack knowledge of how this protocol was supposed to work, so I decided to tinker with it.

# Journal

I'm compiling details of my work on a [journal](journal.md), in which I write details on the technical challenges I'm facing as I walk through this project.