CREATE TABLE IF NOT EXISTS socialmediaaccounts
(
    id         SERIAL references users (id),
    username   VARCHAR(50) NOT NULL,
    password   varchar(50) NOT NULL,
    platform   varchar(50) NOT NULL,
    profileUrl varchar(50) NOT NULL,
    constraint pk_socialmediaaccounts PRIMARY KEY (id, username, password, platform, profileUrl)
);