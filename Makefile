CC_WIN = x86_64-w64-mingw32-gcc
WINDRES = x86_64-w64-mingw32-windres

all: linux

linux:
	$(MAKE) -C src/Graphique-2.0
	$(MAKE) -C src

windows:
	convert icone.png icone.ico
	echo '1 ICON "icone.ico"' > ressources.rc
	$(WINDRES) ressources.rc -O coff -o ressources.res
	$(CC_WIN) src/C_files/*.c src/Graphique-2.0/*.c ressources.res -o SpaceInvaders.exe -I/usr/x86_64-w64-mingw32/include/SDL2 -L/usr/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows
	mkdir -p SpaceInvaders_Windows
	mv SpaceInvaders.exe SpaceInvaders_Windows/
	cp -r src/Lutins SpaceInvaders_Windows/
	cp /usr/x86_64-w64-mingw32/bin/*.dll SpaceInvaders_Windows/
	zip -r SpaceInvaders_Windows.zip SpaceInvaders_Windows

appimage: linux
	wget -nc https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
	chmod +x linuxdeploy-x86_64.AppImage
	mkdir -p AppDir/usr/bin/Lutins
	cp src/build/main AppDir/usr/bin/main
	cp -r src/Lutins/* AppDir/usr/bin/Lutins/
	echo '#!/bin/bash' > custom-apprun
	echo 'HERE="$$(dirname "$$(readlink -f "$${0}")")"' >> custom-apprun
	echo 'export LD_LIBRARY_PATH="$${HERE}/usr/lib:$${LD_LIBRARY_PATH}"' >> custom-apprun
	echo 'cd "$${HERE}/usr/bin"' >> custom-apprun
	echo 'exec ./main "$$@"' >> custom-apprun
	chmod +x custom-apprun
	echo '[Desktop Entry]' > SpaceInvaders.desktop
	echo 'Name=SpaceInvaders' >> SpaceInvaders.desktop
	echo 'Exec=main' >> SpaceInvaders.desktop
	echo 'Icon=icone' >> SpaceInvaders.desktop
	echo 'Type=Application' >> SpaceInvaders.desktop
	echo 'Categories=Game;' >> SpaceInvaders.desktop
	echo 'Terminal=false' >> SpaceInvaders.desktop
	NO_STRIP=1 ./linuxdeploy-x86_64.AppImage --appdir AppDir --executable AppDir/usr/bin/main --custom-apprun custom-apprun --desktop-file SpaceInvaders.desktop --icon-file icone.png --output appimage
	rm -rf AppDir SpaceInvaders.desktop custom-apprun

clean:
	$(MAKE) -C src/Graphique-2.0 clean
	$(MAKE) -C src clean
	rm -rf SpaceInvaders_Windows SpaceInvaders_Windows.zip ressources.res ressources.rc icone.ico SpaceInvaders.exe appimage *.AppImage 