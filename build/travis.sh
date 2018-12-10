#!/usr/bin/env bash

export PS4="☢"

set -ex

OUT_DIR=out

meson --debug $OUT_DIR
ninja -C $OUT_DIR
$OUT_DIR/tests/unit_tests --test-launcher-bot-mode
