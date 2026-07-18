#!/bin/bash

echo "Task 1"
awk -F',' '{print $1, $2}' employees.txt

echo

echo "Task 2"
awk -F',' '$2=="Engineering" {print}' employees.txt

echo

echo "Task 3"
awk -F',' '{print $1 " gross pay: $" $3*$4}' employees.txt

echo

echo "Task 4"
awk -F',' '{print NR " (" NF " fields): " $0}' employees.txt

echo

echo "Task 5"
awk -F',' 'BEGIN{total=0} $2=="Engineering"{total+=$3*$4} END{print "Total Engineering Payroll: $" total}' employees.txt
