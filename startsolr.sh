#!/bin/bash

/solr-8.4.1/bin/solr start -e cloud -noprompt -force

curl -X POST -H 'Content-type:application/json' --data-binary '{"add-field": {"name":"xyzECEF", "type":"3dpoint", "indexed":true, "multiValued":false, "stored":true}}' http://localhost:8983/solr/gettingstarted/schema

curl -X POST -H 'Content-type:application/json' --data-binary '{"add-field": {"name":"xyzLLA", "type":"3dpoint", "indexed":true, "multiValued":false, "stored":true}}' http://localhost:8983/solr/gettingstarted/schema

curl -X POST -H 'Content-type:application/json' --data-binary '{"add-field": {"name":"time", "type":"pint", "docValues":true, "indexed":true, "multiValued":false, "stored":true}}' http://localhost:8983/solr/gettingstarted/schema

curl -X POST -H 'Content-type:application/json' --data-binary '{"add-field": {"name":"velocity", "type":"pdouble", "indexed":true, "multiValued":false, "stored":true}}' http://localhost:8983/solr/gettingstarted/schema

/solr-8.4.1/bin/post -c gettingstarted ./dataset.xml

# curl -X POST -H 'Content-type:application/json' --data-binary '{"add-field": {"name":"xy", "type":"location", "indexed":true, "multiValued":false, "stored":true}}' http://localhost:8983/solr/_default/managed-schema
