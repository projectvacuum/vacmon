#
#  Apache httpd.conf include file for VacMon
#
#  Andrew McNab, University of Manchester.
#  Copyright (c) 2013-8. All rights reserved.
#
#  Redistribution and use in source and binary forms, with or
#  without modification, are permitted provided that the following
#  conditions are met:
#
#    o Redistributions of source code must retain the above
#      copyright notice, this list of conditions and the following
#      disclaimer. 
#    o Redistributions in binary form must reproduce the above
#      copyright notice, this list of conditions and the following
#      disclaimer in the documentation and/or other materials
#      provided with the distribution. 
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
#  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
#  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
#  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
#  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
#  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#
#  Contacts: Andrew.McNab@cern.ch  https://www.gridpp.ac.uk/vac/

#
#  Apache httpd.conf include file for VacMon
#
#  This file should be copied to /etc/httpd/includes/vacmon.httpd.inc
#  where it will be loaded by the common Vac Project httpd.conf
#  The vacmon.gridpp.ac.uk hostnames in this file  must be replaced 
#  with the hostname of your depository service.
#
#  Things to check if you get no successful requests:
#  - iptables is disabled or allows incoming TCP on ports 80 and 443
#  - SE linux is diabled (echo 0 >/selinux/enforce) or configured to allow
#    httpd to access the paths in this file

<VirtualHost vacmon.gridpp.ac.uk:80>
ServerName   vacmon.gridpp.ac.uk
DocumentRoot /var/www/vacmon
CustomLog    logs/http--vacmon.log combined

<Directory /var/www/vacmon>
Options Indexes
</Directory>

ScriptAliasMatch ^/.*/.*  /usr/sbin/vacmon-cgi
ScriptAliasMatch ^/[^.]*$ /usr/sbin/vacmon-cgi

</VirtualHost>

<VirtualHost vacjson.gridpp.ac.uk:443>
ServerName   vacjson.gridpp.ac.uk
DocumentRoot /var/www/vacmon
CustomLog    logs/https-vacjson.log combined

<Directory /var/www/vacmon>
Options Indexes
</Directory>

ScriptAliasMatch ^/.*/.*  /usr/sbin/vacjson-cgi
ScriptAliasMatch ^/[^.]*$ /usr/sbin/vacjson-cgi

SSLEngine               on
SSLCertificateFile      /etc/grid-security/vacjson.gridpp.ac.uk.cert.pem
SSLCertificateKeyFile   /etc/grid-security/vacjson.gridpp.ac.uk.key.pem
SSLCACertificatePath    /etc/grid-security/certificates
#SSLCARevocationPath    YOUR CRL DIRECTORY WOULD GO HERE
SSLVerifyClient         none
SSLVerifyDepth          10
SSLOptions              +StdEnvVars
</VirtualHost>

<VirtualHost vacjson.gridpp.ac.uk:80>
ServerName   vacjson.gridpp.ac.uk
DocumentRoot /var/www/vacmon
CustomLog    logs/http--vacjson.log combined
Redirect     / https://vacjson.gridpp.ac.uk/
</VirtualHost>
