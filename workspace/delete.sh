#!/bin/bash

if [ $# != 1 ]; then
    echo "no project name provided"
fi

name=$1

echo "got project name: $name"

bpf_src="${name}.bpf.c"
c_src="${name}.c"
h_src="${name}.h"

echo "delete $bpf_src"
rm $bpf_src
echo "delete $c_src"
rm $c_src
echo "delete $h_src"
rm $h_src

echo "done."