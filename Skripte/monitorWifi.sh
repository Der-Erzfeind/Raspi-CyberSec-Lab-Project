#!/usr/bin/bash

iw event -T | sed '/phy/d' &
