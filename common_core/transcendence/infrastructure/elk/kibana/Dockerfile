FROM kibana:8.8.0

USER root

RUN apt-get update && apt-get install -y curl && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /usr/share/kibana/config && \
    chown -R kibana:kibana /usr/share/kibana/config

COPY config/kibana.yml /usr/share/kibana/config/kibana.yml

RUN chown kibana:kibana /usr/share/kibana/config/kibana.yml

USER kibana

EXPOSE 5601

CMD ["/usr/share/kibana/bin/kibana"]