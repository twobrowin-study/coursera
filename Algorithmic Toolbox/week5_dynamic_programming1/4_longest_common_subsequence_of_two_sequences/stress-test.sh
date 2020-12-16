#!/bin/bash

out=$(python lcs2_stress.py)

echo $out | python lcs2_naive.py
echo $out | ./a.out
