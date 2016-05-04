TEMPLATE = subdirs
SUBDIRS = src
NAME=syberos-chess
VERSION=-1.0

DISTFILES += qml/*.qml

icon.files = chess.png
icon.path = $${TARGET_DIR}/res

sopconfig.files = sopconfig.xml
sopconfig.path = $${TARGET_DIR}

audio.files = audio/audio_move_chess.ogg
audio.path = $${TARGET_DIR}/audio

INSTALLS += icon sopconfig audio

clear.commands += rm -fr *.tar.gz *.rpm rpmbuild
clear.depends = clean distclean

rpm.target = rpm
rpm.commands = \
                    rm -fr rpmbuild \
                    && mkdir rpmbuild \
                    && mkdir rpmbuild/SOURCES \
                    && mkdir rpmbuild/SPECS \
                    && mkdir rpmbuild/SRPMS \
                    && mkdir rpmbuild/RPMS \
                    && mkdir rpmbuild/BUILD \
                    && cp *.spec rpmbuild/SPECS/ \
                    && cp *.tar.gz rpmbuild/SOURCES/ \
                    && rpmbuild --define=\"_topdir `pwd`/rpmbuild\" -ba --target i586 $${NAME}.spec \
                    && mv rpmbuild/RPMS/i586/*.rpm . \
                    && mv rpmbuild/SRPMS/*.rpm . \
                    && rm -fr rpmbuild  \
                    && rm -fr .tmp

rpm.depends = first dist

QMAKE_EXTRA_TARGETS += dist rpm clear



