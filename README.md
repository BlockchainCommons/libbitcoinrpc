# Libbitcoinrpc Updated

### _original by [Marek Miller](https://github.com/gitmarek)

**libbitcoinrpc** is a C library for JSON-RPC Bitcoin API. The library provides basic routines to send RPC queries to a listening
Bitcoin node, fetch responses and analyse errors.
The original code was tested against Bitcoin Core
v0.10.4, v0.11.2, v0.12.0. This version has started to introduce fixes for more recent versions.

_This is a branch of https://github.com/gitmarek/libbitcoinrpc/. It has been branched because the original has badly fallen out of date, requiring updates._

## Installation Instructions

Please make sure that you have all the required dependencies installed.
Then type in the project folder:

    make

to compile a dynamically linked library and put it in `.lib/`.

If you want to clean the directory of compiled files and start from scratch,
use:

    make clean  

You can also build and perform unit testing with bitcoind daemon in regtest
mode:

    make test

This assumes that you have `bitcoind` and `bitcoin-cli` executables
installed on your system.


### Build dependencies

These dependencies are required:

 Library     | Purpose             | Description
 ------------|---------------------|-----------------------------------------
  curl       | send data over HTTP | tested with >=libcurl-7.14.0
  jansson    | JSON parsing        | tested with >=libjansson-2.2.1
  uuid       | generate UUIDs      | tested with >=libuuid-2.20.1

To install the build dependencies on Ubuntu, please type the following
command:

    sudo apt-get install libcurl4-openssl-dev libjansson-dev uuid-dev

(or other libcurl4-\*-dev flavour).


### Final Installation

To install the successfully compiled source on Unix type systems, please type:

    make install

as a privileged user  (on Debian-like systems: `sudo make install`).
By default, it will install the library in `/usr/local/lib` and the header
file in `/usr/local/include`.  It will also install documentation files in
`/usr/share/doc/bitcoinrpc`, as well as man pages that all start with:
'bitcoinrpc'.  You can specify the variable `INSTALL_PREFIX` to install sources
to some other destination (e.g. chrooted file system).

On some systems, especially Ubuntu, the directory `/usr/local/lib` is not
included by default to the `ldconfig` search path.  So either you change
the `Makefile`'s `INSTALL_LIBPATH` value from `/usr/local/lib` to `/usr/lib`
(which may be not a very good idea, since most of the libraries installed by
`apt-get` are there), or add the following line to your `/etc/ld.so.conf`:

    /usr/local/lib

and run:

    sudo ldconfig

See `man 8 ldconfig` for more information.

To remove the files, type:

    make uninstall


## Usage Instructions

To use the library, it is enough to include the header file:

    #include <bitcoinrpc.h>

in your source code and provide the following linker flag during compilation:

    -lbitcoinrpc

For further information, see documentation in [doc/](./doc/README.md)
and the header file: [`src/bitcoinrpc.h`](./src/bitcoinrpc.h).

*Please notice that the code is in the very early stage of development.*

## Version History

See [Changelog.md](./Changelog.md) and [CREDITS](./CREDITS).

## Origin, Authors, Copyright & Licenses

The source code is released under the terms of the MIT license.  Please, see
[LICENSE](./LICENSE) for more information.


### Derived from ...

This  `$projectname` project is either derived from or was inspired by:

