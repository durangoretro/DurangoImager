FROM stateoftheartio/qt6:6.6-gcc-aqt

# Install libraries

RUN sudo apt-get update &&\
    sudo apt-get install -y libgl-dev fuse file wget
RUN wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage -O ~/linuxdeployqt-continuous-x86_64.AppImage
RUN chmod +x ~/linuxdeployqt-continuous-x86_64.AppImage
VOLUME /src/qt6

WORKDIR /src/qt6

CMD ["sh", "build.sh"]