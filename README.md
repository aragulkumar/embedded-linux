# Embedded Linux Kernel Module – Raspberry Pi

This repository contains a **simple Linux kernel module** developed as part of an **Embedded Linux & Raspberry Pi workshop**.  
The project demonstrates how the **Linux kernel acts as the bridge between software and hardware**, and how **C programming** is used to extend kernel functionality.

The module is built using **cross-compilation** on an x86 Ubuntu host and is intended to run on a **64-bit Raspberry Pi (ARM64)** system.

---

## 📌 Key Concepts Covered

- Embedded Linux fundamentals
- History and role of Unix → Linux
- Linux kernel architecture
- User space vs Kernel space
- Out-of-tree kernel module development
- Cross-compilation for ARM64
- Kernel build system (Kbuild)
- Kernel debugging using `dmesg`

---

## 🧱 Project Structure

```
embedded-linux/
├── code/
│   ├── main.c          # Kernel module source code
│   └── Makefile        # Kbuild Makefile for external module
├── .gitignore          # Ignores kernel build artifacts and sources
└── README.md
```

> ⚠️ **Note:**  
> Raspberry Pi Linux kernel source (`rpi_source/`) and build artifacts (`.ko`, `.o`, `.cmd`, etc.) are intentionally **not included** in this repository.

---

## ⚙️ Prerequisites

### Host System
- Ubuntu Linux (x86_64)
- Cross compiler:
  ```bash
  sudo apt install gcc-aarch64-linux-gnu
  ```

### Target System
- Raspberry Pi (64-bit OS)
- Matching kernel version

### Kernel Source
Raspberry Pi Linux kernel source is required separately:

```bash
git clone --depth=1 https://github.com/raspberrypi/linux.git
```

---

## 🔧 Kernel Preparation (Host Side)

From the kernel source directory:

```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcm2711_defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- modules
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- modules_prepare
```

This generates:
- Kernel headers
- Module.symvers
- Required symbol information for external modules

---

## 🏗️ Building the Kernel Module

From the `code/` directory:

```bash
make
```

Successful build will generate: `main.ko`

---

## 🚀 Running the Module on Raspberry Pi

Copy the module to Raspberry Pi:

```bash
scp main.ko pi@<PI_IP>:/home/pi/
```

On the Raspberry Pi:

```bash
sudo insmod main.ko
sudo dmesg | tail
```

To remove the module:

```bash
sudo rmmod main
sudo dmesg | tail
```

---

## 🧠 Learning Outcome

This project helped me understand:

- How the Linux kernel mediates hardware access
- Why kernel modules require strict version and symbol matching
- The importance of Module.symvers and kernel configuration
- Real-world debugging at the kernel level

It provided hands-on exposure to low-level systems programming and strengthened my interest in Embedded Linux and driver development.

---

## 📚 Future Improvements

- GPIO LED driver
- Character device driver (`/dev`)
- Interrupt handling
- Device Tree integration

---

## 👤 Author

**Ragul Kumar A**  
Embedded Systems & Linux Enthusiast
