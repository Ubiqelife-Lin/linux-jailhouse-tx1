JAILHOUSE for NVIDIA Jetson TX1
===============================

This is the Jailhouse hypervisor [1] for the default **3.10** Linux kernel [2]
running on NVIDIA Jetson TX1 platform [3]. The porting activity has been done
in the context of the HERCULES European project [4]. Refer to the original
website [1] for further information about Jailhouse or other platforms/kernel
versions.


Build & Installation
--------------------

To build Jailhouse, a copy of the compiled Linux kernel with all object files
is needed, to be able of building a kernel module.
You can refer to the guide in [5] for compiling a kernel for the TX1 platform.

To build and install jailhouse just type:

    sudo make KDIR=/path/to/compiled/kernel/ install

The hypervisor requires a contiguous piece of RAM for itself and each
additional cell. This currently has to be pre-allocated during boot-up.
On ARM platforms this is usually achieved by reducing the amount of memory seen
by the Linux kernel. You therefore need to modify the kernel boot arguments
adding ```mem=3968M vmalloc=512M``` (on TX1 this can be written inside the
```/boot/extlinux/extlinux.conf``` file).

Since Jailhouse writes its output directly to the serial port, you also need to
make sure that the kernel command line does *not* have its console set to log to
the serial port. Therefore, remove any ```console=``` parameter from the boot
arguments (again, on TX1 this can be achieved by modifying the
```/boot/extlinux/extlinux.conf``` file). This means that you cannot log
through the serial console and you need a different mechanism (e.g. HDMI or
SSH) for accessing the system.


Usage
-----

Once the boot arguments has been modified and the machine rebooted, to run the
hypervisor type:

	sudo sh -c 'echo 1 > /sys/kernel/debug/cpuidle_t210/fast_cluster_states_enable'
	sudo modprobe jailhouse
	sudo jailhouse enable jailhouse/configs/jetson-tx1.cell


Demonstration
-------------

Next, you can create a cell with a demonstration application as follows:

	sudo jailhouse cell create jailhouse/configs/jetson-demo.cell
	sudo jailhouse cell load jetson-demo jailhouse/inmates/demos/arm64/gic-demo.bin
	sudo jailhouse cell start jetson-demo

This application will program a periodic timer interrupt, measuring the jitter
and displaying the result on the console.

After creation, cells are addressed via the command line tool by providing
their names or their runtime-assigned IDs. You can obtain information about
active cells this way:

	jailhouse cell list

You can also obtain statistical information about the number of VM exists:

	jailhouse cell stats jetson-demo

Cell destruction is performed through the following command:

	sudo jailhouse cell destroy jetson-demo

Finally, the jailhouse hypervisor can be disabled by typing:

	sudo jailhouse disable

References
----------

* [1] Jailhouse hypervisor: https://github.com/siemens/jailhouse
* [2] Linux for Tegra: https://developer.nvidia.com/embedded/linux-tegra
* [3] NVIDIA Jetson TX1 platform: http://www.nvidia.com/object/jetson-tx1-dev-kit.html
* [4] HERCULES EU project: http://hercules2020.eu
* [5] Build TX1 Kernel and Modules: http://www.jetsonhacks.com/2016/09/28/build-tx1-kernel-and-modules-nvidia-jetson-tx1/


