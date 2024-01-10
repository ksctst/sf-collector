#!/bin/bash
set -e

DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
DRIVER_NAME=falco /usr/bin/falco-driver-loader && $DIR/callback k
