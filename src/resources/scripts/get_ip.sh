#!/bin/bash

public=$(curl ifconfig.me)
private=$(hostname -I)
echo $public
