# DArgs - Dumb Argument Parser for C++
DArgs is a minimal, simple argument parser for C++ (Less than 100 lines of C++).
DArgs reads the given arguments on the fly, rather than building a parse tree.
This enables user of DArgs to define argument parsing with minimal lines of code.

## Example
```
da::DArgs dargs(argc, argv);
std::string dataset = dargs("--dataset", "Path to the dataset to load", std::string("dataset/default.txt"));
int n_iters         = dargs("--n_iters", "Number of iterations", 200);
double alpha        = dargs("--beta", "beta value", 0.0001f);

if (!dargs.check()) {
    dargs.print_help();
    exit(EXIT_FAILURE);
}
```
