## About

Repository for fermentation process management using IoT.

## Repository

### Setup

If using WSL 2 for local development and code uploading, sharing connected USB devices is not enabled by default - they have to be bridged. This can be done using usbipd-win. See the latest instructions [here](https://github.com/dorssel/usbipd-win) or follow these steps:
```shell
usbipd list
usbipd bind --busid=<bus-id>
usbipd attach --wsl --busid=<bus-id>
```
