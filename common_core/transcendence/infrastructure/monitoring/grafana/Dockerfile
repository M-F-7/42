FROM grafana/grafana:10.1.0

USER root

RUN mkdir -p /etc/grafana/provisioning/dashboards && \
    mkdir -p /etc/grafana/provisioning/datasources && \
    mkdir -p /var/lib/grafana/dashboards

COPY config/grafana.ini /etc/grafana/grafana.ini
COPY config/datasources/ /etc/grafana/provisioning/datasources/
COPY config/dashboards/dashboard.yml /etc/grafana/provisioning/dashboards/
COPY config/dashboards/*.json /var/lib/grafana/dashboards/


USER grafana

EXPOSE 3000

CMD ["/run.sh"]
