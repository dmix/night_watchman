#!/bin/sh

touch /usr/local/unpriv-ip
chmod 755 /usr/local/unpriv-ip
echo "#!/bin/sh\nsudo /sbin/ip $*" > /usr/local/unpriv-ip
echo "#!/bin/sh\nopenvpn --rmtun --dev tun0\nopenvpn --mktun --dev tun0 --dev-type tun --user openvpn --group openvpn" > /etc/openvpn/openvpn-startup 
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
