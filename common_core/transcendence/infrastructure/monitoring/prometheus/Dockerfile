FROM prom/prometheus:v2.47.0

USER root

RUN mkdir -p /etc/prometheus/rules /prometheus

COPY config/prometheus.yml /etc/prometheus/prometheus.yml
COPY config/rules/*.yml /etc/prometheus/rules/

EXPOSE 9090

ENTRYPOINT ["/bin/prometheus"]
CMD ["--config.file=/etc/prometheus/prometheus.yml", \
     "--storage.tsdb.path=/prometheus", \
     "--web.console.libraries=/usr/share/prometheus/console_libraries", \
     "--web.console.templates=/usr/share/prometheus/consoles", \
     "--storage.tsdb.retention.time=15d", \
     "--web.enable-lifecycle"]
