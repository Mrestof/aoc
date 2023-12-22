#!/bin/env bash

set -e
rustc main.rs
./main
rm main
