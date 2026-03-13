#!/usr/bin/env bash
set -euo pipefail

cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
