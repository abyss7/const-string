#!/usr/bin/env bash

export PS4="☢"

set -ex

OUT=out

meson $OUT
ninja -C $OUT
$OUT/tests/unit_tests --test-launcher-bot-mode
