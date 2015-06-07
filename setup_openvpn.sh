#!/bin/sh
# ---
# Script to set up your system to allow OpenVPN to run without root privileges
# ---
# See OpenVPN Guide for more information
# http://community.openvpn.net/openvpn/wiki/UnprivilegedUser

# Create script to run ip with sudo, the only binary that needs sudp
touch /usr/local/unpriv-ip
chmod 755 /usr/local/unpriv-ip
echo "#!/bin/sh\nsudo /sbin/ip $*" > /usr/local/unpriv-ip

# Prepare tun0 interface manually
echo "#!/bin/sh\nopenvpn --rmtun --dev tun0\nopenvpn --mktun --dev tun0 --dev-type tun --user openvpn --group openvpn" > /etc/openvpn/openvpn-startup 

# Create 'openvpn' user
mkdir /var/lib/openvpn
chown openvpn:openvpn /var/lib/openvpn
usermod -d /var/lib/openvpn -s /sbin/nologin openvpn

# Create log directory with ownership given to 'openvpn' user
mkdir /var/log/openvpn
chown openvpn:openvpn /var/run/openvpn /var/log/openvpn /etc/openvpn -R
chmod u+w /var/run/openvpn /var/log/openvpn -R

echo "--
Successfully set up OpenVPN to run without root privileges!
--

Now run visudo and add these 2 lines:

    openvpn ALL=(ALL) NOPASSWD: /sbin/ip
    Defaults:openvpn !requiretty
"
