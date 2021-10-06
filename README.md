<div align="center">
	<img src="dwm.png">
</div>

# Suckless' Dynamic Window Manager

As the
[Suckless](https://dwm.suckless.org/)
Devs tell us:
DWM is an extremely fast,
small,
and dynamic window manager for X.
This repository is a fork of DWM with many patches
applied and many custom features.

## Requirements

In order to build DWM you need the Xlib header files.

To run this exact build you need the following software installed in your computer:
* `st`
* `dmenu`
* `qutebrowser`
* `mailsync`
* `neomutt`
* `newsboat`

## Installation

Edit `config.mk` to match your local setup
(DWM is installed into the `/usr/local` namespace by default).

Afterwards enter the following command to build and install DWM
(if necessary as root with `sudo` or `doas`):
```sh
make clean install
```

## Running

Add the following line to your `.xinitrc` to start DWM using the `startx` command:
```sh
exec dwm
```

## Configuration

The configuration of DWM is done by creating a custom `config.h` and (re)compiling the source code.

In the `patches` directory some interesting default configs are included.

## Authors

* Sergio Miguéns Iglesias <[sergio@lony.xyz](mailto:dev@suckless.org)>
* Suckless Devs and Hackers <[dev@suckless.org](mailto:dev@suckless.org)>

## License

Check [LICENSE](LICENSE).
