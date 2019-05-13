
Debian
====================
This directory contains files used to package ctdcoind/ctdcoin-qt
for Debian-based Linux systems. If you compile ctdcoind/ctdcoin-qt yourself, there are some useful files here.

## ctdcoin: URI support ##


ctdcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ctdcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ctdcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/ctdcoin128.png` to `/usr/share/pixmaps`

ctdcoin-qt.protocol (KDE)

