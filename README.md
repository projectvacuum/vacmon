# vacmon
State monitoring service for Vac and Vcycle. This version supports 5.2.0 (and may work with 6.x)

Create ElasticSearch indexes with:

curl -T mappings_machinetypes.json "localhost:9200/machinetypes" -H 'Content-Type: application/json' 
curl -T mappings_machines.json "localhost:9200/machines" -H 'Content-Type: application/json' 
curl -T mappings_factories.json "localhost:9200/factories" -H 'Content-Type: application/json' 

Indexes without the correct mappings may be created by ElasticSearch if vacmond is running, receiving
messages, and writing them to ElasticSearch. If necessary, these indexes can be removed
by stopping vacmond and then using:

curl -X DELETE "localhost:9200/machines"  
curl -X DELETE "localhost:9200/factories"  
curl -X DELETE "localhost:9200/factories"  

Then apply the above curl -T commands to recreate the indexes, and then restart vacmond
