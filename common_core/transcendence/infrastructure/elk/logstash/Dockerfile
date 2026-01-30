FROM logstash:8.8.0

USER root

RUN apt-get update && apt-get install -y curl && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /usr/share/logstash/config && \
    mkdir -p /usr/share/logstash/pipeline && \
    chown -R logstash:logstash /usr/share/logstash/config && \
    chown -R logstash:logstash /usr/share/logstash/pipeline

COPY config/logstash.yml /usr/share/logstash/config/logstash.yml
COPY pipeline/logstash.conf /usr/share/logstash/pipeline/logstash.conf

RUN chown logstash:logstash /usr/share/logstash/config/logstash.yml && \
    chown logstash:logstash /usr/share/logstash/pipeline/logstash.conf

USER logstash

EXPOSE 5000

CMD ["/usr/share/logstash/bin/logstash"]