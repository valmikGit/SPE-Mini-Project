# Scientific Calculator (C++)

Terminal-based scientific calculator supporting:
- Square root: √x
- Factorial: !x  (on non-negative integers)
- Natural logarithm: ln(x)
- Power: x^b

This repo includes:
- C++ source (no external libs)
- Simple C++ test runner
- Makefile for build/test
- Dockerfile to containerize
- Jenkinsfile for CI
- Ansible playbook to deploy the docker image locally

## Requirements (development)
- WSL2 (Ubuntu recommended)
- g++ (>=9)
- make
- docker (and docker daemon)
- ansible (for deployment step)
- Jenkins (for CI)

## Quick local run (WSL)
```bash
# Build
make

# Run the calculator
./bin/calculator

# Run tests
make test