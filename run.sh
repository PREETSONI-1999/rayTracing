#!/bin/bash
# if [ -z "$1" ]; then
# echo "Usage: ./run_my_program.sh <program_binary>"
# exit 1
# fi

if [ ! -d "bin" ]; then
echo "Error: 'bin' directory not found. Build the project first using 'make'."
exit 1
fi

if [ ! -f "bin/my_program" ]; then
echo "Error: 'my_program' not found in 'bin' directory. Build the project first using 'make'."
exit 1
fi

./bin/my_program