FROM postgres:latest

ENV POSTGRES_DB=password_keeper
ENV POSTGRES_USER=user
ENV POSTGRES_PASSWORD=temp

COPY SQL_Scripts/1_users.sql /docker-entrypoint-initdb.d/
COPY SQL_Scripts/2_bankaccounts.sql /docker-entrypoint-initdb.d/
COPY SQL_Scripts/3_emailaccounts.sql /docker-entrypoint-initdb.d/
COPY SQL_Scripts/4_socialmediaaccounts.sql /docker-entrypoint-initdb.d/