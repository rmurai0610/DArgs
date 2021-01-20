# DArgs - Dumb Argument Parser for C++
DArgs is a minimal, simple argument parser for C++.
DArgs parses the arguments as the options are defined, enabling the user to use DArgs with minimal lines of code.
## Example
```
DArgs::DArgs dargs(argc, argv);
std::string dataset = dargs("--dataset", "Path to the dataset to load", std::string("dataset/default.txt"));
int n_iters         = dargs("--n_iters", "Number of iterations", 200);
double alpha        = dargs("--alpha", "alpha value", 0.0001f);

if (!dargs.check()) {
    dargs.print_help();
    exit(EXIT_FAILURE);
}
```
