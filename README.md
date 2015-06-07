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

**Step 1)**: Set-up OpenVPN to run as an unprivileged user

To improve security, we're going to run both openvpn and night_watcman without root privileges. OpenVPN typically requires root, so openvpn needs a be set up to run as an unprivileged user.

I've created a simple [instruction guide](https://github.com/dmix/night_watchman/blob/master/OPENVPN.md) you can follow.

**Step 2)**: Now compile & run Night Watchman

    $ make
    $ ./night_watchman
