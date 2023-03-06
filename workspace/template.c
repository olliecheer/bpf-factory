#include <argp.h> // argument parser
#include <bpf/libbpf.h> // libbpf
#include <signal.h> // signal handling
#include <stdio.h> // stdio
#include <string.h> // string

#include "template.h" // shared definitions
#include "template.skel.h" // generated skeleton
#include "vmlinux.h" // kernel type definitions


// argument parser

const char argp_program_doc[] = 
"Usage: ./template [-b <external BTF>] [-v]\n";

static struct config {
    char *btf_path;
    bool verbose;
} config = {
    .btf_path = NULL,
    .verbose = false,
};

static const struct argp_option opts[] = {
    {"btf", 'b', NULL, 0, "Specify external BTF"},
    {"verbose", 'v', NULL, 0, "Verbose debug output"},
    {},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state) {
    switch (key) {
        case 'b': {
            config.btf_path = strdup(arg);
            break;
        }
        case 'v': {
            config.verbose = true;
            break;
        }
        case ARGP_KEY_ARG: {
            argp_usage(state);
            break;
        }
        default: {
            return ARGP_ERR_UNKNOWN;
        }
    }
    return 0;
}

static const struct argp argp = {
    .options = opts,
    .parser = parse_arg,
    .doc = argp_program_doc,
};


// callback functions and handlers

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) {
    if (level == LIBBPF_DEBUG && !config.verbose)
        return 0;
    return vfprintf(stderr, format, args);
}

static volatile bool exiting = false;

static void sig_handler(int sig) {
    exiting = true;
}

static int handle_event(void *ctx, void *data, size_t data_sz) {
    return 0;
}

// other declarations or definitions


int main() {
    // libbpf configuration
    libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
    libbpf_set_print(libbpf_print_fn);

    // signal handler registeration
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    int err;
    struct template_bpf *skel;

    skel = template_bpf__open();
    if (!skel) {
		fprintf(stderr, "Failed to open and load BPF skeleton\n");
		return 1;
	}

    err = template_bpf__load(skel);
	if (err) {
		fprintf(stderr, "Failed to load and verify BPF skeleton\n");
		goto cleanup;
	}

    err = template_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

    // other works


cleanup:
    template_bpf__destroy(skel);

    return err != 0;
}