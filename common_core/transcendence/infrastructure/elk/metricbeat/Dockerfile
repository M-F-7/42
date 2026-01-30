FROM docker.elastic.co/beats/metricbeat:8.13.0

COPY  --chown=metricbeat:metricbeat ./metricbeat.yml /usr/share/metricbeat/metricbeat.yml

USER metricbeat

RUN chmod og-r-w-x /usr/share/metricbeat/metricbeat.yml
