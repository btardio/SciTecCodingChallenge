#!/bin/bash

export JAVA_HOME=$(readlink -f /usr/bin/java | sed "s:bin/java::")

./startsolr.sh
./startactivemq.sh
./starttomcat.sh
./startLLAtoECEF.sh

/bin/bash
