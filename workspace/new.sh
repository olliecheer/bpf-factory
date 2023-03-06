#!/bin/bash

if [ $# != 1 ]; then
    echo "no project name provided"
fi

name=$1

echo "got project name: $name"
echo "generating from template..."

tpl_bpf_src="template.bpf.c"
tpl_c_src="template.c"
tpl_h_src="template.h"

bpf_src="${name}.bpf.c"
c_src="${name}.c"
h_src="${name}.h"

prefix="sed -e 's/template/${name}/g'"

echo $prefix
eval "$prefix $tpl_bpf_src > $bpf_src"
eval "$prefix $tpl_c_src > $c_src"
eval "$prefix $tpl_h_src > $h_src"

echo "done."
echo "please append your project name to APPS in Makefile by hand"