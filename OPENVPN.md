# How to run OpenVPN without root privileges

OpenVPN typically requires being run with sudo privileges - which is bad for security. This would also require night_watchman to have setuid privileges in order to spawn OpenVPN. 

So to increase security we're going to run OpenVPN run without requiring root privileges. 

OpenVPN provides a [how-to guide](http://community.openvpn.net/openvpn/wiki/UnprivilegedUser) on their website. I've summarized the steps below. Alternatively, the shell commands are provided in [night_watchman/setup_openvpn.sh](https://github.com/dmix/night_watchman/blob/master/setup_openvpn.sh).

### Step 1: Create script to run ip with sudo, the only binary that needs sudo

    touch /usr/local/unpriv-ip
    chmod 755 /usr/local/unpriv-ip
    echo "#!/bin/sh\nsudo /sbin/ip $*" > /usr/local/unpriv-ip

### Step 2: Prepare tun0 interface manually

    echo "#!/bin/sh\nopenvpn --rmtun --dev tun0\nopenvpn --mktun --dev tun0 --dev-type tun --user openvpn --group openvpn" > /etc/openvpn/openvpn-startup 

### Step 3: Create 'openvpn' user and prep folders

    useradd -s /sbin/nologin openvpn
    mkdir /var/lib/openvpn
    chown openvpn:openvpn /var/lib/openvpn
    usermod -d /var/lib/openvpn -s /sbin/nologin openvpn

### Step 4: Create log directory with ownership given to 'openvpn' user

    mkdir /var/log/openvpn
    mkdir /var/run/openvpn
    chown openvpn:openvpn /var/run/openvpn /var/log/openvpn /etc/openvpn -R
    chmod u+w /var/run/openvpn /var/log/openvpn -R

### Step 5: Add openvpn user to /etc/sudo

Then add these two lines by editing `/etc/sudo` or running `visudo`:

    openvpn ALL=(ALL) NOPASSWD: /sbin/ip
    Defaults:openvpn !requiretty

### Step 6: Update your openvpn config to include these lines:

    log /var/log/openvpn/openvpn
    iproute /usr/local/sbin/unpriv-ip
    dev tun0
    persist-tun

Done! Openvpn is now set up to run without root privileges.

To manually run openvpn without root, run:

    sudo -u openvpn openvpn --config <config>

*SELinux users*: if you're using SELinux there is one final step at the bottom of the [OpenVPN](https://community.openvpn.net/openvpn/wiki/UnprivilegedUser) guide you must follow.
