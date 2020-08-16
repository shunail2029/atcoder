#!/bin/bash

g++ -g -Wall -std=c++17 -fsanitize=undefined,address $1 -lm