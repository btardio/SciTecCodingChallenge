# sudo docker build ./ -t scitec
# sudo docker run -p 127.0.0.1:8080:8080 -p 127.0.0.1:8983:8983 -p 127.0.0.1:8161:8161 --ulimit nofile=90000:90000 -it scitec /bin/sh

FROM fedora:31

EXPOSE 8983 8983
EXPOSE 8161 8161
EXPOSE 8080 8080

COPY ./apache-activemq-5.15.11 /apache-activemq-5.15.11
COPY ./solr-8.4.1 /solr-8.4.1
COPY ./apache-tomcat-9.0.31 /apache-tomcat-9.0.31
COPY ./spring /spring
COPY ./start.sh /start.sh
COPY ./startsolr.sh /startsolr.sh
COPY ./startactivemq.sh /startactivemq.sh
COPY ./starttomcat.sh /starttomcat.sh
COPY ./startLLAtoECEF.sh /startLLAtoECEF.sh
COPY ./SciTec_code_problem_data.csv /SciTec_code_problem_data.csv
COPY ./convert_csv_to_xml.py /convert_csv_to_xml.py

RUN dnf update -y
RUN dnf upgrade -y
RUN dnf install -y java-1.8.0-openjdk
RUN dnf install -y python3

RUN dnf install -y perl
RUN dnf install -y make
RUN dnf groupinstall -y "C Development Tools and Libraries"
RUN dnf groupinstall -y "Development Tools"

RUN dnf install -y curlpp
RUN dnf install -y curlpp-devel

RUN dnf install -y lsof
RUN dnf install procps -y

RUN dnf install -y cmake

RUN dnf install -y jsoncpp
RUN dnf install -y jsoncpp-devel

RUN dnf install -y python3-pip

RUN pip3 install pyproj

RUN python3 /convert_csv_to_xml.py > dataset.xml

COPY ./LLAtoECEF /LLAtoECEF
RUN rm /LLAtoECEF/CMakeCache.txt

ENTRYPOINT ["/start.sh"]

###
### Architecture
###
###   solr
###     contains points and times (xcel document)
###   sci-tec program
###     needs : gcc+ development tools has build tools for compiling
###     receives from queue
###     sends to queue
###   activemq
###     message passing
###   spring
###     rest requests
###     receives from queue
###     sends to queue
###   
###   
###
