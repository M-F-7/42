FROM prom/prometheus:v2.47.0

USER root

RUN mkdir -p /etc/prometheus/alerts /prometheus /etc/prometheus/data 

COPY config/prometheus.yml /etc/prometheus/prometheus.yml
COPY config/alerts.yml /etc/prometheus/alerts/alerts.yml
COPY config/rules.yml /etc/prometheus/rules/rules.yml


EXPOSE 9090

ENTRYPOINT ["/bin/prometheus"]