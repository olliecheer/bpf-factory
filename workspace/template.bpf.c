#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "template.h"


char LICENSE[] SEC("license") = "Dual BSD/GPL";


// definitions

// maps

// functions