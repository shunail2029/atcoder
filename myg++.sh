#!/bin/bash

g++ -g -Wall -std=c++17 -I ./acl -fsanitize=undefined $1 -lm