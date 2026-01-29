FROM elasticsearch:8.8.0

USER root

RUN apt-get update && \
    apt-get install -y curl unzip && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /usr/share/elasticsearch/config/certs && \
    mkdir -p /usr/share/elasticsearch/data && \
    mkdir -p /usr/share/elasticsearch/logs

COPY config/elasticsearch.yml /usr/share/elasticsearch/config/elasticsearch.yml
COPY config/jvm.options /usr/share/elasticsearch/config/jvm.options

RUN /usr/share/elasticsearch/bin/elasticsearch-certutil ca --silent --pem -out /tmp/certs.zip && \
    unzip /tmp/certs.zip -d /usr/share/elasticsearch/config/certs && \
    rm /tmp/certs.zip

RUN chown -R elasticsearch:elasticsearch /usr/share/elasticsearch && \
    chmod -R 755 /usr/share/elasticsearch/config

USER elasticsearch

EXPOSE 9200 9300

CMD ["/usr/share/elasticsearch/bin/elasticsearch"]