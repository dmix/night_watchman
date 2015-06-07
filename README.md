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


**Step 2)**: Now compile & run Night Watchman

    $ make
    $ ./night_watchman
