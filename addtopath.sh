#!/bin/bash

if grep -q "export PATH=\$PATH:$(pwd)" ~/.bashrc; then
  echo "Already added to PATH"
else
  echo "export PATH="\$PATH:$(pwd)"" >> ~/.bashrc
  export PATH=$PATH:$(pwd)
  echo "Successfully added to PATH"
fi

source ~/.bashrc
