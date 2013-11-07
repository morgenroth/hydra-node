Hydra Node Daemon
=================

Hydra is a distributed emulation framework for large-scale software testing in disrupted networks. The Hydra Node Daemon (hnd) is a small component which must run on all nodes and
performs remote actions.

----------


#### Build The Node Daemon Archive

```
./autogen.sh
./configure
make dist
```

Place the generated `.tar.gz` file into the `dl` folder of the OpenWrt source.


#### Build OpenWrt Package

Copy the contents of the `<repository>/openwrt` to the source of OpenWrt. Then generate
the Node Daemon Archive and place it into the `dl` folder of the OpenWrt source. Finally,
configure OpenWrt to include the `hnd` package in the build.

