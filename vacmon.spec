Name: vacmon
Version: %(echo ${VACMON_VERSION:-0.0})
Release: 1
BuildArch: noarch
Summary: Vacmon daemon and web scripts
License: BSD
Group: System Environment/Daemons
Source: vacmon.tgz
URL: http://www.gridpp.ac.uk/vac/
Vendor: GridPP
Packager: Andrew McNab <Andrew.McNab@cern.ch>
#Requires: 

%description
Vacmon is a monitoring daemon for Vac

%prep

%setup -n vacmon

%build

%install
make install PYTHON_SITEARCH=%{python_sitearch} 

%preun
if [ "$1" = "0" ] ; then
  # if uninstallation rather than upgrade then stop
  service vacmond stop
fi

%post
service vacmond status
if [ $? = 0 ] ; then
  # if already running then restart with new version
  service vacmond restart
fi

%files
/usr/sbin/*
/etc/rc.d/init.d/vacmond
/etc/logrotate.d/vacmond
