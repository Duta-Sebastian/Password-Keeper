FROM postgres:latest

ENV POSTGRES_DB=password_keeper
ENV POSTGRES_USER=user
ENV POSTGRES_PASSWORD=temp

COPY SQL_Scripts/users.sql /docker-entrypoint-initdb.d/