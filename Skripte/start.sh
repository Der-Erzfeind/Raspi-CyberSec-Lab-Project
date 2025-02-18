#!/bin/bash

progdir="$(dirname "$0")/../Program"

$progdir/encoder.out | $progdir/main.out

