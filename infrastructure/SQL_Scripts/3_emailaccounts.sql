CREATE TABLE IF NOT EXISTS emailaccounts
(
    id           SERIAL references users (id),
    username     VARCHAR(50) NOT NULL,
    password     varchar(50) NOT NULL,
    emailAddress varchar(50) NOT NULL,
    mailProvider varchar(50) NOT NULL,
    constraint pk_emailaccounts PRIMARY KEY (id, username, password, emailAddress, mailProvider)
);