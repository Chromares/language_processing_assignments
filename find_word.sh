#!/bin/bash

input="$1"
word="$2"
grep -nr "$word" "$input" 

