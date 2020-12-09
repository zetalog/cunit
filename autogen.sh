#!/bin/sh

echo -n 'running aclocal.......'
if ! aclocal
then
    echo 'error in aclocal!'
    exit -1
fi
echo 'done'

echo -n 'running autoheader....'
if ! autoheader
then
    echo 'error in autoheader!'
    exit -1
fi
echo 'done'

echo -n 'running autoconf......'
if ! autoconf
then
    echo 'error in autoconf!'
    exit -1
fi
echo 'done'

echo -n 'running automake......'
if ! automake --add-missing
then
    echo 'error in automake!'
    exit -1
fi
echo 'done'

echo 'running configure.....'
if ! ./configure
then
    echo 'error in configure!'
    exit -1
fi
echo 'done'
