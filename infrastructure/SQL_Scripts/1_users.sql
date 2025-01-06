CREATE TABLE IF NOT EXISTS users
(
    id
    SERIAL
    PRIMARY
    KEY,
    username
    VARCHAR
(
    50
) UNIQUE NOT NULL,
    passwordSalt VARCHAR
(
    150
) NOT NULL,
    passwordHash VARCHAR
(
    150
) NOT NULL
    );