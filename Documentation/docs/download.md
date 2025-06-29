Download ITK
============

💾 Current release
------------------

More information on this release can be found in the [release notes](releases/5.4.0.md).

### Python packages

To install the [ITK Python packages],

```bash
pip install itk
```

Additionally, wheels for external modules are available through the Python Package Index ([PyPI]).

### Release artifacts

**Guide and Textbook**

- [InsightSoftwareGuide-Book1-5.4.4.pdf](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightSoftwareGuide-Book1-5.4.4.pdf)
- [InsightSoftwareGuide-Book2-5.4.4.pdf](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightSoftwareGuide-Book2-5.4.4.pdf)

**Library Sources**

- [InsightToolkit-5.4.4.tar.gz](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightToolkit-5.4.4.tar.gz)
- [InsightToolkit-5.4.4.zip](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightToolkit-5.4.4.zip)

**Testing Data**

Unpack optional testing data in the same directory where the Library Source is unpacked.

- [InsightData-5.4.4.tar.gz](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightData-5.4.4.tar.gz)
- [InsightData-5.4.4.zip](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightData-5.4.4.zip)

**Checksums and Signatures**

- [InsightToolkit-5.4.4.tar.gz.asc](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightToolkit-5.4.4.tar.gz.asc)
- [InsightToolkit-5.4.4.zip.asc](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightToolkit-5.4.4.zip.asc)

- [InsightData-5.4.4.tar.gz.asc](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightData-5.4.4.tar.gz.asc)
- [InsightData-5.4.4.zip.asc](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/InsightData-5.4.4.zip.asc)

- [MD5SUMS](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/MD5SUMS)
- [SHA512SUMS](https://github.com/InsightSoftwareConsortium/ITK/releases/download/v5.4.4/SHA512SUMS)

Additional releases can be downloaded from [ITK's GitHub Releases page].

📦 Package managers
-------------------

ITK packages exist for many Linux distributions. For Debian and Ubuntu, they
can be obtained running

```bash
sudo apt-get install libinsighttoolkit5-dev
```

This will give you the libraries and development headers.

In GNU Guix, install ITK with:

```bash
guix install insight-toolkit
```

For information on other ITK packages and packages for other distributions, see
this [blog post].

ITK is available in [vcpkg] as `itk`:

```bash
vcpkg install itk
```

If you're a [Homebrew](https://brew.sh/) user, you can install [itk](https://formulae.brew.sh/formula/itk) via:

```bash
brew install itk
```

🚀 Latest sources with Git
--------------------------

First, [download and install Git](https://git-scm.com/downloads).

Note that the software must be compiled from source using [CMake] and your
favorite C++ compiler. The toolkit can be installed, but it is not necessary;
it can be used directly from its build directory. See the [ITK Software Guide]
for further information on configuring and building ITK.

### Clone

Clone ITK using the commands

```bash
git clone https://github.com/InsightSoftwareConsortium/ITK
cd ITK
```

The latest stable release can be cloned into a local repository using

```bash
git clone -b release https://github.com/InsightSoftwareConsortium/ITK ITKLatestRelease
```
where `ITKLatestRelease` is the name of the local repository created.

Additionally, specific releases can be cloned using the tags, for example:

```bash
git clone -b v5.4.4 https://github.com/InsightSoftwareConsortium/ITK ITK-5.4.4
```
where `v5.4.4` corresponds to ITK 5.4.4, and the `ITK-5.4.4` is the name
of the local repository created.

### Update

Users that have made no local changes and simply want to update a clone with
the latest changes may run

```bash
git checkout main
git pull --rebase upstream main
```

Avoid making local changes unless you have read our [developer
instructions](contributing/index.md).

### Checkout

After cloning, your local repository will be configured to follow the upstream
`main` branch by default. This means you will have access to cutting edge
features, but along with these may come cutting edge bugs :grimacing:. One may
create a local branch to track the upstream `release` branch instead, which
should guarantee only bug fixes to the functionality available in the latest
release:

```bash
git checkout --track -b release origin/release
```

This local branch will always follow the latest `release`. Use the [#update]
instructions to update it.

Alternatively, one may checkout a specific release tag using

```bash
git checkout v5.4.4
```

Release tags never move. Repeat the command with a different tag to get a
different release. One may list available tags using:

```bash
git tag
```

[blog post]: https://blog.kitware.com/itk-packages-in-linux-distributions/
[CMake]: https://cmake.org/
[Git]: https://git-scm.com
[GNU Guix]: https://guix.gnu.org/
[ITK Python packages]: https://itkpythonpackage.readthedocs.io/en/latest/Quick_start_guide.html
[ITK's GitHub Releases page]: https://github.com/InsightSoftwareConsortium/ITK/releases
[ITKPythonPackage]: https://itkpythonpackage.readthedocs.io/en/latest/index.html
[ITK Software Guide]: https://github.com/InsightSoftwareConsortium/ITKSoftwareGuide/releases
[PyPI]: https://pypi.org/search/?q=itk
[vcpkg]: https://github.com/microsoft/vcpkg
