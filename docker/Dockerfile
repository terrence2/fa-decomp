# FA decompilation build environment: real VC++ 4.2 command-line tools under Wine.
#
# Build context must be the project root (Makefile sets it), so this Dockerfile
# can COPY /vendor/MSVC420 and /docker into the image.
FROM debian:trixie-slim

ENV DEBIAN_FRONTEND=noninteractive

# i386 architecture + Wine for the 32-bit MSVC binaries, xvfb so wineboot /
# any GUI-touching tool has a display to fail silently against, libfaketime to
# freeze the link timestamp, python3 for the stub generation and diff tooling.
RUN dpkg --add-architecture i386 \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
        wine \
        wine32 \
        libfaketime \
        libfaketime:i386 \
        xvfb \
        libfaketime \
        python3 \
        make \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Portable VC++ 4.2 command-line tools (itsmattkc/MSVC420, git-pinned).
COPY vendor/MSVC420 /opt/msvc420

COPY docker /opt/fa-docker

WORKDIR /work

# X-agnostic, quiet wine.
ENV WINEPREFIX=/work/.wine \
    WINEDEBUG=-all \
    WINEDLLOVERRIDES=mscoree,mshtml= \
    PATH=/opt/msvc420/bin:/usr/bin:/bin

ENV INCLUDE='Z:\opt\msvc420\include' \
    LIB='Z:\opt\msvc420\lib' \
    TMP='Z:\tmp'

ENTRYPOINT ["/opt/fa-docker/entrypoint.sh"]