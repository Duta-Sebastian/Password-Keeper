CREATE TABLE IF NOT EXISTS bankaccounts (
    id SERIAL references users(id),
    username VARCHAR(50) NOT NULL,
    password varchar(50) NOT NULL,
    IBAN varchar(50) NOT NULL,
    bank varchar(50) NOT NULL,
    constraint pk_bankaccount PRIMARY KEY (username,password,IBAN,bank)
);