qmake durangoImagerUI.pro -spec linux-g++ CONFIG+=qtquickcompiler CONIFG+=release
make qmake_all
make -j20

~/linuxdeployqt-continuous-x86_64.AppImage durangoImager -appimage
echo "cleaning directory"
make clean
rm -R doc
rm -R lib
rm -R plugins
rm -R translations
rm .DirIcon
rm AppRun
rm qt.conf
rm durangoImager
