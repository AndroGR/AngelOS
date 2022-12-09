# AngelOS
AngelOS is just an operating system I write to learn low-level programming. It does nothing more than print some text currently. The OS is written in a combination of C and x86 Assembly, and aims to be a project of (personal) research.

# Building
AngelOS uses `make` to build its kernel. You are gonna need to install the `i686-elf-*` toolchain to build, as AngelOS only supports 32-bit CPUs.
To build and run on `qemu`, a convenience target is available:
```sh
$ make qemu
```
Running this will build the kernel and launch it inside QEMU. Otherwise, you can simply invoke `make` with no arguments to build a kernel binary, which you can then use as you wish.

# TODOs:
- [x] Basic bootup
- [ ] Printing CPU information at boot
- [ ] Basic application and userspace support
- [ ] Error handling for incompatible hardware
- [ ] libc (It will be written in Rust, yes)

# License
AngelOS is licensed under the GNU GPLv3 license, apart from some planned libraries which are going to be released seperately 