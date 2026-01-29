FROM grafana/grafana:10.1.0

USER root

RUN mkdir -p /etc/grafana/provisioning/dashboards && \
    mkdir -p /etc/grafana/provisioning/datasources && \
    mkdir -p /var/lib/grafana/dashboards

COPY config/grafana.ini /etc/grafana/grafana.ini
COPY config/dashboards/ /etc/grafana/provisioning/dashboards/

USER grafana

EXPOSE 3000

CMD ["/run.sh"]