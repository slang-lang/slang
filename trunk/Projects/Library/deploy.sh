#!/bin/bash

if [ $1 != "" ]; then
	odepend create $1
fi

scp *.json ticketsharing:/home/ubuntu/projects/objectivescript/repo/stable/modules/
rm *.json

scp *.tar.gz ticketsharing:/home/ubuntu/projects/objectivescript/repo/stable/modules/
rm *.tar.gz

