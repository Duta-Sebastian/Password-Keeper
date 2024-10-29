CREATE TABLE IF NOT EXISTS users
(
    id
    SERIAL
    PRIMARY
    KEY,
    username
    varchar
(
    50
) NOT NULL,
    passwordSalt varchar
(
    150
) NOT NULL,
    passwordHash varchar
(
    150
) NOT NULL
    )