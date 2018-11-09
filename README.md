# Matrix
Animations displaying on LED Matrix, currently just plays snake on loop.

## Build notes
This project depends on a private fork of the [Arduino Websockets](https://github.com/Links2004/arduinoWebSockets) library, found [here](https://github.com/Danappelxx/arduinoWebSockets).

To build locally, clone the fork into a lib subdirectory using the following command:
```bash
git clone https://github.com/Danappelxx/arduinoWebSockets lib/arduinoWebsockets
```

This should be enough to appease the particle compiler.
