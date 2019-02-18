# ___________________________________________________________
# ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
# CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
#
# #RVCGEEKS rvcvault
# created on 27.01.2019
# 
# AES 128 bit file encryption / Decryption
#
# ./Makefile  : makefile for creating an installer...
#
all:
	#build the elf binary from source via g++ completely without dynamic linking and code obfuscation ...
	g++ -ansi -O2 -Wall -static -fpie -fvisibility=hidden -fvisibility-inlines-hidden -s main.cpp -o rvcvault
	
	#create a temporary repostiory for building debian installer ...
	mkdir rvcvault_pkg
	
	#create mandatory subdirectories ...
	mkdir rvcvault_pkg/bin
	mkdir rvcvault_pkg/DEBIAN
	mkdir rvcvault_pkg/usr
	mkdir rvcvault_pkg/usr/local
	mkdir rvcvault_pkg/usr/local/man
	mkdir rvcvault_pkg/usr/local/man/man1
	
	
	#move the builded elf binary , credenentials and manpages in respective directories ...
	mv rvcvault rvcvault_pkg/bin/
	cp changelog rvcvault_pkg/DEBIAN/
	cp control rvcvault_pkg/DEBIAN/
	cp copyright rvcvault_pkg/DEBIAN/
	cp rvcvault.1 rvcvault_pkg/usr/local/man/man1/
	
	#call dpkg to build deb installer for this repostiory and move to releases...
	dpkg-deb --build rvcvault_pkg
	mv rvcvault_pkg.deb releases/
	
	#remove the temporary repostiory as it is obsolete after creation of installer ...
	rm -R rvcvault_pkg/
