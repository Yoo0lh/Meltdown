#!/bin/bash

# this script only search on /proc/kasllsyms

find_banner_on_proc_kallsyms (){
  sudo  cat /proc/kallsyms | grep linux_proc_banner | awk '{print $1}' 
}

find_banner_on_proc_kallsyms 
