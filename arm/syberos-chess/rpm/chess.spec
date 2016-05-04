Name:		syberos-chess
Version:	1.0.0
Release:	1
Summary:	syberos-chess

Group:		Applicaton/Communication
License:	LGPL
URL:		www.syberos.net
Source0:	%{name}-%{version}.tar.gz		
BuildRoot:	%{_tmppath}/%{name}-root
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Widgets)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(syberos-application)
BuildRequires:  pkgconfig(syberos-application-cache)

%define appid %{name}
%define _app_system_datadir /data/data/%{appid}
%define _app_system_appdir /usr/apps/%{appid}

%description
chess-app 

%prep
%setup -q -n %{name}-%{version}/syberos-%{name}
# >> setup
# << setup

#增加的行
%package    coverage
Summary:    coverage testing
Group:      Development/File
%description coverage
coverage testing

%files coverage
/home/abuild/coverage
#增加的行

%build
# >> build pre
# << build pre
#export QT_SELECT=5
%qmake5 TARGET_DIR=%{_app_system_appdir} APP_DATADIR=%{_app_system_datadir}
#make clean
#make
# >> build post
%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig
# << build post


%install
make INSTALL_ROOT=$RPM_BUILD_ROOT install
#增加的行
rm -rf %{buildroot}
mkdir -p %{buildroot}/home/abuild/coverage
%qmake5_install
find ${RPM_BUILD_DIR} -name '*.gcno' -exec  tar -cvzf %{buildroot}/home/abuild/coverage/%{name}-%{version}-%{release}-coverage.tar.gz {} \+
#增加的行

%clean

%files
#%defattr(-,root,root,-) 
%{_app_system_appdir}/bin/chess
%{_app_system_appdir}/sopconfig.xml
%defattr(777,service,service,-)
%{_app_system_appdir}/res/chess.png
%{_app_system_appdir}/audio/audio_move_chess.ogg