- [libbitcoinrpc](https://github.com/gitmarek/libbitcoinrpc/) — Original source of code in this repo.

## Contributing

We encourage public contributions through issues and pull requests! Please review [CONTRIBUTING.md](./CONTRIBUTING.md) for details on our development process. All contributions to this repository require a GPG signed [Contributor License Agreement](./CLA.md).

### Discussions

The best place to talk about Blockchain Commons and its projects is in our GitHub Discussions areas.

[**Gordian System Discussions**](https://github.com/BlockchainCommons/Gordian/discussions). For users and developers of the Gordian system, including the Gordian Server, Bitcoin Standup technology, QuickConnect, and the Gordian Wallet. If you want to talk about our linked full-node and wallet technology, suggest new additions to our Bitcoin Standup standards, or discuss the implementation our standalone wallet, the Discussions area of the [main Gordian repo](https://github.com/BlockchainCommons/Gordian) is the place.

[**Wallet Standard Discussions**](https://github.com/BlockchainCommons/AirgappedSigning/discussions). For standards and open-source developers who want to talk about wallet standards, please use the Discussions area of the [Airgapped Signing repo](https://github.com/BlockchainCommons/AirgappedSigning). This is where you can talk about projects like our [LetheKit](https://github.com/BlockchainCommons/bc-lethekit) and command line tools such as [seedtool](https://github.com/BlockchainCommons/bc-seedtool-cli), both of which are intended to testbed wallet technologies, plus the libraries that we've built to support your own deployment of wallet technology such as [bc-bip39](https://github.com/BlockchainCommons/bc-bip39), [bc-slip39](https://github.com/BlockchainCommons/bc-slip39), [bc-shamir](https://github.com/BlockchainCommons/bc-shamir), [Sharded Secret Key Reconstruction](https://github.com/BlockchainCommons/bc-sskr), [bc-ur](https://github.com/BlockchainCommons/bc-ur), and the [bc-crypto-base](https://github.com/BlockchainCommons/bc-crypto-base). If it's a wallet-focused technology or a more general discussion of wallet standards,discuss it here.

[**Blockchain Commons Discussions**](https://github.com/BlockchainCommons/Community/discussions). For developers, interns, and patrons of Blockchain Commons, please use the discussions area of the [Community repo](https://github.com/BlockchainCommons/Community) to talk about general Blockchain Commons issues, the intern program, or topics other than the [Gordian System](https://github.com/BlockchainCommons/Gordian/discussions) or the [wallet standards](https://github.com/BlockchainCommons/AirgappedSigning/discussions), each of which have their own discussion areas.

### Other Questions & Problems

As an open-source, open-development community, Blockchain Commons does not have the resources to provide direct support of our projects. Please consider the discussions area as a locale where you might get answers to questions. Alternatively, please use this repository's [issues](./issues) feature. Unfortunately, we can not make any promises on response time.

If your company requires support to use our projects, please feel free to contact us directly about options. We may be able to offer you a contract for support from one of our contributors, or we might be able to point you to another entity who can offer the contractual support that you need.

### Credits

The following people directly contributed to this repository. You can add your name here by getting involved. The first step is learning how to contribute from our [CONTRIBUTING.md](./CONTRIBUTING.md) documentation.

| Name              | Role                | Github                                            | Email                                 | GPG Fingerprint                                    |
| ----------------- | ------------------- | ------------------------------------------------- | ------------------------------------- | -------------------------------------------------- |


## Responsible Disclosure

We want to keep all of our software safe for everyone. If you have discovered a security vulnerability, we appreciate your help in disclosing it to us in a responsible manner. We are unfortunately not able to offer bug bounties at this time.

We do ask that you offer us good faith and use best efforts not to leak information or harm any user, their data, or our developer community. Please give us a reasonable amount of time to fix the issue before you publish it. Do not defraud our users or us in the process of discovery. We promise not to bring legal action against researchers who point out a problem provided they do their best to follow the these guidelines.

### Reporting a Vulnerability

Please report suspected security vulnerabilities in private via email to ChristopherA@BlockchainCommons.com (do not use this email for support). Please do NOT create publicly viewable issues for suspected security vulnerabilities.

The following keys may be used to communicate sensitive information to developers:

| Name              | Fingerprint                                        |
| ----------------- | -------------------------------------------------- |
| Christopher Allen | FDFE 14A5 4ECB 30FC 5D22  74EF F8D3 6C91 3574 05ED |

You can import a key by running the following command with that individual’s fingerprint: `gpg --recv-keys "<fingerprint>"` Ensure that you put quotes around fingerprints that contain spaces.
