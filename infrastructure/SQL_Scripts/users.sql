CREATE TABLE IF NOT EXISTS users(
    id SERIAL PRIMARY KEY,
    username varchar(50) NOT NULL,
    passwordSalt varchar(32) NOT NULL,
    passwordHash varchar(100) NOT NULL,
)