# t6zm internal

### Status: `In development`

This is a Black Ops 2 Zombies internal mod menu.

## What is this?

This is an internal mod menu, meaning that when you compile the code you get a DLL file and you inject this inside the application.
There are several benefits and downsides to this but most downsides don't matter because of how old the game is.
The upsides are that we can call native functions from the game, draw our own elements so that we can implement a cool UI over the game.

This mod menu is based of of BigBaseV2 since I love the way it's coded and works.

## Features

 - Menu is drawn with imgui allowing for quickly adding more features
 - Thread Pool to keep features running infinitely without hitting the main thread
 - Settings management
 - Logging to %appdata%/t6zm_cheat
 - Custom Logger made by me

## Credits

 - [Pocakking for his beautifull base](https://github.com/Pocakking/BigBaseV2)
 - [ocornut for developing imgui](https://github.com/ocornut/imgui)
 - [Rebzzel for his DirectX11 Swapchain hook](https://github.com/Rebzzel/kiero)
