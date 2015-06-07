night_watchman
==============

### Summary

A security-focused OpenVPN client for Linux. Planned features:

- Auto-reconnect on failure
- Blocks hosts non-VPN internet traffic in the event VPN connection fails
- Verifies VPN servers IP address and hostname authenticity (similar to SSH known_hosts)
- Verifies cipher suite is forward-secret and not degraded
- Runs OpenVPN as unprivileged user

*Note:* this project is primarily a challenge for me to learn the internals of the Linux kernel and get exposure to C programming. It is very much a work-in-progress.


### How to run:

**Step 1a)**: Set-up OpenVPN to run as an unprivileged user

OpenVPN typically requires being run with sudo privileges - which is bad for security. This would also require night_watchman to have setuid privileges in order to spawn OpenVPN. 

So to increase security we're going to run OpenVPN run without requiring root privileges. 

OpenVPN provides a how-to guide for this http://community.openvpn.net/openvpn/wiki/UnprivilegedUser. I've summarized the steps below. Alternatively, you can run `setup_openvpn.sh` with su to automate this step (after reviewing the contents of the shell script of course).

    $ touch /usr/local/unpriv-ip
    $ chown 755 /usr/local/unpriv-ip
    $ echo "#!/bin/sh\nsudo /sbin/ip $*" > /usr/local/unpriv-ip
    $ echo "#!/bin/sh\nopenvpn --rmtun --dev tun0\nopenvpn --mktun --dev tun0 --dev-type tun --user openvpn --group openvpn" > /etc/openvpn/openvpn-startup 
    $ mkdir /var/log/openvpn
    $ chown openvpn:openvpn /var/run/openvpn /var/log/openvpn /etc/openvpn -R
    $ chmod u+w /var/run/openvpn /var/log/openvpn -R

**Step 1b)**: Add openvpn user to /etc/sudo

Then add these two lines by editing `/etc/sudo` or running `visudo`:

    openvpn ALL=(ALL) NOPASSWD: /sbin/ip
    Defaults:openvpn !requiretty

**Step 1c)**: Update your openvpn config to include these lines:

    log /var/log/openvpn/openvpn
    iproute /usr/local/sbin/unpriv-ip
    dev tun0
    persist-tun

Openvpn is now set up to run without root privileges!

*SELinux users*: if you're using SELinux there is one final step at the bottom of the [OpenVPN](https://community.openvpn.net/openvpn/wiki/UnprivilegedUser) guide you must follow.

*Step 2)*: Now compile & run Night Watchman

    $ make
    $ ./night_watchman
