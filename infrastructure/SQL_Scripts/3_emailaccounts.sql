CREATE TABLE IF NOT EXISTS emailaddresses (
    id SERIAL references users(id),
    username VARCHAR(50) NOT NULL,
    password varchar(50) NOT NULL,
    emailAddress varchar(50) NOT NULL,
    mailProvider varchar(50) NOT NULL,
    constraint pk_bankaccount PRIMARY KEY (username,password,emailAddress,mailProvider)
);