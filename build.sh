#!/usr/bin/env sh
export strace=''
[ "x$*" != "x" ] && export strace='strace'

fasm main.asm main && \
    $strace ./main || exit 1
export errcode=$?
[ "x$errcode" != "x0" ] && \
    echo "[E]: $errcode"
