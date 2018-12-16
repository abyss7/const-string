#!/bin/bash

gn gen --check --export-compile-commands --args="$@" //out
