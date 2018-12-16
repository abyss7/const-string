#!/usr/bin/env bash

export PS4="☢ "

set -ex

# gn is extracted into build dir
export PATH=${PATH}:${TRAVIS_BUILD_DIR}

build/configure.sh
ninja -C out
out/unit_tests --test-launcher-bot-mode
