#! /usr/bin/bash
kill -s SIGINT $(pgrep -f "^node build/app$") && echo "juice-shop server stopped"
